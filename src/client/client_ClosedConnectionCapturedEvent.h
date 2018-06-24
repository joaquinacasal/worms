#ifndef __CLOSEDCONNECTIONCAPTUREDEVENT__
#define __CLOSEDCONNECTIONCAPTUREDEVENT__

#include "client_ICapturedEvent.h"
#include "../common/common_SocketProtocol.h"

class ClosedConnectionCapturedEvent : public ICapturedEvent {
private:
    SocketProtocol& socket_protocol;

    ClosedConnectionCapturedEvent(const ClosedConnectionCapturedEvent&) =\
                                                                        delete;
    ClosedConnectionCapturedEvent& operator=\
                               (const ClosedConnectionCapturedEvent&) = delete;
public:
    explicit ClosedConnectionCapturedEvent(SocketProtocol& _socket_protocol);

    void send();

    ~ClosedConnectionCapturedEvent();
};


#endif //__CLOSEDCONNECTIONCAPTUREDEVENT__
