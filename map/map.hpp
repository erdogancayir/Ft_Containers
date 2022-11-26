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
		
		private:
			typedef Node<value_type>								Node_type;
			typedef Node_type*										Node_ptr;
			typedef Tree<value_type, key_compare, allocator_type>	Tree_type;
			typedef Tree_type*										Tree_ptr;

			Tree_type		_tree;
			allocator_type	_alloc;
			key_compare		_comp;
		
		public:
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
				_tree(comp, alloc), _alloc(alloc), _comp(comp) {}
			template < class InputIterator >
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
				_tree(comp, alloc), _alloc(alloc), _comp(comp) 
			{insert(first, last);}
			map (const map &oth) { *this = x; };

			~map() {this->_tree.clear(); };

			map	&operator=(const map &oth)
			{
				if (this != &oth)
				{
					this->_tree.clear();
					this->_alloc = oth._alloc;
					this->_comp = oth._comp;
					insert(oth.begin(), oth.end());
				}
				return (*this);
			}
		public:
			iterator		begin()					{ return (this->_tree.begin()); };
			const_iterator	begin()					{ return (this->_tree.begin()); };
			iterator		end() 					{ return (this->_tree.end()); };
			const_iterator	end() const				{ return (this->_tree.end()); };
			reverse_iterator	rbegin()			{ return (this->_tree.rbegin()); };
			const_reverse_iterator	rbegin() const	{ return (this->_tree.rbegin()); };
			reverse_iterator	rend()				{ return (this->_tree.rend()); };
			const_reverse_iterator	rend() const	{ return (this->_tree.rend()); };	
		
		public:
			bool	empty() const 			{ return (this->_tree.empty()); };
			size_type	size() 	const		{ return (this->_tree.size()); };
			size_type	max_size() const	{ return (this->_tree.max_size()); };

			mapped_type	&operator[] (const key_type &k) {return (*(insert(ft::make_pair(k, mapped_type())).first)).second}

		public:
			ft::pair<iterator, bool>	insert(const value_type &val)
			{
				iterator	node = iterator(this->_tree.search(val.first));
			}
	};
}; // namespace ft


#endif