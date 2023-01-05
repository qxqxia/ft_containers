#ifndef AVL_HPP
#define AVL_HPP

#include <iostream>
#include "templates.hpp"

namespace ft{

    template<class T>
    struct TreeNode{
        T           data; //T is pair<key, value>
        int         height;
        TreeNode    *left;
        TreeNode    *right;
    };

    typedef struct node node_t;
    typedef struct node* nodeptr_t;

    //height of the node
    int treeHeight(nodeptr_t root){
        if (root == NULL){
            return 0;
        }
        else{
            return max(treeHeight(root->left), treeHeight(root->right)) + 1;
        }
    }

    int treeGetBalanceFactor(nodeptr_t root){
        if (root == NULL){
            return 0;
        }
        else{
            return x->left->height - x->right->height;
        }
    }

    nodeptr_t treeRotateRight(nodeptr_t root){
        nodeptr_t left = root->left;

        root->left = left->right;
        left->right = root;

        left->height = max(treeHeight(left->left), treeHeight(left->right)) + 1;
        right->height = max(treeHeight(right->left), treeHeight(right->right)) + 1;

        return left;
    }

    nodeptr_t treeRotateLeft(nodeptr_t root){
        nodeptr_t right = root->right;

        root->right = right->left;
        right->left = root;

        left->height = max(treeHeight(left->left), treeHeight(left->right)) + 1;
        right->height = max(treeHeight(right->left), treeHeight(right->right)) + 1;

        return right;
    }

    //balanced operations
    nodeptr_t treeRebalance(nodeptr_t root){
        int factor = treeGetBalanceFactor(root);
        if (factor > 1 && treeGetBalanceFactor(root->left) > 0){ //LL
            return (treeRotateRight(root));
        }
        else if (factor > 1 && treeGetBalanceFactor(root->left) <= 0){ //LR
            root->left = treeRotateLeft(root->left);
            return (treeRotateRight(temp));
        }
        else if (factor < -1 && treeGetBalanceFactor(root->right) <= 0){//RR
            return (treeRotateLeft(root));
        }
        else if (factor < -1 && treeGetBalanceFactor(root->right) > 0){//RL
            root->right = treeRotateRight(root->right);
            return (treeRotateLeft(root));
        }
        else{ //nothing happened
            return root;
        }
    }

    void treeInsert(nodeptr_t *rootptr, int value){
        nodeptr_t newNode;
        nodeptr_t root = *rootptr;

        if (root == NULL){
            newNode = malloc(sizeof(node_t));
            assert(newNode);

            newNode->data = value;
            newNode->left = newNode->right = NULL;

            *rootptr = newNode;
        }
        else if(root->data == value){
            return ;
        }
        else{
            if(root->data < value){
                treeInsert(&root->right, value);
            }
            else{
                treeInsert(&root->left, value)
            }    
        }
        treeRebalance(root);
    }

    void treeDelete(nodeptr_t *rootptr, int data){
        nodeptr_t *toFree;
        nodeptr_t root = *rootptr;

        if(root){
            if (root->data == value){
                if(root->right){
                    root->data = treeDeleteMin(&(root->right));
                }
                else{
                    toFree = root;
                    *rootptr = toFree->left;
                    free(toFree);
                }
            }
            else{
                if(root->data < value){
                    treeDelete(&root->right, value);
                }
                else{
                    treeDelete(&root->left, value);
                }
                
            }
            treeRebalance(root);
        }
    }

}