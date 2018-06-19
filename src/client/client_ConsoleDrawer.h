#ifndef __CONSOLEDRAWER__
#define __CONSOLEDRAWER__

#include <string>
#include <vector>
#include "../common/common_Thread.h"
#include "../common/common_SafeQueue.h"

#include "client_IDrawable.h"
#include "client_BeamDrawable.h"
#include "client_ClosedConnectionDrawable.h"
#include "client_DynamiteDrawable.h"
#include "client_DynamiteExplosionDrawable.h"
#include "client_EndTurnDrawable.h"
#include "client_RadiocontrolledDrawable.h"
#include "client_StageDrawable.h"
#include "client_StartTurnDrawable.h"
#include "client_TurnTimeDrawable.h"
#include "client_WormDrawable.h"
#include "client_WormDeathDrawable.h"

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
    ConsoleDrawer(SafeQueue<IDrawable*>& _safe_queue);
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
