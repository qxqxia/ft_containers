#ifndef MAP_HPP 
#define MAP_HPP

#include "iterator.hpp"
#include "mapIterator.hpp"
#include "templates.hpp"
#include <iostream>

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
            ft::Avltree<value_type> _avltree;
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

            typedef typename ft::mapIterator<value_type, ft::treeNode<value_type> > iterator;  //paire
            typedef typename ft::mapIterator<const value_type, ft::treeNode<value_type> > const_iterator;
            
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

            explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _avltree{
                (void)comp;
                (void)alloc;
            }

            template< class InputIt >
            map(InputIt first, InputIt last,
                const key_compare& comp = key_compare(),
                const allocator_type& alloc = allocator_type()) : _avltree{
                    (void)comp;
                    (void)alloc;
                    insert(first, last);
            }

            map(const map& other){
                insert(other.begin(), other.end());
            }

            ~map(){
                clear(); //

            }
            
            map& operator=(const map& other){
                if(this == &other)
                    return (*this);
                map tmp(other);
                this->swap(tmp);
                return (*this);

            }

            //iterators
            iterator begin(){

            }

            const_iterator begin() const{

            }

            iterator end(){

            }

            const_iterator end() const{

            }

            reverse_iterator rbegin(){

            }

            const_reverse_iterator rbegin() const{

            }

            reverse_iterator rend(){

            }

            const_reverse_iterator rend() const{

            }

            //capacity
            bool empty() const{
                return (size() == 0);
            }

            size_type size() const{
                
            }

            size_type max_size() const{

            }

            //element access
            mapped_type& operator[] (const key_type& k){

            }

            //modifiers
            //insert
            pair<iterator,bool> insert (const value_type& val){

            }

            iterator insert (iterator position, const value_type& val){

            }
                
            template <class InputIterator>  
            void insert (InputIterator first, InputIterator last){

            }

            //erase
            void erase (iterator position){

            }

            size_type erase (const key_type& k){

            }

            void erase (iterator first, iterator last){

            }

            //swap
            void swap (map& x){

            }
            //clear
            void clear(){

            }

            //lookup
            //count
            size_type count( const Key& key ) const{

            }
            //find
            iterator find( const Key& key ){

            }

            const_iterator find( const Key& key ) const{

            }

            //equal_range
            pair<iterator,iterator> equal_range( const Key& key ){

            }

            pair<const_iterator,const_iterator> equal_range( const Key& key ) const{

            }

            //lower_bound
            iterator lower_bound( const Key& key ){

            }

            const_iterator lower_bound( const Key& key ) const{

            }

            //upper_bound
            iterator upper_bound( const Key& key ){

            }

            const_iterator upper_bound( const Key& key ) const{

            }

            //observers
            key_compare key_comp() const{

            }
            
            value_compare value_comp() const{
                
            }



        };
};

#endif