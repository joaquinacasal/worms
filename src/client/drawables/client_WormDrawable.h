#ifndef __WORMDRAWABLE__
#define __WORMDRAWABLE__

#include "client_IDrawable.h"
#include <string>
#include "../client_ConsoleDrawer.h"
#include "../client_SdlWindow.h"
class SdlWindow;
class ConsoleDrawer;

// Representación de un gusano.
class WormDrawable : public IDrawable {
private:
    size_t id;
    size_t life_points;
    double x;
    double y;
    int angle;
    bool is_facing_right;
    int team;
    int movement_state;
    bool _is_the_selected_worm;

    WormDrawable(const WormDrawable&) = delete;
    WormDrawable& operator=(const WormDrawable&) = delete;

public:
    WormDrawable(size_t id, size_t life_points, double x, double y, int angle,\
                 bool is_facing_right, int team, int movement_state, \
                 bool is_the_selected_worm);

    void be_drawn_by_console(ConsoleDrawer* console_drawer);
    void be_drawn(SdlWindow* window);

    size_t get_id();
    size_t get_life_points();
    double get_x();
    double get_y();
    int get_angle();
    bool get_is_facing_right();
    int get_team();

    bool is_flying();
    bool is_moving();
    bool is_still();
    bool is_the_selected_worm();
    ~WormDrawable() = default;
};


#endif //__WORMDRAWABLE__
