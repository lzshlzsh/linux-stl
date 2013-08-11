#ifndef __MOVE_H__
#define __MOVE_H__ 1

namespace std
{
    template <typename T>
    T *addressof(T &r)
    {
        return &r;
    }
}

#endif

