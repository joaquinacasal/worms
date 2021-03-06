#ifndef __DRAWABLEFACTORY_H__
#define __DRAWABLEFACTORY_H__

#include <string>
#include <vector>
#include "../../common/common_Thread.h"
#include "../../common/common_SocketProtocol.h"
#include "../../common/common_SafeQueue.h"

#include "client_IDrawable.h"
#include "client_BeamDrawable.h"
#include "client_ClosedConnectionDrawable.h"
#include "client_DynamiteDrawable.h"
#include "client_EndTurnDrawable.h"
#include "client_RadiocontrolledDrawable.h"
#include "client_RadiocontrolledExplosionDrawable.h"
#include "client_StageDrawable.h"
#include "client_StartTurnDrawable.h"
#include "client_TurnTimeDrawable.h"
#include "client_WormDrawable.h"
#include "client_WormDeathDrawable.h"
#include "client_YouWinDrawable.h"
#include "client_YouLoseDrawable.h"
#include "client_MunitionsDrawable.h"

/* Clase que representa a una fábrica de objetos Drawable, recibe por socket
 * la información necesaria (código + datos si son necesarios) y los encola en
 * la cola protegida, que luego serán extraídos en el drawer que se esté
 * utilizando.
 */

 #define PROTOCOL_CLOSED_CON 0x09
 #define PROTOCOL_YOU_WIN_NOTIF 0x10
 #define PROTOCOL_YOU_LOSE_NOTIF 0x11
 #define PROTOCOL_TURN_START 0x30
 #define PROTOCOL_TURN_END 0x31
 #define PROTOCOL_TURN_TIME 0x32
 #define PROTOCOL_WORM_INFO 0x40
 #define PROTOCOL_WORM_DEATH_NOTIF 0x41
 #define PROTOCOL_STAGE_INFO 0x50
 #define PROTOCOL_DYMAMITE_INFO 0x60
 #define PROTOCOL_DYMAMITE_EXPLOSION 0x61
 #define PROTOCOL_MUNITIONS_INFO 0x65
 #define PROTOCOL_RADIOCONTROLLED_INFO 0x70
 #define PROTOCOL_RADIOCONTROLLED_EXPLOSION_INFO 0x71

 #define METERS_TO_PIXELS_CONVERSION 5

 class IDrawable;
 class BeamDrawable;
 class ClosedConnectionDrawable;
 class DynamiteDrawable;
 class EndTurnDrawable;
 class RadiocontrolledDrawable;
 class RadiocontrolledExplosionDrawable;
 class StageDrawable;
 class StartTurnDrawable;
 class TurnTimeDrawable;
 class WormDrawable;
 class WormDeathDrawable;
 class YouWinDrawable;
 class YouLoseDrawable;
 class MunitionsDrawable;

class DrawableFactory : public Thread {
private:
    SocketProtocol& socket_protocol;
    SafeQueue<IDrawable*>& safe_queue;
    bool connected;
    double scenario_height;

    void create_start_turn_drawable();
    void create_end_turn_drawable();
    void create_turn_time_drawable();
    void create_worm_drawable();
    void create_worm_death_drawable();
    void create_stage_drawable();
    void create_beam_drawable();
    void create_dynamite_drawable();
    void create_dynamite_explosion_drawable();
    void create_radiocontrolled_drawable();
    void create_radiocontrolled_explosion_drawable();
    void create_you_win_drawable();
    void create_you_lose_drawable();
    void create_munitions_drawable();
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

    double get_scenario_height();

    ~DrawableFactory() override = default;
};


#endif //__DRAWABLEFACTORY_H__
