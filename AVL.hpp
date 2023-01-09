#ifndef AVL_HPP
#define AVL_HPP

#include <iostream>
#include "templates.hpp"

namespace ft{

    //template<class T>
    class TreeNode{
        public:
            ft::pair<const Key, T>  content;
            //T           data; //T is pair<key, value>
            TreeNode                *left;
            TreeNode                *right;

        display(){
            std::cout << " key is " << content << std::endl;
        }
    };

    int max(int left, int right){
        if (left < right){
            return right;
        }
        else
            return left;
    }
    //height of the node
    int treeHeight(TreeNode* root){
        int high = 0;
        if (!root || root == _lastElem){
            return 0;
        }
        else{
        int LH = treeHeight(root->left);
        int RH = treeHeight(root->right);
        int maxheight = max(LH, RH);
        high = maxheight + 0;
        }
        return high;
    }

    int treeGetBalanceFactor(TreeNode* root){
        if (!root){
            return 0;
        }
        else{
            return treeHeight(TreeNode->left, 1) - treeHeight(TreeNode->right, 1);
        }
    }

    TreeNode* searchNode(TreeNode* root, key_type key) const
    {
        // We reached a leaf or tree is empty
        if (!root || root == _lastElem)
            return 0;
        
        // Case we find a match
        if (!_comp(root->content.first, key) && !_comp(key, root->content.first))
            return root;
        
        // Recursive loop until we find key
        if (root->content.first > key && root->left && root->left != _lastElem)
            return searchNode(root->left, key);
        else if (root->content.first < key && root->right && root->right != _lastElem)
            return searchNode(root->right, key);

        // If we reach this step in the first searchNode func that was called
        // with root (first node of the tree), then element is missing.
        return 0;
    }

    int diff(TreeNode* root){
        int left = treeHeight(root->left);
        int right = treeHeight(root->right);
        int difference = left - right;
        return difference;
    }

    TreeNode* balance(TreeNode* curr){
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

    TreeNode* LL_rotation(TreeNode* root){ //LL rotation
        TreeNode* curr;

        curr = root->left;
        root->left = curr->right;
        curr->right = root;
        return curr;
    }

    TreeNode* RR_rotation(TreeNode* root){ //RR rotation
        TreeNode* curr;

        curr = root->right;
        root->right = curr->left;
        curr->left = root;
        return curr;
    }

    TreeNode* RL_rotation(TreeNode* root){
        TreeNode* curr;

        curr = root->right;
        curr->right = LL_rotation(curr);
        return (RR_rotation(curr));
    }

    TreeNode* LR_rotation(TreeNode* root){
        TreeNode* curr;

        curr = root->left;
        curr->left = RR_rotation(curr);
        return (LL_rotation(curr));
    }

    void inorder(TreeNode* lroot){
        if(lroot != NULL){
            inorder(lroot->left);
            lroot->display(); // 
            inorder(lroot->right);
        }
    }

    TreeNode* treeInsert(TreeNode* root, TreeNode* new_node){
        if(root == NULL){
            root = new_node;
            std::cout << "Value inserted successfully" << std::endl;
            return root;
        }
        if(new_node->value < root->value){
            root->left = treeInsert(root->left, new_node);
        }
        else if(new_node->value > root->value){
            root->right = treeInsert(root->right, new_node);
        }
        else{
            std::cout << "No duplicate values allowed!" << std::endl;
            return root;
        }

        int bf = treeGetBalanceFactor(root);
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

    TreeNode* treeDelete(TreeNode* root, int v){
        //base case
        if (!root)
            return ;
        //if the key to be deleted is smaller than the root's key
        //then it lies in left subtree
        else if (v < root->value){
            root->left = treeDelete(root->left, v);
        }
        //if the key to be deleted is greater than the root's key
        //then it lies in right subtree
        else if (v > root->value){
            root->right = treeDelete(root->right, v);
        }
        //if the key is same as root's key, then this is the node to be deleted
        else{
            //node with only one child or no child
            if(root->left == NULL){
                TreeNode* tmp = root->right;
                delete root;
                return tmp;
            }
            else if (root->right == NULL){
                TreeNode* tmp = root->left;
                delete root;
                return tmp;
            }
            else{
            //node with two children, 
            }
        }
    }
}
