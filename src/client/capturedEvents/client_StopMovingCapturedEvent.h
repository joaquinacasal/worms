#ifndef __STOPMOVINGCAPTUREDEVENT__
#define __STOPMOVINGCAPTUREDEVENT__

#include "client_ICapturedEvent.h"
#include "../../common/common_SocketProtocol.h"

// Representación de la acción de dejar de moverse.
class StopMovingCapturedEvent : public ICapturedEvent {
private:
    SocketProtocol& socket_protocol;

    StopMovingCapturedEvent(const StopMovingCapturedEvent&) = delete;
    StopMovingCapturedEvent& operator=(const StopMovingCapturedEvent&) = delete;
public:
    explicit StopMovingCapturedEvent(SocketProtocol& _socket_protocol);

    void send();

    ~StopMovingCapturedEvent();
};


#endif //__STOPMOVINGCAPTUREDEVENT__
