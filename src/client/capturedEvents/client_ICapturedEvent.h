#ifndef __ICAPTUREDEVENT__
#define __ICAPTUREDEVENT__

/* Interfaz que representa a los objetos dibujables.
 */
class ICapturedEvent {
protected:
  bool _continue_sending = true;
public:
  virtual void send() = 0;
  virtual ~ICapturedEvent(){};

  bool continue_sending(){
    return _continue_sending;
  }
};


#endif //__ICAPTUREDEVENT__
