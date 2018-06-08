#include "client_StartTurnDrawable.h"

StartTurnDrawable::StartTurnDrawable(){}

void StartTurnDrawable::be_drawn_by_console(ConsoleDrawer* console_drawer){
  console_drawer->draw(this);
}
