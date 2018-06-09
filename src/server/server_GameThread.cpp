#include <string>
#include <vector>
#include <syslog.h>
#include "server_GameThread.h"
#include <chrono>
#include <iostream>
#include <thread>

using ms = std::chrono::milliseconds;
using get_time = std::chrono::steady_clock;
using std::move;

void GameThread::create_stage(string map_file, int number_players){
  YamlParser yaml_parser;
  ScenarioDTO scenario_DTO = yaml_parser.load_scenario(map_file);

  vector<WormDTO> worms_DTO = scenario_DTO.get_worms();
  // Verifico que la cantidad de gusanos sea menor o igual a la cantidad de jugadores
  if (worms_DTO.size() < number_players) {
    throw std::runtime_error("Número de jugadores es mayor a la cantidad de gusanos.\n");
  } else if (number_players == 0) {
    throw std::runtime_error("Debe jugar al menos un jugador.\n");
  }

  stage = new Stage((size_t)scenario_DTO.get_width(), (size_t)scenario_DTO.get_height());
  printf("Ancho: %d, Largo: %d\n", scenario_DTO.get_width(), scenario_DTO.get_height());
  // Creo los worms y los jugadores.
  int number_players_with_more_worms =  (worms_DTO.size() % number_players);
  if (number_players_with_more_worms == 0) number_players_with_more_worms = number_players;
  int number_players_with_less_worms = number_players - number_players_with_more_worms;

  // Cantidad de gusanos de los jugadores con MENOS gusanos.
  int number_worms_per_player_with_less_worms = (int) (worms_DTO.size() / number_players);
  int number_worms_per_player_with_more_worms = number_worms_per_player_with_less_worms;

  if (number_players_with_less_worms != 0)
    ++number_worms_per_player_with_more_worms;

  size_t worm_index = 0;

  for (int i = 0; i < number_players_with_more_worms; i++){
    Armory* armory = new Armory(*stage);
    Player* player = new Player(armory);
    for (int j = 0; j < number_worms_per_player_with_more_worms; j++){
      stage->add_worm(worms_DTO[worm_index].get_id(),\
                      INITIAL_LIFE_POINTS, \
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
                      INITIAL_LIFE_POINTS + 25, \
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
    while (alive) {
      tick_turn();
      changeTurn();
    }
}

void GameThread::tick_turn(){
  IEvent* temporal_event = NULL;
  Player* actual_player = turns_manager.get_selected_player();
  Worm* actual_worm = actual_player->get_selected_worm();

  bool weapon_was_used = false;

  while (alive && (turn_chrono > 0 || actual_player->has_an_active_weapon())) {
    auto start = get_time::now();
    // Si ya termina el turno y siguen los ataques dejo de moverlo.
    if (turn_chrono == 0) actual_worm->stop_moving();
    // Si ya termino el turno no ejecuta ninguna acción
    if (turn_chrono > 0 && this->safe_queue.pop(temporal_event)){
      try {
        temporal_event->run();
        delete temporal_event;
      } catch (...){
          std::cout << "Un cliente cerró la conexión\n";
          this->stop();
          std::cout << "DEBUG: Ya termino de stopear el serverThread\n";

          delete temporal_event;
          break;
      }
    }
    stage->step(actual_worm);

    //Chequeo las explosiones del teledirigido.
    if (actual_player->is_radiocontrolled_active())
      check_radiocontrolled_explosions();
    notif_clients();
    std::this_thread::sleep_for(std::chrono::milliseconds(16));
    auto end = get_time::now();
    turn_chrono -= std::chrono::duration_cast<ms>(end - start).count();
    if (turn_chrono < 0) turn_chrono = 0;
    if (actual_player->is_dynamite_active()){
      actual_player->discount_dynamite_time(
        std::chrono::duration_cast<ms>(end - start).count());
    }

    if (!weapon_was_used) {
      // Si nunca se usó el arma, me fijo si se activó.
      if (actual_player->has_an_active_weapon())
        weapon_was_used = true;
    } else {
      // Si alguna vez fue usada un arma, entonces cuando
      // se desactive termina el turno.
      if (!actual_player->has_an_active_weapon())
      turn_chrono = 0;
    }
  }
  if (is_alive()) actual_worm->stop_moving();
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
  std::vector<Worm*> all_worms_alive = this->stage->get_all_alive_worms();
  for (size_t i = 0; i < all_worms_alive.size(); i++){
    size_t id = all_worms_alive[i]->get_id();
    size_t life_points = all_worms_alive[i]->get_life_points();
    int x = all_worms_alive[i]->get_horizontal_position() * 1000;
    int y = all_worms_alive[i]->get_vertical_position() * 1000;
    int angle = (int)all_worms_alive[i]->get_angle();
    bool is_facing_right = all_worms_alive[i]->is_facing_right();

    this->server_thread->send_worm_information_to_clients(id, life_points, x, \
                                          y, angle, is_facing_right);
  }
}

void GameThread::send_stage_information_to_clients(){
  int width = this->stage->get_width();
  int height = this->stage->get_height();
  this->server_thread->send_stage_information_to_clients(width, height);
  std::vector<Beam*> all_beams = this->stage->get_all_beams();
  for (size_t i = 0; i < all_beams.size(); i++){
    int x = all_beams[i]->get_horizontal_position() * 1000;
    int y = all_beams[i]->get_vertical_position() * 1000;
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
    double x = actual_player->get_dynamite_horizontal_position() * 1000;
    double y = actual_player->get_dynamite_vertical_position() * 1000;
    double time_to_explosion = actual_player->get_dynamite_time_to_explosion();
    this->server_thread->send_dynamite_information_to_clients(x, y, time_to_explosion);
  }
  if (actual_player->is_radiocontrolled_active()){
    std::vector<std::pair<float, float>> positions = actual_player->get_radiocontrolled_positions();
    for (size_t i = 0; i < positions.size(); i++){
      double x = positions[i].first * 1000;
      double y = positions[i].second * 1000;
      this->server_thread->send_radiocontrolled_information_to_clients(x, y);
    }
  }
}


void GameThread::stop(){
    alive = false;
    if (server_thread->is_alive()){
      printf("DEGUG: Por enviar la closed_con_notif\n");
      server_thread->send_closed_connection_notif();
      printf("DEGUG: Por hacer el stop\n");
      server_thread->stop();
      printf("DEGUG: Por hacer el join\n");
      server_thread->join();
    }
}

void GameThread::addClient(ClientHandler* client_handler){
  client_handler->add_safe_queue(&(this->safe_queue));
}

void GameThread::add_all_clients(){
  std::vector<ClientHandler*>* clients = server_thread->get_all_connected_clients();
  for (size_t i = 0; i < clients->size(); i++){
    addClient((*clients)[i]);
  }
}

void GameThread::changeTurn(){
  // Seteo todos los gusanos en no movibles.
  std::vector<Worm*> all_worms_alive = this->stage->get_all_alive_worms();
  for (Worm* worm : all_worms_alive){
    worm->make_immovable();
    worm->correct_angle();
  }
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

void GameThread::check_radiocontrolled_explosions(){
  Player* actual_player = turns_manager.get_selected_player();
  if (actual_player->is_radiocontrolled_active())
    actual_player->check_radiocontrolled_explosions();
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
