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
            int         height;
            TreeNode    *parent;
            TreeNode    *left;
            TreeNode    *right;
        
        public:
            TreeNode(): value(), left(NULL), right(NULL), parent(NULL) {}
            
            TreeNode(T const &val, TreeNode *left = NULL, TreeNode *right = NULL, TreeNode *parent = NULL):
                    value(val), left(left), right(right), parent(parent) {}
                    
            TreeNode(TreeNode const&src): value(src.value), left(src.left), parent(src.parent), right(src.right){}
            
            ~TreeNode(){}
            
            TreeNode & operator=(TreeNode const &rhs){
                if (this == &rhs) 
                    return *this; 
                this->value = rhs.value;
                this->left = rhs.left;
                this->right = rhs.right;
                this->parent = rhs.parent;
                return *this;
            }
    };

    template<class T,
            //class Compare,
            class Node = ft::TreeNode<T>,
            class Allocator = std::allocator<Node> >
    class AVL_tree{
        
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
                while (root->right != _null)
                    root = root->right;
                return root;
            }

          

            //delete one node
            bool delete_node(value_type const& val){ 
                if (DeleteNode(this->_root, val) == _null)
                     return false;
                return true;
            }

            pointer DeleteNode(pointer &tree, value_type const &val){
                pointer tmpNode;

                if (tree == _null) {
                    return _null;
                }
                else if (tree->value.first > val.first)
                    tree->left = DeleteNode(tree->left, val);
                else if (tree->value.first < val.first)
                    tree->right = DeleteNode(tree->right, val);
                else if  (tree->value.first == val.first)
                { 
                    if (tree->left !=_null && tree->right != _null ) { 
                        tmpNode = minVal(tree->right);
                        tree = tmpNode;
                        tree->right = DeleteNode(tree->right, tree->value);	
                    }
                    else if (tree->left == _null ) {
                        tmpNode = tree;
                        tree = tree->right;
                        allocator_type().destroy(tmpNode);
                        allocator_type().deallocate(tmpNode, 1);
                    }
                    else if (tree->right  == _null) {
                        tmpNode = tree;
                        tree = tree->left;
                        allocator_type().destroy(tmpNode);
                        allocator_type().deallocate(tmpNode, 1);
                    } 
                    else {
                        tmpNode = tree;
                        allocator_type().destroy(tmpNode);
                        allocator_type().deallocate(tmpNode, 1);
                    }

                }
                return (tree);
            }
            
            void swap(AVL_tree &src){
                pointer root = this->_root;
                pointer null = this->_null;

                this->_root = src.getRoot();
                this->_null = src.getNull();

                src._root = root;
                src._null = null;
            }

            pointer	successor(pointer node) const{
                if (node->right != _null)
                    return minVal(node->_right);
                if (node->parent == _null || node == maxVal(this->_root))
                    return _null;
                pointer tmp = node->parent;
                while (tmp != _null && node == tmp->right) {
                    node = tmp;
                    tmp = tmp->parent;
                }
                return tmp;
            }

            pointer lower_bound(value_type const & val){
                pointer begin = minVal(this->_root);
				while (begin != _null) {
					if (begin->value >= val)
						break ;
					begin = successor(begin);
				}
				return begin;
            }

            pointer upper_bound(value_type const & val) {
                pointer begin = minVal(this->_root);
				while (begin != _null) {
					if (begin->value.first > val.first) 
						break ;
					begin = successor(begin);
				}
				return begin;
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

            int max(int left, int right){
                if (left < right){
                    return right;
                }
                else
                    return left;
            }

            //height of the node
            int TreeHeight(pointer root){
                if (!root)
                    return 0;
                else{
                    return max(TreeHeight(root->left), TreeHeight(root->right)) + 1;
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

            int TreeGetBalanceFactor(pointer root){
                if (!root){
                    return 0;
                }
                else{
                    return (TreeHeight(root->left) - TreeHeight(root->right));
                }
            }

            pointer balance(pointer curr){
                int getBalance = TreeGetBalanceFactor(curr);
                if (getBalance > 1){
                    if(TreeGetBalanceFactor(curr->left) > 0){
                        curr = LL_rotation(curr);
                    }
                    else
                        curr = LR_rotation(curr);
                }
                else if (getBalance < -1){
                    if (TreeGetBalanceFactor(curr->right) > 0)
                        curr = RL_rotation(curr);
                    else
                        curr = RR_rotation(curr);
                }
                return curr;
            }

            pointer LL_rotation(pointer root){ //right rotation
                //               Q                               P              |
                //              / \     RIGHT ROTATION          / \             |
                //             P   C         ==>               A   Q            |
                //            / \                                 / \           |
                //           A   B                               B   C          |                                             
                pointer curr; //P

                curr = root->left; //P is the left child of Q
                root->left = curr->right; // after rotation, B is now the left child of Q
                curr->right = root; //Q becomes the right child of P
                root->height = max(TreeHeight(root->left), TreeHeight(root->right)) + 1;
                curr->height = max(TreeHeight(curr->left), TreeHeight(curr->right)) + 1;
                return curr; //P is the new root now
            }             

            pointer RR_rotation(pointer root){ //RR rotation
                //               p                               Q              |
                //              / \    LEFT ROTATION            / \             |
                //             A   Q        ==>                P   C            |
                //                / \                         / \               |
                //               B   C                       A   B              |
                
                pointer curr; //Q

                curr = root->right; //Q is the right child of P
                root->right = curr->left;//after rotation, B is now the right child of P
                curr->left = root; //P becomes the left child of Q
                root->height = max(TreeHeight(root->left), TreeHeight(root->right)) + 1;
                curr->height = max(TreeHeight(curr->left), TreeHeight(curr->right)) + 1;
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
                root->height = max(TreeHeight(root->left), TreeHeight(root->right)) + 1;
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

            /*pointer TreeDelete(pointer root, value_type value){
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
                }*/
        private:
            pointer     _root;
            pointer     _null;
    };
}

#endif
