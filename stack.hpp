#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{
    template <class T, class Container = ft::vector<T> >
    class stack
    {
        protected:
            Container _c;

        public:
            explicit stack(const Container &container = Container()) : _c(container) {}
            ~stack() {}

            stack &operator= (stack const &src){
                if (this != &src)
                    _c = src._c;
                return (*this);
            }

            bool empty() const { return (_c.empty()); }
            size_t size() const { return (_c.size()); }
            
            T &top() { return (_c.back()); }
            const T &top() const { return (_c.back()); }
            
            void push(const T &val) { return (_c.push_back(val)); }
            void pop() { return (_c.pop_back()); }

            friend bool operator==(const stack &lhs, const stack &rhs){
                return (lhs._c == rhs._c);
            }

            friend bool operator!=(const stack &lhs, const stack &rhs){
                return (lhs._c != rhs._c);
            }

            friend bool operator<(const stack &lhs, const stack &rhs){
                return (lhs._c < rhs._c);
            }
            
            friend bool operator<=(const stack &lhs, const stack &rhs){
                return (lhs._c <= rhs._c);
            }
            
            friend bool operator>(const stack &lhs, const stack &rhs){
                return (lhs._c > rhs._c);
            }
            
            friend bool operator>=(const stack &lhs, const stack &rhs){
                return (lhs._c >= rhs._c);
            }
    };
}

#endif