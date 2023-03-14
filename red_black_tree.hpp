#pragma once
#ifndef __RED_BLACK_TREE_HPP__
# define __RED_BLACK_TREE_HPP__

# include "iostream"
# include "tree_iterator.hpp"
# include "utils.hpp"

enum	e_tree_node_color
{
	RED, BLACK
};

namespace ft
{
	template< typename T, /* pair */ typename Key,
		class Allocator, class Compare >
	class red_black_tree
	{

	private:

		class	Node
		{

		public:
			T	data;
			Node	*left;
			Node	*right;
			Node	*parent;
			e_tree_node_color color;

		public:
			Node (const T & heart /* ptr */ = T ())
			: data(heart), left(0), right(0), parent(0) {}

		};

		typedef size_t	size_type;

		typedef typename
		Allocator::template rebind<Node>::other	node_allocator;


		Node		*m_root;//, *m_end;
		Node		*m_end;
		size_t		m_size;
		Compare		m_compare;
		node_allocator	m_allocator;

	public:

		typedef typename
		ft::tree_iterator<T, Node*, Compare> iterator;

		typedef typename
		ft::tree_iterator<const T, Node*, Compare> const_iterator;


		// gaia : constr, deconstr, make_node

		red_black_tree(
			const Compare & C = Compare(),
			const node_allocator & A = node_allocator()
		)
		{
			m_end = create_node();
			m_root = m_end;
			m_size = 0;
			m_compare = C;
			m_allocator = A;
		}

		~ red_black_tree()
		{
			if (m_size) clear();
			_destroy_node(m_root);
		}

		Node	*create_node(const T & val = T ()) // default: RED
		{
			Node	*node; 

			node = m_allocator.construct(node, Node(val));
			node->parent = 0;
			node->left = 0;
			node->right = 0;
			node->color = RED;
			return (node);
		}


		// capapcity

		size_type max_size() const { return (m_allocator.max_size()); }
		size_type empty() const { return (!(m_size)); }
		size_type size() const { return (m_size); }


		// accessor

		iterator	begin()
		{ return (iterator(_min_node())); } // inorder

		const_iterator	begin() const
		{ return const_iterator(_min_node()); } // inorder

		iterator	end()
		{ return iterator(m_end); }

		const_iterator	end() const
		{ return const_iterator(m_end); }

		Compare	compare() const
		{ return m_compare; }


		// modifiers

		void	clear()
		{
			_clear( m_root );
			m_root = m_end;
			m_size = 0;
		}

		void	swap_tree(red_black_tree & dummy)
		{
			ft::swap(m_root, dummy.m_root);
			ft::swap(m_end, dummy.m_end);
			ft::swap(m_size, dummy.m_size);
			ft::swap(m_allocator, dummy.m_allocator);
			ft::swap(m_compare, dummy.m_compare);
		}


		// operations

		// size_type /* size_t */ count(const T & dummy) const
		size_type	count(const T & dummy) const
		{
			Node	*it;

			it = _binary_search_tree_find(dummy);
			return (it ? 1 : 0);
		}

		iterator	lower_bound(const T & dummy)
		{
			iterator	it, ite;

			it = begin();
			ite = end();
			while (it != ite && m_compare(it->first, dummy.first))
			{
				++it;
			}
			return (it);
		}

		const_iterator	lower_bound(const T & dummy) const
		{
			const_iterator it, ite;

			it = begin();
			ite = end();
			while (it != ite && m_compare(it->first, dummy.first))
			{
				++it;
			}
			return (it);
		}

		iterator	upper_bound(const T & dummy)
		{
			const_iterator it, ite;

			it = begin();
			ite = end();
			while (it != ite && m_compare(dummy->first, it.first))
			{
				++it;
			}
			return (it);
		}

		const_iterator	upper_bound(const T & dummy) const
		{
			const_iterator it, ite;

			it = begin();
			ite = end();
			while (it != ite && m_compare(dummy->first, it.first))
			{
				++it;
			}
			return (it);
		}

		iterator	find(const T & dummy)
		{
			Node	*it;

			it = _binary_search_tree_find(dummy);
			return (it ? iterator(it) : (end()));
		}

		// iterator	find(const T & dummy) const
		const_iterator	find(const T & dummy) const
		{
			Node	*it;

			it = _binary_search_tree_find(dummy);
			return (it ? const_iterator(it) : (end()));
		}


		void	swap_values(Node *L, Node *R)
		{
			Key key;
			Key *key1;
			Key	*key2;
			T   tmp;

			key1 = const_cast<Key *>(& L->data.first);
			key2 = const_cast<Key *>(& R->data.first);

			key = *key1;
			*key1 = *key2;
			*key2 = key;

			tmp.second = L->data.second;
			L->data.second = R->data.second;
			R->data.second = tmp.second;
		}

		size_type	node_erase(T p)
		{
			Node	*node;

			if (empty())
				return 0;
			node = _binary_search_tree_find(p);
			if (!node)
				return 0;
			if (m_size == 1)
			{
				clear();
				return (1);
			}
			_binary_search_tree_delete_node(node);
			return (1);
		}

		void	range_erase(iterator first, iterator last)
		{
			size_type	i;
			iterator	it;
			Node		*node;

			node = first.base();
			if (first == begin() && last == end())
			{
				clear();
				return ;
			}
			i = 0;
			it = first;
			while (it != last)
			{
				it++;
				i++;
			}
			while (i)
			{
				node = _binary_search_tree_delete_node(node);
				i--;
			}
		}


	private:

		ft::pair<iterator, bool>	_insert_empty(Node *);

		Node	*_fix_red_uncle(Node *parent, Node *grandparent, Node *uncle);
		void	_fix_double_black(Node *);

		Node	*_binary_search_tree_replace(Node *);

		Node	*_binary_search_tree_find(const T &) const;
		Node	*_min_node() const;
		Node	*_max_node() const;
		Node	*_successor(Node *);
		Node	*_sibling(Node *);
		Node	*_binary_search_tree_delete_node(Node *);

		bool	_is_left_child(Node *) const;
		bool	_has_red_child(Node *);

		void	_left_rotate(Node *);
		void	_right_rotate(Node *);
		void	_move_down(Node * node, Node * parent);

		void	_swap_values(Node *dummy, Node *node);
		void	_binary_search_tree_fix_insert(Node *);

		void	_assign_colors_p_gp(Node *parent, Node *grandparent);
		void	_assign_values(Node *dummy, Node *node);
		void	_assign_end();

		void	_destroy_node(Node *);
		void	_clear(Node *);

	};

}

# include "red_black_tree.tpp"

#endif

