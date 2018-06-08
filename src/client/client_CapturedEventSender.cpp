#include "client_CapturedEventSender.h"

CapturedEventSender::CapturedEventSender(BlockingQueue<ICapturedEvent*>&\
                                            _blocking_queue):
                                            blocking_queue(_blocking_queue){
  connected = true;
}


void CapturedEventSender::run(){
  ICapturedEvent* event;
  while(connected || blocking_queue.size() > 0) {
    blocking_queue.pop(event);
    if (!event) continue;
    event->send();
    if (!event->continue_sending()) {
      printf("DEBUG: DEVOLVIO FALSO EL evento\n");
      connected = false;
    } else {
      printf("DEBUG: DEVOLVIO Verdadero EL evento\n");
    }
    delete event;
  }
}

bool CapturedEventSender::is_connected(){
  return connected;
}


void CapturedEventSender::stop(){
  connected = false;
  blocking_queue.push(NULL);
}

CapturedEventSender::~CapturedEventSender(){
  ICapturedEvent* event;
  while(blocking_queue.size() > 0) {
      blocking_queue.pop(event);
      delete event;
  }
}
