#ifndef TREE_HPP
#define TREE_HPP

#include "iterator.hpp"

namespace ft
{
	template < class T>
	struct Node
	{
		public:
			typedef T   value_type;

			T   key;
			Node*   left;
			Node*   right;
			Node*   parent;
			int     height;
		public:
			Node() : key() {}
			Node(T key) : key(key) {}
	};

	template < class T, class Compare, class Allocator>
	class Tree
	{
		public:
			typedef T           value_type;
			typedef Compare     key_compare;
			typedef Allocator   allocator_type;
		private:
			typedef typename allocator_type::template rebind<Node<T> >::other	allocator_node;
			typedef typename allocator_node::reference							node_reference;
			typedef typename allocator_node::const_reference					node_const_reference;
			typedef typename allocator_node::difference_type					node_difference_type;
			typedef typename allocator_node::pointer							node_pointer;
			typedef typename allocator_node::const_pointer						node_const_pointer;
			typedef typename allocator_node::size_type							node_size_type;
			typedef Node<value_type>											Node_type;
			typedef Node_type*													Node_ptr;
		public:
			typedef typename allocator_type::reference							reference;
			typedef typename allocator_type::const_reference					const_reference;
			typedef typename allocator_type::difference_type					difference_type;
			typedef typename allocator_type::pointer							pointer;
			typedef typename allocator_type::const_pointer						const_pointer;
			typedef typename allocator_type::size_type							size_type;
			typedef typename value_type::first_type								key_type;
			typedef typename value_type::second_type							mapped_type;
			typedef ft::TreeIter<pointer, Node_ptr>								iterator;
			typedef ft::TreeIter<const_pointer, Node_ptr>						const_iterator;
			typedef ft::reverse_iterator<iterator>								reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;
		private:
			allocator_node								_alloc;
			key_compare									_comp;
			Node_ptr									_root;
			Node_ptr									_end;
			int											_size;
		public:
			Tree(const key_compare &compare = key_compare(), const allocator_type& alloc = allocator_type()): _comp(compare), _size(0)
			{
				this->_alloc = alloc;
				this->_end = this->_makeNode(value_type());
				this->_root = this->_end;
			};
			~Tree() {};
		public:
			iterator		begin()					{ return (iterator(Min())); };
			const_iterator	begin() const			{ return (const_iterator(Min())); };
			iterator		end()					{ return (iterator(this->_end)); };
			const_iterator	end() const				{ return (const_iterator(this->_end)); };
			reverse_iterator rbegin()				{ return (reverse_iterator(end())); };
			const_reverse_iterator rbegin() const	{ return (const_reverse_iterator(end())); };
			reverse_iterator rend()					{ return (reverse_iterator(begin())); };
			const_reverse_iterator rend() const		{ return (const_reverse_iterator(begin())); };
		public:
			bool empty() const { return (this->_size == 0); };
			size_type size() const { return (this->_size); };
			//alabilecegi max öğe sayisi
			size_type	max_size()	const	{ return (std::min<size_type>(std::numeric_limits<size_type>::max() / sizeof(Node_type), std::numeric_limits<difference_type>::max())); };
		private:/* !!!! */
			void	_destroy(Node_ptr node)
			{
				if (node != nullptr)
				{
					_destroy(node->left);
					_destroy(node->right);
					this->_alloc.destroy(node);
					this->_alloc.deallocate(node, 1);
				}
			};
			Node_ptr _makeNode(value_type key)
			{
				Node_ptr newnode = this->_alloc.allocate(1);
				this->_alloc.construct(newnode, key);
				newnode->height = 1;
				newnode->parent = nullptr;
				newnode->left = nullptr;
				newnode->right = nullptr;
				return (newnode);
			};
			void _deletNode(Node_ptr* node)
			{
				this->_alloc.destroy(*node);
				this->_alloc.deallocate(*node, 1);
				*node = nullptr;
			};
			int		_Height(Node_ptr temp)
			{
				if (temp == nullptr)
					return (0);
				return (temp->height);
			};
			int _getBalanceFactor(Node_ptr N)
			{
				if (N == NULL)
					return 0;
				return (_Height(N->left) - _Height(N->right));
			}
			Node_ptr _leftRotate(Node_ptr Node)
			{
				Node_ptr y = Node->right;
				Node_ptr T2 = y->left;
				Node_ptr p = Node->parent;
				y->left = Node;
				Node->right = T2;
				if (p != this->_end)
				{
					if (p->left == Node)
						p->left = y;
					else
						p->right = y;
				}
				y->parent = Node->parent;
				Node->parent = y;
				if (T2 != nullptr)
					T2->parent = Node;
				Node->height = std::max(_Height(Node->left), _Height(Node->right)) + 1;
				y->height = std::max(_Height(y->left), _Height(y->right)) + 1;
				return y;
			};

			Node_ptr _rightRotate(Node_ptr Node)
			{
				Node_ptr child = Node->left;
				Node_ptr T2 = child->right;
				Node_ptr p = Node->parent;
				child->right = Node;
				Node->left = T2;
				if (p != this->_end)
				{
					if (p->right == Node)
						p->right = child;
					else
						p->left = child;
				}
				child->parent = Node->parent;
				Node->parent = child;
				if (T2 != nullptr)
					T2->parent = Node;
				Node->height = std::max(_Height(Node->left), _Height(Node->right)) + 1;
				child->height = std::max(_Height(child->left), _Height(child->right)) + 1;
				return child;
			};
			Node_ptr _RightLeftRotate(Node_ptr node)
			{
				node->right = _rightRotate(node->right);
				return (_leftRotate(node));
			};

			Node_ptr _LeftRightRotate(Node_ptr node)
			{
				node->left = _leftRotate(node->left);
				return (_rightRotate(node));
			};
			Node_ptr	_reBalance(Node_ptr node)
			{
				int	balanceFactor = _getBalanceFactor(node);
				if (balanceFactor > 1)
				{
					if (_getBalanceFactor(node->left) >= 0)
						return (_rightRotate(node));
					else
						return (_LeftRightRotate(node));
				}
				else if (balanceFactor < -1)
				{
					if (_getBalanceFactor(node->right) <= 0)
						return (_leftRotate(node));
					else
						return (_RightLeftRotate(node));
				}
				return (node);
			};
			Node_ptr	_insert(Node_ptr temp, Node_ptr newNode)
			{
				if (temp == nullptr || temp == this->_end)
					return (newNode);
				if (!this->_comp(temp->key.first, newNode->key.first))
				{
					temp->left = _insert(temp->left, newNode);
					if (temp->left == newNode)
						newNode->parent = temp;
				}
				else if (this->_comp(temp->key.first, newNode->key.first))
				{
					temp->right = _insert(temp->right, newNode);
					if (temp->right == newNode)
						newNode->parent = temp;
				}
				else
					return (temp);
				_ReSetHeight(temp);
				temp = _reBalance(temp);
				return (temp);
			};
			Node_ptr	_remove(Node_ptr root, T key)
			{
				if (root == nullptr) return (nullptr);
				else if (this->_comp(key.first, root->key.first))
					root->left = _remove(root->left, key);
				else if (this->_comp(root->key.first, key.first))
					root->right = _remove(root->right, key);
				else
				{
					if (root->left == nullptr && root->right == nullptr){
						this->_alloc.destroy(root);
						this->_alloc.deallocate(root, 1);
						root = nullptr;
						return (root);
					}
					else if (root->left == nullptr)
					{
						Node_ptr	temp = root;
						root = root->right;
						root->parent = temp->parent;
						this->_alloc.destroy(temp);
						this->_alloc.deallocate(temp, 1);
						temp = nullptr;
						return (root);
					}
					else if (root->right == nullptr)
					{
						Node_ptr	temp = root;
						root = root->left;
						root->parent = temp->parent;
						this->_alloc.destroy(temp);
						this->_alloc.deallocate(temp, 1);
						temp = nullptr;
						return (root);
					}
					else{
						Node_ptr	temp = _TreeMin(root->right);
						value_type p = temp->key;
						root->right = _remove(root->right , temp->key);
						this->_alloc.construct(root, p);
					}
				}
				_ReSetHeight(root);
				root = _reBalance(root);
				return (root);
			};
			Node_ptr _search(Node_ptr temp, key_type key) const
			{
				if (temp == nullptr)
					return (this->_end);

				if (temp->key.first == key)
					return (temp);
				else if (this->_comp(key, temp->key.first))
					return (_search(temp->left, key));
				else if (this->_comp(temp->key.first, key))
					return (_search(temp->right, key));

				return (this->_end);
			};
			void		_ReSetHeight(Node_ptr temp)
			{
				if (!temp->left && !temp->right)
					temp->height = 1;
				else if (temp->left == nullptr)
					temp->height = 1 + temp->right->height;
				else if (temp->right == nullptr || temp->right == this->_end)
					temp->height = 1 + temp->left->height;
				else
					temp->height = 1 + std::max(temp->right->height, temp->left->height);
			};
		public:
			Node_ptr	insert(value_type key)
			{
				Node_ptr newnode = _makeNode(key);
				if (this->_root == this->_end)
				{
					this->_root = newnode;
					this->_root->parent = this->_end;
					this->_end->left = this->_root;
					++this->_size;
				}
				else
				{
					++this->_size;
					this->_root = _insert(this->_root, newnode);
				}
				return (newnode);
			};

			Node_ptr	insertInPossition(Node_ptr position, T key)
			{
				Node_ptr newnode = _makeNode(key);
				if (position == this->_end)
				{
					position = newnode;
					position->parent = this->_end;
					this->_end->left = position;
					++this->_size;
				}
				else
				{
					++this->_size;
					position = _insert(position, newnode);
				}
				return (newnode);
			};

			void	remove(T key)
			{
				this->_root =  _remove(this->_root, key);
			};
			void	clear()
			{
				if (this->_root != this->_end)
				{
					_destroy(this->_root);
					this->_size = 0;
					this->_root = this->_end;
					this->_end->left = this->_root;
				}
			};
			void	swap(Tree &x)
			{
				size_type tmp_size = x._size;
				allocator_type tmp_alloc = x._alloc;
				Node_ptr tmp_root = x._root;
				Node_ptr tmp_end = x._end;

				x._size = this->_size;
				_size = tmp_size;

				x._alloc = this->_alloc;
				this->_alloc = tmp_alloc;

				x._end = this->_end;
				this->_end = tmp_end;

				x._root = this->_root;
				this->_root = tmp_root;
			};
			//aralığındaki değerden büyük olan ilk öğeyi veya böyle bir öğe bulunamazsa son öğeyi
			Node_ptr lower_bound(key_type val) const
			{
				Node_ptr node = Min();

				while (!this->_comp(val, node->key.first))
				{
					if (val == node->key.first)
						break;
					node = successor(node);
					if (node == nullptr || node == this->_end)
					{
						return (this->_end);
					}
				}
				return (node);
			};
			Node_ptr upper_bound(key_type val) const
			{
				Node_ptr node = Min();

				while (!this->_comp(val, node->key.first))
				{
					node = successor(node);
					if (node == nullptr || node == this->_end)
					{
						return (this->_end);
					}
				}
				return (node);
			};
			Node_ptr	Min() const
			{
				Node_type * tmp = this->_root;

				while (tmp != this->_end && tmp->left)
					tmp = tmp->left;
				return (tmp);
			};
			Node_ptr Max() const
			{
				Node_ptr tmp = this->_root;

				while (tmp->right && tmp->right != this->_end)
					tmp = tmp->right;
				return (tmp);
			};
			Node_ptr search(key_type key) const
			{
				if (this->_root == this->_end)
					return (this->_end);
				else
					return (_search(this->_root, key));
			};
			value_type	get_Key() const { return (this->_root->key); };
			int	getSize() const { return (this->_size); };
			value_type	get_height() const { return (this->_root->height); };
	};
	template<class Node_ptr>
	Node_ptr _TreeMin(Node_ptr temp)
	{
		while (temp->left != nullptr)
			temp = temp->left;
		return (temp);
	};

	template<class Node_ptr>
	Node_ptr _TreeMax(Node_ptr temp)
	{
		while (temp->right != nullptr)
			temp = temp->right;
		return (temp);
	};
	//Bir düğümün sıralı ardılı, sağ alt ağacında en az değere 
	//sahip olan düğümdür, yani sağ alt ağacının en soldaki çocuğu.
	/*  Hangi ataların ardıl olduğunu bulmak için, 
	ebeveyninin sol çocuğu olan bir node'la karşılaşana kadar ağaçta köke
	doğru ilerleyebiliriz. Böyle bir node bulunursa, sıra dışı ardıl onun üst öğesidir; */
	template<class Node_ptr>
	Node_ptr successor(Node_ptr node)
	{
		if (node->right)
			return (_TreeMin(node->right));

		Node_ptr temp = node->parent;
		while (temp && temp->right == node)
		{
			node = temp;
			temp = temp->parent;
		}
		return (temp);
	};

	template<class Node_ptr>
	Node_ptr predecessor(Node_ptr node)
	{
		if (node->left)
			return (_TreeMax(node->left));

		Node_ptr temp = node->parent;
		while (temp && temp->left == node)
		{
			node = temp;
			temp = temp->parent;
		}
		if (temp == nullptr)
			return (node);
		return (temp);
	};
};

#endif