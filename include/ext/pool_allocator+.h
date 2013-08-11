#ifndef __POOL_ALLOCATOR_H__
#define __POOL_ALLOCATOR_H__ 1

#include <cstdlib>
#include <new>
#include <ext/concurrence.h>
#include <bits/functexcept.h>

#include "bits/move+.h"

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
        void *refill(size_t n);
        char *allocate_chunk(size_t n, int &nobjs);
    };

    template<typename T>
    class pool_alloc: private pool_alloc_base
    {
    public:
        typedef T value_type;
        typedef T *pointer;
        typedef const T *const_pointer;
        typedef T &reference;
        typedef const T &const_reference;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;

        template<typename T1>
        struct rebind {
            typedef pool_alloc<T1> other;
        };

        pool_alloc() throw() {}
        pool_alloc(const pool_alloc &) throw() {}
        template<typename T1>
        pool_alloc(const pool_alloc<T1>) throw() {}
        ~pool_alloc() throw() {}

        pointer address(reference r) const throw()
        {
            return mystd::addressof(r);
        }
        const_pointer address(const_reference cr) const throw()
        {
            return mystd::addressof(cr);
        }
        size_type max_size() const throw()
        {
            return (size_type)-1 / sizeof(T);
        }
        void construct(pointer p, const_reference r)
        {
            ::new (reinterpret_cast<void *>(p)) T(r);
        }

        void destroy(pointer p)
        {
            p->~T();
        }

        pointer allocate(size_type n, const void * = 0);
        void deallocate(pointer p, size_type n);
    };

    template<typename T>
    T *pool_alloc<T>::allocate(size_type n, const void *)
    {
        pointer ret = 0;
        if (__builtin_expect(n, true)) {
            if (n > max_size()) {
                std::__throw_bad_alloc();
            }

            const size_type size = n * sizeof(T);
            if (size > MAX_BYTES) {
                ret = reinterpret_cast<pointer>(::operator new(size));
            } else {
                obj *volatile*list = get_free_list(size);

                __gnu_cxx::__scoped_lock lock(get_mutex());
                obj *result = *list;
                if (__builtin_expect(NULL != result, true)) {
                    ret = reinterpret_cast<pointer>(result);
                    *list = result->link;
                } else {
                    ret = reinterpret_cast<pointer>(refill(round_up(size)));
                }

                if (0 == ret) {
                    std::__throw_bad_alloc();
                }
            }
        }
        return ret;
    }

    template<typename T>
    void pool_alloc<T>::deallocate(pointer p, size_type n)
    {
        if (__builtin_expect(NULL != p && n, true)) {
            const size_type size = n * sizeof(T);
            if (size > MAX_BYTES) {
                ::operator delete(p);
            } else {
                obj *volatile* list = get_free_list(size);
                obj *q = reinterpret_cast<obj *>(p);
                    
                __gnu_cxx::__scoped_lock lock(get_mutex());
                q->link = *list;
                *list = q;
            }
        }
    }

    template <typename T>
    inline bool operator ==(const pool_alloc<T> &a, const pool_alloc<T> &b)
    {
        return true;
    }
    template <typename T>
    inline bool operator !=(const pool_alloc<T> &a, const pool_alloc<T> &b)
    {
        return false;
    }
}

#endif

