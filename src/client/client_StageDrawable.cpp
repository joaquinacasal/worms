#include "client_StageDrawable.h"

StageDrawable::StageDrawable(size_t width, size_t height, std::string background){
    this->width = width;
    this->height = height;
    this->background = background;
}

void StageDrawable::be_drawn_by_console(ConsoleDrawer* console_drawer){
  console_drawer->draw(this);
}

void StageDrawable::be_drawn(SdlWindow* window){
  window->draw(this);
}

size_t StageDrawable::get_width(){
    return this->width;
}

size_t StageDrawable::get_height(){
    return this->height;
}

std::string StageDrawable::get_background(){
    return this->background;
}
