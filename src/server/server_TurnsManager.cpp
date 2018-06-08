#include "server_TurnsManager.h"

TurnsManager::TurnsManager(){
  players = std::vector<Player*>();
  selected_index = 0;
}

void TurnsManager::add_player(Player* player){
  players.push_back(player);
}

Player* TurnsManager::get_selected_player(){
  return players[selected_index];
}

void TurnsManager::finish_turn(){
  if (get_number_players_alive() == 0) return;
  players.at(selected_index)->select_next_worm();
  do {
    if (++selected_index == players.size()) selected_index = 0;
  } while (!players[selected_index]->has_worms_alive());
}

size_t TurnsManager::get_number_players_alive(){
  size_t count = 0;
  for (size_t i = 0; i < players.size(); i++){
    if (players[i]->has_worms_alive()) ++count;
  }
  return count;
}

size_t TurnsManager::get_number_players(){
  return players.size();
}

TurnsManager::~TurnsManager(){
  for (size_t i = 0; i < players.size(); i++){
    delete players[i];
  }
}