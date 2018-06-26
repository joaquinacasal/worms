#ifndef __INOTIFICATION__
#define __INOTIFICATION__

#include "../server_ClientHandler.h"

/* Interfaz que representa a las notificaciones que se le envían a los clientes.
 */
class INotification {
public:
    /* Ejecuta la acción */
    virtual void run() = 0;
    virtual ~INotification(){}
};


#endif //__INOTIFICATION__
