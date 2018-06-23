#include "server_Stage.h"
#define timeStep 1.0f/50.0f   //the length of time passed to simulate (seconds)
#define velocityIterations 8.0f   //how strongly to correct velocity
#define positionIterations 3.0f   //how strongly to correct position


Stage::Stage(size_t width, size_t height, std::string background){
  this->width = width;
  this->height = height;
  this->background = background;
  b2Vec2 gravity;
	gravity.Set(0.0f, -10.0f);
	bool doSleep = true;
	m_world = new b2World(gravity, doSleep);


  b2BodyDef myBodyDef;
  myBodyDef.type = b2_staticBody;
  b2PolygonShape polygonShape;
  b2FixtureDef myFixtureDef;
  myFixtureDef.shape = &polygonShape;
  myFixtureDef.density = 1;
  myFixtureDef.friction = 0.4;
  //Piso
  myBodyDef.position.Set(width/2, -2);
  polygonShape.SetAsBox(width/2, 2);
  m_world->CreateBody(&myBodyDef)->CreateFixture(&myFixtureDef);

  //Techo
  myBodyDef.position.Set(width/2, height + 2);
  m_world->CreateBody(&myBodyDef)->CreateFixture(&myFixtureDef);

  //Pared izq
  myBodyDef.position.Set(- 2 , height / 2);
  polygonShape.SetAsBox(2, height);
  m_world->CreateBody(&myBodyDef)->CreateFixture(&myFixtureDef);

  //Pared der
  myBodyDef.position.Set(width + 2, height / 2);
  polygonShape.SetAsBox(2, height);
  m_world->CreateBody(&myBodyDef)->CreateFixture(&myFixtureDef);
}

void Stage::add_worm(size_t id, size_t life, float position_h, \
                            float position_v){
  //worm definition
  b2BodyDef myBodyDef;
  myBodyDef.type = b2_dynamicBody;
  myBodyDef.position.Set(position_h, position_v);
  b2Body* worm_body = m_world->CreateBody(&myBodyDef);

  //shape definition
  b2PolygonShape polygonShape;
  polygonShape.SetAsBox(2, 2);

  //fixture definition
  b2FixtureDef myFixtureDef;
  myFixtureDef.shape = &polygonShape;
  myFixtureDef.density = 1;
  myFixtureDef.friction = 0.4;

  worm_body->CreateFixture(&myFixtureDef);
  Worm* worm = new Worm(id, life, worm_body);
  worms.insert(std::make_pair(id, worm));
}

void Stage::add_beam(size_t id, size_t length, float position_h,\
                      float position_v, float angle){
  b2BodyDef myBodyDef;
  myBodyDef.type = b2_staticBody;
  myBodyDef.position.Set(position_h, position_v);
  myBodyDef.angle = angle * DEGTORAD;
  b2Body* beam_body = m_world->CreateBody(&myBodyDef);
  //shape definition
  b2PolygonShape polygonShape;
  polygonShape.SetAsBox(length / 2, 4.0f); // 0.8m de alto.

  //fixture definition
  b2FixtureDef myFixtureDef;
  myFixtureDef.shape = &polygonShape;
  beam_body->CreateFixture(&myFixtureDef);
  beam_body->SetTransform(beam_body->GetPosition(), \
                                              angle * DEGTORAD);
  Beam* beam = new Beam(id, length, angle, beam_body);
  beams.insert(std::make_pair(id, beam));
}

b2Body* Stage::add_dynamite(float x, float y){
  b2BodyDef myBodyDef;
  myBodyDef.type = b2_staticBody;
  myBodyDef.position.Set(x, y);
  b2Body* dynamite_body = m_world->CreateBody(&myBodyDef);

  //shape definition
  b2PolygonShape polygonShape;
  polygonShape.SetAsBox(0.001, 0.001); // Tamanio muy chico

  //fixture definition
  b2FixtureDef myFixtureDef;
  myFixtureDef.shape = &polygonShape;
  dynamite_body->CreateFixture(&myFixtureDef);
  return dynamite_body;
}

b2Body* Stage::add_radiocontrolled(float x){
  b2BodyDef myBodyDef;
  myBodyDef.type = b2_dynamicBody;
  myBodyDef.position.Set(x, height - 10);
  b2Body* radiocontrolled_body = m_world->CreateBody(&myBodyDef);
  radiocontrolled_body->SetLinearVelocity( b2Vec2( 5, 0 ) );
  //shape definition
  b2PolygonShape polygonShape;
  polygonShape.SetAsBox(0.1, 0.1); // Tamanio muy chico

  //fixture definition
  b2FixtureDef myFixtureDef;
  myFixtureDef.shape = &polygonShape;
  radiocontrolled_body->CreateFixture(&myFixtureDef);
  return radiocontrolled_body;
}

Worm* Stage::get_worm(size_t id){
  auto search = worms.find(id);
  if(search != worms.end()) return search->second;
  return NULL;
}

Beam* Stage::get_beam(size_t id){
  auto search = beams.find(id);
  if(search != beams.end()) return search->second;
  return NULL;
}

size_t Stage::get_width(){
  return this->width;
}

size_t Stage::get_height(){
  return this->height;
}

std::string Stage::get_background(){
  return this->background;
}

void Stage::step(Worm* worm_actual){
  m_world->Step(timeStep, velocityIterations, positionIterations);
  worm_actual->apply_movement();
}

float Stage::calculate_distance(float x1, float y1, float x2, float y2){
  return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

std::vector<Worm*> Stage::get_worms_in_radius(float x, float y, float radius){
  std::vector<Worm*> worms_in_radius;
  for (auto it : worms)
    if (calculate_distance(it.second->get_horizontal_position(), \
                          it.second->get_vertical_position(), x, y) < radius)
      worms_in_radius.push_back(it.second);
  return worms_in_radius;
}

std::vector<Worm*> Stage::get_all_alive_worms(){
  std::vector<Worm*> worms_alive;
  for (auto it : worms)
    if (it.second->is_alive()) worms_alive.push_back(it.second);
  return worms_alive;
}

std::vector<Beam*> Stage::get_all_beams(){
  std::vector<Beam*> all_beams;
  for (auto it : beams)
    all_beams.push_back(it.second);
  return all_beams;
}


void Stage::explode(float x, float y, float radius, float epicentre_damage){
  radius += 2; // Para compensar el cuerpo de los gusanos.
  std::vector<Worm*> affected_worms = get_worms_in_radius(x, y, radius);
  for (size_t i = 0; i < affected_worms.size(); i++){
    float distance = calculate_distance(x, y, \
              affected_worms[i]->get_horizontal_position(), \
              affected_worms[i]->get_vertical_position()) - 2;
    // Resto puntos de vida proporcionales a la distancia. Si la distancia es 0
    // Resto el epicentre_damage, si es igual al radio resto 0.
    float force = (radius - distance) / radius * epicentre_damage;

    affected_worms[i]->subtract_life( (size_t)force );
    affected_worms[i]->make_movable();

    bool fly_to_the_left = (affected_worms[i]->get_horizontal_position() < x);
    if (fly_to_the_left) affected_worms[i]->apply_force(-force * EXPLOSION_FORCE, force * EXPLOSION_FORCE);
    else affected_worms[i]->apply_force(force * EXPLOSION_FORCE, force * EXPLOSION_FORCE);
  }
}

void Stage::remove_body(b2Body* body){
  m_world->DestroyBody(body);
}

Stage::~Stage(){
  for (size_t i = 0; i < worms.size(); i++){
    delete worms[i];
  }
  for (size_t i = 0; i < beams.size(); i++){
    delete beams[i];
  }
  delete m_world;

}
