#ifndef __GAMETHREAD__
#define __GAMETHREAD__

#include "../common/common_Thread.h"
#include "server_TurnsManager.h"
#include "server_Stage.h"
#include "server_ServerThread.h"
#include "server_ClientHandler.h"
#include "../common/common_SafeQueue.h"
#include "server_IEvent.h"
#include "server_Armory.h"
#include "server_Worm.h"
#include "scenario_parser/YamlParser.h"
#include "scenario_parser/ScenarioDTO.h"
#include "scenario_parser/WormDTO.h"
#include "scenario_parser/BeamDTO.h"

#define TURN_LENGTH 60000
#define INITIAL_LIFE_POINTS 100

class ServerThread;

/* Clase que hereda de Thread que representa a un juego en su totalidad.
 * Crea la ronda de jugadores con sus gusanos y lee el mapa para construir el
 * escenario. Crea el ServerThread para aceptar a los jugadores.
 * Internamente ejecuta los steps del escenario.
 */
class GameThread : public Thread {
private:
    TurnsManager turns_manager;
    Stage* stage;
    ServerThread* server_thread;
    bool alive;
    bool has_been_connected;
    SafeQueue<IEvent*> safe_queue;
    int turn_chrono = TURN_LENGTH;

    GameThread(const GameThread &other) = delete;
    GameThread& operator=(const GameThread &other) = delete;
    void create_stage(string map_file, int number_players);
    void addClient(ClientHandler* client_handler);
    void send_stage_information_to_clients();
    void send_turn_time_information();
    void send_worms_information_to_clients();
    void send_weapon_information_to_clients();
    void notif_clients();

    void check_falling();
    void check_radiocontrolled_explosions();
public:
    // Recibe el puerto donde escuchará y el nombre del archivo
    // donde leerá las características del mapa.
    GameThread(const char* port, string map_file, int number_players);
    GameThread(GameThread&& other) = default;

    void start_connection();

    void run() override;
    void tick_turn();

    void stop();
    /* Indica si el hilo ya terminó su ejecución */
    bool is_alive() const;
    /* Indica si el hilo alguna vez inicio su ejecución */
    bool was_connected() const;

    void add_all_clients();

    void changeTurn();

    ~GameThread() override;
};



#endif
