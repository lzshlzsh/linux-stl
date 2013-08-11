#ifndef __MOVE_H__
#define __MOVE_H__ 1

namespace mystd
{
    template <typename T>
    T *addressof(T &r)
    {
        return &r;
    }

    template <typename T>
    inline void swap(T &a, T &b)
    {
        T tmp = a;
        a = b;
        b = tmp;
    }
}

#endif

