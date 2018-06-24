#include "server_Radiocontrolled.h"
#include <map>
#include <utility>
#include <vector>

Radiocontrolled::Radiocontrolled(Stage& a_stage) : stage(a_stage){
  active = false;
}

bool Radiocontrolled::fire(float x){
  if (active) return false;
  // Crea 6 municiones en el aire con una distancia de 30m entre ellas.
  // Calculo la más pegada al borde (-75 m) para correrlo si choca con la pared.
  // Los crea con una velocidad inicial (10, -1).
  float x_max = x + 75;
  if (x_max > stage.get_width() - MARGIN) {
    x_max = stage.get_width() - MARGIN;
  }
  float x_min = x_max - DISTANCE_BETWEEN_BOMBS * (FLYING_BOMBS - 1);
  if (x_min <= MARGIN) x_min = MARGIN;

  float distance =  DISTANCE_BETWEEN_BOMBS;
  if ((x_max - x_min) / (FLYING_BOMBS - 1) < distance)
    distance = (x_max - x_min) / (FLYING_BOMBS - 1);


  for (size_t i = 0; i < FLYING_BOMBS; i++){
    munitions[i] = stage.add_radiocontrolled(x_min);
    x_min += distance;
  }
  active = true;
  return true;
}

bool Radiocontrolled::is_active(){
  return active;
}

std::vector<size_t> Radiocontrolled::check_explosions(){
  std::vector<size_t> explosions;
  if (!active) return explosions;
  for (size_t i = 0; i < FLYING_BOMBS; i++){
    if (munitions.count(i) == 0) continue;
    if (is_colliding(munitions[i])){
      explosions.push_back(i);
      stage.explode(munitions[i]->GetPosition().x,\
                    munitions[i]->GetPosition().y,\
                    RADIUS_RADIOCONTROLLED,\
                    EPICENTRE_DAMAGE_RADIOCONTROLLED);
      stage.remove_body(munitions[i]);
      munitions.erase(i);
    }
  }
  if (munitions.size() == 0) active = false;
  return explosions;
}

bool Radiocontrolled::is_colliding(b2Body* munition){
  if (!is_active()) return false;
  for (b2ContactEdge* edge = munition->GetContactList(); \
      edge; edge = edge->next){
    if (edge->contact->IsTouching()) return true;
  }
  return false;
}

std::map<size_t, std::pair<float, float>> Radiocontrolled::get_positions(){
  std::map<size_t, std::pair<float, float>> positions;
  for (size_t i = 0; i < FLYING_BOMBS; i++){
    if (munitions.count(i) == 0) continue;
    std::pair<float, float> munition_position(munitions[i]->GetPosition().x,\
                  munitions[i]->GetPosition().y);
    positions[i] = munition_position;
  }
  return positions;
}

int Radiocontrolled::get_munitions(){
  return munitions_q;
}
