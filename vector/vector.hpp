#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "iterator.hpp"
# include "iterator_traits.hpp"
# include "utils.hpp"
# include <string>
# include <limits>
# include <algorithm>
# include <iostream>
# include "reverse_iterator.hpp"

namespace ft
{
    template < class T, class Allocator = std::allocator<T> >
    class vector
    {
        public:
            typedef T											value_type;
			typedef Allocator									allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef typename allocator_type::difference_type	difference_type;
			typedef typename allocator_type::size_type			size_type;
			typedef VectorIter<pointer>							iterator;
			typedef VectorIter<const_pointer>					const_iterator;
			typedef ft::reverse_iterator<pointer>				reverse_iterator;
			typedef ft::reverse_iterator<const_pointer>			const_reverse_iterator;
			
		private: /* ** Values ** */
			size_type		_size;
			size_type		_capacity;
			value_type		*_vec;
			allocator_type	_alloc;
		public:
			explicit vector (const allocator_type &alloc = allocator_type()) : _alloc(alloc), _size(0), _capacity(0), _vec(nullptr) {};
			explicit vector (size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()) : _alloc(alloc), _size(0), _capacity(0), _vec(nullptr)
			{ assign(n, val); };
			template < class InputIterator >
			explicit vector (InputIterator first, InputIterator sec, const allocator_type &alloc = allocator_type(), typename ft::enable_if<!is_integral<InputIterator>::value, bool>::type = true):
			_alloc(alloc), _size(0), _capacity(0), _vec(nullptr)
			{ assign(first, sec); };
			vector( const vector &obj) : _size(0), _capacity(0), _vec(nullptr) { *this = obj; };
		
		public:
			bool		empty() 	const	{ return (!this->_size); };
			size_type	size() 		const	{ return (this->_size); };
			size_type	capacity()	const	{ return (this->_capacity); };
			size_type	max_size()	const	{ return (this->_alloc.max_size()); };
			void	reserve(size_type n)
			{
				if (n > capacity())
				{
					value_type *temp = this->_alloc.allocate(n);
					if (this->_vec)
					{
						for (size_t i = 0; i < size(); i++)
						{
							this->_alloc.construct(temp + i, _vec[i]);
							this->_alloc.destroy(_vec + i);
						}
						this->_alloc.deallocate(this->_vec, capacity());
					}
					this->_capacity = n;
					this->_vec = temp;
				}
			}
			void	resize(size_type n, value_type val = value_type()) // elemanlari ekleyerek veya silerek kabin içeriğini fiilen değiştiriyor.
			{
				if (n != this->_size)
				{
					value_type	*temp = this->_alloc.allocate(n);
					if (n < this->_size)
					{
						for (size_t i = 0; i < n; i++)
							this->_alloc.construct(temp + i, this->_vec[i]);
						for (size_t i = 0; i < size(); i++)
							this->_alloc.destroy(&this->_vec[i]);
						this->_alloc.deallocate(this->_vec, capacity());
					}
					else if (n > this->_size)
					{
						for (size_t i = 0; i < size(); i++)
						{
							this->_alloc.construct(temp + i, this->_vec[i]);
							this->_alloc.destroy(&this->_vec[i]);
						}
						this->_alloc.deallocate(this->_vec, capacity());
						for (size_t i = size(); i < n; i++)
							this->_alloc.construct(temp + i, val);
					}
					this->_capacity = this->_size = n;
					this->_vec = temp;
				}
			}

		public:
			reference		operator[] (size_type n)		{ return (this->_vec[n]); };
			const_reference	operator[] (size_type n) const	{ return (this->_vec[n]); };
			reference		at(size_type n)					{ return (n >= size()) ? throw(std::out_of_range("vector")) : (this->_vec[n]); };
			const_reference	at(size_type n) const			{ return (n >= size()) ? throw(std::out_of_range("vector")) : (this->_vec[n]); };
			reference		front()							{ return (this->_vec[0]); };
			const_reference	front() const					{ return (this->_vec[0]); };
			reference		back()							{ return (this->_vec[size() - 1]); };
			const_reference	back() const 					{ return (this->_vec[size() - 1]); };

		public:
			iterator				begin()					{ return (iterator(this->_vec)); };
			const_iterator			begin() const			{ return (const_iterator(this->_vec)); };
			iterator				end()					{ return (iterator(begin() + size())); };
			const_iterator			end() const				{ return (const_iterator(begin() + size())); };
			reverse_iterator		rbegin()				{ return (reverse_iterator((end() - 1).base())); };
			const_reverse_iterator	rbegin() const			{ return (const_reverse_iterator((end() - 1).base())); };
			reverse_iterator		rend()					{ return (reverse_iterator((begin() - 1).base())); };
			const_reverse_iterator	rend() const			{ return (const_reverse_iterator((begin() - 1).base())); };
		public: 			/****** Allocator  *******/
				allocator_type get_allocator() const { return (this->_alloc); };
		public:
			template < class InputIterator>
			void	assign(InputIterator first, InputIterator sec, typename ft::enable_if<!is_integral<InputIterator>::value, bool>::type = true)
			{
				difference_type len = sec - first;
				clear();
				if (len > capacity())
				{
					this->_alloc.deallocate(this->_vec, capacity());
					this->_vec = this->_alloc.allocate(len);
					this->_capacity = len;
				}
				for (size_t i = 0; i < len; i++)
					this->_alloc.construct(this->_vec + i, *(first + i));
				this->_size = len;
			}
			void	assign(size_type n, const value_type &val)
			{
				clear();	// i am using it to destroy the vector;
				if (n > capacity())
				{
					this->_alloc.deallocate(this->_vec, capacity());
					this->_vec = this->_alloc.allocate(n);
					this->_capacity = n;
				}
				for (size_t i = 0; i < n; i++)
					this->_alloc.construct(this->_vec + i, val);
				this->_size = n;
			}
			iterator	insert(iterator pos, const value_type &val)
			{
				difference_type len = end() - pos;
				if (size() == capacity())
					reserve(capacity() + 1);
				iterator _it = end();
				for (size_t i = 0; i < len; i++)
				{
					*(_it) = *(_it - 1);
					_it--;
				}
				*(_it) = val;
				this->_size += 1;
				return (_it);
			}
			void	insert (iterator pos, size_type n, const value_type &val)
			{
				difference_type len = end() - pos;
				difference_type len2 = pos - begin();
				if (size() + n > capacity())
				{
					if (size() + n > capacity() * 2)
						reserve(size() + n);
					else
						reserve(capacity() * 2);
				}
				iterator _it = end() - 1;
				for (size_t i = 0; i < len; i++)
				{
					*(_it + n) = *_it;
					_it--;
				}
				_it = begin() + len2;
				for (size_t i = 0; i < n; i++)
					*(_it + i) = val;
				this->_size += n;
			}
			template < class InputIterator >
			void	insert (iterator pos, InputIterator first, InputIterator sec, typename ft::enable_if<!is_integral<InputIterator>::value, bool>::type = true)
			{
				difference_type last_len = end() - pos;
				difference_type first_len = pos - begin();
				difference_type diff = sec - first;
				if (diff + size() > capacity())
				{
					if (diff + size() > capacity() * 2)
						reserve(size() + diff);
					else
						reserve(capacity() * 2);
				}
				iterator _it = end() - 1;
				for (size_t i = 0; i < last_len; i++)
				{
					*(_it + diff) = *(_it);
					_it--; 
				}
				_it = begin() + first_len;
				for (size_t i = 0; i < diff; i++)
					*(_it) = *(first++);
				this->_size += diff;
			}
			void	push_back(const value_type &val)
			{
				if (size() == capacity())
					reserve(capacity() * 2);
				if (this->_vec == NULL)
					reserve(1);
				this->_alloc.construct(this->_vec + size(), val);
				++this->_size;
			}
			iterator	erase(iterator pos)
			{
				iterator it = pos;
				this->_alloc.destroy(it.base());
				while (it != end() - 1)
				{
					*(it) = *(it + 1);
					it++;
				}
				this->_size--;
				return (pos);
			}
			iterator	erase(iterator first, iterator sec)
			{
				iterator it = first;
				difference_type len = sec - first;
				for (size_t i = 0; i < len; i++)
					this->_alloc.destroy((first + i).base());
				while (it != end())
				{
					*(it) = *(it + len);
					it++;
				}
				this->_size -= len;
				return (first);
			}
			void	pop_back()
			{
				this->_alloc.destroy(this->_vec + size());
				this->_size--;
			}
			void	swap(vector &obj)
			{
				std::swap(obj._size, this->_size);
				std::swap(obj._capacity, this->_capacity);
				std::swap(obj._vec, this->_vec);
				std::swap(obj._alloc, this->_alloc);
			}

		public:
			void	clear()
			{
				for (size_t i = 0; i < this->_size; i++)
					this->_alloc.destroy(&this->_vec[i]);
				this->_size = 0;
			}
		public:
			~vector()
			{
				if (this->_vec)
					clear();
			}
		public:
			vector	&operator=(const vector &x)
			{
				if (this != &x)
				{
					this->_vec = x._vec;
					assign(x.begin(), x.end());	// this_size sonra atıyorum cunku allacote ederken size 0 oldugunu bilmeliyim.
					this->_size = x._size;
					this->_capacity = x._capacity;
				}
				return (*this);
			}
	};
	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
	{
		x.swap(y);
	};

	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return ((lhs.size() == rhs.size()) && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));};
	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (!(lhs == rhs));};
	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));};
	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (!(rhs < lhs));};
	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));};
	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (!(lhs < rhs));};
};




#endif