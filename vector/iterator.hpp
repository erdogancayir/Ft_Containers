#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <vector>
# include <iterator>
# include <iostream>
# include "iterator_traits.hpp"

namespace ft
{
    template <class T>
    class VectorIter : public std::iterator<std::random_access_iterator_tag, T>
    {
        public:
            typedef T                                               iterator_type;
            typedef std::random_access_iterator_tag                 iterator_category;
            typedef typename iterator_traits<T>::value_type         value_type;
            typedef typename iterator_traits<T>::difference_type    difference_type;
            typedef typename iterator_traits<T>::pointer            pointer;
            typedef typename iterator_traits<T>::reference          reference;
        private:
            iterator_type   _iter; //my_vec
        public:
            VectorIter() : _iter(nullptr) {};
            explicit VectorIter(iterator_type obj) : _iter(obj) {}
            template <class Iter>
            explicit VectorIter(VectorIter<Iter> &vec_it) : _iter(vec_it.base()) {}

            iterator_type   base() const                            { return (this->_iter); };  //returns adress for class(iterator)
            reference       operator*() const                       { return (*this->_iter); };
            VectorIter      operator+( difference_type n) const     { return (VectorIter(this->_iter + n));};
            VectorIter      operator-( difference_type n) const     { return (VectorIter(this->_iter - n));};
            VectorIter      &operator++()                           { ++this->_iter; return (*this);};
            VectorIter      operator++(int)                         { VectorIter temp(*this); ++(*this); return(temp); };
            VectorIter      &operator--()                           { --this->_iter; return(*this); };
            VectorIter      operator--(int)                         { VectorIter temp(*this); --(*this); return (temp); };
            VectorIter      &operator+=( difference_type n)         { this->_iter += n; return (*this); };
            VectorIter      &operator-=( difference_type n)         { this->_iter -= n; return (*this); };
            pointer         operator->()                            { return (&(operator*())); };
            reference       operator[](difference_type n)           { return (*(this->iter + n)); };
    };
    template <class Iterator1, class Iterator2>
	bool operator== (const VectorIter<Iterator1>& lhs, const VectorIter<Iterator2>& rhs) { return (lhs.base() == rhs.base()); };
	template <class Iterator1, class Iterator2>
	bool operator!= (const VectorIter<Iterator1>& lhs, const VectorIter<Iterator2>& rhs) { return (lhs.base() != rhs.base()); };
	template <class Iterator1, class Iterator2>
	bool operator<  (const VectorIter<Iterator1>& lhs, const VectorIter<Iterator2>& rhs) { return (lhs.base() < rhs.base()); };
	template <class Iterator1, class Iterator2>
	bool operator<= (const VectorIter<Iterator1>& lhs, const VectorIter<Iterator2>& rhs) { return (lhs.base() <= rhs.base()); };
	template <class Iterator1, class Iterator2>
	bool operator>  (const VectorIter<Iterator1>& lhs, const VectorIter<Iterator2>& rhs) { return (lhs.base() > rhs.base()); };
	template <class Iterator1, class Iterator2>
	bool operator>=  (const VectorIter<Iterator1>& lhs, const VectorIter<Iterator2>& rhs) { return (lhs.base() >= rhs.base()); };

    template <class Iterator>   // extra // it has no function
	VectorIter<Iterator> operator+ (typename VectorIter<Iterator>::difference_type n, const VectorIter<Iterator>& vec_it)
	{ return (VectorIter<Iterator>( vec_it + n)); };
	template <class Iterator>   // i used for difference of two different iterators last - first vs. 
	typename VectorIter<Iterator>::difference_type operator- (const VectorIter<Iterator>& lhs, const VectorIter<Iterator>& rhs)
	{ return (lhs.base() - rhs.base()); };    
};

#endif