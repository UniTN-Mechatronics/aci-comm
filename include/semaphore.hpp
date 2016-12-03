#ifndef _SEMAPHORE_HPP_
#define _SEMAPHORE_HPP_
#ifdef __cplusplus

class Semaphore
{
public:
    Semaphore(int value) : _value(value) {};
    Semaphore(const Semaphore &S) = delete;
    Semaphore& operator=(Semaphore S) = delete;
    ~Semaphore() {};

    void
    wait() {
        std::unique_lock<std::mutex> lock(_mutex);
        --_value;
        if (_value < 0) {
            do {
                _cv.wait(lock);
            } while (_wake_ups < 1);
            --_wake_ups;
        }
    }

    void 
    signal() {
        std::unique_lock<std::mutex> lock(_mutex);
        ++_value;
        if (_value <= 0) {
            ++_wake_ups;
            _cv.notify_one();
        }
    }

private:
    int _value;
    int _wake_ups = 0;
    std::mutex _mutex;
    std::condition_variable _cv;
};


#endif // __cplusplus
#endif // _ACI_COMM_SEMAPHORE_HPP_
