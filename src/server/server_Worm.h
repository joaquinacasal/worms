#ifndef __WORM_H__
#define __WORM_H__

#include "server_Movement.h"
#include <stdlib.h>

#define WATER_HEIGTH 8

/* Clase que representa a un gusano del juego, con un id, vida, posición,
 * ángulo y movimiento. Es no copiable.
 */
class Worm {
private:
  size_t id;
  size_t life;
  Movement movement;

  float last_solid_height;
  bool changed;

  // No copiable.
  Worm(const Worm&) = delete;
  Worm& operator=(const Worm&) = delete;

public:
  // Contructor, recibe el id, la vida inicial y el body de Box2D que lo
  // representa en el escenario.
  Worm(size_t id, size_t life, b2Body* body);

  // Devuelve el id
  size_t get_id();

  // Disminuye la vida del gusano en el valor recibido. Si pasa a ser menor
  // que 0, la vida queda en 0.
  void subtract_life(size_t life_points);

  // Devuelve la cantidad de puntos de vida del gusano.
  size_t get_life_points();

  // Devuele un booleano indicando si el gusano sigue vivo.
  bool is_alive();

  // Devuelve un float indicando la posición horizontal del gusano.
  float get_horizontal_position();

  // Devuele un float indicando la posición vertical del gusano.
  float get_vertical_position();

  // Devuelve un float indicando la velocidad horizontal del gusano.
  float get_horizontal_velocity();

  // Devuelve un float indicando la velocidad vertical del gusano.
  float get_vertical_velocity();
  // Devuelve un float indicando el ángulo en grados.
  float get_angle();

  // Setea el movimiento del gusano hacia la derecha, hasta que se llame a
  // stop_moving.
  void move_right();

  // Setea el movimiento del gusano hacia la izquierda, hasta que se llame a
  // stop_moving.
  void move_left();

  // Setea el movimiento del gusano a quieto.
  void stop_moving();

  // Salta hacia adelante 10m y 5 de alto.
  void jump_forward();

  // Salta hacia atras 2m y 12 de alto. Además, da una vuelta hacia atrás.
  void jump_backward();

  // Aplica un impulso al cuerpo en la dirección  que esté seteado el
  // movimiento.
  void apply_movement();

  // Teletransporta el gusano a la posición (X,Y) recibida.
  void teletransport(double x, double y);

  // Devuelve true si el gusano está mirando hacia la derecha, false en caso
  // contrario.
  bool is_facing_right();

  // Hace que el gusano pueda moverse
  void make_movable();

  // Hace que el gusano no pueda moverse
  void make_immovable();

  // Devuelve un booleano indicando si puede moverse o no.
  bool is_movable();

  // Corrige el ángulo del gusano, seteandolo a 0.
  void correct_angle();

  // Aplica la fuerza recibida.
  void apply_force(float x, float y);

  void check_falling();

  bool is_moving();

  // Devuelve un booleano indicando si está colisionando
  // con algún objeto.
  bool is_colliding();

  // Devuelve un booleano indicando si cambió el estado del gusano desde
  // la última vez que se consultó.
  bool has_suffered_changes();
};


#endif //__WORM_H__
