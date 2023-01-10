#ifndef MAP_HPP 
#define MAP_HPP

#include "iterator.hpp"
#include "mapIterator.hpp"
#include "templates.hpp"
#include <iostream>
#include "AVL.hpp"

namespace ft{
    //ft::less
    template <class T>
    class less{
    public:
         bool operator() (const T& x, const T& y) const { return x  < y; }  //x < y is true
    };
    //ft::map
    template< class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T>> >
    class map{
        private:
            ft::AVL_tree<value_type>        _avltree;
        public:
            typedef Key                                 key_type;   
            typedef T                                   mapped_type;  
            typedef Compare                             key_compare; 
            typedef Alloc                               allocator_type;
            typedef pair<const key_type, mapped_type>   value_type;

            typedef T&                                  reference;
            typedef const T&                            const_reference;
            typedef T*                                  pointer;
            typedef const T*                            const_pointer;
            typedef long int                            difference_type;
            typedef size_t                              size_type;

            typedef typename ft::mapIterator<value_type, ft::TreeNode<value_type> > iterator;  //paire
            typedef typename ft::mapIterator<const value_type, ft::TreeNode<value_type> > const_iterator;
            
            typedef typename ft::reverse_iterator<iterator> reverse_iterator;
            typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

        //value_compare
        class value_compare : public binary_function<value_type, value_type, bool> {
                    friend class map;
                    
                    protected:
                        key_compare comp;     //less<Key>
                        value_compare (Compare c) : comp(c) {} 
                        
                    public:
                        typedef bool        result_type;
                        typedef value_type  first_argument_type;
                        typedef value_type  second_argument_type;
                        
                    bool operator() (const value_type& lhs, const value_type& rhs) const {
                        return comp(lhs.first, rhs.first);
                    }
                };

        public:
            //coplien form
            map(){}

            explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
            _avltree(){
                (void)comp;
                (void)alloc;
            }

            template< class InputIt >
            map(InputIt first, InputIt last,
                const key_compare& comp = key_compare(),
                const allocator_type& alloc = allocator_type()) : 
                _avltree() {
                    (void)comp;
                    (void)alloc;
                    insert(first, last);
            }

            map(const map& other){
                insert (other.begin(), other.end());
            }

            ~map(){
                clear();
                _avltree.destroy_null();
            }
            
            map& operator=(const map& other){
                if (this == &other)
                    return *this;
                this->~map();
                _avltree = ft::AVL_tree<value_type>();
                insert (other.begin(), other.end());
                return *this;
            }

            //iterators
            iterator begin(){
                return iterator(_avltree.getRoot(), _avltree.min(), _avltree.getNull());
            }

            const_iterator begin() const{
                return const_iterator(_avltree.getRoot(), _avltree.min(), _avltree.getNull());
            }

            iterator end(){ 
                return iterator(_avltree.getRoot(), _avltree.getNull(), _avltree.getNull());
            }

            const_iterator end() const{
                return const_iterator(_avltree.getRoot(), _avltree.getNull(), _avltree.getNull());
            }

            reverse_iterator rbegin(){ 
                return reverse_iterator(this->end()); 
            }

            const_reverse_iterator rbegin() const{
                return const_reverse_iterator(this->end()); 
            }

            reverse_iterator rend(){
                return reverse_iterator(this->begin()); 
            }

            const_reverse_iterator rend() const{
                return const_reverse_iterator(this->begin());
            }

            //capacity
            bool empty() const{
                return (size() == 0);
            }

            size_type size() const{
                return (_avltree.size(_avltree.get()));
            }

            size_type max_size() const{
                return (_avltree.max_size());
            }

            //element access
            mapped_type& operator[] (const key_type& k){
                return (*((insert(ft::make_pair(k, mapped_type()))).first)).second;
            }

            //modifiers
            //insert
            pair<iterator,bool> insert (const value_type& val){
                if (_avltree.insert(val) == false) {
					return ft::make_pair(find(val.first), false);
                }
				return ft::make_pair(find(val.first), true);
            }

            iterator insert (iterator position, const value_type& val){
                (void)position;
                return insert(val).first;
            }
                
            template <class InputIterator>  
            void insert (InputIterator first, InputIterator last){
                for(; first != last; first++)
                    insert(*first);
            }

            //erase
            void erase (iterator position){
                erase(position->first);
            }

            size_type erase (const key_type& k){
                if (_avltree.delete_node(ft::make_pair(k, mapped_type())) == false)
                    return 0;
                return 1;
            }

            void erase (iterator first, iterator last){
                while(first != last){
                    first = find(first->first);
                    erase(first++);
                }
            }

            //swap
            void swap (map& x){
                _avltree.swap(x._avltree);
            }
            //clear
            void clear(){
                _avltree.destroy_tree();
            }

            //lookup
            //count
            size_type count( const Key& key ) const{
                 if (_avltree.searchNode(_avltree.getRoot(), ft::make_pair(k, mapped_type())) == _avltree.getNull())
                    return (0);
                return (1);
            }
            //find
            iterator find( const Key& key ){
                return iterator(_avltree.getRoot(), _avltree.searchNode(_avltree.getRoot(), ft::make_pair(k, mapped_type())), _avltree.getNull());
            }

            const_iterator find( const Key& key ) const{
                return const_iterator(_avltree.getRoot(), _avltree.searchNode(_avltree.getRoot(), ft::make_pair(k, mapped_type())), _avltree.getNull());
            }

            //equal_range
            pair<iterator,iterator> equal_range( const Key& key ){
                return ft::make_pair<iterator, iterator>(lower_bound(k), upper_bound(k));
            }

            pair<const_iterator,const_iterator> equal_range( const Key& key ) const{
                return ft::make_pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
            }

            //lower_bound
            iterator lower_bound( const Key& key ){
                return iterator(_avltree.getRoot(), _avltree.lower_bound(ft::make_pair(k, mapped_type())), _avltree.getNull());
            }

            const_iterator lower_bound( const Key& key ) const{
                return const_iterator(_avltree.getRoot(), _avltree.lower_bound(ft::make_pair(k, mapped_type())), _avltree.getNull());
            }

            //upper_bound
            iterator upper_bound( const Key& key ){
                return iterator(_avltree.getRoot(), _avltree.upper_bound(ft::make_pair(k, mapped_type())), _avltree.getNull());
            }

            const_iterator upper_bound( const Key& key ) const{
                return const_iterator(_avltree.getRoot(), _avltree.upper_bound(ft::make_pair(k, mapped_type())), _avltree.getNull());
            }

            //observers
            key_compare key_comp() const{
                return key_compare();
            }
            
            value_compare value_comp() const{
                return value_compare(key_compare());
            }

            allocator_type get_allocator() const{ return allocator_type();}

        };

        /*relational operators*/
        template <class Key, class T, class Compare, class Alloc>
        bool operator== ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ){
            if(lhs.size() != rhs.size())
                return (false);
            return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
        }

        template <class Key, class T, class Compare, class Alloc>
        bool operator!= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ){
            return !(lhs == rhs);
        }

        template <class Key, class T, class Compare, class Alloc>
        bool operator<  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ){
            return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
        }

        template <class Key, class T, class Compare, class Alloc>
        bool operator<= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ){
            return !(rhs < lhs);
        }

        template <class Key, class T, class Compare, class Alloc>
        bool operator>  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ){
            return rhs < lhs;
        }

        template <class Key, class T, class Compare, class Alloc>
        bool operator>= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ){
            return !(lhs < rhs);
        }
        
        template <class Key, class T, class Compare, class Alloc>
        void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y){
            x.swap(y);
        }
}

#endif