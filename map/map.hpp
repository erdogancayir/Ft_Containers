#ifndef MAP_HPP
# define MAP_HPP

# include "iostream"
# include "pair.hpp"
# include "../vector/reverse_iterator.hpp"
# include "../vector/iterator.hpp"
# include "tree.hpp"
# include "../vector/utils.hpp"

namespace ft
{
	template <	class Key,
				class T,
				class Compare = std::less<Key>,
				class Alloc = std::allocator<ft::pair<const Key, T> >
			>
	class map
	{
		public:
			typedef Key											key_type;
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
					bool operator()( const value_type& lhs, const value_type& rhs ) const{ //for map elements
						return _comp(lhs.first, rhs.first); }// type std::map::value_type (key-value pairs)
			};
		
		private:
			typedef Node<value_type>								Node_type;
			typedef Node_type*										Node_ptr;
			typedef Tree<value_type, key_compare, allocator_type>	Tree_type;
			typedef Tree_type*										Tree_ptr;

			Tree_type		_tree;
			allocator_type	_alloc;
			key_compare		_comp;

			typedef typename Tree_type::iterator			iterator;
			typedef typename Tree_type::const_iterator		const_iterator;
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
		
		public:
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
				_tree(comp, alloc), _alloc(alloc), _comp(comp) {}
			template < class InputIterator >
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
				_tree(comp, alloc), _alloc(alloc), _comp(comp) 
			{insert(first, last);}
			map (const map &oth) { *this = oth; };

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
			const_iterator	begin()	const			{ return (this->_tree.begin()); };
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

			mapped_type	&operator[] (const key_type &k) {return (*(insert(ft::make_pair(k, mapped_type())).first)).second ;}

		public:
			ft::pair<iterator, bool>	insert(const value_type &val)
			{
				iterator	node = iterator(this->_tree.search(val.first));
				if (node != end())
					return (ft::pair<iterator, bool>(node, false));
				Node_ptr insertNode = this->_tree.insert(val);
				return (ft::pair<iterator, bool>(iterator(insertNode), true));
			}
			iterator	insert(iterator position, const value_type &val)
			{
				Node_ptr node = position.base();
				if (val.first > predecessor(node)->key.first && val.first < successor(node)->key.first)
					position = iterator(this->_tree._insertInPosition(node, val));
				else
					position = insert(val).first; // pair iterator kismi icin.
				return position;
			}
			template <class InputIterator>
			void	insert(InputIterator first, InputIterator second)
			{
				while (first != second)
				{
					this->_tree.insert(*first);
					first++;
				}
			}
			void		erase(iterator position) {this->_tree.remove(*position); };
			size_type	erase(const key_type &k)
			{
				size_type s = size();
				this->_tree.remove(*find(k));
				return (s - size());
			}
			void	erase(iterator first, iterator second)
			{
				iterator position;
				while (first != second)
				{
					position = first;
					first++;
					erase(first);
				}
			}
			void	swap (map& oth) { this->_tree.swap(oth._tree); };
			void	clear() { this->_tree.clear(); };
			key_compare		key_comp()	const	{ return (this->_comp); };
			value_compare	value_comp()	const	{ return (value_compare(_comp)); };
	
			iterator		find(const key_type &oth)			{ return (iterator(this->_tree.search(oth))); };
			const_iterator	find(const key_type &oth) const		{ return (const_iterator(this->_tree.search(oth)));};
			size_type		count (const key_type& k) const		{ return (this->find(k) != this->end() ? 1 : 0); };

			iterator		lower_bound (const key_type& k)			{ return (iterator(this->_tree.lower_bound(k))); };
			const_iterator	lower_bound (const key_type& k) const	{ return (const_iterator(this->_tree.lower_bound(k))); };
			iterator		upper_bound (const key_type& k)			{ return (iterator(this->_tree.upper_bound(k))); };
			const_iterator	upper_bound (const key_type& k)	const	{ return (const_iterator(this->_tree.upper_bound(k))); };
			
			pair<const_iterator, const_iterator>	equal_range (const key_type &k)	const	{ return (ft::make_pair(this->lower_bound(k), this->upper_bound(k))); };
			pair<iterator, iterator>				equal_range (const key_type &k)			{ return (ft::make_pair(this->lower_bound(k), this->upper_bound(k))); };
	
			allocator_type	get_allocator() const { return (allocator_type()); };
	};
	template <class Key, class T, class Compare, class Alloc>
	bool operator== (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs) { return ((lhs.size() == rhs.size()) && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));};
	template <class Key, class T, class Compare, class Alloc>
	bool operator!= (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs) { return (!(lhs == rhs));};
	template <class Key, class T, class Compare, class Alloc>
	bool operator<  (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs) { return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));};
	template <class Key, class T, class Compare, class Alloc>
	bool operator<= (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs) { return (!(rhs < lhs));};
	template <class Key, class T, class Compare, class Alloc>
	bool operator>  (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs) { return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));};
	template <class Key, class T, class Compare, class Alloc>
	bool operator>= (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs) { return (!(lhs < rhs));};
	
	template <class Key, class T, class Compare, class Alloc>
	void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y) { x.swap(y); };
}; // namespace ft


#endif