#ifndef __SERVERTHREAD__
#define __SERVERTHREAD__

#include <vector>
#include "../common/common_Socket.h"
#include "../common/common_Thread.h"
#include "server_ClientHandler.h"
#include "server_TurnsManager.h"
#include "server_GameThread.h"
#include "server_Player.h"
#include "../common/common_SafeQueue.h"
#include "events/server_IEvent.h"
#include "server_NotifierThread.h"
#include <string>
using std::vector;

class GameThread;

/* Clase que representa al servidor del juego. Permite aceptar nuevos clientes
 * y enviarles diferentes notificaciones.
 * Es un objeto activo, ya que se ejecuta en paralelo al hilo principal,
 * para que este pueda recibir una señal de cierre del servidor.
 */
class ServerThread : public Thread {
private:
    Socket socket;
    vector<ClientHandler*> clients;
    size_t actual_turn = 0;
    bool keep_running;
    TurnsManager& turns_manager;
    GameThread& game_thread;
    NotifierThread notifier;

    ServerThread(const ServerThread &other) = delete;
    ServerThread& operator=(const ServerThread &other) = delete;

    void startTurn(ClientHandler* client);
    void finishTurn(ClientHandler* client);

public:
    ServerThread(const char* port, TurnsManager& turns_manager, GameThread& gt);

    /* Lógica del servidor.
     * Acepta nuevos clientes hasta llegar al numero de jugadores necesario.
     */
    void run() override;

    /* Envía una señal al lservidor para que deje de ejecutarse */
    void stop();

    // Le da start al a todos los clientes y los habilita para recibir eventos.
    void start_clients();

    // Devuelve una lista de todos los clientes conectados.
    vector<ClientHandler*>* get_all_connected_clients();

    // Envía la información de un gusano (id, puntos de vida, posición, angulo}
    // y para qué lado está mirando) a todos los clientes.
    void send_worm_information_to_clients(size_t id, size_t life_points,\
                                          double x, double y, int angle, \
                                          bool is_facing_right, int team,\
                                          int movement_state,\
                                          bool is_the_selected_worm);

    // Envía la notificación de que el gusano con id recibido murió.
    void send_worm_death_notif_to_clients(size_t id, int team);

    // Envía la información pertinente del escenario (ancho y largo) a todos
    // los clientes.
    void send_stage_information_to_clients(int width, int height, \
                                           std::string background);

    // Envía el tiempo restante hasta finalizar el turno en ms a todos los
    // clientes.
    void send_turn_time_information_to_clients(int turn_chrono);

    // Envía la información de una viga (posición, ancho, alto y ángulo) a
    // todos los clientes.
    void send_beam_information_to_clients(double x, double y, int length,\
                                          int width, int angle);

    // Envía la información de la dinamita activa (posición y tiempo hasta
    // la explosión) a todos los clientes.
    void send_dynamite_information_to_clients(double x, double y, \
                                                    int time_to_explosion);


    // Envía una notificación informando que la dinamita explotó.
    void send_dynamite_explosion_to_clients();

    // Envía la información (posición) de una munición del teledirigido
    // a todos los clientes.
    void send_radiocontrolled_information_to_clients(size_t id,\
                                                     double x, double y);

    // Envía la notificación de explosión del teledirigido con id recibido.
    void send_radiocontrolled_explosion_to_clients(size_t id);

    // Envía la cantidad de municiones de cada arma.
    void send_munitions_info(int dynamite_m, int radiocontrolled_m, \
                             int teletransportation_m);

    // Envía la información de las municiones disponibles de cada arma a todos
    // los jugadores.
    void send_munitions_info_to_all_clients();

    // Envía una notificiación indicando que el jugador actual gano el juego.
    void send_you_win_notif();

    // Envía una notificiación indicando que el jugador recibido perdió.
    void send_you_lose_notif(Player* player);

    // Envía una notificiación para cerrar la conexión a todos los clientes.
    void send_closed_connection_notif();

    // Devuelve un booleano indicando si el hilo sigue vivo.
    bool is_alive();

    // Cambia el turno, cambiando el jugador actual, y el gusano actual. Además
    // se notifica a los jugadores involucrados del comienzo/finalización de
    // su turno.
    void changeTurn();

    ~ServerThread() override;
};


#endif
