#ifndef __DYNAMITEEXPLOSIONDRAWABLE__
#define __DYNAMITEEXPLOSIONDRAWABLE__

#include "client_IDrawable.h"
#include "client_ConsoleDrawer.h"
#include "client_SdlWindow.h"
class SdlWindow;
class ConsoleDrawer;

class DynamiteExplosionDrawable : public IDrawable {
private:
    DynamiteExplosionDrawable(const DynamiteExplosionDrawable&) = delete;
    DynamiteExplosionDrawable& operator=(const DynamiteExplosionDrawable&) = delete;
public:
    DynamiteExplosionDrawable();

    void be_drawn_by_console(ConsoleDrawer* console_drawer);
    void be_drawn(SdlWindow* window);

};


#endif //__DYNAMITEEXPLOSIONDRAWABLE__
