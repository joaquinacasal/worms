#include "server_ProtocolTranslator.h"

bool ProtocolTranslator::need_coordinates(char code){
  if (code == PROTOCOL_TELETRANSPORTATION) return true;
  if (code == PROTOCOL_RADIOCONTROLLED) return true;
  return false;
}

IEvent* ProtocolTranslator::translate(Player* player, char code){
  Worm* worm = player->get_selected_worm();
  switch (code) {
    case PROTOCOL_RIGHT_ARROW: return new MoveRightEvent(worm);
    case PROTOCOL_LEFT_ARROW: return new MoveLeftEvent(worm);
    case PROTOCOL_STOP_MOVING: return new StopMovingEvent(worm);
    case PROTOCOL_ENTER: return new JumpForwardEvent(worm);
    case PROTOCOL_BACKSPACE: return new JumpBackwardEvent(worm);
    case PROTOCOL_DYMAMITE: return new DynamiteEvent(player);
    case PROTOCOL_CLOSED_CON: return new ClosedConnectionEvent();
  }
  return NULL;
}

IEvent* ProtocolTranslator::translate(Player* player, char code, double x,\
                                                                double y){
  switch (code) {
    case PROTOCOL_TELETRANSPORTATION:
      return new TeletransportationEvent(player, x, y);
    case PROTOCOL_RADIOCONTROLLED:
      return new RadiocontrolledEvent(player, x, y);
  }
  return NULL;
}
