#ifndef __MOVERIGHTEVENT__
#define __MOVERIGHTEVENT__

#include "server_IEvent.h"
#include "../server_Worm.h"

// Hereda de IEvent. Mueve al gusano hacia la derecha.
class MoveRightEvent : public IEvent {
private:
    Worm* worm;
    MoveRightEvent(const MoveRightEvent&) = delete;
    MoveRightEvent& operator=(const MoveRightEvent&) = delete;
public:
    explicit MoveRightEvent(Worm* worm);

    void run();

    ~MoveRightEvent() = default;
};


#endif //__MOVERIGHTEVENT__
