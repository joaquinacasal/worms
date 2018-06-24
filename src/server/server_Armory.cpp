#include "server_Armory.h"
#include <map>
#include <utility>
#include <vector>


Armory::Armory(Stage& a_stage) :  stage(a_stage),
                                  dynamite(a_stage),
                                  radiocontrolled(a_stage){
  //dynamite = new Dynamite(a_stage);
  //teletransportation = new Teletransportation();
}

bool Armory::use_teletransportation(Worm* worm, float x, float y){
  return teletransportation.teletransport_to(worm, x, y);
}

int Armory::get_teletransportation_munitions(){
  return teletransportation.get_munitions();
}

bool Armory::was_teletransportation_used(){
  return teletransportation.was_teletransportation_used();
}

bool Armory::use_dynamite(Worm* worm, bool is_facing_right){
  float x = worm->get_horizontal_position();
  if (is_facing_right)
    x += 2.02;
  else
    x -= 2.02;
  float y = worm->get_vertical_position();
  return this->dynamite.turn_on_dynamite(x, y);
}

int Armory::get_dynamite_munitions(){
  return this->dynamite.get_munitions();
}

void Armory::discount_dynamite_time(float t){
  this->dynamite.discount_time(t);
}

bool Armory::is_dynamite_active(){
  return this->dynamite.is_active();
}

float Armory::get_dynamite_horizontal_position(){
  return this->dynamite.get_horizontal_position();
}

float Armory::get_dynamite_vertical_position(){
  return this->dynamite.get_vertical_position();
}

float Armory::get_dynamite_time_to_explosion(){
  return this->dynamite.get_time_to_explosion();
}

bool Armory::use_radiocontrolled(float x){
  return this->radiocontrolled.fire(x);
}

bool Armory::is_radiocontrolled_active(){
  return this->radiocontrolled.is_active();
}

int Armory::get_radiocontrolled_munitions(){
  return this->radiocontrolled.get_munitions();
}

std::map<size_t, std::pair<float, float>> Armory::\
                                              get_radiocontrolled_positions(){
  return this->radiocontrolled.get_positions();
}

std::vector<size_t> Armory::check_radiocontrolled_explosions(){
  return this->radiocontrolled.check_explosions();
}

Armory::~Armory(){}
