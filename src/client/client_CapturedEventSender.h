#ifndef __CAPTUREDEVENTSENDER__
#define __CAPTUREDEVENTSENDER__

#include "../common/common_Thread.h"
#include "../common/common_BlockingQueue.h"

#include "client_ICapturedEvent.h"

class ICapturedEvent;

/* Clase que representa al dibujador por consola. Saca los Drawables de una
 * protegida y los imprime por consola.
 */
class CapturedEventSender : public Thread {
private:
    BlockingQueue<ICapturedEvent*>& blocking_queue;
    bool connected;

    CapturedEventSender(const CapturedEventSender&) = delete;
    CapturedEventSender& operator=(const CapturedEventSender&) = delete;
public:
    explicit CapturedEventSender(BlockingQueue<ICapturedEvent*>&\
                                 _blocking_queue);
    CapturedEventSender(CapturedEventSender&& other) = default;

    void run() override;

    void stop();

    bool is_connected();

    ~CapturedEventSender();
};


#endif // __CAPTUREDEVENTSENDER__
