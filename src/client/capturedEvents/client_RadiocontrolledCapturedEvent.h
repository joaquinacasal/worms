#ifndef __RADIOCONTROLLEDCAPTUREDEVENT__
#define __RADIOCONTROLLEDCAPTUREDEVENT__

#include "client_ICapturedEvent.h"
#include "../../common/common_SocketProtocol.h"

// Representación de la acción de disparar los teledirigidos. Va acompañado
// de una coordenada.
class RadiocontrolledCapturedEvent : public ICapturedEvent {
private:
    SocketProtocol& socket_protocol;
    int x;
    int y;

    RadiocontrolledCapturedEvent(const RadiocontrolledCapturedEvent&) = delete;
    RadiocontrolledCapturedEvent& operator=\
                            (const RadiocontrolledCapturedEvent&) = delete;
public:
    RadiocontrolledCapturedEvent(SocketProtocol& _socket_protocol, \
                                 int x, int y);

    void send();

    ~RadiocontrolledCapturedEvent();
};


#endif //__RADIOCONTROLLEDCAPTUREDEVENT__
