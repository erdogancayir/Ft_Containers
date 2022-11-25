#ifndef MAP_HPP
# define MAP_HPP

# include "iostream"
# include "pair.hpp"

namespace ft
{
	template <	class Key,
				class T,
				class Compare = std::less<Key>,
				class Alloc = std::allocator<ft::pair<const Key, T>>
			>
	class map
	{
		public:
			typedef Key											key_value;
			typedef T											mapped_type;
			typedef ft::pair<const Key, T>						value_type;
			typedef Compare										key_compare;
			typedef	Alloc										allocator_type;
			typedef typename allocator_type::difference_type	difference_type;
			typedef typename allocator_type::size_type			size_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
		public:
			class value_compare
			{
				friend class map; //map can use funcs of value_compare. i said
				protected:
					Compare _comp;
					value_compare(Compare val) : _comp(val) {}
				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					//Compares lhs.first and rhs.first by calling the stored comparator.
					bool operator()( const value_type& lhs, const value_type& rhs ) const //for map elements
						return _comp(x.first, y.first); // type std::map::value_type (key-value pairs)
			};
		public:
			
	};
} // namespace ft


#endif