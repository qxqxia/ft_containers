#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include <iostream>
#include "utils.hpp"
#include <memory>
#include "iterator.hpp"

enum e_color
{
    RED,
    BLACK
};

namespace ft
{

    template <typename T, // T is a pair
              typename K, // K is key_type
              class Compare,
              class Allocator>
    class red_black_tree
    {
    private:
        typedef T value_type;

        struct TreeNode
        {
            value_type data;
            e_color color;
            TreeNode *parent;
            TreeNode *left;
            TreeNode *right;

            TreeNode(const value_type &v = value_type()) : data(v), left(0), right(0), parent(0) {}
        };

        typedef K key_type;
        typedef Allocator allocator_type;
        typedef size_t size_type;
        typedef Compare compare_type;
        typedef value_type *pointer;
        typedef TreeNode *treenode_pointer;
        typedef const TreeNode *const_treenode_pointer;
        typedef const value_type &const_reference;
        typedef typename allocator_type::template rebind<TreeNode>::other treenode_allocator;

        treenode_pointer _root;
        treenode_pointer _end;
        size_type _size;
        treenode_allocator _treenode_alloc;
        compare_type _comp;

    public:
        typedef typename ft::tree_iterator<value_type, treenode_pointer, compare_type> iterator;
        typedef typename ft::tree_iterator<const value_type, treenode_pointer, compare_type> const_iterator;

        red_black_tree(const compare_type& comp = compare_type(), const treenode_allocator& treenode_alloc = treenode_allocator())
        {
		_treenode_alloc = treenode_alloc;
		_end = new_node();
		_root = _end;
		_size = 0;
		_comp = comp;
	
        }

        /* destructor */
        ~red_black_tree() {
		if(_size){ clear();}
		destroy_node(_root);
	}

	treenode_pointer	new_node(const_reference val = value_type())
	{
		treenode_pointer node = _treenode_alloc.allocate(1);

		_treenode_alloc.construct(node, TreeNode(val));
		node->color = RED;
		node->left = NULL;
		node->right = NULL;
		node->parent = NULL;
		return node;
	}

	

        /* size of node(tree) */
        size_type size() const
        {
            return _size;
        }

        size_type max_size() const
        {
            return _treenode_alloc.max_size();
        }

	bool empty()const {return _size == 0;}

	iterator	begin(){return iterator(minVal());}

	const_iterator	begin()const{return const_iterator(minVal());}

	iterator	end(){return iterator(_end);}

	const_iterator	end(){return const_iterator(_end);}

	compare_type	comp()const{return _comp;}

	/*iterator	find(const_reference val)
	{
		treenode_pointer 
	}*/

        /*min val in tree*/
       /* treenode_pointer minVal(treenode_pointer _root) const
        {
            if (!_root)
                return;
            while (_root->left != NULL)
                _root = _root->left;
            return _root;
        }*/

        /* max val in tree*/
       /* treenode_pointer maxVal(treenode_pointer _root) const
        {
            if (!_root)
                return;
            while (_root->right != NULL)
                _root = root->right;
            return _root;
        }*/

        // delete one node
        bool delete_node(value_type const &val)
        {
        }

        void swap(red_black_tree &src)
        {
        }

        treenode_pointer successor(treenode_pointer node)
        {
            if (node->right)
                return minVal(node->right);
            if (node->parent || node == maxVal(this->_root))
                return _null;
            /*pointer tmp = node->parent;
            while (tmp != _null && node == tmp->right) {
                node = tmp;
                tmp = tmp->parent;
            }
            return tmp;*/
        }

        iterator lower_bound(const_reference val)
        {
        }

        iterator lower_bound(const_reference val) const
        {
        }

        iterator upper_bound(const_reference val)
        {
        }

        iterator upper_bound(const_reference val) const
        {
        }

        // delete tree
        void destroy_tree()
        {
            destroy_tree(this->_root);
            this->_root = _null;
        }

        int max(int left, int right)
        {
            if (left < right)
            {
                return right;
            }
            else
                return left;
        }

        /*pointer searchNode(pointer root, value_type const& val) const
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
    };
}

#endif
