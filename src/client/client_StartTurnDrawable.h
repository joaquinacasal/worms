#ifndef __STARTTURNDRAWABLE__
#define __STARTTURNDRAWABLE__

#include "client_IDrawable.h"
#include "client_ConsoleDrawer.h"
class ConsoleDrawer;

class StartTurnDrawable : public IDrawable {
private:
    StartTurnDrawable(const StartTurnDrawable&) = delete;
    StartTurnDrawable& operator=(const StartTurnDrawable&) = delete;
public:
    StartTurnDrawable();

    void be_drawn_by_console(ConsoleDrawer* console_drawer);
};


#endif //__STARTTURNDRAWABLE__
