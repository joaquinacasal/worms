#ifndef __MOVEMENT_H__
#define __MOVEMENT_H__
#include "Box2D/Box2D.h"

// Which was the last movement.
enum _lastMovement {
  LEFT,
  RIGHT,
};
// Which is the actual movement state.
enum _moveState {
  MS_STOP,
  MS_LEFT,
  MS_RIGHT,
};

/* Clase encargada de la movilidad y la representación en el escenario de un
 * gusano. Tiene una referencia a un body de Box2D, en la cual delega su
 * representación sobre el Stage.Es no copiable.
 */
class Movement {
private:
  _lastMovement last_movement;
  _moveState move_state;
  b2Body* body;

  // No copiable
  Movement(const Movement&) = delete;
  Movement& operator=(const Movement&) = delete;

public:
  // Constructor. Recibe el body de Box2D.
  explicit Movement(b2Body* body);

  // Devuelve un float indicando la posición horizontal del gusano.
  float get_horizontal_position();

  // Devuelve un float indicando la posición vertical del gusano.
  float get_vertical_position();

  // Devuelve un float indicando la velocidad horizontal del gusano.
  float get_horizontal_velocity();

  // Devuelve un float indicando la velocidad vertical del gusano.
  float get_vertical_velocity();

  // Devuelve el ángulo en grados.
  float get_angle();

  // Salta hacia adelante 10m y 5 de alto.
  void jump_forward();

  // Salta hacia atras 2m y 12 de alto. Además, da una vuelta hacia atrás.
  void jump_backward();

  // Setea el movimiento del gusano hacia la derecha, hasta que se llame a
  // stop_moving.
  void move_right();

  // Setea el movimiento del gusano hacia la izquierda, hasta que se llame a
  // stop_moving.
  void move_left();

  // Setea el movimiento del gusano a quieto.
  void stop_moving();

  // Aplica un impulso al cuerpo en la dirección  que esté seteado el
  // movimiento.
  void apply_movement();

  // Teletransporta el gusano a la posición (X,Y) recibida.
  void teletransport(int x, int y);

  // Devuelve true si el gusano está mirando hacia la derecha, false en caso
  // contrario.
  bool is_facing_right();

  // Hace que el cuerpo pueda moverse
  void make_movable();

  // Hace que el cuerpo no pueda moverse
  void make_immovable();

  // Devuelve un booleano indicando si puede moverse o no.
  bool is_movable();

  // Deja el cuerpo quieto.
  void reset_velocity();

  // Corrige el ángulo del cuerpo, seteandolo a 0.
  void correct_angle();

  // Aplica la fuerza recibida.
  void apply_force(float x, float y);

  // Devuelve un booleano indicando si está colisionando
  // con algún objeto.
  bool is_colliding();

  // Devuelve un booleano indicando si el cuerpo se está moviendo a la
  // izquierda o a la derecha.
  bool is_moving();
};


#endif //__MOVEMENT_H__
