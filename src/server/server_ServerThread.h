#ifndef __SERVERTHREAD__
#define __SERVERTHREAD__

#include <vector>
#include "../common/common_Socket.h"
#include "../common/common_Thread.h"
#include "server_ClientHandler.h"
#include "server_TurnsManager.h"
#include "server_GameThread.h"
#include "../common/common_SafeQueue.h"
#include "server_IEvent.h"
#include "server_NotifierThread.h"
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
    void send_worm_information_to_clients(size_t id, size_t life_points, int x,\
                                int y, int angle, bool is_facing_right);

    // Envía la información pertinente del escenario (ancho y largo) a todos
    // los clientes.
    void send_stage_information_to_clients(int width, int height);

    // Envía el tiempo restante hasta finalizar el turno en ms a todos los
    // clientes.
    void send_turn_time_information_to_clients(int turn_chrono);

    // Envía la información de una viga (posición, ancho, alto y ángulo) a
    // todos los clientes.
    void send_beam_information_to_clients(int x, int y, int length, int width,\
                                                            int angle);

    // Envía la información de la dinamita activa (posición y tiempo hasta
    // la explosión) a todos los clientes.
    void send_dynamite_information_to_clients(int x, int y, \
                                                    int time_to_explosion);


    // Envía una notificación informando que la dinamita explotó.
    void send_dynamite_explosion_to_clients();

    // Envía la información (posición) de una munición del teledirigido
    // a todos los clientes.
    void send_radiocontrolled_information_to_clients(int x, int y);

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
