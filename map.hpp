#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include "tree_Iterator.hpp"
#include "Red_Black_Tree.hpp"

namespace ft
{
    template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T>>>
    class map
    {

    public:
        typedef Key key_type;
        typedef T mapped_type;
        typedef Compare key_compare;
        typedef Alloc allocator_type;
        typedef ft::pair<const key_type, mapped_type> value_type;

        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef ptrdiff_t difference_type;
        typedef size_t size_type;

        typedef typename ft::red_black_tree<value_type, key_type, key_compare, allocator_typr> tree_type;
        typedef typename tree_type::iterator iterator;
        typedef typename tree_type::const_iterator const_iterator;

        typedef typename ft::reverse_iterator<iterator> reverse_iterator;
        typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

        // value_compare
        class value_compare : public std::binary_function<value_type, value_type, bool>
        {
            friend class map;

        protected:
            key_compare comp; // less<Key>
            value_compare(key_comp c) : comp(c) {}

        public:
            bool operator()(const value_type &lhs, const value_type &rhs) const
            {
                return comp(lhs.first, rhs.first);
            }
        };

    private:
        tree_type _rbttree;

    public:
        explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
        {
            static_cast<void> comp; // why static_cast
            static_cast<void> alloc;
        }

        template <class InputIt>
        map(InputIt first, InputIt last,
            const key_compare &comp = key_compare(),
            const allocator_type &alloc = allocator_type(),
            typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type * = 0)
        {
            static_cast<void>(comp);
            static_cast<void>(alloc);
            insert(first, last);
        }

        map(const map &other)
        {
            insert(other.begin(), other.end());
        }

        ~map()
        {
        }

        map &operator=(const map &other)
        {
            if (*this != other)
            {
                clear();
                insert(other.begin(), other.end());
            }
            return *this;
        }

        // iterators
        iterator begin()
        {
            return _rbttree.begin();
        }

        const_iterator begin() const
        {
            return _rbttree.begin();
        }

        iterator end()
        {
            return _rbttree.end();
        }

        const_iterator end() const
        {
            return _rbttree.end();
        }

        reverse_iterator rbegin()
        {
            return reverse_iterator(_rbttree.end());
        }

        const_reverse_iterator rbegin() const
        {
            return const_reverse_iterator(_rbttree.end());
        }

        reverse_iterator rend()
        {
            return reverse_iterator(_rbttree.begin());
        }

        const_reverse_iterator rend() const
        {
            return const_reverse_iterator(_rbttree.begin());
        }

        // capacity
        bool empty() const
        {
            return _rbttree.empty();
        }

        size_type size() const
        {
            return _rbttree.size();
        }

        size_type max_size() const
        {
            return _rbttree.max_size();
        }

        // element access
        mapped_type &operator[](const key_type &k)
        {
            return ((insert(ft::make_pair(k, mapped_type()))).first)->second;
        }

        // modifiers
        // insert
        pair<iterator, bool> insert(const_reference val)
        {
            return _rbttree.insert(val);
        }

        iterator insert(iterator position, const value_type &val)
        {
            (void)position;
            return _rbttree.insert(val).first;
        }

        template <class InputIterator>
        void insert(InputIterator first, InputIterator last)
        {
            for (; first != last; first++)
                _rbttree.insert(*first);
        }

        // erase
        void erase(iterator position)
        {
            erase(position->first);
        }

        size_type erase(const key_type &k)
        {
        }

        void erase(iterator first, iterator last)
        {
        }

        // swap
        void swap(map &x)
        {
        }
        // clear
        void clear()
        {
            if (size())
                _rbttree.clear();
        }

        // lookup
        // count
        size_type count(const key_type &k) const
        {
            return _rbttree.count(ft::make_pair(k, mapped_type()));
        }
        // find
        iterator find(const key_type &k)
        {
            return _rbttree.find(ft::make_pair(k, mapped_type()));
        }

        const_iterator find(const key_type &k) const
        {
            return _rbttree.find(ft::make_pair(k, mapped_type()));
        }

        // lower_bound
        iterator lower_bound(const key_type &k)
        {
            return _rbttree.lower_bound(ft::make_pair(k, mapped_type()));
        }

        const_iterator lower_bound(const key_type &k) const
        {
            return _rbttree.lower_bound(ft::make_pair(k, mapped_type()));
        }

        // upper_bound
        iterator upper_bound(const key_type &k)
        {
            return _rbttree.upper_bound(ft::make_pair(k, mapped_type()));
        }

        const_iterator upper_bound(const key_type &k) const
        {
            return _rbttree.upper_bound(ft::make_pair(k, mapped_type()));
        }

        // equal_range
        pair<iterator, iterator> equal_range(const key_type &k)
        {
            return ft::make_pair(lower_bound(k), upper_bound(k));
        }

        pair<const_iterator, const_iterator> equal_range(const Key &k) const
        {
            return ft::make_pair(lower_bound(k), upper_bound(k));
        }
        // observers
        key_compare key_comp() const
        {
            return key_compare();
        }

        value_compare value_comp() const
        {
            return value_compare(_rbttree.comp());
        }

        allocator_type get_allocator() const { return allocator_type(); }

    };

    /*relational operators*/
    template <class Key, class T, class Compare, class Alloc>
    bool operator==(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
    {
        typename map<Key, T, key_compare, Alloc>::const_iterator    it;
        typename map<Key, T, key_compare, Alloc>::const_iterator    it2;

        if (lhs.size() != rhs.size()){
            return (false);
        }
        lhs = lhs.begin();
        rhs = rhs.begin();
        while (it != lhs.end()){
            if (*it != *it2){
                return (false);
            }
            it++;
            it2++;
        }
        return (true);
    }
   
    template <class Key, class T, class Compare, class Alloc>
    bool operator<(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
    {
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator<=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
    {
        return !(rhs < lhs);
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator>(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
    {
        return (rhs < lhs);
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator>=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
    {
        return !(lhs < rhs);
    }

    template <class Key, class T, class Compare, class Alloc>
    void swap(map<Key, T, Compare, Alloc> &x, map<Key, T, Compare, Alloc> &y)
    {
        x.swap(y);
    }
}

#endif