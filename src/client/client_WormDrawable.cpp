#include "client_WormDrawable.h"

WormDrawable::WormDrawable(size_t id, size_t life_points, double x, double y,\
              int angle, bool is_facing_right){
    this->id = id;
    this->life_points = life_points;
    this->x = x;
    this->y = y;
    this->angle = angle;
    this->is_facing_right = is_facing_right;
}

void WormDrawable::be_drawn_by_console(ConsoleDrawer* console_drawer){
  console_drawer->draw(this);
}

size_t WormDrawable::get_id(){
    return id;
}

size_t WormDrawable::get_life_points(){
    return life_points;
}

double WormDrawable::get_x(){
    return x;
}

double WormDrawable::get_y(){
    return y;
}

int WormDrawable::get_angle(){
    return angle;
}

bool WormDrawable::get_is_facing_right(){
    return is_facing_right;
}
