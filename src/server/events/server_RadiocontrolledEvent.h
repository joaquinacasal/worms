#ifndef __RADIOCONTROLLEDEVENT__
#define __RADIOCONTROLLEDEVENT__

#include "server_IEvent.h"
#include "../server_Player.h"

// Hereda de IEvent. Activa el teledirigido en una coordenada indicada.
class RadiocontrolledEvent : public IEvent {
private:
    Player* player;
    double x;
    double y;

    RadiocontrolledEvent(const RadiocontrolledEvent&) = delete;
    RadiocontrolledEvent& operator=(const RadiocontrolledEvent&) = delete;
public:
    explicit RadiocontrolledEvent(Player* player, double x, double y);

    void run();

    ~RadiocontrolledEvent() = default;
};


#endif //__RADIOCONTROLLEDEVENT__
