#ifndef __SOCKETPROTOCOL__
#define __SOCKETPROTOCOL__

#include <string>
#include <vector>
#include "common_Socket.h"

#define PROTOCOL_LENGTHS_VALUE 4
#define PROTOCOL_CLOSED_CON 0x09

// Send by client
#define PROTOCOL_RIGHT_ARROW 0x01
#define PROTOCOL_LEFT_ARROW 0x02
#define PROTOCOL_STOP_MOVING 0x03
#define PROTOCOL_ENTER 0x04
#define PROTOCOL_BACKSPACE 0x05
#define PROTOCOL_TELETRANSPORTATION 0X06
#define PROTOCOL_DYMAMITE 0X07
#define PROTOCOL_RADIOCONTROLLED 0X08


// Send by server
#define PROTOCOL_TURN_START 0x30
#define PROTOCOL_TURN_END 0x31
#define PROTOCOL_TURN_TIME 0x32

#define PROTOCOL_WORM_INFO 0x40

#define PROTOCOL_STAGE_INFO 0x50
#define PROTOCOL_BEAM_INFO 0x51

#define PROTOCOL_DYMAMITE_INFO 0x60
#define PROTOCOL_DYMAMITE_EXPLOSION 0x61
#define PROTOCOL_RADIOCONTROLLED_INFO 0x70




/* Clase protocolo que abstrae al sistema de como se realiza la
 * comunicación entre los clientes y el servidor.
 * Esta implementación particular utiliza un socket para la comunicación
 */
class SocketProtocol {
private:
    Socket socket;


    /* Recibe un caracter (que debería representar un comando o un código)
     * a través del socket.
     */
    char receive_command_or_code();
    /* Envía un caracter (que debería representar un comando o un código)
     * a través del socket.
     */
    void send_command_or_code(char command_or_code);

    /* Envía un caracter (que debería representar un comando o un código)
     * a través del socket.
     */
    SocketProtocol& operator<<(char command_or_code);


    SocketProtocol(const SocketProtocol &other) = delete;
    SocketProtocol& operator=(const SocketProtocol &other) = delete;

    /* Envía un número a través del socket */
    void send_numeric_value(int value);

    /* Envía un número a través del socket */
    SocketProtocol& operator<<(int value);


public:
    /* Constructor que se conecta a la ip y puerto indicados */
    SocketProtocol(const char* ip, const char* port);

    /* Constructor que utiliza el socket recibido para la comunicación */
    explicit SocketProtocol(Socket&& other_socket);

    SocketProtocol(SocketProtocol&& other) noexcept = default;

    /* Devuelve el código recibido a través del socket */
    char receive();

    /* Envía el cliente */
    void send_right_arrow();
    void send_left_arrow();
    void send_stop_moving();
    void send_enter();
    void send_backspace();
    void send_teletransportation(int x, int y);
    void send_dynamite();
    void send_radiocontrolled(int x, int y);

    /* Envía el servidor*/
    void send_turn_start();
    void send_turn_end();
    void send_worm_info(size_t id, size_t life_points, int x, int y, \
                        int angle, bool is_facing_right);
    void send_beam_info(int x, int y, int length, int width, int angle);
    void send_stage_info(int width, int height);
    void send_dynamite_info(int x, int y, int time_to_explosion);
    void send_dynamite_explosion_notif();
    void send_radiocontrolled_info(size_t id, int x, int y);
    void send_start_turn_notif();
    void send_end_turn_notif();
    void send_turn_time_info(int turn_chrono);

    // Envían ambos
    void send_closed_connection_notif();

    /* Recibe un número a través del socket */
    uint32_t receive_numeric_value();

    void shutdown(int mode);
    ~SocketProtocol();
};

#endif
