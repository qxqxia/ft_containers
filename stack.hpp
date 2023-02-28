#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"
//use vector as default underlying container
namespace ft{
    template <class T, class Container = ft::vector<T> >
    class stack{
        public:
            typedef Container                           container_type;
            typedef typename container_type::size_type  size_type;
            typedef typename container_type::value_type value_type;
        public:
            explicit stack(const Container& cont = Container());
            ~stack();
            stack& operator=(const stack& other);

            bool empty() const{
                return _containerVec.empty();
            }
            size_type size() const{
                return _containerVec.size();
            }
            void push( const value_type& value ){
                _containerVec.push_back(val);
            }
            void pop(){
                _containerVec.pop_back();
            }
            value_type& top(){
                return _containerVec.back();
            }
            const value_type& top() const{
                return _containerVec.back();
            }
            //why friend
            friend bool operator == (const stack<T,Container> & lhs, const stack<T,Container> & rhs) {
                    return lhs._containerVec == rhs._containerVec;
            }
            
            friend bool operator != (const stack<T,Container> & lhs, const stack<T,Container> & rhs) {
                return !(lhs == rhs);
            }
            
            friend bool operator < (const stack<T,Container> & lhs, const stack<T,Container> & rhs){
                return lhs._containerVec < rhs._containerVec;
            }
            
            friend bool operator > (const stack<T,Container> & lhs, const stack<T, Container> & rhs){
                return rhs < lhs;
            }
            
            friend bool operator <= (const stack<T,Container> & lhs, const stack<T, Container> & rhs){
                return !(rhs < lhs);
            }
            
            friend bool operator >= (const stack<T,Container> & lhs, const stack<T, Container> & rhs){
                return !(lhs < rhs);
            }
        
        protected:
            container_type _containerVec;

    };
}
#endif