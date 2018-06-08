#include "common_Lock.h"

Lock::Lock(std::mutex &m) : internal_mutex(m){
  internal_mutex.lock();
}

Lock::~Lock(){
  internal_mutex.unlock();
}
