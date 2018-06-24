#include "client_DynamiteExplosionDrawable.h"

DynamiteExplosionDrawable::DynamiteExplosionDrawable(){}

void DynamiteExplosionDrawable::be_drawn_by_console(\
                                                ConsoleDrawer* console_drawer){
  console_drawer->draw(this);
}

void DynamiteExplosionDrawable::be_drawn(SdlWindow* window){
  window->draw(this);
}
