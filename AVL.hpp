#ifndef AVL_HPP
#define AVL_HPP

#include <iostream>
#include "templates.hpp"
#include <memory>

namespace ft{

    template<class T>
    class TreeNode{

        public:
            T           value; //T is pair<key, value>
            TreeNode    *parent;
            TreeNode    *left;
            TreeNode    *right;
        
        public:
            TreeNode(): _value(), _left(NULL), _right(NULL), _parent(NULL) {}
            
            TreeNode(T const &val, TreeNode *left = NULL, TreeNode *right = NULL, TreeNode *parent = NULL):
                    _value(val), _left(left), _right(right), _parent(parent) {}
                    
            TreeNode(TreeNode const&src): _value(src._value), _left(src._left), _right(src._right), _parent(src._parent) {}
            
            ~TreeNode(){}
            
            TreeNode & operator=(TreeNode const &rhs){
                if (this == &rhs) 
                    return *this; 
                this->_value = rhs._value;
                this->_left = rhs._left;
                this->_right = rhs._left;
                this->_parent = rhs._parent;
                return *this;
            }
    };

    template<class T,
            //class Compare,
            class Node = ft::TreeNode<T>,
            class Allocator = std::allocator<Node> >
    class AVL_tree{
        private:
            pointer     _root;
            pointer     _null;
        public:
            typedef	 T                          value_type;  // T is pair<key, value>
            typedef Node                        node_type; 
            typedef Allocator                   allocator_type;
           
            
			typedef	typename	allocator_type::pointer					pointer;
			typedef	typename	allocator_type::const_pointer			const_pointer;
			typedef	typename	allocator_type::size_type				size_type;

            AVL_tree() {
                this->_null =  allocator_type().allocate(1);
				allocator_type().construct(_null, node_type());
                this->_root = this->_null;
            }
    
            /* destructor */
            ~AVL_tree(){}
            
            /* get value*/
            pointer getRoot()const {return this->_root;}
            
            pointer getNull()const {return this->_null;}

            /* size of node(tree) */
            size_type  size(pointer root) const {
                if (root == _null)
                    return 0;
                return (size(root->left) + size(root->right) + 1);
            }

            size_type max_size() const {
                return allocator_type().max_size();
            }

            /*min val in tree*/
            pointer minVal(pointer root)const{
                if (root == _null)
                    return _null;
                while (root->left != _null)
                    root = root->left;
                return root;
            }

            /* max val in tree*/
            pointer maxVal(pointer root) const {
                 if (root == _null)
                    return _null;
                while (root->_right != _null)
                    root = root->right;
                return root;
            }

            int max(int left, int right){
                if (left < right){
                    return right;
                }
                else
                    return left;
            }

            //delete one node
            ??bool delete_node(value_type const& val){ 
                if ()
            }

            ??pointer DeleteNode(pointer &tree, value_type const &val){

            }
            
            ??void swap(AVL_tree *src){

            }

            ??pointer lower_bound(value_type const & val){

            }

            ??pointer upper_bound(value_type const & val) {

            }

            ??pointer	successor(pointer node) const{

            }
            
            //delete tree
            void destroy_tree(){
                destroy_tree(this->_root);
                this->_root = _null;
            }

            void destory_null(){
                allocator_type().destroy(_null);
                allocator_type().deallocate(_null, 1);
            }

            //height of the node
            int TreeHeight(pointer root){
                int high = 0;
                if (!root || root == _lastElem){
                    return 0;
                }
                else{
                int LH = TreeHeight(root->left);
                int RH = TreeHeight(root->right);
                int maxheight = max(LH, RH);
                high = maxheight + 0;
                }
                return high;
            }

            int TreeGetBalanceFactor(pointer root){
                if (!root){
                    return 0;
                }
                else{
                    return TreeHeight(TreeNode->left, 1) - TreeHeight(TreeNode->right, 1);
                }
            }

            pointer searchNode(pointer root, value_type const& val) const
            {
                // We reached a leaf or Tree is empty
                if (!root)
                    return 0;
                else{
                    // Recursive loop until we find key
                    if (val.first < root->value.first)
                        return searchNode(root->left, val);
                    else if (val.first > root->value.first)
                        return searchNode(root->right, val);
                    else
                        return root;
                }
            }

            int diff(pointer root){
                int left = TreeHeight(root->left);
                int right = TreeHeight(root->right);
                int difference = left - right;
                return difference;
            }

            pointer balance(pointer curr){
                int getBalance = diff(curr);
                if (getBalance > 1){
                    if(diff(curr->left) > 0){
                        curr = LL_rotation(curr);
                    }
                    else
                        curr = LR_rotation(curr);
                }
                else if (getBalance < -1){
                    if (diff(curr->right) > 0)
                        curr = RL_rotation(curr);
                    else
                        curr = RR_rotation(curr);
                }
                return curr;
            }

            pointer LL_rotation(pointer root){ //LL rotation
                //               Q                                 P              |
                //              / \     RIGHT ROTATION            / \             |
                //             P   C  ------------------->>>     A   Q            |
                //            / \                                   / \           |
                //           A   B                                 B   C          |                                             
                pointer curr; //P

                curr = root->left; //P is the left child of Q
                root->left = curr->right; // after rotation, B is now the left child of Q
                curr->right = root; //Q becomes the right child of P
                return curr; //P is the new root now
            }             

            pointer RR_rotation(pointer root){ //RR rotation
                //               Q                                 P              |
                //              / \          LEFT ROTATION        / \             |
                //             P   C    <<<-------------------   A   Q            |
                //            / \                                   / \           |
                //           A   B                                 B   C          |
                
                pointer curr; //Q

                curr = root->right; //Q is the right child of P
                root->right = curr->left;//after rotation, B is now the right child of P
                curr->left = root; //P becomes the left child of Q
                return curr;//return new root
            }

            pointer RL_rotation(pointer root){
                //RL(D rotates to the right, then C rotates to the left):
                //             k3                         k3                          k2       |
                //            /  \                       /  \                        /  \      |
                //           A    k1                    A    k2                     k3   k1    |
                //               /  \       ==>             /  \         ==>       /  \  / \   |
                //              k2   B                     C    k1                A   C D   B  |
                //             /  \                            /  \                            |
                //            C    D                          D    B                           |
                
                pointer curr;

                curr = root->right;
                curr->right = LL_rotation(curr);
                return (RR_rotation(curr));
            }

            pointer LR_rotation(pointer root){
                // LR(B rotates to the left, then C rotates to the right):
                //            k3                         k3                       k2        |
                //           /  \                       /  \                     /  \       |
                //          k1   D                     k2   D                   k1   k3     |
                //         /  \         ==>           /  \        ==>          / \   / \    |
                //        A    k2                    k1   C                   A  B  C   D   |
                //            /  \                  /  \                                    |
                //            B   C                A    B                                   |

                pointer curr;

                curr = root->left;
                curr->left = RR_rotation(curr);
                return (LL_rotation(curr));
            }

            void inorder(pointer lroot){
                if(lroot){
                    inorder(lroot->left);
                    std::cout << lroot->value << " "; 
                    inorder(lroot->right);
                }
            }

            pointer TreeInsert(pointer root, pointer new_node){
                if(root == NULL){
                    root = new_node;
                    std::cout << "Value inserted successfully" << std::endl;
                    return root;
                }
                if(new_node->value < root->value){
                    root->left = TreeInsert(root->left, new_node);
                }
                else if(new_node->value > root->value){
                    root->right = TreeInsert(root->right, new_node);
                }
                else{
                    std::cout << "No duplicate values allowed!" << std::endl;
                    return root;
                }

                int bf = TreeGetBalanceFactor(root);
                //LL
                if (bf > 1 && new_node->value < root->left->value)
                    return LL_rotation(root);
                //RR
                if (bf < -1 && new_node->value > root->right->value)
                    return RR_rotation(root);
                //LR
                if (bf > 1 && new_node->value > root->left->value)
                    return LR_rotation(root);
                //RL
                if (bf < -1 && new_node->value < root->right->value){
                    root->right = LL_rotation(root->right);
                    return (RR_rotation(root));
                }
                return root;
            }

            pointer TreeDelete(pointer root, value_type value){
                //base case
                if (!root)
                    return ;
                if (value < root->value){
                    root->left = TreeDelete(root->left, value);
                }
                else if(value > root->value){
                    root->right = TreeDelete(root->right, value);
                }
                else{
                    //leaf node
                    if (root->left == NULL && root->right == NULL){
                        delete (root);
                        return NULL;
                    }
                    else if(root->left == NULL){
                        pointer tmp = root->right;
                        delete(root);
                        root = tmp;
                    }
                    else if(root->right == NULL){
                        pointer tmp = right->left;
                        delete(root);
                        root = tmp;
                    }
                    else{
                        pointer tmp = root->left;
                        //find the max value in th eleft subtree
                        while(tmp->right != NULL){
                            tmp = tmp->right;
                        }
                        root->value = tmp->value;
                        root->left = TreeDelete(root->left, tmp->value);
                    }
                }
                return root;
                
    };
}
