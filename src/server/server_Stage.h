#ifndef __STAGE_H__
#define __STAGE_H__

#include "server_Beam.h"
#include "server_Worm.h"
#include <stdlib.h>
#include <math.h>
#include "Box2D/Box2D.h"
#include <unordered_map>
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

/* Clase que representa el escenario donde se lleva a cabo una partida. Contiene
 * vigas, gusanos y puede crear nuevos cuerpos que representen municiones o
 * proyectiles. Recibe el ancho y el largo del escenario en el constructor, y
 * se pueden agregar el resto de los elementos mediante sus métodos públicos.
 * No es copiable.
 */
class Stage {
private:
  size_t width;
  size_t height;
  std::unordered_map<size_t, Worm*> worms;
  std::unordered_map<size_t, Beam*> beams;
  b2World* m_world;

  // Calcula la distancia entre los puntos recibidos.
  float calculate_distance(float x1, float y1, float x2, float y2);

  // Obtiene un vector con los worms contenidos en el radio con centro en el
  // punto (X,Y) recibido.
  std::vector<Worm*> get_worms_in_radius(float x, float y, float radius);


  // No es copiable.
  Stage(const Stage&) = delete;
  Stage& operator=(const Stage&) = delete;
public:
  // Constructor. Recibe el ancho y el largo del escenario.
  Stage(size_t width, size_t height);

  // Crea un nuevo gusano en la posición (X,Y) recibida. Las posiciones deben
  // ser mayores que 0 y menores  que el ancho/largo, respectivamente. Además,
  // recibe el id y la vida del gusano.
  void add_worm(size_t id, size_t life, float position_h, float position_v);

  // Crea una nueva viga en la posición (X,Y) recibida. Las posiciones deben
  // ser mayores que 0 y menores  que el ancho/largo, respectivamente. Además
  // recibe el id, el largo y el ángulo de la viga.
  void add_beam(size_t id, size_t length, float position_h,\
                        float position_v, float angle);

  // Crea una nuevo cuerpo que representa una dinamita en la posición recibida
  // y lo devuelve.
  b2Body* add_dynamite(float x, float y);

  // Crea una nuevo cuerpo que representa un proyectil del teledirigido
  // en la posición recibida y lo devuelve.
  b2Body* add_radiocontrolled(float x);

  // Devuelve un puntero al worm con el id indicado. NULL si no existe ese id.
  Worm* get_worm(size_t id);
  // Devuelve un puntero al beam con el id indicado. NULL si no existe ese id.
  Beam* get_beam(size_t id);

  // Getters de las dimensiones del escenario.
  size_t get_width();
  size_t get_height();

  // Recibe el gusano del cual es el turno para avanzar un frame y actualizar
  // su movimiento.
  void step(Worm* worm_actual);

  // Genera una explosión en la posición (X,Y) recibida, con el radio y
  // daño en el epicentro indicados. Le resta la vida correspondiente a los
  // gusanos que se encuentran dentro de ese radio.
  void explode(float x, float y, float radius, float epicentre_damage);

  // Limpia todos los elementos del escenario.
  void clean_stage();

  // Elimina el cuerpo recibido.
  void remove_body(b2Body* body);

  // Devuelve un vector con todos los gusanos vivos.
  std::vector<Worm*> get_all_alive_worms();

  // Devuelve un vector con todos los gusanos.
  std::vector<Beam*> get_all_beams();

  ~Stage();
};

#endif
