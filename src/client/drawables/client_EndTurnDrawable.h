#ifndef __ENDTURNDRAWABLE__
#define __ENDTURNDRAWABLE__

#include "client_IDrawable.h"
#include "../client_ConsoleDrawer.h"
#include "../client_SdlWindow.h"
class SdlWindow;
class ConsoleDrawer;

class EndTurnDrawable : public IDrawable {
private:
    EndTurnDrawable(const EndTurnDrawable&) = delete;
    EndTurnDrawable& operator=(const EndTurnDrawable&) = delete;
public:
    EndTurnDrawable();

    void be_drawn_by_console(ConsoleDrawer* console_drawer);
    void be_drawn(SdlWindow* window);
};


#endif //__ENDTURNDRAWABLE__
