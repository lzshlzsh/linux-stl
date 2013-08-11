#ifndef __ALLOC_TRAITS_H__
#define __ALLOC_TRAITS_H__ 1

#include "bits/allocator+.h" /* for alloc_swap::swap */

namespace mycxx 
{
    template <typename Alloc>
    class alloc_traits
    {
    public:
        typedef Alloc allocator_type;
        typedef typename Alloc::size_type size_type;
        typedef typename Alloc::difference_type difference_type;
        typedef typename Alloc::value_type value_type;
        typedef typename Alloc::poiner pointer;
        typedef typename Alloc::const_pointer const_pointer;
        typedef typename Alloc::reference reference;
        typedef typename Alloc::const_reference const_reference;

        static pointer allocate(Alloc &a, size_type n)
        {
            return a.allocate(n);
        }
        static void deallocate(Alloc &a, pointer p, size_type n)
        {
            a.deallocate(p, n);
        }

        template<typename T1>
        static void construct(Alloc &a, pointer p, const T1 &r)
        {
            a.construct(p, r);
        }
        static void destroy(Alloc &a, pointer p)
        {
            a.destroy(p);
        }
        static size_type max_size(Alloc &a)
        {
            return a.max_size();
        }
        
        template <typename T1>
        struct rebind {
            typedef typename Alloc:: template rebind<T1>::other other;
        };

        static const Alloc &select_on_copy(const Alloc &a) 
        {
            return a;
        }

        static void on_swap(Alloc &a, Alloc &b)
        {
            mystd::alloc_swap<Alloc>::do_it(a, b);
        }
    };
}

#endif

