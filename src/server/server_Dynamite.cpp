#include "server_Dynamite.h"

Dynamite::Dynamite(Stage& a_stage) : stage(a_stage){
  counting = 7000; // 7 segundos.
  active = false;
}

bool Dynamite::turn_on_dynamite(float x, float y){
  // Si no hay municiones o ya hay una dinamita activa
  if (q_munitions == 0 || active) return false;

  munition = stage.add_dynamite(x, y);
  --q_munitions;
  active = true;
  return true;
}

bool Dynamite::is_active(){
  return active;
}

void Dynamite::discount_time(float t){
  if (!is_active()) return;
  this->counting -= t;
  if (this->counting <= 0) {
    this->active = false;
    this->counting = 7000;
    this->stage.explode(munition->GetPosition().x, munition->GetPosition().y, \
                  RADIUS_DYNAMITE, EPICENTRE_DAMAGE_DYNAMITE);
    stage.remove_body(munition);
    munition = NULL;
  }
}

size_t Dynamite::get_munitions(){
  return q_munitions;
}

float Dynamite::get_horizontal_position(){
  // TODO: Controlar si está activo. Sino, tirar exception
  return munition->GetPosition().x;
}

float Dynamite::get_vertical_position(){
  // TODO: Controlar si está activo. Sino, tirar exception
  return munition->GetPosition().y;
}

float Dynamite::get_time_to_explosion(){
  return counting;
}
