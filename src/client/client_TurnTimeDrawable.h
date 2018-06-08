#ifndef __TURNTIMEDRAWABLE__
#define __TURNTIMEDRAWABLE__

#include "client_IDrawable.h"
#include "client_ConsoleDrawer.h"
class ConsoleDrawer;

class TurnTimeDrawable : public IDrawable {
private:
    double time_left;

    TurnTimeDrawable(const TurnTimeDrawable&) = delete;
    TurnTimeDrawable& operator=(const TurnTimeDrawable&) = delete;
public:
    TurnTimeDrawable(double t);

    void be_drawn_by_console(ConsoleDrawer* console_drawer);
    double get_time_left();
};


#endif //__TURNTIMEDRAWABLE__
