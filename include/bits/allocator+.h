#ifndef __ALLOCATOR_H__
#define __ALLOCATOR_H__ 1

#include "bits/c++allocator+.h"
#include "bits/move+.h"

namespace mystd
{
    using std::size_t;
    using std::ptrdiff_t;

    template <typename T>
    class allocator: public base_allocator<T>
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
            typedef allocator<T1> other;
        };

        allocator() throw() {}
        allocator(const allocator<T> &a) throw ()
            : base_allocator<T>(a) {}
        template <typename T1>
        allocator(const allocator<T1> &a) throw() {}
        ~allocator() throw() {}
    };

    template<>
    class allocator<void>
    {
    public:
        typedef size_t      size_type;
        typedef ptrdiff_t   difference_type;
        typedef void*       pointer;
        typedef const void* const_pointer;
        typedef void        value_type;

        template<typename _Tp1>
        struct rebind
        { typedef allocator<_Tp1> other; };
    };

    template <typename T>
    inline bool operator == (const allocator<T> &a1, const allocator<T> &a2)
    {
        return true;
    }
    template <typename T>
    inline bool operator != (const allocator<T> &a1, const allocator<T> &a2)
    {
        return false;
    }
    template <typename T1, typename T2>
    inline bool operator == (const allocator<T1> &a1, const allocator<T2> &a2)
    {
        return true;
    }
    template <typename T1, typename T2>
    inline bool operator != (const allocator<T1> &a1, const allocator<T2> &a2)
    {
        return false;
    }

#undef base_allocator
    
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

