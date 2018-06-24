#include "client_RadiocontrolledExplosionDrawable.h"

RadiocontrolledExplosionDrawable::RadiocontrolledExplosionDrawable(size_t id){
    this->id = id;
}

void RadiocontrolledExplosionDrawable::be_drawn_by_console(\
                                                ConsoleDrawer* console_drawer){
  console_drawer->draw(this);
}

void RadiocontrolledExplosionDrawable::be_drawn(SdlWindow* window){
  window->draw(this);
}

size_t RadiocontrolledExplosionDrawable::get_id(){
    return id;
}
