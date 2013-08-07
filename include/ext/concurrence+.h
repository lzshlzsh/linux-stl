#ifndef __COCURRENCE_H__
#define __COCURRENCE_H__ 1

#include <pthread.h>

namespace mycxx
{
    class mutex
    {
    private:
        pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

        mutex(const mutex &mtx);
        mutex &operator=(const mutex &mtx);
    public:
        mutex() {}
        ~mutex() {}
        
    };
}

#endif

