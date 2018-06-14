#include <string>
#include <vector>
#include <cstring>
#include <syslog.h>
#include "common_SocketProtocol.h"

using std::string;
using std::vector;
using std::move;

SocketProtocol::SocketProtocol(const char *ip, const char *port) :
                                                socket(ip, port) {}

SocketProtocol::SocketProtocol(Socket &&other_socket) : socket(move(other_socket)) {}

void SocketProtocol::send_command_or_code(char command_or_code) {
    socket.send(&command_or_code, 1);
}

SocketProtocol &SocketProtocol::operator<<(char command_or_code) {
    send_command_or_code(command_or_code);
    return *this;
}

char SocketProtocol::receive_command_or_code() {
    char command;
    socket.receive(&command, 1);
    return command;
}

void SocketProtocol::send_numeric_value(int value) {
    uint32_t value_big_endian = htonl(value);
    char value_big_endian_char[PROTOCOL_LENGTHS_VALUE];
    memcpy(value_big_endian_char, &value_big_endian, PROTOCOL_LENGTHS_VALUE);
    socket.send(value_big_endian_char, PROTOCOL_LENGTHS_VALUE);
}

SocketProtocol &SocketProtocol::operator<<(int value) {
    send_numeric_value(value);
    return *this;
}

uint32_t SocketProtocol::receive_numeric_value() {
    char value_big_endian_char[PROTOCOL_LENGTHS_VALUE];
    socket.receive(value_big_endian_char, PROTOCOL_LENGTHS_VALUE);
    uint32_t value_big_endian;
    memcpy(&value_big_endian, value_big_endian_char, PROTOCOL_LENGTHS_VALUE);
    uint32_t value = ntohl(value_big_endian);
    return value;
}

char SocketProtocol::receive(){
    return receive_command_or_code();
}

void SocketProtocol::send_right_arrow(){
    send_command_or_code(PROTOCOL_RIGHT_ARROW);
}

void SocketProtocol::send_left_arrow(){
    send_command_or_code(PROTOCOL_LEFT_ARROW);
}

void SocketProtocol::send_stop_moving(){
    send_command_or_code(PROTOCOL_STOP_MOVING);
}

void SocketProtocol::send_enter(){
    send_command_or_code(PROTOCOL_ENTER);
}

void SocketProtocol::send_backspace(){
    send_command_or_code(PROTOCOL_BACKSPACE);
}

void SocketProtocol::send_teletransportation(int x, int y){
    send_command_or_code(PROTOCOL_TELETRANSPORTATION);
    send_numeric_value(x);
    send_numeric_value(y);
}

void SocketProtocol::send_radiocontrolled(int x, int y){
    send_command_or_code(PROTOCOL_RADIOCONTROLLED);
    send_numeric_value(x);
    send_numeric_value(y);
}


void SocketProtocol::send_dynamite(){
    send_command_or_code(PROTOCOL_DYMAMITE);
}

void SocketProtocol::send_turn_start(){
    send_command_or_code(PROTOCOL_TURN_START);
}

void SocketProtocol::send_turn_end(){
    send_command_or_code(PROTOCOL_TURN_END);
}

void SocketProtocol::send_worm_info(size_t id, size_t life_points, int x,\
              int y, int angle, bool is_facing_right){

    send_command_or_code(PROTOCOL_WORM_INFO);
    send_numeric_value((int)id);
    send_numeric_value((int)life_points);
    send_numeric_value(x);
    send_numeric_value(y);
    send_numeric_value(angle);
    if (is_facing_right) send_numeric_value(1);
    else send_numeric_value(0);
}

void SocketProtocol::send_beam_info(int x, int y, int length, int width, int angle){
    send_command_or_code(PROTOCOL_BEAM_INFO);
    send_numeric_value(x);
    send_numeric_value(y);
    send_numeric_value(length);
    send_numeric_value(width);
    send_numeric_value(angle);
}

void SocketProtocol::send_stage_info(int width, int height){
  send_command_or_code(PROTOCOL_STAGE_INFO);
  send_numeric_value(width);
  send_numeric_value(height);
  // TODO: mandar nombre de la foto de fondo
}

void SocketProtocol::send_dynamite_info(int x, int y, int time_to_explosion){
    send_command_or_code(PROTOCOL_DYMAMITE_INFO);
    send_numeric_value(x);
    send_numeric_value(y);
    send_numeric_value(time_to_explosion);
}

void SocketProtocol::send_dynamite_explosion_notif(){
    send_command_or_code(PROTOCOL_DYMAMITE_EXPLOSION);
}

void SocketProtocol::send_radiocontrolled_info(size_t id, int x, int y){
    send_command_or_code(PROTOCOL_RADIOCONTROLLED_INFO);
    send_numeric_value((int)id);
    send_numeric_value(x);
    send_numeric_value(y);
}

void SocketProtocol::send_start_turn_notif(){
  send_command_or_code(PROTOCOL_TURN_START);
}

void SocketProtocol::send_end_turn_notif(){
  send_command_or_code(PROTOCOL_TURN_END);
}

void SocketProtocol::send_turn_time_info(int turn_chrono){
  send_command_or_code(PROTOCOL_TURN_TIME);
  send_numeric_value(turn_chrono);
}

void SocketProtocol::send_closed_connection_notif(){
  send_command_or_code(PROTOCOL_CLOSED_CON);
}

void SocketProtocol::shutdown(int mode){
    socket.shutdown(mode);
}

SocketProtocol::~SocketProtocol() {
    try {
        socket.shutdown(SHUT_RDWR);
    }
    catch (std::exception& ex) {
        syslog(LOG_ERR, "%s", ex.what());
    }
}
