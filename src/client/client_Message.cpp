#include "client_Message.h"

Message::Message(SdlTexture* message_texture, int time) :\
                         message_texture(message_texture), time_alive(time) {}

void Message::render(Camera& camera) {
    if (this->time_alive > 0 && this->message_texture) {
        Area old_area = this->message_texture->get_position();
        Area new_area = camera.get_center(old_area.getWidth(),\
                                            old_area.getHeight());
        this->message_texture->set_position(new_area.getX(), new_area.getY());
        this->message_texture->render();
        this->time_alive = this->time_alive - 1;
        if (this->time_alive == 0)
          this->set_message_texture(NULL);
    }
}

void Message::set_message_texture(SdlTexture* message_texture){
    if (this->message_texture)
        delete this->message_texture;
    this->message_texture = message_texture;
}

void Message::set_time_alive(int time){
    this->time_alive = time;
}

Message::~Message(){
    if (this->message_texture)
        delete this->message_texture;
}
