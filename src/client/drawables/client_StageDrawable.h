#ifndef __STAGEDRAWABLE__
#define __STAGEDRAWABLE__

#include "client_IDrawable.h"
#include <string>
#include "../client_ConsoleDrawer.h"
#include "../client_SdlWindow.h"
class SdlWindow;
class ConsoleDrawer;

class StageDrawable : public IDrawable {
private:
    size_t width;
    size_t height;
    std::string background;

    StageDrawable(const StageDrawable&) = delete;
    StageDrawable& operator=(const StageDrawable&) = delete;
public:
    StageDrawable(size_t width, size_t height, std::string background);
    void be_drawn_by_console(ConsoleDrawer* console_drawer);
    void be_drawn(SdlWindow* window);

    size_t get_width();
    size_t get_height();
    std::string get_background();
};


#endif //__STAGEDRAWABLE__
