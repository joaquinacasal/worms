#ifndef __JUMPFORWARDEVENT__
#define __JUMPFORWARDEVENT__

#include "server_IEvent.h"
#include "../server_Worm.h"

// Hereda de IEvent. Hace un salto hacia adelante.
class JumpForwardEvent : public IEvent {
private:
    Worm* worm;
    JumpForwardEvent(const JumpForwardEvent&) = delete;
    JumpForwardEvent& operator=(const JumpForwardEvent&) = delete;
public:
    explicit JumpForwardEvent(Worm* worm);

    void run();

    ~JumpForwardEvent() = default;
};


#endif //__JUMPFORWARDEVENT__
