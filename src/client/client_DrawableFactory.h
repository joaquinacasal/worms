#ifndef __DRAWABLEFACTORY_H__
#define __DRAWABLEFACTORY_H__

#include <string>
#include <vector>
#include "../common/common_Thread.h"
#include "../common/common_SocketProtocol.h"
#include "../common/common_SafeQueue.h"

#include "client_IDrawable.h"
#include "client_BeamDrawable.h"
#include "client_ClosedConnectionDrawable.h"
#include "client_DynamiteDrawable.h"
#include "client_EndTurnDrawable.h"
#include "client_RadiocontrolledDrawable.h"
#include "client_StageDrawable.h"
#include "client_StartTurnDrawable.h"
#include "client_TurnTimeDrawable.h"
#include "client_WormDrawable.h"

/* Clase que representa a una fábrica de objetos Drawable, recibe
 * por socket la información necesaria y los encola en la cola protegida.
 */

 #define PROTOCOL_CLOSED_CON 0x09
 #define PROTOCOL_TURN_START 0x30
 #define PROTOCOL_TURN_END 0x31
 #define PROTOCOL_TURN_TIME 0x32
 #define PROTOCOL_WORM_INFO 0x40
 #define PROTOCOL_STAGE_INFO 0x50
 #define PROTOCOL_DYMAMITE_INFO 0x60
 #define PROTOCOL_RADIOCONTROLLED_INFO 0x70
 #define METERS_TO_PIXELS_CONVERSION 1

 class IDrawable;
 class BeamDrawable;
 class ClosedConnectionDrawable;
 class DynamiteDrawable;
 class EndTurnDrawable;
 class RadiocontrolledDrawable;
 class StageDrawable;
 class StartTurnDrawable;
 class TurnTimeDrawable;
 class WormDrawable;

class DrawableFactory : public Thread {
private:
    SocketProtocol& socket_protocol;
    SafeQueue<IDrawable*>& safe_queue;
    bool connected;
    double scenario_heigth;

    void create_start_turn_drawable();
    void create_end_turn_drawable();
    void create_turn_time_drawable();
    void create_worm_drawable();
    void create_stage_drawable();
    void create_beam_drawable();
    void create_dynamite_drawable();
    void create_radiocontrolled_drawable();
    void create_closed_connection_drawable();

    void create_drawable();
    double adapt_y_coordinate(double y);
    double meters_to_pixels(double meters);

    DrawableFactory(const DrawableFactory&) = delete;
    DrawableFactory& operator=(const DrawableFactory&) = delete;
public:
    DrawableFactory(SocketProtocol& sp, SafeQueue<IDrawable*>& _safe_queue);
    DrawableFactory(DrawableFactory&& other) = default;

    /* Lógica del cliente.
     * Recibe comandos y crea los Drawables.
     */
    void run() override;

    void stop();

    bool is_connected();

    double get_scenario_heigth();

    ~DrawableFactory() override = default;
};


#endif //__DRAWABLEFACTORY_H__
