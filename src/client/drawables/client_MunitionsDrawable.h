#ifndef __MUNITIONSDRAWABLE__
#define __MUNITIONSDRAWABLE__

#include "client_IDrawable.h"
#include "../client_ConsoleDrawer.h"
#include "../client_SdlWindow.h"
class SdlWindow;
class ConsoleDrawer;

class MunitionsDrawable : public IDrawable {
private:
    int dynamite_m;
    int radiocontrolled_m;
    int teletransportation_m;

    MunitionsDrawable(const MunitionsDrawable&) = delete;
    MunitionsDrawable& operator=(const MunitionsDrawable&) = delete;
public:
    MunitionsDrawable(int dynamite_m, int radiocontrolled_m, \
                      int teletransportation_m);

    void be_drawn_by_console(ConsoleDrawer* console_drawer);
    void be_drawn(SdlWindow* window);

    int get_dynamite_munitions();
    int get_radiocontrolled_munitions();
    int get_teletransportation_munitions();
    ~MunitionsDrawable() = default;
};


#endif //__DYNAMITEDRAWABLE__
