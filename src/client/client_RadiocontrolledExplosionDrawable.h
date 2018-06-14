#ifndef __RADIOCONTROLLEDEXPLOSIONDRAWABLE__
#define __RADIOCONTROLLEDEXPLOSIONDRAWABLE__

#include "client_IDrawable.h"
#include "client_ConsoleDrawer.h"
#include "client_SdlWindow.h"
class SdlWindow;
class ConsoleDrawer;

class RadiocontrolledExplosionDrawable : public IDrawable {
private:
    size_t id;

    RadiocontrolledExplosionDrawable(const RadiocontrolledExplosionDrawable&) = delete;
    RadiocontrolledExplosionDrawable& operator=(const RadiocontrolledExplosionDrawable&) = delete;
public:
    RadiocontrolledExplosionDrawable(size_t id);

    void be_drawn_by_console(ConsoleDrawer* console_drawer);
    void be_drawn(SdlWindow* window);

    size_t get_id();
    ~RadiocontrolledExplosionDrawable() = default;
};


#endif //__RADIOCONTROLLEDEXPLOSIONDRAWABLE__
