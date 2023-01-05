#ifndef MAPITERATOR_HPP
#define MAPITERATOR_HPP

#include <iostream>
#include <cstddef>

#include "iterator.hpp"

namespace ft{
    template<class T, class TreeNode >
    class mapIterator : public ft::iterator<bidirectional_iterator_tag, T> {
        public:
            typedef T               value_type;   //pair<key, mapped_value>
            typedef TreeNode*       nodeptr;
        
            typedef typename ft::iterator<bidirectional_iterator_tag, T>::iterator_category iterator_category;
            typedef typename ft::iterator<bidirectional_iterator_tag, T>::difference_type   difference_type;
            typedef typename ft::iterator<bidirectional_iterator_tag, T>::pointer           pointer;
            typedef typename ft::iterator<bidirectional_iterator_tag, T>::reference         reference;

            /*constructor and destructor*/
        mapIterator():_root(NULL), _node(NULL), _null(NULL) {}
        
        mapIterator (nodeptr root, nodeptr node, nodeptr null):
          _root(root),
          _node(node),
          _null(null){}       	
        
        mapIterator (mapIterator const&src) :_root(src._root), _node(src._node), _null(src._null){}
        
        ~mapIterator(){} 
        
        mapIterator &operator= (const mapIterator &rhs){
            if (this == &rhs) 
                return *this;
            this->_root = rhs._root;
            this->_node = rhs._node;
            this->_null = rhs._null;
            return *this;
        }
         /*Member functions*/
        nodeptr getRoot() const{return this->_root;}
        nodeptr getNode() const{return this->_node;}
        
        //Dereference iterator
        reference operator*() const {return this->_node->_value;}; //_value is pair<key, mapped_value>

         //Returns a pointer to the root pointed to by the iterator (in order to access one of its members).
        pointer operator->() const{return &(operator*());}

        //Increment iterator position  ++key
        mapIterator &operator++(){
            if (this->_node == max()){
                this->_node = _null;
                return *this;
            }
            else if (this->_node == _null){
                this->_node = _null;
                return *this;
            }
            this->_node = successor(this->_node);
            return *this;
        }
          
        nodeptr min() {return minVal(this->_root);}

        nodeptr max() {return maxVal(this->_root);}
        
        //The post-increment version
        mapIterator operator++(int){
            mapIterator tmp(*this);
            this->operator++();
            return tmp;
        }

        //Decreases iterator position --key
        mapIterator& operator--(){
          if (this->_node == _null){
            this->_node = max();
            return *this;
            }
            this->_node = predecessor(this->_node);
            return *this;
        }
        
        //The post-increment version
        mapIterator operator--(int){
            mapIterator  tmp(*this);
            this->operator--();
            return tmp;
        }

        nodeptr minVal(nodeptr node) const {
            if (node == _null){
                return (_null);
            }
            while (node->_left != _null){
                node = node->_left;
            }
            return (node);
        }
        
        /* max val in node*/
        nodeptr maxVal(nodeptr node) const {
            if (node == _null)
                return (_null);
            while (node->_right != _null)
                node = node->_right;
            return (node);
        }
        
        nodeptr	successor(nodeptr node) const {
          if (node->_right != _null){
            return minVal(node->_right);
          }
          nodeptr tmp = node->_parent;
          while (tmp != _null && node == tmp->_right){
            node = tmp;
            tmp = tmp->_parent;
          }
          return tmp;
		}

        nodeptr	predecessor(nodeptr node) {
          if (node->_left != _null){
            return maxVal(node->_left);
          }
          nodeptr tmp = node->_parent;
          while (tmp != _null && node == tmp->_left) {
            node = tmp;
            tmp = tmp->_parent;
          }
          return tmp;
        }
        
        operator mapIterator<const T,  treeNode> (void){
            return mapIterator<const T,  treeNode>(_root, _node, _null);
	    }

        private:
            nodeptr _root;
            nodeptr _node;
            nodeptr _null;
    };
    
    /*Non-member function overloads :*/
    template <class T, class Node>
    bool operator== (const mapIterator<T, Node>& lhs, const mapIterator<T, Node>& rhs){ 
        return lhs.getNode() == rhs.getNode();
    }  
    template <class T, class Node>
    bool operator!= (const mapIterator<T, Node>& lhs, const mapIterator<T, Node>& rhs){
        return lhs.getNode() != rhs.getNode();
    }
    /*Non-member function overloads : const case*/ 
    template <class T, class _T, class Node>
    bool operator== (const mapIterator<T, Node>& lhs, const mapIterator<_T, Node>& rhs){ 
        return lhs.getNode() == rhs.getNode();
    }  
    template <class T, class _T, class Node>
    bool operator!= (const mapIterator<T, Node>& lhs, const mapIterator<_T, Node>& rhs){
        return lhs.getNode() != rhs.getNode();
    }
}

#endif
