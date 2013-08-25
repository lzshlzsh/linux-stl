#ifndef __STL_ITERATOR_BASE_TYPES_H__
#define __STL_ITERATOR_BASE_TYPES_H__

namespace mystd 
{
    struct input_iterator_tag { };
    struct output_iterator_tag { };
    struct forward_iterator_tag : public input_iterator_tag { };
    struct bidirectional_iterator_tag : public forward_iterator_tag { };
    struct random_access_iterator_tag : public bidirectional_iterator_tag { };

    template<typename _Category, typename _Tp, typename _Distance = ptrdiff_t,
       typename _Pointer = _Tp*, typename _Reference = _Tp&>
    struct iterator
    {
        /// One of the @link iterator_tags tag types@endlink.
        typedef _Category  iterator_category;
        /// The type "pointed to" by the iterator.
        typedef _Tp        value_type;
        /// Distance between iterators is represented as this type.
        typedef _Distance  difference_type;
        /// This type represents a pointer-to-value_type.
        typedef _Pointer   pointer;
        /// This type represents a reference-to-value_type.
        typedef _Reference reference;
    };

    template <typename T>
    class iterator_traits
    {
    public:
        typedef typename T::iterator_category iterator_category;
        typedef typename T::value_type value_type;
        typedef typename T::difference_type difference_type;
        typedef typename T::pointer pointer;
        typedef typename T::reference reference;
    };

    template <typename T>
    class iterator_traits<T *>
    {
    public:
        typedef random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef T *pointer;
        typedef T &reference;
    };
    template <typename T>
    class iterator_traits<const T *>
    {
    public:
        typedef random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef const T *pointer;
        typedef const T &reference;
    };

    template <typename T>
    inline typename iterator_traits<T>::iterator_category
    __iterator_category(const T &)
    {
        return typename iterator_traits<T>::iterator_category();
    }
}

#endif

