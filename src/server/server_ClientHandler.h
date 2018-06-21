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
 * Es un objeto activo, ya que cada cliente se ejecuta en paralelo.
 * Encapsula las acciones a ejecutar con cada cliente
 * (recibir y ejecutar un comando). Es no copiable. Se encarga de enviar
 * notificaciones al cliente y recibir los eventos que éste envía y encolarlos
 * en una cola protegida.
 */
class ClientHandler : public Thread {
private:
    SocketProtocol protocol;
    ProtocolTranslator protocol_translator;
    Player* player;
    bool alive;
    bool is_queue_enabled = false;
    SafeQueue<IEvent*>* safe_queue = NULL;

    // No copiable.
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

    // Agrega una safe queue, en la cual va a agregar los eventos recibidos.
    void add_safe_queue(SafeQueue<IEvent*>* safe_queue);

    // Envía la información de un gusano (id, puntos de vida, posición, angulo}
    // y para qué lado está mirando).
    void send_worm_info(size_t id, size_t life_points, double x, double y, \
                                int angle, bool is_facing_right, int team);

    // Envía una notificación indicando que el gusano con el id recibido murió.
    void send_worm_death_notif(size_t id, int team);

    // Envía la información pertinente del escenario (ancho y largo e
    // imagen de fondo).
    void send_stage_info(size_t width, size_t height, std::string background);

    // Envía la información de una viga (posición, ancho, alto y ángulo).
    void send_beam_info(double x, double y, int length, int width, int angle);

    // Envía la información de la dinamita activa (posición y tiempo hasta
    // la explosión).
    void send_dynamite_info(double x, double y, int time_to_explosion);

    // Envía una notificación avisando que la dinamita explotó.
    void send_dynamite_explosion_notif();

    // Envía la información (posición) de una munición del teledirigido.
    void send_radiocontrolled_info(size_t id, double x, double y);

    // Notificación sobre la explosión del teledirigido con el id recibido.
    void send_radiocontrolled_explosion_info(size_t id);

    // Envía el tiempo restante hasta finalizar el turno en ms.
    void send_turn_time_info(int turn_chrono);

    // Envía una notificación indicando que inició el turno.
    void send_start_turn_notif();

    // Envía una notificación indicando que finalizó el turno.
    void send_end_turn_notif();

    // Envía una notificación indicando que se cerró la conexión desde el
    // servidor.
    void send_closed_connection_notif();

    // Indica al client Handler que puede encolar elementos a la cola de
    // eventos.
    void enable_queue();
    // Indica al client Handler que ya no puede encolar elementos a
    // la cola de eventos.
    void disable_queue();

    Player* get_player();

    ~ClientHandler() override = default;
};


#endif
