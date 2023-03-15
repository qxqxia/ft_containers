#ifndef TREE_ITERATOR_HPP
#define TREE_ITERATOR_HPP

#include <iostream>
#include "iterator.hpp"

namespace ft{
    template<class T, class N, class Compare >
    class tree_iterator : public ft::iterator<bidirectional_iterator_tag, N> {
        public:
            typedef T*       pointer;   //pair<key, mapped_value>
            typedef T&       reference;
            typedef N        nodeptr;
        
            typedef typename ft::iterator_traits<N>::iterator_category iterator_category;
            typedef typename ft::iterator_traits<N>::difference_type   difference_type;
            typedef typename ft::iterator_traits<N>::value_type         value_type;

        protected:
            nodeptr _node;
         /*constructor and destructor*/
        
        public:
            tree_iterator():_node(0) {}
            
            tree_iterator(nodeptr node):_node(node){}       	
            
            tree_iterator (tree_iterator const&src) :_node(src._node){}
            
            ~tree_iterator(){} 
            
            tree_iterator &operator= (const tree_iterator &rhs){
                if (this == &rhs) 
                    return *this;
                this->_node = rhs._node;
                return *this;
            }

            operator tree_iterator<const T, N, Compare>() const{ //for const_iterator
                return tree_iterator<const T, N, Compare>(_node);
            }

            nodeptr base()const {return _node;}
         
        
            //Dereference iterator
            reference operator*() const {return _node->data;}; //_value is pair<key, mapped_value>

            //Returns a pointer to the root pointed to by the iterator (in order to access one of its members).
            pointer operator->() const{return &(_node->data);}

            //Increment iterator position  ++key
            tree_iterator &operator++(){ //inorder traversal
                if (_node && _node->right){
                    _node = _node->right;
                    while(_node->left)
                        _node = _node->left;
                }
                else if(_node && _node->parent){
                    nodeptr tmp1 = _node;
                    nodeptr tmp2 = _node->parent;
                    while(tmp2 && _node == tmp2->right){
                        if (tmp2->parent == NULL) //if tmp is root
                        {
                            _node = tmp1->parent;
                            return *this;
                        }
                        _node = tmp2;
                        tmp2 = tmp2->parent;
                    }
                    _node = tmp2;
                }
                return *this;
            }
        
            //The post-increment version
            tree_iterator operator++(int){
                tree_iterator tmp(*this);
                
                operator++();
                return tmp;
            }

            //The post-increment version
            tree_iterator operator--(){
                if (_node && _node->left){
                    _node = _node->left;
                    while(_node->right && _node->right != NULL)
                        _node = _node->right;
                }
                else if(_node && _node->parent){
                    nodeptr tmp1 = _node;
                    nodeptr tmp2 = _node->parent;
                    while(tmp2 && _node == tmp2->left){
                        if (tmp2->parent == NULL) //if tmp is root
                        {
                            _node = tmp1;
                            return *this;
                        }
                        _node = tmp2;
                        tmp2 = tmp2->parent;
                    }
                    _node = tmp2;
                }
                return *this;
            }
            
            //Decreases iterator position --key
            tree_iterator& operator--(int){
                tree_iterator tmp(*this);

                operator--();
                return tmp;
            }

            friend bool operator== (const tree_iterator<T, N, Compare>& lhs, const tree_iterator<T, N, Compare>& rhs){ 
                return lhs.base() == rhs.base();
            }  
           
            friend bool operator!= (const tree_iterator<T, N, Compare>& lhs, const tree_iterator<T, N, Compare>& rhs){
                return lhs.base() != rhs.base();
            }
        
    };
   
}

#endif