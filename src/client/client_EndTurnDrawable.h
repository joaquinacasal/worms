#ifndef __ENDTURNDRAWABLE__
#define __ENDTURNDRAWABLE__

#include "client_IDrawable.h"
#include "client_ConsoleDrawer.h"
class ConsoleDrawer;

class EndTurnDrawable : public IDrawable {
private:
    EndTurnDrawable(const EndTurnDrawable&) = delete;
    EndTurnDrawable& operator=(const EndTurnDrawable&) = delete;
public:
    EndTurnDrawable();

    void be_drawn_by_console(ConsoleDrawer* console_drawer);
};


#endif //__ENDTURNDRAWABLE__
