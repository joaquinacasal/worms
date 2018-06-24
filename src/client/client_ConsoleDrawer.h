#ifndef __CONSOLEDRAWER__
#define __CONSOLEDRAWER__

#include <string>
#include <vector>
#include "../common/common_Thread.h"
#include "../common/common_SafeQueue.h"

#include "drawables/client_IDrawable.h"
#include "drawables/client_BeamDrawable.h"
#include "drawables/client_ClosedConnectionDrawable.h"
#include "drawables/client_DynamiteDrawable.h"
#include "drawables/client_DynamiteExplosionDrawable.h"
#include "drawables/client_EndTurnDrawable.h"
#include "drawables/client_RadiocontrolledDrawable.h"
#include "drawables/client_StageDrawable.h"
#include "drawables/client_StartTurnDrawable.h"
#include "drawables/client_TurnTimeDrawable.h"
#include "drawables/client_WormDrawable.h"
#include "drawables/client_WormDeathDrawable.h"
#include "drawables/client_YouWinDrawable.h"
#include "drawables/client_MunitionsDrawable.h"

class IDrawable;
class BeamDrawable;
class ClosedConnectionDrawable;
class DynamiteDrawable;
class DynamiteExplosionDrawable;
class EndTurnDrawable;
class RadiocontrolledDrawable;
class RadiocontrolledExplosionDrawable;
class StageDrawable;
class StartTurnDrawable;
class TurnTimeDrawable;
class WormDrawable;
class WormDeathDrawable;
class YouWinDrawable;
class MunitionsDrawable;

/* Clase que representa al dibujador por consola. Saca los Drawables de una
 * protegida y los imprime por consola.
 */
class ConsoleDrawer : public Thread {
private:
    bool connected;
    SafeQueue<IDrawable*>& safe_queue;

    void draw(IDrawable* drawable);

    ConsoleDrawer(const ConsoleDrawer&) = delete;
    ConsoleDrawer& operator=(const ConsoleDrawer&) = delete;

public:
    explicit ConsoleDrawer(SafeQueue<IDrawable*>& _safe_queue);
    ConsoleDrawer(ConsoleDrawer&& other) = default;

    void draw(StartTurnDrawable* drawable);
    void draw(EndTurnDrawable* drawable);
    void draw(TurnTimeDrawable* drawable);
    void draw(WormDrawable* drawable);
    void draw(StageDrawable* drawable);
    void draw(BeamDrawable* drawable);
    void draw(DynamiteDrawable* drawable);
    void draw(DynamiteExplosionDrawable* drawable);
    void draw(RadiocontrolledDrawable* drawable);
    void draw(RadiocontrolledExplosionDrawable* drawable);
    void draw(WormDeathDrawable* drawable);
    void draw(YouWinDrawable* drawable);
    void draw(MunitionsDrawable* drawable);
    void draw(ClosedConnectionDrawable* drawable);

    /* Lógica del cliente.
     * Recibe comandos y los ejecuta.
     */
    void run() override;

    void stop();

    bool is_connected();

    ~ConsoleDrawer();
};


#endif // __CONSOLEDRAWER__
