#ifndef __CLOSEDCONNECTIONDRAWABLE__
#define __CLOSEDCONNECTIONDRAWABLE__

#include "client_IDrawable.h"
#include "client_ConsoleDrawer.h"
#include "client_SdlWindow.h"
class SdlWindow;
class ConsoleDrawer;

class ClosedConnectionDrawable : public IDrawable {
private:
    ClosedConnectionDrawable(const ClosedConnectionDrawable&) = delete;
    ClosedConnectionDrawable& operator=(const ClosedConnectionDrawable&) =\
                                                                        delete;
public:
    ClosedConnectionDrawable();

    void be_drawn_by_console(ConsoleDrawer* console_drawer);
    void be_drawn(SdlWindow* window);
};


#endif //__CLOSEDCONNECTIONDRAWABLE__
