#ifndef TREE_HPP
# define TREE_HPP

namespace ft
{
	template < class T >
	struct Node
	{
		public:
			typedef T value_type;

			value_type  key;
			Node        *parent;
			Node		*left;
			Node		*right;
			int			height;

			Node() : key() {}
			Node(value_type val) : key(val) {}
	};
	template <class T, class Compare, class Allocator>
	class Tree
	{
		public:
			typedef T				value_type;
			typedef Compare			key_compare;
			typedef Allocator		allocator_type;
			
			//rebind, ayırıcı sınıfın bir yapı üyesi olarak tanımlanır; bu farklı bir ayırıcı oluşturur bize. Karışmayacak artık.
			typedef typename allocator_type::template rebind< Node<T> >::other	allocator_node;//The member template class rebind provides a way to obtain an allocator for a different type
			typedef typename allocator_node::const_reference					node_const_reference;
			typedef typename allocator_node::difference_type					node_difference_type;
			typedef typename allocator_node::pointer							node_pointer;
			typedef typename allocator_node::const_pointer						node_const_pointer;
			typedef typename allocator_node::size_type							node_size_type;
			
			typedef Node<value_type>											Node_type;
			typedef Node_type													*Node_ptr;
		
		public: /* allacoter_type   -*** */
			typedef typename allocator_type::reference							reference;
			typedef typename allocator_type::const_reference					const_reference;
			typedef typename allocator_type::difference_type					difference_type;
			typedef typename allocator_type::pointer							pointer;
			typedef typename allocator_type::const_pointer						const_pointer;
			typedef typename allocator_type::size_type							size_type;

			typedef typename value_type::first_type								key_type;
			typedef typename value_type::seconde_type							mapped_type;

			typedef ft::TreeIter<pointer, Node_ptr>								iterator;
			typedef ft::TreeIter<const_pointer, Node_ptr>		               	const_iterator;
			typedef ft::reverse_iterator<iterator>								reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>                        const_reverse_iterator;
		
		private:
		    allocator_node								_alloc;
			key_compare									_comp;
			Node_ptr									_root;
			Node_ptr									_end;
			int											_size;
		
		public:
			Tree(const key_compare &compare = key_compare(), const allocator_type& alloc = allocator_type()): _size(0), _comp(compare)
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
			bool		empty() 	const	{ return (!this->_size); };
			size_type	size() 		const	{ return (this->_size); };
			size_type	max_size()	const	{ return (this->_alloc.max_size()); };

			int	getSize() const { return (this->_size); };
			value_type	get_Key() const { return (this->_root->key); };
			value_type	get_height() const { return (this->_root->height); };

			Node_ptr	_makeNode(value_type key)
			{
				Node_ptr	node = this->_alloc.allocate(1);
				this->_alloc.construct(node, key);
				node->height = 1;
				node->left = node->right = nullptr;
				node->parent = nullptr;
				return (node);
			}

			int	_Height(Node_ptr node)
			{
				if (node == NULL)
					return (0);
				return (node->height);
			}

			int _getBalanceFactor(Node_ptr node)
			{
				if (node == NULL)
                    return (0);
				return (_Height(node->left) - _Height(node->right));
			}
			Node_ptr	_reBalance(Node_ptr node)
			{
				int balanceFactor = _getBalanceFactor(node);
				if (balanceFactor > 1)
				{
					if (_getBalanceFactor(node->left) >= 0)
						return _rightRotate(node);
					else //düzlestirmek icin yapiyorum.
					{
						node->left = _leftRotate(node->left);
						return (_rightRotate(node));
					}
				}
				else if (balanceFactor < 1)
				{
					if (_getBalanceFactor(node->right) <= 0)
						return _leftRotate(node);
					else //düzlestirmek icin yapiyorum.
					{
						node->right = _rightRotate(node->right);
						return (_leftRotate(node));
					}
				}
				return (node);
			}
			void	_ReSetHeight(Node_ptr temp)
			{
				if (!temp->left && !temp->right)
					temp->height = 1;
				else if (temp->left == nullptr)
					temp->height = 1 + temp->right->height;
				else if (temp->right == nullptr || temp->right == this->_end)
					temp->height = 1 + temp->left->height;
				else
					temp->height = 1 + std::max(temp->right->height, temp->left->height);
			}
			//create a node with val key and add to Node_ptr
			Node_ptr	insert(value_type val)
			{
				Node_ptr newNode = _makeNode(val);
				if (this->_root == this->_end) // beginning
				{
					this->_root = newNode;
					this->_size++;
					this->_root->parent = this->_end;
					this->_end->left = this->_root;
				}
				else{
					this->_size++;
					this->_root = _insert(this->_root, newNode);
				}
				return (newNode);
			}
			//to add to left or right
			Node_ptr	_insert(Node_ptr temp, Node_ptr newNode)
			{
				if (temp == NULL || temp == this->_end)
					return (newNode);
				if (!this->_comp(temp->key.first, newNode->key.first))
				{
					temp->left = _insert(temp->left, newNode);
					if (temp->left == newNode)
						newNode->parent = temp;
				}
				else if (this->_comp(temp->key.first, newNode))
				{
					temp->right = _insert(temp->right, newNode);
					if (temp->right == newNode)
					    newNode->parent = temp;
				}
				else
					return (temp);
				_ReSetHeight(temp); //yüksekliğini güncelledim.
				temp = _reBalance(temp); // rotate varmi diye baktim.
				return (temp);
			}
			Node_ptr	_insertInPosition(Node_ptr position, T key)
			{
				Node_ptr newNode = _makeNode(key);
				if (position == this->_end)
				{
					position = newNode;
					position->parent = this->_end;
					this->_end->left = position;
					this->_size++;
				}
				else
				{
					this->_size++;
					position = _insert(position, newNode);
				}
				return (newNode);
			}
			Node_ptr	_leftRotate(Node_ptr node)
			{
				Node_ptr y = node->right;
				Node_ptr t = y->left;
				Node_ptr p = node->parent;
				y->left = node;
				node->right = T2;
				if (p != this->_end)
				{
					if (p->right == node)
						p->left = y;
					else
						p->right = y;
				}
				y->parent = node->parent;
				node->parent = y;
				if (t != nullptr)
					t->parent = node;
				x->height = std::max(_Height(nodex->left), _Height(node->right)) + 1;
				y->height = std::max(_Height(y->left), _Height(y->right)) + 1;
				return y;
			}
			Node_ptr	_rightRotate(Node_ptr Node)
			{
				Node_ptr y = Node->left;
				Node_ptr t = y->right;
				Node_ptr p = Node->parent;
			    y->right = Node;
                Node->left = T2;
				if (p != this->_end)
				{
					if (p->left == Node)
						p->left = y;
					else
						p->right = y;
				}
				y->parent = Node->parent;
                Node->parent = y;
				if (t != nullptr)
					t->parent = Node;
				Node->height = std::max(_Height(Node->left), _Height(Node->right));
				y->height = std::max(_Height(y->left), _Height(y->right)) + 1;
				return (y);
			}
			Node_ptr	_search(Node_ptr node, key_type key) const
			{
				if (node == nullptr)
					return this->_end;
				if (node->key.first == key)
					return node;
				else if (this->_comp(key, node->key.first))
					return (_searh(node->left, key));
				else if (this->_comp(node->key.first, key));
					return (_search(node->right, key));
				return (this->_end);
			}
			Node_ptr	_remove(Node_ptr root, T key)
			{
				if (root == nullptr)
                    return nullptr;
				else if (this->_comp(key.first, root->key.first))
					this->left = _remove(root->left, key);
				else if (this->_comp(root->key.first, key.first))
					this->right = _remove(root->right, key);
				else
				{
					if (root->left == nullptr && root->right == nullptr)
					{
						this->_alloc.destroy(root);
						this->_alloc.deallocate(root, 1);
						root = nullptr;
						return (root);
					}
					else if (root->left == nullptr)
					{
						Node_ptr temp = root;
						root = root->right;
						root->parent = temp->parent;
						this->_alloc.destroy(temp);
						this->_alloc.deallocate(temp, 1);
						temp = nullptr;
						return (root);
					}
					else if (root->right == nullptr)
					{
						Node_ptr temp = root;
						root = root->left;
						root->parent = temp->parent;
						this->_alloc.destroy(temp);
						this->_alloc.deallocate(temp, 1);
						temp = nullptr;
                        return (root);
					}
					else
					{
						Node_ptr temp = _TreeMin(root->right);
						value_type min = temp->key;
						root->right = _remove(root->right, temp->key);
						this->_alloc.construct(root, min);
					}
				}
				_ReSetHeight(root);
				root = _reBalance(root);
				return (root);
			}
			void	remove(T key)
			{
				this->root = _remove(this->_root, key);
			}
			void	_destroy(Node_ptr node)
			{
				if (node)
				{
					_destroy(node->right);
					_destroy(node->left);
                    this->_alloc.destroy(node);
					this->_alloc.deallocate(node, 1);
				}
			}
			void	_deleteNode(Node_ptr *node)
			{
				this->_alloc.destroy(*node);
				this->_alloc.deallocate(*node, 1);
				*node = nullptr;
			}
			void    clear()
            {
				if (this->_root != this->_end)
				{
					_destroy(this->_root);
					this->_size = 0;
					this->_root = this->_end;
					this->_end->left = this->_root;
				}
			}
			void	swap(Tree &_tree_)
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
			}
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
		//aralığındaki değerden büyük olan ilk öğeyi veya böyle bir öğe bulunamazsa son öğeyi
		// aralık valueden kucuk degerler.
			/* Input : 10 20 30 40 50
			Output : upper_bound for element 45 is at index 4 */
			Node_ptr	upper_bound(key_type key) const
			{
				Node_ptr temp = Min();
				while (!this->_comp(val, node->key.first))
				{
					node = successor(temp);
					if (node == nullptr || node == this->_end)
						return this->_end;
				}
				return (node);
			}
			//Input: 10 20 30 40 50
			//Output: lower_bound for element 35 at index 3
			Node_ptr	lower_bound(key_type key) const
			{
				Node_ptr node = Min();

				while (!this->_comp(val, node->key.first))
				{z
					if (val == node->key.first)
						break;
					node = successor(node);
					if (node == nullptr || node == this->_end)
					{
						return (this->_end);
					}
				}
				return (node);
			}
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
		else
			return (temp);
	}
};


#endif