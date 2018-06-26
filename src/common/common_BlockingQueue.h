#ifndef __BLOCKINGQUEUE__
#define __BLOCKINGQUEUE__

#include <mutex>
#include <condition_variable>
#include <deque>

template <typename T>
class BlockingQueue
{
private:
    std::mutex              d_mutex;
    std::condition_variable d_condition;
    std::deque<T>           d_queue;
public:
    void push(T const& value) {
        {
          std::unique_lock<std::mutex> lock(this->d_mutex);
          d_queue.push_front(value);
        }
        this->d_condition.notify_one();
    }
    bool pop(T& elem) {
        std::unique_lock<std::mutex> lock(this->d_mutex);
        // la función wait solo funciona recibiendo un unique_lock, por eso
        // no utilizo la función RAII Lock. Si falla se llama al segundo
        // bloque de código que recibe.
        this->d_condition.wait(lock, [=]{ return !d_queue.empty(); });
        elem = this->d_queue.back();
        this->d_queue.pop_back();
        return true;
    }

    size_t size(){
        return this->d_queue.size();
    }
};

#endif
