#ifndef __BEAM_H__
#define __BEAM_H__

#include "Box2D/Box2D.h"
#include <stdlib.h>

#define BEAM_WIDTH 8.0
/* Clase que representa una Viga en el juego, con un alto fijo de 8m. Son
 * elementos solidos e impentrables, en los cuales los gusanos se pueden parar.
 * Tienen un ángulo determinado, y un largo recibido por parametro. No es
 * copiable.
 */
class Beam {
private:
  size_t id;
  float length;
  float width = BEAM_WIDTH;
  float angle;
  b2Body* body;

  // No es copiable
  Beam(const Beam&) = delete;
  Beam& operator=(const Beam&) = delete;

public:
  // Constructor. Recibe el id de la viga, el largo, el ángulo y el body de
  // Box2D que lo representa en el escenario.
  Beam(size_t id, float length, float angle, b2Body* body);

  // Devuelve la posición horizontal.
  float get_horizontal_position();

  // Devuelve la posición vertical.
  float get_vertical_position();

  // Devuelve el largo.
  float get_length();

  // Devuelve el ancho (8m).
  float get_width();

  // Devuelve el id.
  size_t get_id();

  // Devuelve el angulo.
  float get_angle();
};

#endif
