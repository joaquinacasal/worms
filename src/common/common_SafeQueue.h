#ifndef __SAFEQUEUE__
#define __SAFEQUEUE__

#include <queue>
#include <mutex>
#include "common_Lock.h"

/* Template de una cola protegida con la cual pueden interactuar varios hilos
 * de forma segura ya que tiene los recursos protegidos con un mutex.
 */
template <class T>
class SafeQueue {
private:
 std::queue<T> queue_;
 std::mutex mutex_;

public:
  // Guarda el primer elemento el puntero recibido.
  bool pop(T& elem) {
    Lock l(mutex_);
    if (queue_.empty()) {
       return false;
    }
    elem = queue_.front();
    queue_.pop();
    return true;
  }

  // Guarda el elemento recibido de manera segura.
  void push(T elem) {
      Lock l(mutex_);
      queue_.push(elem);
  }
};

#endif
