#ifndef MAP_HPP
#define MAP_HPP

#include "iterator.hpp"
#include "mapIterator.hpp"
#include "templates.hpp"
#include <iostream>
#include "AVL.hpp"
#include "vector.hpp"

namespace ft
{
    // ft::less
    template <class T>
    class less
    {
    public:
        bool operator()(const T &x, const T &y) const { return x < y; } // x < y is true
    };
    // ft::map
    template <class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<pair<const Key, T> > >
	class map
	{
		
    public:
        typedef Key                                                                         key_type;
        typedef T                                                                           mapped_type;
        typedef Compare                                                                     key_compare;
        typedef Alloc                                                                       allocator_type;
        typedef ft::pair<const key_type, mapped_type>                                       value_type;

        typedef typename allocator_type::reference                                          reference;
        typedef typename allocator_type::const_reference                                    const_reference;
        typedef typename allocator_type::pointer                                            pointer;
        typedef typename allocator_type::const_pointer                                      const_pointer;
        typedef ft::AVL_tree<value_type, Compare, Alloc>                                    tree;
        typedef typename ft::AVL_tree<value_type, Compare, Alloc>::iterator                 iterator;
        typedef typename ft::AVL_tree<value_type, Compare, Alloc>::const_iterator           const_iterator;
        typedef typename ft::AVL_tree<value_type, Compare, Alloc>::reverse_iterator         reverse_iterator;
        typedef typename ft::AVL_tree<value_type, Compare, Alloc>::const_reverse_iterator   const_reverse_iterator;
        typedef std::ptrdiff_t                                                              difference_type;
        typedef size_t                                                                      size_type;

        // value_compare
        class value_compare : public std::binary_function<value_type, value_type, bool>
        {
            friend class map;

            protected:
                Compare comp; // less<Key>
                value_compare(Compare c) : comp(c) {}

            public:
                typedef bool result_type;
                typedef value_type first_argument_type;
                typedef value_type second_argument_type;

                bool operator()(const value_type &lhs, const value_type &rhs) const
                {
                    return comp(lhs.first, rhs.first);
                }
        };

    private:
            tree            _avl;
            allocator_type  _alloc;
            key_compare     _cmp;
    public:
        // coplien form
        explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _alloc(alloc), _cmp(comp) {}

        template <class InputIt>
        map(InputIt first, InputIt last,
            const key_compare &comp = key_compare(),
            const allocator_type &alloc = allocator_type()) : _alloc(alloc), _cmp(comp)
        {
            for (; first != last; first++)
                _avl.insert(*first);
        }

        map(const map &x) : _avl(x._avl), _alloc(x._alloc), _cmp(x._cmp) {}

        ~map() {}

        map &operator=(const map &x)
        {
            _alloc = x._alloc;
            _cmp = x._cmp;
            _avl = _avl.assign(x._avl);
            return (*this);
        }
        // iterators
        iterator begin() { return (_avl.begin()); }

        const_iterator begin() const { return (_avl.begin()); }

        iterator end() { return (_avl.end()); }

        const_iterator end() const { return (_avl.end()); }

        reverse_iterator rbegin() { return (_avl.rbegin()); }

        const_reverse_iterator rbegin() const { return (_avl.rbegin()); }

        reverse_iterator rend() { return (_avl.rend()); }

        const_reverse_iterator rend() const { return (_avl.rend()); }

        // capacity
        bool empty() { return (_avl.empty()); }

        size_type size() const {return _avl.size(); }

        size_type max_size() const { return (_avl.get_alloc()); }

        // element access
        mapped_type &operator[](const key_type &k)
        {
            if (_avl.find(k) == nullptr)
                return (insert(ft::make_pair(k, mapped_type())).first)->second;
            return (_avl.find(k)->data->second);
        }

        // modifiers
        // insert
        ft::pair<iterator, bool> insert(const value_type &val)
        {
            bool sec = _avl.insert(val);
            iterator first = iterator(_avl.find(val.first), &_avl);
            ft::pair<iterator, bool> ret = ft::make_pair(first, sec);
            return (ret);
        }

        iterator insert(iterator position, const value_type &val)
        {
            (void)position;
            _avl.insert(val);
            return (iterator(_avl.find(val.first), &_avl));
        }

        template <class InputIterator>
        void insert(InputIterator first, InputIterator last)
        {
            for (; first != last; first++)
                _avl.insert(*first);
            return;
        }

        // erase
        void erase(iterator position)
        {
            key_type x = position->first;
            _avl.delete(x);
            return;
        }

        size_type erase(const key_type &k)
        {
            return (_avl.delete(k));
        }

        void erase(iterator first, iterator last)
        {
            ft::vector<key_type> keys;
            while (first != last)
            {
                keys.push_back(first->first);
                first++;
            }
            for (size_t i = 0; i < keys.size(); i++)
                _avl.delete(keys[i]);
            return ;
        }

        // swap
        void swap(map &x)
        {
            tree tmp;

            tmp = x._avl;
            x._avl = _avl;
            _avl = tmp;

            return;
        }
        // clear
        void clear()
        {
            _avl.clear();
        }

        // lookup
        // count
        size_type count(const key_type &k) const
        {
            return (_avl.doublecheck(k));
        }
        // find
        iterator find(const key_type &k)
        {
            return (iterator(_avl.find(k), &_avl));
        }

        const_iterator find(const key_type &k) const
        {
            return (iterator(_avl.find(k), &_avl));
        }

        // equal_range
        ft::pair<iterator, iterator> equal_range(const key_type &k)
        {
            ft::pair<iterator, iterator> ret = ft::make_pair(lower_bound(k), upper_bound(k));
            return (ret);
        }

        ft::pair<const_iterator, const_iterator> equal_range(const Key &k) const
        {
            ft::pair<const_iterator, const_iterator> ret = ft::make_pair(lower_bound(k), upper_bound(k));
            return (ret);
        }

        // lower_bound
        iterator lower_bound(const key_type &k)
        {
            return (_avl.bound(k, "lower"));
        }

        const_iterator lower_bound(const key_type &k) const
        {
            return (_avl.bound(k, "lower"));
        }

        // upper_bound
        iterator upper_bound(const Key &k)
        {
            return (_avl.bound(k, "upper"));
        }

        const_iterator upper_bound(const Key &k) const
        {
            return (_avl.bound(k, "upper"));
        }

        // observers
        key_compare key_comp() const { return (_cmp); }

        value_compare value_comp() const
        {
            return (value_compare(_cmp));
        }

        allocator_type get_allocator() const { return (_avl.get_allocator()); }

    
    };
    /*relational operators*/
    template <class Key, class T, class Compare, class Alloc>
    bool operator==(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
    {
        if (lhs.size() != rhs.size())
            return (lhs.size() == rhs.size());
        return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator!=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
    {
        return !(lhs == rhs);
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator<(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
    {
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator<=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
    {
        if (lhs < rhs || lhs == rhs)
            return (true);
        return (false);
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator>(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
    {
        return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator>=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
    {
        if (lhs > rhs || lhs == rhs)
            return (true);
        return (false);
    }

    template <class Key, class T, class Compare, class Alloc>
    void swap(map<Key, T, Compare, Alloc> &x, map<Key, T, Compare, Alloc> &y)
    {
        x.swap(y);
    }
}

#endif
