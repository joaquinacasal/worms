#ifndef __YOUWINDRAWABLE__
#define __YOUWINDRAWABLE__

#include "client_IDrawable.h"
#include "../client_ConsoleDrawer.h"
#include "../client_SdlWindow.h"
class SdlWindow;
class ConsoleDrawer;

class YouWinDrawable : public IDrawable {
private:
    YouWinDrawable(const YouWinDrawable&) = delete;
    YouWinDrawable& operator=(const YouWinDrawable&) = delete;
public:
    YouWinDrawable();

    void be_drawn_by_console(ConsoleDrawer* console_drawer);
    void be_drawn(SdlWindow* window);
};


#endif //__YOUWINDRAWABLE__
