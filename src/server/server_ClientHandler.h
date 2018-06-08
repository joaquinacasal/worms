#ifndef __CLIENTHANDLER__
#define __CLIENTHANDLER__

#include <string>
#include <vector>
#include "../common/common_Thread.h"
#include "../common/common_Socket.h"
#include "server_Player.h"
#include "../common/common_SocketProtocol.h"
#include "server_ProtocolTranslator.h"
#include "../common/common_SafeQueue.h"
#include "server_IEvent.h"

/* Clase que representa a un cliente del sistema.
 * Es un objecto activo, ya que cada cliente se ejecuta en paralelo.
 * Encapsula las acciones a ejecutar con cada cliente
 * (recibir y ejecutar un comando).
 */
class ClientHandler : public Thread {
private:
    SocketProtocol protocol;
    ProtocolTranslator protocol_translator;
    Player* player;
    bool alive;
    bool is_queue_enabled = false;
    SafeQueue<IEvent*>* safe_queue = NULL;


    ClientHandler(const ClientHandler &other) = delete;
    ClientHandler& operator=(const ClientHandler &other) = delete;

public:
    ClientHandler(Player* player, Socket&& socket);
    ClientHandler(ClientHandler&& other) = default;

    /* Lógica del cliente.
     * Recibe comandos y los ejecuta.
     */
    void run() override;

    void stop();

    /* Indica si el hilo ya terminó su ejecución */
    bool is_alive() const;

    void add_safe_queue(SafeQueue<IEvent*>* safe_queue);

    void send_worm_info(size_t id, size_t life_points, int x, int y, \
                                int angle, bool is_facing_right);

    void send_stage_info(size_t width, size_t height);
    void send_beam_info(int x, int y, int length, int width, int angle);
    void send_dynamite_info(int x, int y, int time_to_explosion);
    void send_radiocontrolled_info(int x, int y);
    void send_turn_time_info(int turn_chrono);
    void send_start_turn_notif();
    void send_end_turn_notif();
    void send_closed_connection_notif();

    // Indica al client Handler que puede encolar elementos a la cola de
    // eventos.
    void enable_queue();
    // Indica al client Handler que ya no puede encolar elementos a
    // la cola de eventos.
    void disable_queue();

    ~ClientHandler() override = default;
};


#endif
