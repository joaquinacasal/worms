#ifndef __TURNTIMEDRAWABLE__
#define __TURNTIMEDRAWABLE__

#include "client_IDrawable.h"
#include "../client_ConsoleDrawer.h"
#include "../client_SdlWindow.h"
class SdlWindow;
class ConsoleDrawer;

class TurnTimeDrawable : public IDrawable {
private:
    double time_left;

    TurnTimeDrawable(const TurnTimeDrawable&) = delete;
    TurnTimeDrawable& operator=(const TurnTimeDrawable&) = delete;
public:
    explicit TurnTimeDrawable(double t);

    void be_drawn_by_console(ConsoleDrawer* console_drawer);
    void be_drawn(SdlWindow* window);
    double get_time_left();
};


#endif //__TURNTIMEDRAWABLE__
