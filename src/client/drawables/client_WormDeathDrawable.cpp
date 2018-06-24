#include "client_WormDeathDrawable.h"

WormDeathDrawable::WormDeathDrawable(size_t id, int team){
    this->id = id;
    this->team = team;
}

void WormDeathDrawable::be_drawn_by_console(ConsoleDrawer* console_drawer){
  console_drawer->draw(this);
}

void WormDeathDrawable::be_drawn(SdlWindow* window){
  window->draw(this);
}

size_t WormDeathDrawable::get_id(){
    return id;
}

int WormDeathDrawable::get_team(){
    return team;
}
