#ifndef __ARMORY_H__
#define __ARMORY_H__

#include <stdlib.h>
#include "server_Teletransportation.h"
#include "server_Dynamite.h"
#include "server_Radiocontrolled.h"
#include "server_Worm.h"
#include "server_Stage.h"

/* Clase que representa el armamento de un jugador, el cual es compartido por
 * todos los gusanos de su equipo. Está conformado por la herramienta de
 * teletransportación, la dinamita y el teledirigido. Es no copiable.
 */
class Armory {
  private:
    Teletransportation teletransportation;
    Dynamite dynamite;
    Radiocontrolled radiocontrolled;
    Stage& stage;

    // No copiable
    Armory(const Armory&) = delete;
    Armory& operator=(const Armory&) = delete;

  public:
    // Constructor. Recibe el stage donde van a actuar todas las armas.
    Armory(Stage& a_stage);

    // Teletransporta el gusano recibido a la coordenada (x,y) recibida.
    // Si no tiene municiones devuelve false. En caso contrario, devuelve true.
    bool use_teletransportation(Worm* worm, float x, float y);

    // Devuelve el número de municiones de la teletransportación.
    size_t get_teletransportation_munitions();

    // Hace que el gusano recibido deje una dinamita. Si is_facing_right es True
    // entonces lo deja a la derecha, en caso contrario lo deja a la izquierda.
    // Devuelve false si no hay municiones o si ya está activa otra dinamita.
    bool use_dynamite(Worm* worm, bool is_facing_right);

    // Devuelve el numero de municiones de la dinamita.
    size_t get_dynamite_munitions();

    // Descuenta el tiempo recibido en milisegundos a la explosión de la
    // dinamita.
    void discount_dynamite_time(float t);

    // Devuelve un booleano indicando si la dinamita está activa.
    bool is_dynamite_active();

    // Pre: La dinamita debe estar activa
    // Devuelve un float indicando la posición horizontal de la dinamita activa.
    float get_dynamite_horizontal_position();

    // Pre: La dinamita debe estar activa
    // Devuelve un float indicando la posición vertical de la dinamita activa.
    float get_dynamite_vertical_position();

    // Devuelve un float indicando la cantidad de milisegundos restantes hasta
    // la explosión de la dinamita. En caso que no esté activa, devuelve 7000.
    float get_dynamite_time_to_explosion();


    // Utiliza el teledirigido centrado, si es posible, en la poisición x
    // recibida. Devuelve false si sigue activo el teledirigido.
    bool use_radiocontrolled(float x);

    // Devuelve un booleano indicando si el teledirigido está activo.
    bool is_radiocontrolled_active();

    // Devuelve un vector de pares (X,Y) con las posiciones actuales de todos los
    // proyectiles.
    std::vector<std::pair<float, float>> get_radiocontrolled_positions();


    // Verifica si algun proyectil está colisionando, y en caso que sea verdadero lo hace
    // explotar.
    void check_radiocontrolled_explosions();

    // Destructor.
    ~Armory();
};

#endif //__ARMORY_H__
