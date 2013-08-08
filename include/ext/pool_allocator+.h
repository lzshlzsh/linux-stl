#ifndef __POOL_ALLOCATOR_H__
#define __POOL_ALLOCATOR_H__ 1

#include <cstdlib>
#include <new>
#include <ext/concurrence.h>

namespace mycxx
{
    using std::size_t;
    using std::ptrdiff_t;

    class pool_alloc_base
    {
    protected:
        enum { ALIGN = 8 };
        enum { MAX_BYTES = 128 };
        enum { FREE_LIST_SIZE = (size_t)MAX_BYTES / (size_t)ALIGN };
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
            return (bytes + (size_t)ALIGN - 1) & ~((size_t)ALIGN - 1);
        }
        
        obj *volatile* get_free_list(size_t bytes) throw();
        __gnu_cxx::__mutex &get_mutex() throw ();
        void refill(size_t n);
        char *allocate_chunk(size_t n, int &nobjs);
    };
    
}

#endif

