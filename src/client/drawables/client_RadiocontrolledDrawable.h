#ifndef __RADIOCONTROLLEDDRAWABLE__
#define __RADIOCONTROLLEDDRAWABLE__

#include "client_IDrawable.h"
#include "../client_ConsoleDrawer.h"
#include "../client_SdlWindow.h"
class SdlWindow;
class ConsoleDrawer;

class RadiocontrolledDrawable : public IDrawable {
private:
    size_t id;
    double x;
    double y;

    RadiocontrolledDrawable(const RadiocontrolledDrawable&) = delete;
    RadiocontrolledDrawable& operator=(const RadiocontrolledDrawable&) = delete;
public:
    RadiocontrolledDrawable(size_t id, double x, double y);

    void be_drawn_by_console(ConsoleDrawer* console_drawer);
    void be_drawn(SdlWindow* window);

    size_t get_id();
    double get_x();
    double get_y();
    ~RadiocontrolledDrawable() = default;
};


#endif //__RADIOCONTROLLEDDRAWABLE__
