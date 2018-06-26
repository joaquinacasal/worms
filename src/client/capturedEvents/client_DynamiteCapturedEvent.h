#ifndef __DYNAMITECAPTUREDEVENT__
#define __DYNAMITECAPTUREDEVENT__

#include "client_ICapturedEvent.h"
#include "../../common/common_SocketProtocol.h"

// Representación de la acción de poner una dinamita.
class DynamiteCapturedEvent : public ICapturedEvent {
private:
    SocketProtocol& socket_protocol;

    DynamiteCapturedEvent(const DynamiteCapturedEvent&) = delete;
    DynamiteCapturedEvent& operator=(const DynamiteCapturedEvent&) = delete;
public:
    explicit DynamiteCapturedEvent(SocketProtocol& _socket_protocol);

    void send();

    ~DynamiteCapturedEvent();
};


#endif //__DYNAMITECAPTUREDEVENT__
