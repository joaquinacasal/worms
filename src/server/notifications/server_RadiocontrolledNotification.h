#ifndef __RADIOCONTROLLEDNOTIFICATION__
#define __RADIOCONTROLLEDNOTIFICATION__

#include "server_INotification.h"

/*
 * Hereda de INotification. Envía información sobre un teledirigido.
 */
class RadiocontrolledNotification : public INotification {
private:
    ClientHandler* client;
    size_t id;
    double x;
    double y;

    RadiocontrolledNotification(const RadiocontrolledNotification&) = delete;
    RadiocontrolledNotification& operator=(const RadiocontrolledNotification&)\
                                                                  = delete;
public:
    RadiocontrolledNotification(ClientHandler* client, size_t id, double x,\
                                                                    double y);

    void run();

    ~RadiocontrolledNotification() = default;
};


#endif //__RADIOCONTROLLEDNOTIFICATION__
