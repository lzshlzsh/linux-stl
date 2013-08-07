#ifndef __POOL_ALLOCATOR_H__
#define __POOL_ALLOCATOR_H__ 1

#include <cstdlib>
#include <new>

namespace mycxx
{
    using std::size_t;
    using std::ptrdiff_t;

    class pool_alloc_base
    {
    protected:
        enum { ALIGN = 8 };
        enum { MAX_BYTES = 128 };
        enum { FREE_LIST_SIZE = size_t(_MAX_BYTES) / size_t(_ALIGN) };
        union obj {
            union obj *link;
            char data[1];
        };
        static obj * volatile free_list[FREE_LIST_SIZE];
        static char *start;
        static char *end;
        static size_t heap_size;

        size_t round_up(size_t bytes)
        {
        }

        obj *volatile* get_free_list(size_t bytes) throw()
        {
        }
        
    };
}

#endif

