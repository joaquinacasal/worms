#ifndef __IEVENT__
#define __IEVENT__

/* Interfaz que representa a los eventos que pueden ser ejecutados.
 */
class IEvent {
public:
    /* Ejecuta la acción */
    virtual void run() = 0;
};


#endif //__IEVENT__
