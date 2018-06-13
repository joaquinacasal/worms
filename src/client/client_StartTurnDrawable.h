#ifndef __STARTTURNDRAWABLE__
#define __STARTTURNDRAWABLE__

#include "client_IDrawable.h"
#include "client_ConsoleDrawer.h"
#include "client_SdlWindow.h"
class SdlWindow;
class ConsoleDrawer;

class StartTurnDrawable : public IDrawable {
private:
    StartTurnDrawable(const StartTurnDrawable&) = delete;
    StartTurnDrawable& operator=(const StartTurnDrawable&) = delete;
public:
    StartTurnDrawable();

    void be_drawn_by_console(ConsoleDrawer* console_drawer);
    void be_drawn(SdlWindow* window);
};


#endif //__STARTTURNDRAWABLE__
