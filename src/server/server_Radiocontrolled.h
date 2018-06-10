#ifndef __RADIOCONTROLLED_H__
#define __RADIOCONTROLLED_H__

#include <stdlib.h>
#include <vector>
#include "Box2D/Box2D.h"
#include "server_Stage.h"

#define RADIUS_RADIOCONTROLLED 20.0 // 2 m * 10 .
#define EPICENTRE_DAMAGE_RADIOCONTROLLED 40.0
#define FLYING_BOMBS 6


/* Clase que representa el arma teledirigido del juego. Crea 6 proyectiles
 * en el aire, si es posible centrados en la coordenada indicada, si no
 * mas a la derecha, que caen por efecto de la gravedad y con una leve
 * velocidad hacia la derecha. Se crean a 50 metros de distancia entre ellos
 * abarcando así 250 metros de terreno. Cada proyectil tiene un radio de
 * explosión de 20 metros, con un daño máximo de 40 puntos de vida en el
 * epicentro (el daño va disminuyendo proporcionalmente a la distancia al
 * epicentro). Cuenta con infinitas municiones. Es no copiable.
 */
class Radiocontrolled {
  private:
    std::vector<b2Body*> munitions;
    bool active;
    Stage& stage;

    // No copiable
    Radiocontrolled(const Radiocontrolled&) = delete;
    Radiocontrolled& operator=(const Radiocontrolled&) = delete;

    // Método privado que recibe una munición y devuelve un booleano
    // indicando si está colisionando con algún objeto.
    bool is_colliding(b2Body* munition);
  public:
    // Constructor. Recibe el stage donde creará las 6 municiones.
    Radiocontrolled(Stage& a_stage);


    // Si ya esta activo, devuelve false sin cambiar nada.
    // Si no, devuelve True y crea las municiones en la altura, sobre la
    // coordenada x recibida. Crea en x-125, x-75, x-25, x+25, x+75 y x+125.
    // Las crea con una velocidad inicial de (5m/s, 0m/s).
    bool fire(float x);

    // Devuelve un booleano indicando si está activo.
    bool is_active();

    // Devuelve un vector de pares X,Y indicando las posiciones de todos los
    // teledirigidos activos.
    std::vector<std::pair<float, float>> get_positions();

    // Revisa, para cada munición activa, si está colisionando con algún
    // objeto y en caso que sea verdadero se encarga de hacerlo explotar
    // y eliminar dicha munición.
    void check_explosions();
};

#endif //__RADIOCONTROLLED_H__
