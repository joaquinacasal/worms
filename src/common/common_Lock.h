#ifndef __LOCK_H__
#define __LOCK_H__

#include <mutex>

// Clase que encapsula el comportamiento de un mutex en una clase RAII.
class Lock{
  private:
    std::mutex& internal_mutex;
    Lock(const Lock&) = delete;
    Lock& operator=(const Lock&) = delete;
  public:
    // Constructor. Bloquea el mutex.
    explicit Lock(std::mutex &m);

    // Destructor. Desbloquea el mutex.
    ~Lock();
};

#endif
