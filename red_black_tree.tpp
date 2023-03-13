#ifndef __RED_BLACK_TREE_TPP__
# define __RED_BLACK_TREE_TPP__

# include "iostream"
# include "tree_iterator.hpp"
# include "utils.hpp"


// template<typename T, typename Key, class Compare, class Allocator> // T is a pair, Key is Key

template<typename T, typename Key, class C, class A> 
typename ft::red_black_tree<T, Key, C, A>::
Node	*ft::red_black_tree<T, Key, C, A>::
_binary_search_tree_find(const T & to_find) const
{
	Node *tmp = m_root;

	while (tmp != NULL && tmp != m_end)
	{
		if (m_compare_type(tmp->data.first, to_find.first))
			tmp = tmp->right;
		else if (m_compare_type(to_find.first, tmp->data.first))
			tmp = tmp->left;
		else
			return tmp;
	}
	return (NULL);
}

template<typename T, typename Key, class C, class A>
typename ft::pair<typename ft::red_black_tree<T, Key, C, A>::iterator, bool>
ft::red_black_tree<T, Key, C, A>::
_insert_empty(typename ft::red_black_tree<T, Key, C, A>::Node *node)
{
	m_root = node;
	m_root->left = NULL;
	m_root->right = m_end;
	m_end->parent = m_root;
	m_root->color = BLACK;
	m_size++;
	return (ft::make_pair(iterator(m_root), true));
}

template<typename T, typename Key, class C, class A>
void	ft::red_black_tree<T, Key, C, A>::
_binary_search_tree_fix_insert(
	typename ft::red_black_tree<T, Key, C, A>::Node *node
)
{
	while (node->parent && node->parent->color == RED)
	{
		if (node->parent->parent->left == node->parent)
		// case: node parent is a left node
		{
			if (node->parent->parent->right && 
				node->parent->parent->right->color == RED
			) // case: uncle right is red
				node = _fix_red_uncle(
					node->parent,
					node->parent->parent,
					node->parent->parent->right
				);
				// parent grandparent uncle
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

			return ;
		}
		// remaining cases: node is a right node
		if (node->parent->parent->left && node->parent->parent->left->color == RED)
		{
			// case: uncle left is red

			node = _fix_red_uncle(
				node->parent,
				node->parent->parent,
				node->parent->parent->left
			);
			// p gp u
		}
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
	m_root->color = BLACK;
}


template<typename T, typename Key, class C, class A> 
typename ft::red_black_tree<T, Key, C, A>::
Node	*ft::red_black_tree<T, Key, C, A>::
_binary_search_tree_delete_node(Node *node)
{
	Node *parent = node->parent;
	Node *child = _binary_search_tree_replace(node);
	Node *res = _successor(node);
	bool both_black = ((child == NULL || child->color == BLACK) && (node->color == BLACK));

	if (!child) // if !child, node is leaf
	{
		if (node == m_root)
			m_root = NULL;
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
		m_size--;
		_assign_end();
		return res;
	}
	if (node->left == NULL || node->right == NULL) // if node has 1 child
	{
		if (node == m_root)
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
		m_size--;
		_assign_end();
		return res;
	}
	// if node has 2 children
	// swap node data with child data recursively
	// until node is a leaf or has one child
	swap_values(child, node);
	_binary_search_tree_delete_node(child);

	return (node);
}


template<typename T, typename Key, class C, class A> 
typename ft::red_black_tree<T, Key, C, A>::
Node	*ft::red_black_tree<T, Key, C, A>::_successor(Node *node)
{
	if (node->right)
	{
		node = node->right;
		while (node->left)
			node = node->left;
		return (node);
	}
	while (node->parent && !_is_left_child(node))
		node = node->parent;
	return (node->parent);
}


template<typename T, typename Key, class C, class A> 
typename ft::red_black_tree<T, Key, C, A>::
Node *ft::red_black_tree<T, Key, C, A>::_binary_search_tree_replace(Node *node)
// find node that replace the deleted one
{
	if (node->left && node->right && node->right != m_end)
	// return the most left subtree node
		return (_successor(node));
	if (!node->left && !node->right)
		return (NULL);
	if (node->left)
		return node->left;
	return node->right;
}


template<typename T, typename Key, class C, class A>
void	ft::red_black_tree<T, Key, C, A>::_move_down(
	typename ft::red_black_tree<T, Key, C, A>::Node *node, 
	typename ft::red_black_tree<T, Key, C, A>::Node *parent
)
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


template<typename T, typename Key, class C, class A>
void	ft::red_black_tree<T, Key, C, A>::_left_rotate(Node *node)
{
	Node *parent = node->right;

	if (node == m_root)
		m_root = parent;
	_move_down(node, parent);
	node->right = parent->left;
	if (parent->left)
		parent->left->parent = node;
	parent->left = node;
}


template<typename T, typename Key, class C, class A>
void	ft::red_black_tree<T, Key, C, A>::_right_rotate(Node *node)
{
	Node	*parent;

	parent = node->left;
	if  (node == m_root)
		m_root = parent;
	_move_down(node, parent);
	node->left = parent->right;
	if (parent->right)
		parent->right->parent = node;
	parent->right = node;
}


template<typename T, typename Key, class C, class A> 
typename ft::red_black_tree<T, Key, C, A>::
Node	*ft::red_black_tree<T, Key, C, A>::_fix_red_uncle(
	Node	*parent,
	Node	*grandparent,
	Node	*uncle
)
{
	uncle->color = BLACK;
	parent->color = BLACK;
	grandparent->color = RED;
	return (grandparent);
}


template<typename T, typename Key, class C, class A>
void	ft::red_black_tree<T, Key, C, A>::_fix_double_black(Node *node)
{
	if (node == m_root)
		return;

	Node	*sibling;// = _sibling(node);
	Node	*parent;// = node->parent;

	sibling = _sibling(node);
	parent = node->parent;
	if (!sibling)
	{
		_fix_double_black(parent);
		return ;
	}
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
	else if ( ! _has_red_child(sibling)) // 2 black kids
	{
		sibling->color = RED ;
		if (parent->color == BLACK)
			_fix_double_black(parent);
		else
			parent->color = BLACK;
	}
	else if (sibling->left && sibling->left->color == RED)
	{
		if (_is_left_child(sibling)) // left left
		{
			sibling->left->color = sibling->color;
			sibling->color = parent->color;

			_right_rotate(parent);
		}
		else // right - left
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
		else // right - right
		{
			sibling->right->color = sibling->color;
			sibling->color = parent->color;

			_left_rotate(parent);
		}
	}
	parent->color = BLACK;
}
/*
else // two black children
}
}
}
*/

template<typename T, typename Key, class C, class A>
void	ft::red_black_tree<T, Key, C, A>::_destroy_node(Node *node)
{
	m_allocator.destroy(node);
	m_allocator.deallocate(node, 1);
}


template<typename T, typename Key, class C, class A> 
typename ft::red_black_tree<T, Key, C, A>::
Node	*ft::red_black_tree<T, Key, C, A>::_sibling(Node *node)
{
	if (!node->parent)
		return (NULL);
	if (_is_left_child(node))
		return ( node->parent->right );
	return ( node->parent->left );
}

template<typename T, typename Key, class C, class A>
bool	ft::red_black_tree<T, Key, C, A>::_is_left_child(Node *node) const
{
	return (node == node->parent->left);
}


template<typename T, typename Key, class C, class A>
bool	ft::red_black_tree<T, Key, C, A>::_has_red_child(Node *node)
{
	return ((node->left && node->left->color == RED) ||
		(node->right && node->right->color == RED)
	);
}


template<typename T, typename Key, class C, class A>
void	ft::red_black_tree<T, Key, C, A>::_clear(Node *node)
{
	if (!node || node == m_end)
		return ;
	_clear(node->left);
	_clear(node->right);
	_destroy_node(node);
}


template<typename T, typename Key, class C, class A>
void	ft::red_black_tree<T, Key, C, A>::_assign_values(
	Node	*dummy,
	Node	*other
)
{
	Key	*key1;
	Key	*key2;

	key1 = const_cast<Key *>(& dummy->data.first);
	key2 = const_cast<Key *>(& other->data.first);
	*key1 = *key2;
	dummy->data.second = other->data.second;
}


template<typename T, typename Key, class C, class A> 
typename ft::red_black_tree<T, Key, C, A>::
Node	*ft::red_black_tree<T, Key, C, A>::_min_node() const
{
	Node    *node;

	node = m_root;
	while (node && node->left)
		node = node->left;
	return (node);
}

template<typename T, typename Key, class C, class A> 
typename ft::red_black_tree<T, Key, C, A>::
Node	*ft::red_black_tree<T, Key, C, A>::_max_node() const
{
	Node    *node;

	node = m_root;
	while (node && node->right && node->right)
		node = node->right;
	return (node);
}


template<typename T, typename Key, class C, class A>
void	ft::red_black_tree<T, Key, C, A>::_assign_colors_p_gp(
	typename ft::red_black_tree<T, Key, C, A>::Node *parent,
	typename ft::red_black_tree<T, Key, C, A>::Node *grandparent
)
{
	parent->color = BLACK;
	grandparent->color = RED;
}


template<typename T, typename Key, class C, class A>
void ft::red_black_tree<T, Key, C, A>::_assign_end(void)
{
	Node	*max_node;

	max_node= _max_node();
	max_node->right = m_end;
	m_end->parent = max_node;
	m_end->color = BLACK;
	m_end->right = NULL;
}


#endif

