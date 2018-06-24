#include <string>
#include <vector>
#include <syslog.h>
#include "server_GameThread.h"
#include "config.h"
#include <chrono>
#include <iostream>
#include <thread>
#include <utility>
#include <map>

using ms = std::chrono::milliseconds;
using get_time = std::chrono::steady_clock;
using std::move;

void GameThread::load_config(){
  YamlParser yaml_parser;
  map<string, string> config = yaml_parser.load_config(string(CONFIG_FOLDER) +\
                                string(CONFIG_FILE));
  if (config.count("worm_life") == 1) {
    worm_life_points = (size_t)std::stoi(config["worm_life"]);
  } else {
    worm_life_points = INITIAL_LIFE_POINTS;
  }
}

void GameThread::create_stage(string map_file, int number_players){
  YamlParser yaml_parser;
  ScenarioDTO scenario_DTO = yaml_parser.load_scenario(map_file);

  vector<WormDTO> worms_DTO = scenario_DTO.get_worms();
  // Verifico que la cantidad de gusanos sea <= a la cantidad de jugadores
  if (worms_DTO.size() < number_players) {
    throw std::runtime_error(\
                  "Número de jugadores es mayor a la cantidad de gusanos.\n");
  } else if (number_players == 0) {
    throw std::runtime_error("Debe jugar al menos un jugador.\n");
  }

  stage = new Stage((size_t)scenario_DTO.get_width(), \
            (size_t)scenario_DTO.get_height(), scenario_DTO.get_background());
  // Creo los worms y los jugadores.
  int number_players_with_more_worms = (worms_DTO.size() % number_players);
  if (number_players_with_more_worms == 0)
    number_players_with_more_worms = number_players;
  int number_players_with_less_worms = \
    number_players - number_players_with_more_worms;

  // Cantidad de gusanos de los jugadores con MENOS gusanos.
  int number_worms_per_player_with_less_worms = \
                              (int)(worms_DTO.size() / number_players);
  int number_worms_per_player_with_more_worms = \
                              number_worms_per_player_with_less_worms;

  if (number_players_with_less_worms != 0)
    ++number_worms_per_player_with_more_worms;

  size_t worm_index = 0;

  for (int i = 0; i < number_players_with_more_worms; i++){
    Armory* armory = new Armory(*stage);
    Player* player = new Player(armory);
    for (int j = 0; j < number_worms_per_player_with_more_worms; j++){
      stage->add_worm(worms_DTO[worm_index].get_id(),\
                      worm_life_points, \
                      worms_DTO[worm_index].get_x(),\
                      worms_DTO[worm_index].get_y());
      player->add_worm(stage->get_worm(worms_DTO[worm_index].get_id()));
      ++worm_index;
    }
    turns_manager.add_player(player);
  }

  for (int i = 0; i < number_players_with_less_worms; i++){
    Armory* armory = new Armory(*stage);
    Player* player = new Player(armory);
    for (int j = 0; j < number_worms_per_player_with_less_worms; j++){
      stage->add_worm(worms_DTO[worm_index].get_id(),\
                      worm_life_points + 25, \
                      worms_DTO[worm_index].get_x(),\
                      worms_DTO[worm_index].get_y());
      player->add_worm(stage->get_worm(worms_DTO[worm_index].get_id()));
      ++worm_index;
    }
    turns_manager.add_player(player);
  }

  vector<BeamDTO> beams_DTO = scenario_DTO.get_beams();
  for (BeamDTO beam : beams_DTO){
      stage->add_beam(beam.get_id(), beam.get_length(), beam.get_x(), \
                                        beam.get_y(), beam.get_angle());
  }
}


GameThread::GameThread(const char* port, string map_file, int number_players){
  alive = false;
  has_been_connected = false;
  load_config();
  create_stage(map_file, number_players);
  server_thread = new ServerThread(port, turns_manager, *this);
}

void GameThread::start_connection(){
  server_thread->start();
}

void GameThread::run() {
    alive = true;
    has_been_connected = true;
    add_all_clients();
    server_thread->start_clients();
    send_stage_information_to_clients();
    send_munitions_information_to_all_clients();
    deadTime();
    set_worms_as_immovable();
    turns_manager.get_selected_player()->get_selected_worm()->make_movable();
    while (alive) {
      check_winner();
      tick_turn();
      deadTime();
      check_falling();
      changeTurn();
    }
}

bool GameThread::are_all_worms_still(){
  std::vector<Worm*> all_worms_alive = this->stage->get_all_alive_worms();
  for (Worm* worm : all_worms_alive) {
    if (!(worm->get_horizontal_velocity() > -0.1 && \
        worm->get_horizontal_velocity() < 0.1  && \
        worm->get_vertical_velocity() > -0.1 && \
        worm->get_vertical_velocity() < 0.1))
        return false;
  }
  return true;
}

void GameThread::deadTime(){
  Player* actual_player = turns_manager.get_selected_player();
  Worm* actual_worm = actual_player->get_selected_worm();

  // Tiempo minimo entre turnos.
  int time_between_turns = TIME_BETWEEN_TURNS;
  while (time_between_turns > 0) {
    auto start = get_time::now();
    stage->step(actual_worm);
    notif_clients();
    auto end = get_time::now();
    time_between_turns -= TICK_TIME;
    std::this_thread::sleep_for(std::chrono::milliseconds((int) TICK_TIME - \
                (int)std::chrono::duration_cast<ms>(end - start).count()));
  }

  bool all_worms_still = are_all_worms_still();
  while (!all_worms_still) {
    auto start = get_time::now();
    stage->step(actual_worm);
    notif_clients();
    all_worms_still = are_all_worms_still();
    auto end = get_time::now();
    std::this_thread::sleep_for(std::chrono::milliseconds((int) TICK_TIME - \
                (int)std::chrono::duration_cast<ms>(end - start).count()));
  }
}

void GameThread::tick_turn(){
  Player* actual_player = turns_manager.get_selected_player();
  Worm* actual_worm = actual_player->get_selected_worm();
  size_t initial_life = actual_worm->get_life_points();

  bool weapon_was_used = false;

  while (alive && (turn_chrono > 0 || actual_player->has_an_active_weapon())) {
    auto start = get_time::now();
    check_falling();
    check_life_discount(initial_life, actual_worm);
    check_immobilization(actual_worm);
    if (!execute_event()) break;
    stage->step(actual_worm);
    check_weapons(actual_player, weapon_was_used);
    auto end = get_time::now();
    discount_time((int)std::chrono::duration_cast<ms>(end - start).count());
    notif_clients();
  }
  actual_worm->stop_moving();
}

void GameThread::check_life_discount(size_t initial_life, Worm* actual_worm){
  if (initial_life > actual_worm->get_life_points())
    turn_chrono = 0;
}

void GameThread::check_winner(){
  if (turns_manager.get_number_players() == 1) return;
  if (turns_manager.get_number_players_alive() == 1)
    this->server_thread->send_you_win_notif();
}

void GameThread::check_immobilization(Worm* actual_worm){
  // Si ya termina el turno y siguen los ataques dejo de moverlo.
  if (turn_chrono == 0) actual_worm->stop_moving();
}

bool GameThread::execute_event(){
  IEvent* temporal_event = NULL;
  // Si ya termino el turno no ejecuta ninguna acción
  if (turn_chrono > 0 && this->safe_queue.pop(temporal_event)){
    try {
      temporal_event->run();
      delete temporal_event;
    } catch (...){
        std::cout << "Un cliente cerró la conexión\n";
        this->stop();

        delete temporal_event;
        return false;
    }
  }
  return true;
}

void GameThread::check_weapons(Player* actual_player, bool& weapon_was_used){
  // Chequeo las explosiones del teledirigido.
  if (actual_player->is_radiocontrolled_active())
    check_radiocontrolled_explosions();
  // Chequeo la explosión de la dinamita
  if (actual_player->is_dynamite_active())
    check_dynamite_explosion();

  if (!weapon_was_used) {
    // Si nunca se usó el arma, me fijo si se activó.
    if (actual_player->has_an_active_weapon()){
      weapon_was_used = true;
      send_munitions_information();
      return;
    }
  } else {
    // Si alguna vez fue usada un arma, entonces cuando
    // se desactive termina el turno.
    if (!actual_player->has_an_active_weapon())
      turn_chrono = 0;
  }

  if (actual_player->was_teletransportation_used())
    send_munitions_information();
}

void GameThread::discount_time(int time_spent){
  turn_chrono -= TICK_TIME;
  std::this_thread::sleep_for(std::chrono::milliseconds(\
                                                (int) TICK_TIME - time_spent));
  if (turn_chrono < 0) turn_chrono = 0;
}

void GameThread::notif_clients(){
  send_turn_time_information();
  send_worms_information_to_clients();
  send_weapon_information_to_clients();
}

void GameThread::send_turn_time_information(){
  this->server_thread->send_turn_time_information_to_clients((int)turn_chrono);
}

void GameThread::send_worms_information_to_clients(){
  std::vector<Player*> players = turns_manager.get_players();
  Worm* actual_worm = turns_manager.get_selected_player()->get_selected_worm();
  for (int i = 0; i < players.size(); i++){
    std::vector<Worm*> worms = players[i]->get_worms();
    for (Worm* worm : worms) {
      // Solo envío la información de los movibles.
      if (!worm->is_movable() || !worm->is_alive() ||\
                      !worm->has_suffered_changes()) continue;
      size_t id = worm->get_id();
      size_t life_points = worm->get_life_points();
      double x = worm->get_horizontal_position();
      double y = worm->get_vertical_position();
      int angle = (int)worm->get_angle();
      bool is_facing_right = worm->is_facing_right();
      int movement_state;
      if (!worm->is_colliding()){
        movement_state = 3; // Volando
      } else {
        if (worm->is_moving())
          movement_state = 2; // Moviendose
        else
          movement_state = 1; // Quieto
      }
      bool is_the_selected_worm = (actual_worm->get_id() == id);
      this->server_thread->send_worm_information_to_clients(id, life_points,\
        x, y, angle, is_facing_right, i, movement_state, is_the_selected_worm);
    }
  }
}

void GameThread::send_stage_information_to_clients(){
  int width = this->stage->get_width();
  int height = this->stage->get_height();
  std::string background = this->stage->get_background();
  this->server_thread->send_stage_information_to_clients(width, \
                                                          height, background);
  std::vector<Beam*> all_beams = this->stage->get_all_beams();
  for (size_t i = 0; i < all_beams.size(); i++){
    double x = all_beams[i]->get_horizontal_position();
    double y = all_beams[i]->get_vertical_position();
    int length = all_beams[i]->get_length();
    int width = all_beams[i]->get_width();
    int angle = all_beams[i]->get_angle();

    this->server_thread->send_beam_information_to_clients(x, y, length, width,\
                                            angle);
  }
}

void GameThread::send_weapon_information_to_clients(){
  Player* actual_player = turns_manager.get_selected_player();
  if (actual_player->is_dynamite_active()){
    double x = actual_player->get_dynamite_horizontal_position();
    double y = actual_player->get_dynamite_vertical_position();
    double time_to_explosion = actual_player->get_dynamite_time_to_explosion();
    this->server_thread->send_dynamite_information_to_clients(x,\
                                                      y, time_to_explosion);
  }
  if (actual_player->is_radiocontrolled_active()){
    std::map<size_t, std::pair<float, float>> positions = \
                                actual_player->get_radiocontrolled_positions();
    for (size_t i = 0; i < 6; i++){
      if (positions.count(i) == 0) continue;
      double x = positions[i].first;
      double y = positions[i].second;
      this->server_thread->send_radiocontrolled_information_to_clients(i, x, y);
    }
  }
}

void GameThread::send_munitions_information(){
  Player* actual_player = turns_manager.get_selected_player();
  this->server_thread->send_munitions_info(\
                            actual_player->get_dynamite_munitions(), \
                            actual_player->get_radiocontrolled_munitions(), \
                            actual_player->get_teletransportation_munitions());
}

void GameThread::send_munitions_information_to_all_clients(){
  Player* actual_player = turns_manager.get_selected_player();
  this->server_thread->send_munitions_info_to_all_clients();
}


void GameThread::stop(){
    alive = false;
    if (server_thread->is_alive()){
      server_thread->send_closed_connection_notif();
      server_thread->stop();
      server_thread->join();
    }
}

void GameThread::addClient(ClientHandler* client_handler){
  client_handler->add_safe_queue(&(this->safe_queue));
}

void GameThread::add_all_clients(){
  std::vector<ClientHandler*>* clients = \
                                  server_thread->get_all_connected_clients();
  for (size_t i = 0; i < clients->size(); i++){
    addClient((*clients)[i]);
  }
}

void GameThread::set_worms_as_immovable(){
  // Seteo todos los gusanos en no movibles.
  std::vector<Worm*> all_worms_alive = this->stage->get_all_alive_worms();
  for (Worm* worm : all_worms_alive){
    worm->correct_angle();
    send_worms_information_to_clients();
    worm->make_immovable();
  }
}

void GameThread::changeTurn(){
  set_worms_as_immovable();
  if (server_thread->is_alive()) server_thread->changeTurn();
  // Vacío la cola.
  IEvent* temporal_event = NULL;
  while (this->safe_queue.pop(temporal_event)) {
    delete temporal_event;
  }
  turn_chrono = TURN_LENGTH;
  Worm* actual_worm = turns_manager.get_selected_player()->get_selected_worm();
  actual_worm->make_movable();
}

bool GameThread::is_alive() const {
    return alive;
}

bool GameThread::was_connected() const {
  return has_been_connected;
}

void GameThread::check_falling(){
  std::vector<Worm*> all_worms_alive = this->stage->get_all_alive_worms();
  for (Worm* worm : all_worms_alive){
    worm->check_falling();
  }
  check_deaths(all_worms_alive);
}

void GameThread::check_deaths(std::vector<Worm*> initial_worms_alive){
  std::vector<Worm*> actual_worms_alive = this->stage->get_all_alive_worms();
  if (initial_worms_alive.size() == actual_worms_alive.size()) return;

  for (Worm* i_worm : initial_worms_alive){
    size_t id = i_worm->get_id();
    bool still_alive = false;

    for (Worm* actual_worm : actual_worms_alive){
      if (id == actual_worm->get_id()) {
        still_alive = true;
        break;
      }
    }
    if (!still_alive){
      i_worm->correct_angle();
      int team = turns_manager.get_team_of_worm(i_worm);
      if (team != -1)
        this->server_thread->send_worm_death_notif_to_clients(id, team);
    }
  }
}

void GameThread::check_radiocontrolled_explosions(){
  std::vector<Worm*> all_worms_alive = this->stage->get_all_alive_worms();
  Player* actual_player = turns_manager.get_selected_player();
  if (actual_player->is_radiocontrolled_active()){
    std::vector<size_t> explosions = \
                            actual_player->check_radiocontrolled_explosions();
    for (size_t i = 0; i < explosions.size(); i++){
      this->server_thread->\
                    send_radiocontrolled_explosion_to_clients(explosions[i]);
    }
  }
  check_deaths(all_worms_alive);
}

void GameThread::check_dynamite_explosion(){
  std::vector<Worm*> all_worms_alive = this->stage->get_all_alive_worms();
  Player* actual_player = turns_manager.get_selected_player();
  actual_player->discount_dynamite_time(TICK_TIME);
  if (!actual_player->is_dynamite_active())
    this->server_thread->send_dynamite_explosion_to_clients();
  check_deaths(all_worms_alive);
}


GameThread::~GameThread(){
  delete stage;
  IEvent* temporal_event = NULL;
  while (this->safe_queue.pop(temporal_event)) {
    delete temporal_event;
  }
  stop();
  delete server_thread;
}
