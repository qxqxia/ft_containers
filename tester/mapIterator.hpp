#ifndef MAPITERATOR_HPP
#define MAPITERATOR_HPP

#include <iostream>
#include <cstddef>

#include "iterator.hpp"
#include "templates.hpp"

namespace ft
{
    template <class T, class Node, class Compare, class tree>
    class mapIterator : public ft::iterator<std::bidirectional_iterator_tag, T>
    {
    public:
        typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::iterator_category iterator_category;
        typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::value_type value_type;
        typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::difference_type difference_type;
        typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::pointer pointer;
        typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::reference reference;

    public:
        /*constructor and destructor*/
        mapIterator() : _tree(), _ptr(), _cmp() {}
        mapIterator(Node *node, const tree *other) : _ptr(node), _tree(other) {}
        mapIterator(mapIterator const &src) { *this = src; }
        virtual ~mapIterator() {}
        Node *base() const { return (_ptr); }
        mapIterator &operator=(const mapIterator &rhs)
        {
            _ptr = rhs._ptr;
            _tree = rhs._tree;
            _cmp = rhs._cmp;
            return *this;
        }

        operator mapIterator<const T, const Node, Compare, tree>() const
        {
            return mapIterator<const T, const Node, Compare, tree>(_ptr, _tree);
        }

        // Returns a pointer to the root pointed to by the iterator (in order to access one of its members).
        T *operator->() const { return (_ptr->data); }
        T &operator*() const { return (*_ptr->data); }
        // Increment iterator position  ++key
        mapIterator &operator++()
        {
            Node *p;
            if (_ptr == nullptr)
                return (*this = mapIterator(_tree->findmin(_tree->getRoot()), _tree));
            if (_ptr == _tree->findmax(_tree->getRoot()))
                return (*this = mapIterator(nullptr, _tree));
            if (_ptr->right != nullptr)
            {
                _ptr = _ptr->right;
                while (_ptr->left != nullptr)
                    _ptr = _ptr->left;
            }
            else
            {
                p = _ptr->parent;
                while (p != nullptr && _ptr == p->right)
                {
                    _ptr = p;
                    p = p->parent;
                }
                _ptr = p;
            }
            return (*this);
        }

        // The post-increment version
        mapIterator operator++(int)
        {
            mapIterator tmp(*this);
            ++(*this);
            return tmp;
        }

        // Decreases iterator position --key
        mapIterator &operator--()
        {
            Node *p;
            if (_ptr == nullptr)
                _ptr = _tree->findmax(_tree->getRoot());
            else
            {
                if (_ptr->left != nullptr)
                {
                    _ptr = _ptr->left;
                    while (_ptr->right != nullptr)
                        _ptr = _ptr->right;
                }
                else
                {
                    p = _ptr->parent;
                    while (p != nullptr && _ptr == p->left)
                    {
                        _ptr = p;
                        p = p->parent;
                    }
                    _ptr = p;
                }
            }
            return (*this);
        }

        // The post-increment version
        mapIterator operator--(int)
        {
            mapIterator tmp(*this);
            operator--();
            return tmp;
        }

        friend bool operator==(mapIterator const &lhs, mapIterator const &rhs)
        {
            return (lhs._ptr == rhs._ptr);
        }

        friend bool operator!=(mapIterator const &lhs, mapIterator const &rhs)
        {
            return (lhs._ptr != rhs._ptr);
        }

    private:
        Node *_ptr;
        tree const *_tree;
        Compare _cmp;
    };
}

#endif
