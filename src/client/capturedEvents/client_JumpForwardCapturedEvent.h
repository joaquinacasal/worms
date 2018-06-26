#ifndef __JUMPFORWARDCAPTUREDEVENT__
#define __JUMPFORWARDCAPTUREDEVENT__

#include "client_ICapturedEvent.h"
#include "../../common/common_SocketProtocol.h"

// Representación de la acción de saltar hacia adelante.
class JumpForwardCapturedEvent : public ICapturedEvent {
private:
    SocketProtocol& socket_protocol;

    JumpForwardCapturedEvent(const JumpForwardCapturedEvent&) = delete;
    JumpForwardCapturedEvent& operator=(const JumpForwardCapturedEvent&) =\
                                                                        delete;

public:
    explicit JumpForwardCapturedEvent(SocketProtocol& _socket_protocol);

    void send();

    ~JumpForwardCapturedEvent();
};


#endif //__JUMPFORWARDCAPTUREDEVENT__
