#include "client_EndTurnDrawable.h"

EndTurnDrawable::EndTurnDrawable(){}

void EndTurnDrawable::be_drawn_by_console(ConsoleDrawer* console_drawer){
  console_drawer->draw(this);
}

void EndTurnDrawable::be_drawn(SdlWindow* window){
  window->draw(this);
}
