#ifndef __TELETRANSPORTATION_H__
#define __TELETRANSPORTATION_H__

#include <stdlib.h>
#include "server_Worm.h"

/* Clase que representa la herramienta de teletransportación, la cual
 * cambia la posición del gusano actual a la indicada por el usuario.
 * Tiene 5 municiones.
 */
class Teletransportation {
  private:
    int munitions = 5;
    bool was_used;

    // No copiable.
    Teletransportation(const Teletransportation&) = delete;
    Teletransportation& operator=(const Teletransportation&) = delete;
  public:
    // Constructor.
    Teletransportation();

    // Si la cantidad de municiones es 0, devuelve false sin cambiar nada.
    // Si tenía municiones, devuelve True y teletransporta el gusano a la
    // posición x e y recibidas, y reduce en 1 las municiones.
    bool teletransport_to(Worm* worm, int x, int y);

    // Devuelve la cantidad de municiones disponibles.
    int get_munitions();

    // Devuelve un booleano indicando si la teletransportacion fue utilizada
    // desde la última vez que se preguntó.
    bool was_teletransportation_used();
};

#endif //__TELETRANSPORTATION_H__
