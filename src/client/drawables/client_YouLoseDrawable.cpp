#include "client_YouLoseDrawable.h"

YouLoseDrawable::YouLoseDrawable(){}

void YouLoseDrawable::be_drawn_by_console(ConsoleDrawer* console_drawer){
  console_drawer->draw(this);
}

void YouLoseDrawable::be_drawn(SdlWindow* window){
  window->draw(this);
}
