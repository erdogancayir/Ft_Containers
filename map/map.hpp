#ifndef MAP_HPP
#define MAP_HPP

#include "tree.hpp"
#include "utils.hpp"

namespace ft
{
	template <	class Key,												// map::key_type
				class T,												// map::mapped_type
				class Compare = std::less<Key>,							// map::key_compare
				class Alloc = std::allocator<ft::pair<const Key,T> >	// map::allocator_type
				>
	class map
    {
        public:
            typedef Key											key_type;
		    typedef T											mapped_type;
		    typedef ft::pair<const key_type, mapped_type>		value_type;
		    typedef	Compare										key_compare;
		    typedef Alloc										allocator_type;
		    typedef typename allocator_type::difference_type	difference_type;
		    typedef typename allocator_type::size_type			size_type;
		    typedef typename allocator_type::reference			reference;
		    typedef typename allocator_type::const_reference	const_reference;
		    typedef typename allocator_type::pointer			pointer;
		    typedef typename allocator_type::const_pointer		const_pointer;
        public:
            class value_compare // key kıyaslamaları icin kullanacagim.
            {
                friend class map;
                protected:
                    Compare _comp;
                    value_compare(Compare c) : _comp(c) {}
                public:
                    typedef bool result_type;
                    typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator()(const value_type &x, const value_type &y) const
					{
						return _comp(x.first, y.first); //firstlerinin cagirarak kiyaslar.
					};
            };
        private:    /* Tree ve Node yapılarım building  */
            typedef Node<value_type>		Node_type; // value_type pair olucak.
            typedef Node_type				*Node_ptr;
            
			typedef Tree<value_type, key_compare, allocator_type>	Tree_type;
			typedef Tree_type										*Tree_ptr;
		public: /* iterator tree's iterator baglanacak. */
			typedef typename Tree_type::iterator				iterator;
			typedef typename Tree_type::const_iterator			const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;//tree nin pointerını alır.
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
		private: /* variables */
			Tree_type		_tree;
			allocator_type	_alloc;
			key_compare		_comp;
		public: /* constructor and destructors*/
			//no param
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
				_tree(comp, alloc), _alloc(alloc), _comp(comp) {};
			//(first, last) iterator maybe. insert eder from first to last.
			template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
				_tree(comp, alloc), _alloc(alloc), _comp(comp) { insert(first, last); };
			map (const map& x) { *this = x; };	//copy constructor
			//_tree 'yi temizler.
			~map() {this->_tree.clear(); };
		public: /* operator */
			map	&operator= (const map& oth)
			{
				if (this != &oth)
				{
					this->_tree.clear();
					this->_comp = oth._comp;
					this->_alloc = oth._alloc;
					insert(oth.begin(), oth.end());
				}
				return (*this);
			};
		public:
			iterator				begin()					{ return (this->_tree.begin()); };
			const_iterator			begin() const			{ return (this->_tree.begin()); };
			iterator				end()					{ return (this->_tree.end()); };
			const_iterator			end() const				{ return (this->_tree.end()); };
			reverse_iterator 		rbegin()				{ return (this->_tree.rbegin()); };
			const_reverse_iterator	rbegin() const			{ return (this->_tree.rbegin()); };
			reverse_iterator 		rend()					{ return (this->_tree.rend()); };
			const_reverse_iterator	rend()	const			{ return (this->_tree.rend()); };
		public: /* Capacity and  Element access*/
			bool		empty() const { return (this->_tree.empty()); };
			size_type	size() const { return (this->_tree.size()); };
			size_type	max_size()	const	{ return (this->_tree.max_size()); };
			mapped_type& operator[] (const key_type& k) { return ((*(insert(ft::make_pair(k, mapped_type())).first)).second); };
		public: /* insters */
			//true or false olarak pair return eder. eger search de val varsa bida eklemez.
			ft::pair<iterator,bool>	insert (const value_type& val) //varmı yokmu kondtrulu yapar _inserte gonderir.
			{
				iterator node = iterator(this->_tree.search(val.first));
				if (node != end())
					return (ft::pair<iterator,bool>(node, false)); //ayni keyden varsa

				Node_ptr inserted_node = this->_tree.insert(val); // val yoktu yenisini ekledi.
				return (ft::pair<iterator,bool>(iterator(inserted_node), true));
			};
			// bi iterator and bi degerde 
			/*  öğenin nereye ekleneceğini bulur. eklenecegi yer dogru degilse eklemez. */
			iterator 				insert (iterator position, const value_type& val)
			{
				Node_ptr node = position.base();
				if (val.first > predecessor(node)->key.first && val.first < successor(node)->key.first)
					position = iterator(this->_tree.insertInPossition(node, val));
				else
					position = insert(val).first;
				return (position);
			};
			// if there are begin and last;
			template <class InputIterator>
			void 					insert (InputIterator first, InputIterator last)
			{
				while (first != last)
				{
					this->_tree.insert(*first);
					first++;
				};
			};
			/* **erase** */
			void		erase (iterator position) { this->_tree.remove(*position); };
			size_type	erase (const key_type &key){
				size_type len = size();
				this->_tree.remove(*find(key));
				return (len - size());
			}
			void		erase (iterator first, iterator last)
			{
				iterator position;
				while(first != last)
				{
					position = first;
					first++;
					erase(position);
				}
			};
			void	swap (map& x)	{ this->_tree.swap(x._tree); };
			void	clear() 		{ this->_tree.clear(); };
			//valuemi verecek.
			key_compare		key_comp()	const	{ return (this->_comp); };
			//new value_compare
			value_compare	value_comp()	const	{ return (value_compare(_comp)); };
		public:
			//k'ye eşdeğer bir key sahip öğe arar ve bulunursa ona bir iterator döndürür, aksi halde map::end için bir iterator döndürür
        	iterator								find (const key_type& k)				{ return (iterator(this->_tree.search(k))); };
			const_iterator							find (const key_type& k)		const	{ return (const_iterator(this->_tree.search(k))); };
			size_type								count (const key_type& k)		const	{ return (this->find(k) != this->end() ? 1 : 0); };
			//key_comp(element_key,k) işlevinin false  dönünce, k ya esdeger deger dondurur. k'den biraz daha büyük olan bir sonraki öğeyi işaret eden bir yineleyici döndürür.
			iterator								lower_bound (const key_type& k)			{ return (iterator(this->_tree.lower_bound(k))); };
			const_iterator							lower_bound (const key_type& k)	const	{ return (const_iterator(this->_tree.lower_bound(k))); };
			//key_comp(k,element_key) true dönen ilk degeri verir.
			iterator								upper_bound (const key_type& k)			{ return (iterator(this->_tree.upper_bound(k))); };
			const_iterator							upper_bound (const key_type& k)	const	{ return (const_iterator(this->_tree.upper_bound(k))); };
			pair<const_iterator, const_iterator>	equal_range (const key_type &k)	const	{ return (ft::make_pair(this->lower_bound(k), this->upper_bound(k))); };
			pair<iterator, iterator>				equal_range (const key_type &k)			{ return (ft::make_pair(this->lower_bound(k), this->upper_bound(k))); }; 


			allocator_type	get_allocator() const { return (allocator_type()); };
	};
	template <class Key, class T, class Compare, class Alloc>
	void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y) { x.swap(y); };

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
};

#endif