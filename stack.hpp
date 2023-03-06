#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{
    template <class T, class Container = ft::vector<T> >
    class stack
    {
    public:
        typedef typename Container::value_type   value_type;
        typedef typename Container::size_type    size_type;
        typedef Container                        container_type;
        
    protected:
        container_type _c;

    public:
        explicit stack(const container_type &container = container_type()) : _c(container) {}
        ~stack() {}
        bool empty() const { return (_c.empty()); }
        size_type size() const { return (_c.size()); }
        value_type &top() { return (_c.back()); }
        const value_type &top() const { return (_c.back()); }
        void push(const value_type &val) { return (_c.push_back(val)); }
        void pop() { return (_c.pop_back()); }

        friend bool operator==(const stack &lhs, const stack &rhs);
        friend bool operator!=(const stack &lhs, const stack &rhs);
        friend bool operator<(const stack &lhs, const stack &rhs);
        friend bool operator<=(const stack &lhs, const stack &rhs);
        friend bool operator>(const stack &lhs, const stack &rhs);
        friend bool operator>=(const stack &lhs, const stack &rhs);
    };
    template <class T, class Container>
    bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        return (lhs._c == rhs._c);
    }
    template <class T, class Container>
    bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        return (lhs._c != rhs._c);
        // return !(lhs == rhs);
    }
    template <class T, class Container>
    bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        return (lhs._c < rhs._c);
    }
    template <class T, class Container>
    bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        return (lhs._c <= rhs._c);
    }
    template <class T, class Container>
    bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        return (lhs._c > rhs._c);
    }
    template <class T, class Container>
    bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        return (lhs._c >= rhs._c);
    }
}

#endif