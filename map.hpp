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
            struct TreeNode{
                ft::pair<const Key, T>      content;
                TreeNode*                   parent;
                TreeNode*                   left;
                TreeNode*                   right;
            };

        private:
            TreeNode*                   _root;         
            TreeNode*                   _lastElem;      
            size_type                   _size;        
            allocator_type              _allocPair;     // Copy of allocator_type object
            key_compare                 _comp;          // Copy of comp key_compare predicate
            std::allocator<TreeNode>    _allocNode;     // Node's allocator

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

            explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
            _size(0), _allocPair(alloc), _comp(comp){
                _lastElem = createNode(ft::pair<const key_type, mapped_type>());
                _root = _lastElem;
                _lastElem->left = _lastElem;
                _lastElem->right = _lastElem;
            }

            template< class InputIt >
            map(InputIt first, InputIt last,
                const key_compare& comp = key_compare(),
                const allocator_type& alloc = allocator_type(),
                typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0) : 
                _size(0), _allocPair(alloc), _comp(comp){
                    _lastElem = createNode(ft::pair<const key_type, mapped_type>());
                    _root = _lastElem;
                    _lastElem->left = _lastElem;
                    _lastElem->right = _lastElem;
                    
                    for (; first != last; ++first)
                        insert(*first);
            }

            map(const map& other):
             _size(0), _allocPair(other._allocPair), _comp(other._comp), _allocNode(other._allocNode)
            {
                _lastElem = createNode(ft::pair<const key_type, mapped_type>());
                _root = _lastElem;
                _lastElem->left = _lastElem;
                _lastElem->right = _lastElem;

                for (const_iterator it = other.begin(); it != other.end(); ++it)
                    insert(*it);
            }

            ~map(){
                clear();
                deallocateNode(_lastElem);

            }
            
            map& operator=(const map& other){
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
                return (_size);
            }

            size_type max_size() const{

            }

            //element access
            mapped_type& operator[] (const key_type& k){
                TreeNode* tmp = searchNode(_root, k);

                if (tmp){
                    return tmp->content.second;
                }
                value_type val = make_pair<key_type, mapped_type>(k, mapped_type());
                return insertNode(_rot, val)->content.second;
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