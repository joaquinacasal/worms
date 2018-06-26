#ifndef __CAPTUREDEVENTSENDER__
#define __CAPTUREDEVENTSENDER__

#include "../../common/common_Thread.h"
#include "../../common/common_BlockingQueue.h"

#include "client_ICapturedEvent.h"

class ICapturedEvent;

/* Conectado con el thread que captura los eventos y los crea a través de
 * una cola bloqueante, los desencola y los envía a través del socket.
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
