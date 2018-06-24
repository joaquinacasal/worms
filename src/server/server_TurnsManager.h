#ifndef __TURNSMANAGER_H__
#define __TURNSMANAGER_H__

#include "server_Player.h"
#include <stdlib.h>
#include <vector>

/* Clase que representa el manejador de turnos del juego. Tiene una lista de
 * los jugadores y organiza de quién es el turno actual y quién le sigue.
 * Es no copiable.
 */
class TurnsManager {
private:
  std::vector<Player*> players;
  size_t selected_index;

  // No copiable
  TurnsManager(const TurnsManager&) = delete;
  TurnsManager& operator=(const TurnsManager&) = delete;

public:
  // Constructor.
  TurnsManager();

  // Agrega el jugador apuntado por el puntero a la ronda de turnos.
  void add_player(Player* player);

  // Devuelve un puntero al jugador del cual es el turno actual.
  Player* get_selected_player();

  // Finaliza el turno del jugador actual, y actualiza de quién es el turno
  // ahora.
  void finish_turn();

  // Devuelve el numero de jugadores que siguen vivos.
  size_t get_number_players_alive();

  // Devuelve el numero total de jugadores.
  size_t get_number_players();

  // Devuelve un vector de todos los jugadores del juego.
  std::vector<Player*> get_players();

  // Devuelve el equipo al que pertenece el gusano recibido.
  int get_team_of_worm(Worm* worm);

  // Destructor.
  ~TurnsManager();
};

#endif
