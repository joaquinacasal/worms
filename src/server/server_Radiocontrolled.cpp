#include "server_Radiocontrolled.h"

Radiocontrolled::Radiocontrolled(Stage& a_stage) : stage(a_stage){
  active = false;
}

bool Radiocontrolled::fire(float x){
  if (active) return false;
  // Crea 6 municiones en el aire con una distancia de 50m entre ellas.
  // Calculo la más pegada al borde (-125 m) para correrlo si choca con la pared.
  // Los crea con una velocidad inicial (10, -1).
  float x_min = x - 125;
  if (x_min <= 5) x_min = 5;
  for (size_t i = 0; i < FLYING_BOMBS; i++){
    munitions.push_back(stage.add_radiocontrolled(x_min));
    x_min += 50;
  }
  active = true;
  return true;
}

bool Radiocontrolled::is_active(){
  return active;
}

void Radiocontrolled::check_explosions(){
  if (!active) return;
  for (size_t i = 0; i < munitions.size(); i++){
    if (is_colliding(munitions[i])){
      stage.explode(munitions[i]->GetPosition().x,\
                    munitions[i]->GetPosition().y,\
                    RADIUS_RADIOCONTROLLED,\
                    EPICENTRE_DAMAGE_RADIOCONTROLLED);
      stage.remove_body(munitions[i]);
      munitions.erase(munitions.begin() + i);
    }
  }
  if (munitions.size() == 0) active = false;
}

bool Radiocontrolled::is_colliding(b2Body* munition){
  if (!is_active()) return false;
  for (b2ContactEdge* edge = munition->GetContactList(); edge; edge = edge->next){
    return true;
  }
  return false;
}

std::vector<std::pair<float, float>> Radiocontrolled::get_positions(){
  std::vector<std::pair<float, float>> positions;
  for (size_t i = 0; i < munitions.size(); i++){
    std::pair<float, float> munition_position(munitions[i]->GetPosition().x,\
                  munitions[i]->GetPosition().y);
    positions.push_back(munition_position);
  }
  return positions;
}
