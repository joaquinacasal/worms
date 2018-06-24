#ifndef __JUMPBACKWARDCAPTUREDEVENT__
#define __JUMPBACKWARDCAPTUREDEVENT__

#include "client_ICapturedEvent.h"
#include "../../common/common_SocketProtocol.h"

class JumpBackwardCapturedEvent : public ICapturedEvent {
private:
    SocketProtocol& socket_protocol;

    JumpBackwardCapturedEvent(const JumpBackwardCapturedEvent&) = delete;
    JumpBackwardCapturedEvent& operator=(const JumpBackwardCapturedEvent&)\
                                       = delete;
public:
    explicit JumpBackwardCapturedEvent(SocketProtocol& _socket_protocol);

    void send();

    ~JumpBackwardCapturedEvent();
};


#endif //__JUMPBACKWARDCAPTUREDEVENT__
