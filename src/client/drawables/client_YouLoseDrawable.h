#ifndef __YOULOSEDRAWABLE__
#define __YOULOSEDRAWABLE__

#include "client_IDrawable.h"
#include "../client_ConsoleDrawer.h"
#include "../client_SdlWindow.h"
class SdlWindow;
class ConsoleDrawer;

// Representación del mensaje que indica que el jugador perdió.
class YouLoseDrawable : public IDrawable {
private:
    YouLoseDrawable(const YouLoseDrawable&) = delete;
    YouLoseDrawable& operator=(const YouLoseDrawable&) = delete;
public:
    YouLoseDrawable();

    void be_drawn_by_console(ConsoleDrawer* console_drawer);
    void be_drawn(SdlWindow* window);
};


#endif //__YOULOSEDRAWABLE__
