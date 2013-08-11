#include <new>

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
        return free_list + ((bytes + (size_t)ALIGN - 1) / (size_t)ALIGN - 1);
    }
    __gnu_cxx::__mutex &pool_alloc_base::get_mutex() throw ()
    {
        return get_palloc_mutex();
    }
    void *pool_alloc_base::refill(size_t n)
    {
        int nobjs = 20;
        char *chunk = allocate_chunk(n, nobjs);
        obj *volatile*list;
        obj *next, *cur;
        
        if (1 == nobjs) {
            return chunk;
        }

        list = get_free_list(n);
        next = reinterpret_cast<obj *>(chunk + n);
        for (int i = 1; ; i++) {
            cur = next;
            next = reinterpret_cast<obj *>(reinterpret_cast<char *>(next) + n);
            if (nobjs - 1 == i) {
                cur->link = *list;
                *list = reinterpret_cast<obj *>(chunk + n);
                break;
            } else {
                cur->link = next;
            }
        }
        return chunk;
    }
    char *pool_alloc_base::allocate_chunk(size_t n, int &nobjs)
    {
        char *result;
        size_t total = n * nobjs;
        size_t free = end - start;

        if (free >= total) {
            result = start;
            start += total;
            return result;
        } else if (free >= n) {
            result = start;
            nobjs = free / n;
            start += nobjs * n;
            return result;
        } else {
            if (free > 0) {
                obj *volatile*list = get_free_list(free);
                
                reinterpret_cast<obj *>(start)->link = *list;
                *list = reinterpret_cast<obj *>(start);
            }

            size_t bytes_to_get = (2 * total + (heap_size >> 4));
            try {
                start = reinterpret_cast<char *>(::operator new(bytes_to_get));
            } catch (std::bad_alloc &) {
                for (size_t i = n; i <= (size_t)MAX_BYTES; i += ALIGN) {
                    obj *volatile*list = get_free_list(i);
                    if (*list) {
                        start = reinterpret_cast<char *>(*list);
                        end = start + i;
                        *list = (*list)->link;
                        return allocate_chunk(n, nobjs);
                    }
                }

                start = end = NULL;
                throw;
            }

            end = start + bytes_to_get;
            heap_size += bytes_to_get;
            return allocate_chunk(n, nobjs);    
        }
    }

}

