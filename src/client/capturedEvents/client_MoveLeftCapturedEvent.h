#ifndef __MOVELEFTCAPTUREDEVENT__
#define __MOVELEFTCAPTUREDEVENT__

#include "client_ICapturedEvent.h"
#include "../../common/common_SocketProtocol.h"

class MoveLeftCapturedEvent : public ICapturedEvent {
private:
    SocketProtocol& socket_protocol;

    MoveLeftCapturedEvent(const MoveLeftCapturedEvent&) = delete;
    MoveLeftCapturedEvent& operator=(const MoveLeftCapturedEvent&) = delete;
public:
    explicit MoveLeftCapturedEvent(SocketProtocol& _socket_protocol);

    void send();

    ~MoveLeftCapturedEvent();
};


#endif //__MOVELEFTCAPTUREDEVENT__
