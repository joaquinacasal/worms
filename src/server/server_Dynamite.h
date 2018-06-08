#ifndef __DYNAMITE_H__
#define __DYNAMITE_H__

#include <stdlib.h>
#include "Box2D/Box2D.h"
#include "server_Stage.h"

#define RADIUS_DYNAMITE 40.0 // 4 m * 10 .
#define EPICENTRE_DAMAGE_DYNAMITE 50.0


/* Clase que representa el arma dinamita del juego. Es un elemento sólido, que
 * no se puede mover, y que al cabo de 7 segundos explota con un radio de
 * 40 metros y un daño máximo de 50 puntos de vida en el epicentro (el daño
 * va disminuyendo proporcionalmente a la distancia al epicentro). Cuenta con
 * 5 municiones. Es no copiable.
 */
class Dynamite {
  private:
    size_t q_munitions = 5;
    b2Body* munition = NULL;
    bool active;
    float counting;
    Stage& stage;

    //
    Dynamite(const Dynamite&) = delete;
    Dynamite& operator=(const Dynamite&) = delete;
  public:
    // Constructor. Recibe el Stage donde va a crearse.
    Dynamite(Stage& a_stage);


    // Si la cantidad de municiones es 0, devuelve false sin cambiar nada.
    // Si tenía municiones, devuelve True y crea una dinamita en la posición
    // especificada. Además, setea counting en 7000 (7 segundos), se reduce
    // en uno la cantidad de municiones y se setea como activa.
    bool turn_on_dynamite(float x, float y);

    // Devuelve si la dinamita está activa.
    bool is_active();

    // Si la dinamita esta activa, descuenta la cantidad de milisegundos
    // recibida. Si no, no hace nada.
    void discount_time(float t);

    // Obtiene la cantidad de municiones de dinamita disponibles.
    size_t get_munitions();

    // Pre: La dinamita está activa
    // Obtiene la posición horizontal de la dinamita activa.
    float get_horizontal_position();

    // Pre: La dinamita está activa
    // Obtiene la posición vertical de la dinamita activa.
    float get_vertical_position();

    // Obtiene la cantidad de ms restantes para la explosión.
    // Si la dinamita no está activa, devuelve 7000.
    float get_time_to_explosion();

};

#endif  //__DYNAMITE_H__
