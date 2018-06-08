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

/* Clase que representa al servidor del sistema de versionado.
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

    /* Envía una señal al servidor para que deje de ejecutarse */
    void stop();

    void start_clients();

    vector<ClientHandler*>* get_all_connected_clients();
    void send_worm_information_to_clients(size_t id, size_t life_points, int x,\
                                int y, int angle, bool is_facing_right);

    void send_stage_information_to_clients(int width, int height);
    void send_turn_time_information_to_clients(int turn_chrono);
    void send_beam_information_to_clients(int x, int y, int length, int width, int angle);
    void send_dynamite_information_to_clients(int x, int y, int time_to_explosion);
    void send_radiocontrolled_information_to_clients(int x, int y);
    void send_closed_connection_notif();

    bool is_alive();
    void changeTurn();

    ~ServerThread() override;
};


#endif
