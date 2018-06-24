#include "client_TurnMessage.h"

TurnMessage::TurnMessage(SdlTexture* message_texture, int time) :\
                         message_texture(message_texture), time_alive(time) {}

int TurnMessage::render() {
    if (this->time_alive > 0) {
        this->message_texture->render();
        this->time_alive = this->time_alive - 1;
        if (this->time_alive == 0)
          this->set_message_texture(NULL);
    }
}

void TurnMessage::set_message_texture(SdlTexture* message_texture){
    if (this->message_texture)
        delete this->message_texture;
    this->message_texture = message_texture;
}

void TurnMessage::set_time_alive(int time){
    this->time_alive = time;
}

TurnMessage::~TurnMessage(){
    if (this->message_texture)
        delete this->message_texture;
}
