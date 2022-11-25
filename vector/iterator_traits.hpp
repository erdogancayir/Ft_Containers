#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

# include <string>
# include <iterator>
# include <iostream>

namespace ft
{								/* Traits class definig for prototips of iterator */
    template <class Iterator>	/* A template helper construct used to specify all critical type definitions that the iterator must have. */
    class iterator_traits
    {
        typedef typename Iterator::difference_type      difference_type;
        typedef typename Iterator::value_type           value_type;
        typedef typename Iterator::pointer              pointer;
        typedef typename Iterator::reference            reference;
        typedef typename Iterator::iterator_category    iterator_category;
    };

    template <class T>
	struct iterator_traits<T*>	/* iterator_traits kendi türünden alan bir default tanımla gelebilir. Pointerlar icin özelleştirilmiştir.*/
	{
		typedef ptrdiff_t						difference_type;
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
	};

	template <class T>
	struct iterator_traits<const T*>
	{
		typedef ptrdiff_t						difference_type;
		typedef T								value_type;
		typedef const T*						pointer;
		typedef const T&						reference;
	};
};

#endif