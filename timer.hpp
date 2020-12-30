#ifndef _TIMER_HPP_
#define _TIMER_HPP_

#include <string.h>
#include <pthread.h>
#include <signal.h>

#include <memory>
#include <thread>

namespace BING
{

class Timer 
{
public:
    void setInterval(const uint32_t &value)
    {
        interval = value;   
    }

    void setCallback(const std::function<void(void)> &cb)
    {
        timer_callback = cb;
    }

    void start(void)
    {
        thread = std::thread(std::bind(&Timer::thread_func, this));
    }   

    void stop(void)
    {
        thread.detach();
    }

private:
    void thread_func(void)
    {
        while (1) {
            struct timeval tv;
            memset(&tv, 0, sizeof(struct timeval));
            tv.tv_sec = interval;

            select(0, NULL, NULL, NULL, &tv);
            timer_callback();
        }
    }

private:
    std::function<void(void)>   timer_callback;

    uint32_t                    interval;

    std::thread                 thread;
};

}   // endof namespace BING

#endif
