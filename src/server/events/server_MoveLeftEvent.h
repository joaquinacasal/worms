#ifndef __MOVELEFTEVENT__
#define __MOVELEFTEVENT__

#include "server_IEvent.h"
#include "../server_Worm.h"

// Hereda de IEvent. Mueve al gusano hacia la izquierda.
class MoveLeftEvent : public IEvent {
private:
    Worm* worm;
    MoveLeftEvent(const MoveLeftEvent&) = delete;
    MoveLeftEvent& operator=(const MoveLeftEvent&) = delete;
public:
    explicit MoveLeftEvent(Worm* worm);

    void run();

    ~MoveLeftEvent() = default;
};


#endif //__MOVELEFTEVENT__
