#ifndef __PROTOCOLTRANSLATOR__
#define __PROTOCOLTRANSLATOR__

#include <string>
#include <vector>
#include "server_Player.h"
#include "events/server_IEvent.h"
#include "events/server_MoveRightEvent.h"
#include "events/server_MoveLeftEvent.h"
#include "events/server_StopMovingEvent.h"
#include "events/server_JumpForwardEvent.h"
#include "events/server_JumpBackwardEvent.h"
#include "events/server_TeletransportationEvent.h"
#include "events/server_RadiocontrolledEvent.h"
#include "events/server_DynamiteEvent.h"
#include "events/server_ClosedConnectionEvent.h"

#define PROTOCOL_CLOSED_CON 0x09
#define PROTOCOL_RIGHT_ARROW 0x01
#define PROTOCOL_LEFT_ARROW 0x02
#define PROTOCOL_STOP_MOVING 0x03
#define PROTOCOL_ENTER 0x04
#define PROTOCOL_BACKSPACE 0x05
#define PROTOCOL_TELETRANSPORTATION 0X06
#define PROTOCOL_DYMAMITE 0X07
#define PROTOCOL_RADIOCONTROLLED 0X08



/* Clase que se encarga de ejecutar los codigos recibidos y matchearlos a una
 * función del gusano.
 */
class ProtocolTranslator {
public:
    // Transforma el codigo recibido en un evento
    IEvent* translate(Player* player, char code);
    IEvent* translate(Player* player, char code, double x, double y);


    // Indica si el codigo recibido necesita coordenadas.
    bool need_coordinates(char code);
};

#endif //__PROTOCOLTRANSLATOR__
