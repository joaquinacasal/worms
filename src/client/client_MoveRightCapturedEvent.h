#ifndef __MOVERIGHTCAPTUREDEVENT__
#define __MOVERIGHTCAPTUREDEVENT__

#include "client_ICapturedEvent.h"
#include "../common/common_SocketProtocol.h"

class MoveRightCapturedEvent : public ICapturedEvent {
private:
    SocketProtocol& socket_protocol;

    MoveRightCapturedEvent(const MoveRightCapturedEvent&) = delete;
    MoveRightCapturedEvent& operator=(const MoveRightCapturedEvent&) = delete;
public:
    explicit MoveRightCapturedEvent(SocketProtocol& _socket_protocol);

    void send();

    ~MoveRightCapturedEvent();
};


#endif //__MOVERIGHTCAPTUREDEVENT__
