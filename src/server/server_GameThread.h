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
#define MS_BETWEEN_TURNS 4000
#define TICK_TIME 20

class ServerThread;

/* Clase que hereda de Thread que representa a un juego en su totalidad.
 * Lee el mapa recibido por parámetro, y reparte los gusanos entre la cantidad
 * de jugadores indicada.
 * Crea el ServerThread para aceptar a los jugadores.
 * Internamente ejecuta los steps del escenario y maneja los turnos.
 * Por último, notifica a los clientes sobre la actualidad del juego.
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

    // No copiable.
    GameThread(const GameThread &other) = delete;
    GameThread& operator=(const GameThread &other) = delete;

    // Crea el escenario leyendo el mapa recibido por parámetro, en formato
    // YAML. Además, recibe la cantidad de jugadores para asignar los
    // gusanos y poder compensar con 25 puntos de vida a los jugadores que
    // tienen menos.
    void create_stage(string map_file, int number_players);

    // Le agrega al cliente recibido la cola protegida del game thread, para
    // que puedan encolar los eventos recibidos.
    void addClient(ClientHandler* client_handler);

    // Le envía la información pertinente del escenario a los clientes.
    void send_stage_information_to_clients();

    // Le envía la cantidad de milisegundos que faltan para finalizar el turno.
    void send_turn_time_information();

    // Le envía a los clientes la información pertinente de los gusanos
    // que sufrieron alguna modificación durante el tick.
    void send_worms_information_to_clients();

    // Le envía la información relacionada a las armas activas a los clientes.
    void send_weapon_information_to_clients();

    // Notifica a los clientes sobre toda la información pertinente del tick.
    void notif_clients();

    // Verifica si los gusanos cayeron de una distancia elevada, y en ese caso
    // se les descuenta la vida correspondiente.
    void check_falling();

    // Verifica si alguno los teledirigidos activos colisionó contra un objeto
    // y en ese caso dispara la explosión de esa munición.
    void check_radiocontrolled_explosions();

    // Ejecuta un turno del juego.
    void tick_turn();

    // Deja pasar algunos ticks del juego para que se acomoden los cuerpos.
    void deadTime();

    // Setea todos los gusanos como estáticos.
    void set_worms_as_immovable();

    // Chequea las muertes y envía las notificaciones correspondientes indicando
    // qué gusanos murieron. Recibe un vector de Worm*, con todos los gusanos
    // previos al evento que los pudo haber matado, y compara contra los que
    // están vivos actualmente.
    void check_deaths(std::vector<Worm*> initial_worms_alive);

    // Chequea la explosión de la dinamita y los gusanos afectados.
    void check_dynamite_explosion();
public:
    // Recibe el puerto donde escuchará y el nombre del archivo
    // donde leerá las características del mapa.
    GameThread(const char* port, string map_file, int number_players);
    GameThread(GameThread&& other) = default;

    // Le da start al server thread.
    void start_connection();

    void run() override;

    void stop();
    /* Indica si el hilo ya terminó su ejecución */
    bool is_alive() const;
    /* Indica si el hilo alguna vez inicio su ejecución */
    bool was_connected() const;

    // Agrega a todos los clientes activos, agregandoles una cola protegida
    // para que en ella encolen los eventos recibidos.
    void add_all_clients();

    // Cambia el turno, cambiando el jugador actual, y el gusano actual. Además
    // se notifica a los jugadores involucrados del comienzo/finalización de
    // su turno.
    void changeTurn();

    // Destructor.
    ~GameThread() override;
};



#endif
