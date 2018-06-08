#ifndef __DYNAMITEDRAWABLE__
#define __DYNAMITEDRAWABLE__

#include "client_IDrawable.h"
#include "client_ConsoleDrawer.h"
class ConsoleDrawer;

class DynamiteDrawable : public IDrawable {
private:
    double x;
    double y;
    double time_to_explosion;

    DynamiteDrawable(const DynamiteDrawable&) = delete;
    DynamiteDrawable& operator=(const DynamiteDrawable&) = delete;
public:
    DynamiteDrawable(double x, double y, double time_to_explosion);

    void be_drawn_by_console(ConsoleDrawer* console_drawer);

    double get_x();
    double get_y();
    double get_time_to_explosion();
    ~DynamiteDrawable() = default;
};


#endif //__DYNAMITEDRAWABLE__
