#include "client_ClosedConnectionDrawable.h"

ClosedConnectionDrawable::ClosedConnectionDrawable(){}

void ClosedConnectionDrawable::be_drawn_by_console(ConsoleDrawer* console_drawer){
  console_drawer->draw(this);
}

void ClosedConnectionDrawable::be_drawn(SdlWindow* window){
  window->draw(this);
}
