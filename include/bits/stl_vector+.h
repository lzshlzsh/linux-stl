#ifndef __STL_VECTOR_H__ 
#define __STL_VECTOR_H__ 1

#include "ext/alloc_traits+.h"

namespace mystd 
{
    template <typename T, typename Alloc>
    struct vector_base
    {
        typedef typename mycxx::alloc_traits<Alloc>:: template rebind<T>::other
            T_alloc_type;
        typedef typename mycxx::alloc_traits<T_alloc_type>::pointer pointer;

        struct vector_imp : public T_alloc_type
        {
            pointer start;
            pointer finish;
            pointer end_of_storage;

            vector_imp(): T_alloc_type(), start(0), finish(0), end_of_storage() {}
            vector_imp(const T_alloc_type &a): T_alloc_type(a), start(0), finish(0), end_of_storage() {}
            void swap(vector_imp &imp)
            {
                mystd::swap(start, imp.start);
                mystd::swap(finish, imp.finish);
                mystd::swap(end_of_storage, imp.end_of_storage);
            }
        };

        typedef Alloc allocator_type;
        vector_imp imp;

        T_alloc_type &get_T_allocator() throw()
        {
            return static_cast<T_alloc_type>(imp);
        }
        const T_alloc_type &get_T_allocator() const throw()
        {
            return static_cast<const T_alloc_type>(imp);
        }
        allocator_type get_alloc_type() const throw()
        {
            return allocator_type(get_T_allocator());
        }

        pointer allocate(size_t n)
        {
            return n ? imp.T_alloc_type::allocate(n) : 0;
        }
        void deallocate(pointer p, size_t n)
        {
            if (p) {
                imp.T_alloc_type.deallocate(p, n);
            }
        }

        vector_base(): imp() {}
        vector_base(const allocator_type &a): imp(a) {}
        vector_base(size_t n): imp() 
        {
            create_storage(n);
        }
        vector_base(const allocator_type &a, size_t n): imp(a)
        {
            create_storage(n);
        }

        ~vector_base()
        {
            deallocate(imp.start, imp.end_of_storage - imp.start);
        }

    private:
        void create_storage(size_t n)
        {
            imp.start = allocate(n);
            imp.finish = imp.start;
            imp.end_of_storage = imp.start + n;
        }
    };

    template <typename T, typename Alloc = mystd::allocator<T> >
    class vector: protected vector_base<T, Alloc>
    {
        typedef vector_base<T, Alloc> base_t;
        typedef typename base_t::T_alloc_type T_alloc_type;
        typedef mycxx::alloc_traits<T_alloc_type> alloc_traits;
    public:
        typedef T value_type;
        typedef typename base_t::pointer pointer;
        typedef typename alloc_traits::const_pointer const_pointer;
        typedef typename alloc_traits::reference reference;
        typedef typename alloc_traits::const_reference const_reference;
        
    };
}

#endif

