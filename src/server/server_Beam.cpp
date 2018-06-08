#include "server_Beam.h"

Beam::Beam(size_t id, float length, float angle,b2Body* body){
  this->id = id;
  this->body = body;
  this->length = length;
  this->angle = angle;
}

float Beam::get_horizontal_position(){
  return body->GetPosition().x;
}

float Beam::get_vertical_position(){
  return body->GetPosition().y;
}

float Beam::get_length(){
  return this->length;
}

float Beam::get_width(){
  return this->width;
}

size_t Beam::get_id(){
  return this->id;
}

float Beam::get_angle(){
  return this->angle;
}
