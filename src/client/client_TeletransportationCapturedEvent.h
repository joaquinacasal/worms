#ifndef __TELETRANSPORTATIONCAPTUREDEVENT__
#define __TELETRANSPORTATIONCAPTUREDEVENT__

#include "client_ICapturedEvent.h"
#include "../common/common_SocketProtocol.h"

class TeletransportationCapturedEvent : public ICapturedEvent {
private:
    SocketProtocol& socket_protocol;
    int x;
    int y;

    TeletransportationCapturedEvent(const TeletransportationCapturedEvent&) = delete;
    TeletransportationCapturedEvent& operator=(const TeletransportationCapturedEvent&) = delete;
public:
    TeletransportationCapturedEvent(SocketProtocol& _socket_protocol, int x, int y);

    void send();

    ~TeletransportationCapturedEvent();
};


#endif //__TELETRANSPORTATIONCAPTUREDEVENT__
