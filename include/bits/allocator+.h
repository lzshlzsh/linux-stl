#ifndef __ALLOCATOR_H__
#define __ALLOCATOR_H__ 1

#include "bits/c++allocator+.h"
#include "bits/move+.h"

namespace mystd
{
    template <typename Alloc, bool = __is_empty(Alloc)>
    struct alloc_swap
    {
        static void do_it(Alloc &a, Alloc &b) {}
    };

    template <typename Alloc>
    struct alloc_swap<Alloc, false>
    {
        static void do_it(Alloc &a, Alloc &b) 
        {
            if (a != b) {
                swap(a, b);
            }
        }
    };
}

#endif

