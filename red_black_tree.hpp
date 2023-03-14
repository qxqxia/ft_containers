#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include <memory>
#include <iostream>
#include "utils.hpp"
#include "tree_iterator.hpp"

enum e_color
{
	RED,
	BLACK
};

namespace ft
{
	template <typename T, typename K, class Compare, class Alloc> // T is a pair, K is key_type
	class red_black_tree
	{
		private :
			typedef T	value_type;

			// Private nested struct, for each nodes
			struct Node
			{
				value_type	data;
				e_color		color;
				Node		*left;
				Node		*right;
				Node		*parent;

				Node(const value_type& p = value_type()) : data(p), left(NULL), right(NULL), parent(NULL) {}
			};

			typedef size_t													size_type;
			typedef K														key_type;
			typedef Compare													compare_type;
			typedef Alloc													allocator_type;
			typedef value_type*												pointer;
			typedef	Node*													node_pointer;
			typedef const Node*												const_node_pointer;
			typedef const value_type&										const_reference;
			typedef typename allocator_type::template rebind<Node>::other	node_allocator;

			node_pointer	_root;
			node_pointer	_end;
			size_type		_size;
			node_allocator	_node_alloc;
			compare_type	_comp;

		public :
			typedef typename ft::tree_iterator<value_type, node_pointer, compare_type>			iterator;
			typedef typename ft::tree_iterator<const value_type, node_pointer, compare_type>	const_iterator;

			red_black_tree(const compare_type& comp = compare_type(), const node_allocator& node_alloc = node_allocator())
			{
				_node_alloc = node_alloc;
				_end = create_node();
				_root = _end;
				_size = 0;
				_comp = comp;
			}

			~red_black_tree()
			{
				if (_size)
					clear();
				_destroy_node(_root);
			}

			node_pointer	create_node(const_reference value = value_type())
			{
				node_pointer node = _node_alloc.allocate(1);

				_node_alloc.construct(node, Node(value));
				node->color = RED;
				node->left = NULL;
				node->right = NULL;
				node->parent = NULL;
				return node;
			}

			// ==================== Capacity
			bool	empty() const
			{
				return _size == 0;
			}

			size_type	size() const
			{
				return _size;
			}

			size_type	max_size() const
			{
				return _node_alloc.max_size();
			}

			// ==================== Accessor
			iterator	begin()
			{
				return iterator(_min_node());

			}

			const_iterator	begin() const
			{
				return const_iterator(_min_node());
			}

			iterator	end()
			{
				return iterator(_end);
			}

			const_iterator	end() const
			{
				return const_iterator(_end);
			}

			compare_type	comp() const
			{
				return _comp;
			}

			// ==================== Operations

			iterator	find(const_reference val)
			{
				node_pointer ret = _bst_find(val);

				if (!ret)
					return end();
				return iterator(ret);
			}

			const_iterator	find(const_reference val) const
			{
				node_pointer ret = _bst_find(val);

				if (!ret)
					return end();
				return const_iterator(ret);
			}

			size_type	count(const_reference val) const
			{
				node_pointer ret = _bst_find(val);

				if (!ret)
					return 0;
				return 1;
			}

			iterator	lower_bound(const_reference val)
			{
				iterator it = begin();
				iterator ite = end();

				for (; it != ite; it++)
				{
					if (!(_comp(it->first, val.first)))
						return (it);
				}
				return (it);
			}

			const_iterator	lower_bound(const_reference val) const
			{
				const_iterator it = begin();
				const_iterator ite = end();

				for (; it != ite; it++)
				{
					if (!(_comp(it->first, val.first)))
						return (it);
				}
				return (it);
			}

			iterator	upper_bound(const_reference val)
			{
				iterator it = begin();
				iterator ite = end();

				for(; it != ite; it++)
				{
					if (_comp(val.first, it->first))
						return (it);
				}
				return (it);
			}

			const_iterator	upper_bound(const_reference val) const
			{
				const_iterator it = begin();
				const_iterator ite = end();

				for(; it != ite; it++)
				{
					if (_comp(val.first, it->first))
						return (it);
				}
				return (it);
			}

			// ==================== Modifiers

			ft::pair<iterator, bool>	insert(const_reference val)
			{
				node_pointer node = create_node(val);
				node_pointer tmp = _root;
				node_pointer parent = NULL;

				if (empty())
					return _insert_empty(node);
				while (tmp != NULL && tmp != _end) // Find if already a node with the same key, if not, give pos for new node
				{
					parent = tmp;
					if (_comp(val.first, tmp->data.first))
						tmp = tmp->left;
					else if (_comp(tmp->data.first, val.first))
						tmp = tmp->right;
					else
					{
						_destroy_node(node);
						_assign_end();
						return ft::make_pair(iterator(tmp), false); // already a node
					}
				}
				node->parent = parent;
				if (_comp(val.first, parent->data.first))
					parent->left = node;
				else
					parent->right = node;
				_bst_fix_insert(node);
				_assign_end();
				_size++;
				return ft::make_pair(iterator(node), true);
			}

			void	clear()
			{
				_clear(_root);
				_root = _end;
				_size = 0;
			}

			void	swap_tree(red_black_tree &x)
			{
				ft::_swap(_root, x._root);
				ft::_swap(_end, x._end);
				ft::_swap(_size, x._size);
				ft::_swap(_node_alloc, x._node_alloc);
				ft::_swap(_comp, x._comp);
			}

			size_type	node_erase(value_type val)
			{
				node_pointer node;

				if (empty())
					return 0;
				node = _bst_find(val);
				if (!node)
					return 0;
				if (_size == 1)
				{
					clear();
					return 1;
				}
				_bst_delete_node(node);
				return 1;
			}

			void	range_erase(iterator first, iterator last)
			{
				size_type i = 0;
				node_pointer tmp = first.base();

				if (first == begin() && last == end())
				{
					clear();
					return;
				}
				for (iterator it = first; it != last; it++)
					i++;
				while (i)
				{
					tmp = _bst_delete_node(tmp);
					i--;
				}
			}

		// Private helpers
		private :

			node_pointer	_bst_find(const_reference to_find) const
			{
				node_pointer tmp = _root;

				while (tmp != NULL && tmp != _end)
				{
					if (_comp(tmp->data.first, to_find.first))
						tmp = tmp->right;
					else if (_comp(to_find.first, tmp->data.first))
						tmp = tmp->left;
					else
						return tmp;
				}
				return NULL;
			}

			ft::pair<iterator, bool>	_insert_empty(node_pointer node)
			{
				_root = node;
				_root->left = NULL;
				_root->right = _end;
				_end->parent = _root;
				_root->color = BLACK;
				_size++;
				return ft::make_pair(iterator(_root), true);
			}

			void	_bst_fix_insert(node_pointer node)
			{
				while (node->parent && node->parent->color == RED)
				{
					if (node->parent->parent->left == node->parent) // if node parent is a left node
					{
						if (node->parent->parent->right && node->parent->parent->right->color == RED) // if uncle right is red
							node = _fix_red_uncle(node->parent, node->parent->parent, node->parent->parent->right); // p gp u
						else
						{
							if (node == node->parent->right)
							{
								node = node->parent;
								_left_rotate(node);
							}
							_assign_colors_p_gp(node->parent, node->parent->parent);
							_right_rotate(node->parent->parent);
						}
					}
					else // if node is a right node
					{
						if (node->parent->parent->left && node->parent->parent->left->color == RED) // if uncle left is red
							node = _fix_red_uncle(node->parent, node->parent->parent, node->parent->parent->left); // p gp u
						else
						{
							if (node == node->parent->left)
							{
								node = node->parent;
								_right_rotate(node);
							}
							_assign_colors_p_gp(node->parent, node->parent->parent);
							_left_rotate(node->parent->parent);
						}
					}
				}
				_root->color = BLACK;
			}

			node_pointer	_bst_delete_node(node_pointer node)
			{
				node_pointer parent = node->parent;
				node_pointer child = _bst_replace(node);
				node_pointer ret = _successor(node);
				bool both_black = ((child == NULL || child->color == BLACK) && (node->color == BLACK));

				if (!child) // if !child, node is leaf
				{
					if (node == _root)
						_root = NULL;
					else
					{
						if (both_black)
							_fix_double_black(node);
						else if (_sibling(node))
							_sibling(node)->color = RED;
						if (_is_left_child(node))
							parent->left = NULL;
						else
							parent->right = NULL;
					}
					_destroy_node(node);
					_size--;
					_assign_end();
					return ret;
				}
				if (node->left == NULL || node->right == NULL) // if node has 1 child
				{
					if (node == _root)
					{
						_assign_values(node, child);
						_destroy_node(child);
						node->left = NULL;
						node->right = NULL;
					}
					else
					{
						if (_is_left_child(node))
							parent->left = child;
						else
							parent->right = child;
						_destroy_node(node);
						child->parent = parent;
						if (both_black)
							_fix_double_black(child);
						else
							child->color = BLACK;
					}
					_size--;
					_assign_end();
					return ret;
				}
				// if node has 2 children, swap node data with child data and recursion until node if a leaf or has one child
				_swap_values(child, node);
				_bst_delete_node(child);
				return node; // return node because of the swap
			}

			node_pointer	_successor(node_pointer node)
			{
				if (node->right)
				{
					node = node->right;
					while (node->left)
						node = node->left;
					return node;
				}
				while (node->parent && !_is_left_child(node))
					node = node->parent;
				return node->parent;
			}

			node_pointer	_bst_replace(node_pointer node) // find node that replace the deleted one
			{
				if (node->left && node->right && node->right != _end) // return the most left subtree node
					return _successor(node);
				if (!node->left && !node->right)
					return NULL;
				if (node->left)
					return node->left;
				return node->right;
			}

			void	_move_down(node_pointer node, node_pointer parent)
			{
				if (node->parent)
				{
					if (_is_left_child(node))
						node->parent->left = parent;
					else
						node->parent->right = parent;
				}
				parent->parent = node->parent;
				node->parent = parent;
			}

			/* Left rotate
			To go from (rotation around 5) :
			  5
			/  \
		   /   \
		  2    10
			  / \
			 /   \
			8    12
		   / \
		  /  \
		 6	 9
	----------------------
			To :
			10
		   /  \
		  /    \
		5      12
	   / \
	  /   \
	 2    8
		 / \
		/   \
	   6    9
			*/

			void	_left_rotate(node_pointer node)
			{
				node_pointer parent = node->right;

				if (node == _root)
					_root = parent;
				_move_down(node, parent);
				node->right = parent->left;
				if (parent->left)
					parent->left->parent = node;
				parent->left = node;
			}

			/* Right rotate

			To go from (rotation around 10) :
			10
		   / \
		  /  \
		 5   12
		/ \
	   /  \
	  2   8
		 / \
		/  \
	   6	9
	----------------------
			To :
			5
		   / \
		  /   \
		 2    10
			 / \
			/  \
		   8    12
		  / \
		 /  \
		6	9
			*/

			void	_right_rotate(node_pointer node)
			{
				node_pointer parent = node->left;

				if  (node == _root)
					_root = parent;
				_move_down(node, parent);
				node->left = parent->right;
				if (parent->right)
					parent->right->parent = node;
				parent->right = node;
			}

			node_pointer	_fix_red_uncle(node_pointer p, node_pointer gp, node_pointer u)
			{
				p->color = BLACK;
				u->color = BLACK;
				gp->color = RED;
				return gp;
			}

			void	_fix_double_black(node_pointer node)
			{
				if (node == _root)
					return;
				node_pointer sibling = _sibling(node);
				node_pointer parent = node->parent;

				if(!sibling)
					_fix_double_black(parent);
				else
				{
					if (sibling->color == RED)
					{
						parent->color = RED;
						sibling->color = BLACK;
						if (_is_left_child(sibling))
							_right_rotate(parent);
						else
							_left_rotate(parent);
						_fix_double_black(node);
					}
					else // sibling black
					{
						if (_has_red_child(sibling))
						{
							if (sibling->left && sibling->left->color == RED)
							{
								if (_is_left_child(sibling)) // left left
								{
									sibling->left->color = sibling->color;
									sibling->color = parent->color;
									_right_rotate(parent);
								}
								else // right left
								{
									sibling->left->color = parent->color;
									_right_rotate(sibling);
									_left_rotate(parent);
								}
							}
							else
							{
								if (_is_left_child(sibling)) // left right
								{
									sibling->right->color = parent->color;
									_left_rotate(sibling);
									_right_rotate(parent);
								}
								else // right right
								{
									sibling->right->color = sibling->color;
									sibling->color = parent->color;
									_left_rotate(parent);
								}
							}
							parent->color = BLACK;
						}
						else // two black children
						{
							sibling->color = RED;
							if (parent->color == BLACK)
								_fix_double_black(parent);
							else
								parent->color = BLACK;
						}
					}
				}
			}

			void	_destroy_node(node_pointer node)
			{
				_node_alloc.destroy(node);
				_node_alloc.deallocate(node, 1);
			}

			node_pointer	_sibling(node_pointer node)
			{
				if (!node->parent)
					return NULL;
				if (_is_left_child(node))
					return node->parent->right;
				return node->parent->left;
			}

			bool	_is_left_child(node_pointer node) const
			{
				return node == node->parent->left;
			}

			bool	_has_red_child(node_pointer node)
			{
				return ((node->left && node->left->color == RED) || (node->right && node->right->color == RED));
			}

			void	_clear(node_pointer node)
			{
				if (!node || node == _end)
					return ;
				_clear(node->left);
				_clear(node->right);
				_destroy_node(node);
			}

			void	_assign_values(node_pointer x, node_pointer y) // Can't find another way since key_type are const from map erase
			{
				key_type* key1;
				key_type* key2;

				key1 = const_cast<key_type*>(&x->data.first);
				key2 = const_cast<key_type*>(&y->data.first);

				*key1 = *key2;
				x->data.second = y->data.second;
			}

			void	_swap_values(node_pointer x, node_pointer y) // Can't find another way since key_type are const from map erase
			{
				key_type	key;
				key_type	*key1;
				key_type	*key2;
				value_type	tmp;

				key1 = const_cast<key_type *>(&x->data.first);
				key2 = const_cast<key_type *>(&y->data.first);

				key = *key1;
				*key1 = *key2;
				*key2 = key;

				tmp.second = x->data.second;
				x->data.second = y->data.second;
				y->data.second = tmp.second;
			}

			node_pointer	_min_node() const
			{
				node_pointer min = _root;

				while (min && min->left != NULL)
					min = min->left;
				return min;
			}

			node_pointer	_max_node() const
			{
				node_pointer max = _root;

				while (max && max->right != NULL && max->right != _end)
					max = max->right;
				return max;
			}

			void	_assign_colors_p_gp(node_pointer p, node_pointer gp)
			{
				p->color = BLACK;
				gp->color = RED;
			}

			void	_assign_end()
			{
				node_pointer max_node = _max_node();

				max_node->right = _end;
				_end->parent = max_node;
				_end->right = NULL;
				_end->color = BLACK;
			}

///////////////////////////////////////////////////////////////////////////////////////

			// void	printHelper(node_pointer root, std::string indent, bool last)
			// {
			// 	if (root != NULL)
			// 	{
			// 		std::cout << indent;
			// 		if (last)
			// 		{
			// 			std::cout << "R---- ";
			// 			indent += "   ";
			// 		}
			// 		else
			// 		{
			// 			std::cout << "L---- ";
			// 			indent += "|  ";
			// 		}

			// 		std::string sColor = "BLACK";
			// 		if (root->color == RED)
			// 			sColor = "RED";
			// 		std::cout << root->data.second << " (" << sColor << ")" << std::endl;
			// 		printHelper(root->left, indent, false);
			// 		printHelper(root->right, indent, true);
			// 	}
			// }

			// void	print_red_black_tree()
			// {
			// 	if (_root)
			// 		printHelper(_root, "", true);
			// }

///////////////////////////////////////////////////////////////////////////////////////
	};
} // namespace ft


#endif
