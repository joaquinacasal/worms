#include "client_YouWinMessage.h"

YouWinMessage::YouWinMessage(SdlTexture* message_texture, int time) : \
                        message_texture(message_texture), time_alive(time) {}

int YouWinMessage::render() {
    if (this->time_alive > 0) {
        this->message_texture->render();
        this->time_alive = this->time_alive - 1;
        if (this->time_alive == 0)
          this->set_message_texture(NULL);
    }
}

void YouWinMessage::set_message_texture(SdlTexture* message_texture){
    if (this->message_texture)
        delete this->message_texture;
    this->message_texture = message_texture;
}

void YouWinMessage::set_time_alive(int time){
    this->time_alive = time;
}

YouWinMessage::~YouWinMessage(){
    if (this->message_texture)
        delete this->message_texture;
}
