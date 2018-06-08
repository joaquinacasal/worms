#ifndef __BEAMDRAWABLE__
#define __BEAMDRAWABLE__

#include "client_IDrawable.h"
#include "client_ConsoleDrawer.h"
class ConsoleDrawer;

class BeamDrawable : public IDrawable {
private:
    double x;
    double y;
    int length;
    int width;
    int angle;

    BeamDrawable(const BeamDrawable&) = delete;
    BeamDrawable& operator=(const BeamDrawable&) = delete;
public:
    BeamDrawable(double x, double y, int length, int width, int angle);

    void be_drawn_by_console(ConsoleDrawer* console_drawer);

    double get_x();
    double get_y();
    int get_length();
    int get_width();
    int get_angle();
    ~BeamDrawable() = default;
};


#endif //__BEAMDRAWABLE__
