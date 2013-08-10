#include "ext/pool_allocator+.h"

namespace 
{
    __gnu_cxx::__mutex &get_palloc_mutex()
    {
        static __gnu_cxx::__mutex mutex;
        return mutex;
    }
}

namespace mycxx
{
    pool_alloc_base::obj * volatile pool_alloc_base::free_list[pool_alloc_base::FREE_LIST_SIZE];
    char *pool_alloc_base::start = 0;
    char *pool_alloc_base::end = 0;
    size_t pool_alloc_base::heap_size = 0;

    pool_alloc_base::obj *volatile* pool_alloc_base::get_free_list(size_t bytes) throw()
    {
        return NULL;
    }
    __gnu_cxx::__mutex &pool_alloc_base::get_mutex() throw ()
    {
        return get_palloc_mutex();
    }
    void pool_alloc_base::refill(size_t n)
    {
    }
    char *pool_alloc_base::allocate_chunk(size_t n, int &nobjs)
    {
        return NULL;
    }

}

