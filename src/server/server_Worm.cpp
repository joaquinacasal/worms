#include "server_Worm.h"

Worm::Worm(size_t id, size_t life, b2Body* body): movement(body){
  this->id = id;
  this->life = life;
}

size_t Worm::get_id(){
  return this->id;
}

void Worm::subtract_life(size_t life_points){
  if (this->life >= life_points) this->life -= life_points;
  else this->life = 0;
}

bool Worm::is_alive(){
  return this->life > 0;
}

size_t Worm::get_life_points(){
  return life;
}


float Worm::get_horizontal_position(){
  return this->movement.get_horizontal_position();
}

float Worm::get_vertical_position(){
  return this->movement.get_vertical_position();
}

float Worm::get_horizontal_velocity(){
  return this->movement.get_horizontal_velocity();
}

float Worm::get_vertical_velocity(){
  return this->movement.get_vertical_velocity();
}

float Worm::get_angle(){
  return this->movement.get_angle();
}

void Worm::move_right(){
  this->movement.move_right();
}

void Worm::move_left(){
  this->movement.move_left();
}

void Worm::jump_forward(){
  this->movement.jump_forward();
}

void Worm::jump_backward(){
  this->movement.jump_backward();
}

void Worm::stop_moving(){
  this->movement.stop_moving();
}

void Worm::apply_movement(){
  this->movement.apply_movement();
}

void Worm::teletransport(int x, int y){
  this->movement.teletransport(x, y);
}

bool Worm::is_facing_right(){
  return this->movement.is_facing_right();
}