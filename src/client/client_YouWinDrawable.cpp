#include "client_YouWinDrawable.h"

YouWinDrawable::YouWinDrawable(){}

void YouWinDrawable::be_drawn_by_console(ConsoleDrawer* console_drawer){
  console_drawer->draw(this);
}

void YouWinDrawable::be_drawn(SdlWindow* window){
  window->draw(this);
}
