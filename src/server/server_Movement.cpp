#include "server_Movement.h"
#define epsilon 0.00001f
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

Movement::Movement(b2Body* body) : body(body){
  this->last_movement = RIGHT;
  this->move_state = MS_STOP;
}

float Movement::get_horizontal_position(){
  return body->GetPosition().x;
}
float Movement::get_vertical_position(){
  return body->GetPosition().y;
}

float Movement::get_horizontal_velocity(){
  return body->GetLinearVelocity().x;
}
float Movement::get_vertical_velocity(){
  return body->GetLinearVelocity().y;
}

float Movement::get_angle(){
  return body->GetAngle() * RADTODEG;
}

void Movement::jump_forward(){
  // Salta 1 m hacia adelante y 0.5 hacia arriba.
  int side = 1;
  if (last_movement == LEFT) side = -1;

  // Solo salto si estoy quieto en la velocidad vertical para no poder saltar
  // en el aire. Hay que cambiarlo para poder saltar en las vigas con angulo.
  if (body->GetLinearVelocity().y < epsilon && body->GetLinearVelocity().y > -epsilon)
    // Formulas calculadas a mano.
    body->ApplyLinearImpulse( b2Vec2( side * 78.85f, 162.0f), body->GetWorldCenter() );
}

void Movement::jump_backward(){
  // Salta 0.2m hacia atras, 1.2 hacia arriba y da una vuelta.
  int side = 1;
  if (last_movement == LEFT) side = -1;

  // Solo salto si estoy quieto en la velocidad vertical para no poder saltar
  // en el aire. Hay que cambiarlo para poder saltar en las vigas con angulo.
  if (body->GetLinearVelocity().y < epsilon && body->GetLinearVelocity().y > -epsilon){
    // Formulas calculadas a mano.
    body->ApplyLinearImpulse( b2Vec2(side * -10.3f, 250.0f), body->GetWorldCenter() );
    body->ApplyAngularImpulse( side * 86.3);
  }
}

void Movement::move_right(){
  move_state = MS_RIGHT;
  last_movement = RIGHT;
}

void Movement::move_left(){
  move_state = MS_LEFT;
  last_movement = LEFT;
}

void Movement::stop_moving(){
  move_state = MS_STOP;
}

void Movement::apply_movement(){
  b2Vec2 vel = body->GetLinearVelocity();
  float force = 0;
  switch ( move_state )
  {
    case MS_LEFT:  if ( vel.x > -2 ) force = -200;  break;
    case MS_STOP:  force = 0; break;
    case MS_RIGHT: if ( vel.x <  2 ) force =  200; break;
  }
  body->ApplyForce( b2Vec2(force,0), body->GetWorldCenter() );
}

void Movement::teletransport(int x, int y){
  body->SetTransform(b2Vec2(x, y), 0);
}

bool Movement::is_facing_right(){
  return last_movement == RIGHT;
}

void Movement::make_movable(){
  this->body->SetType(b2_dynamicBody);
}

void Movement::make_immovable(){
  this->body->SetType(b2_staticBody);
}

bool Movement::is_movable(){
  return this->body->GetType() == b2_dynamicBody;
}

void Movement::reset_velocity(){
  b2Vec2 vel = body->GetLinearVelocity();
  vel.x = 0;
  vel.y = 0;
  body->SetLinearVelocity( vel );
}


void Movement::correct_angle(){
  this->body->SetTransform(this->body->GetPosition(), 0);
}

void Movement::apply_force(float x, float y){
  this->body->ApplyForce( b2Vec2(x, y), body->GetWorldCenter() );
}

bool Movement::is_colliding(){
  for (b2ContactEdge* edge = body->GetContactList(); edge; edge = edge->next){
    return true;
  }
  return false;
}

bool Movement::is_moving(){
  return (move_state == MS_LEFT || move_state == MS_RIGHT);
}
