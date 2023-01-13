#include <iostream>
using namespace std;
struct AvlNode
{
    int data;
    AvlNode *parent;
    AvlNode *left;
    AvlNode *right;
    int height;
};

int Height(AvlNode *root)
{
    if (root == NULL)
        return 0;
    return root->height;
}

AvlNode *GetNewNode(int data)
{
    AvlNode *newNode = new AvlNode();
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    newNode->parent = NULL;
    newNode->height = 1;
    return newNode;
}

void inorder(AvlNode *root)
{
    if (!root)
    {
        return;
    }
    // std::cout << "(go left) ";
    inorder(root->left);
    std::cout << root->data << " ";
    // std::cout << "(go right) ";
    inorder(root->right);
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

int rootGetBalanceFactor(AvlNode *root)
{
    if (root == NULL)
    {
        return 0;
    }
    else
    {
        return (Height(root->left) - Height(root->right));
    }
}

AvlNode *LL_rotation(AvlNode *root)
{                  // right rotation
    AvlNode *curr; // P

    curr = root->left;        // P is the left child of Q
    root->left = curr->right; // after rotation, B is now the left child of Q
    curr->right = root;       // Q becomes the right child of P
    root->height = max(Height(root->left), Height(root->right)) + 1;
    curr->height = max(Height(curr->left), Height(curr->right)) + 1;
    return curr; // P is the new root now
}

AvlNode *RR_rotation(AvlNode *root)
{ // RR rotation
    AvlNode *temp = root->right;
    AvlNode *temp2 = temp->left;
    temp->left = root;
    root->right = temp2;
    root->parent = temp;
    temp->parent = NULL;
    root->height = max(Height(root->left), Height(root->right)) + 1;
    temp->height = max(Height(temp->left), Height(temp->right)) + 1;
    return temp;
}

AvlNode *rootInsert(AvlNode *root, int data)
{
    if (root == NULL)
    {
        // std::cout << "Value inserted successfully" << std::endl;
        return GetNewNode(data);
    }
    if (data < root->data)
    {
        root->left = rootInsert(root->left, data);
    }
    else if (data > root->data)
    {
        root->right = rootInsert(root->right, data);
    }
    else
    {
        std::cout << "No duplicate values allowed!" << std::endl;
        return root;
    }
    root->height = max(Height(root->left), Height(root->right)) + 1;
    int bf = rootGetBalanceFactor(root);
    // LL
    if (bf > 1 && data < root->left->data)
        return LL_rotation(root);
    // RR
    if (bf < -1 && data > root->right->data)
        return RR_rotation(root);
    // LR
    // if (bf > 1 && data > root->left->data){
    //     root->left = RR_rotation(root->left);
    //     return LL_rotation(root);
    // }
    // RL
    // if (bf < -1 && data < root->right->data) {
    //     root->right = LL_rotation(root->right);
    //     return RR_rotation(root);
    // }
    return root;
}

int main()
{
    AvlNode *root = NULL;
    root = rootInsert(root, 2);
    root = rootInsert(root, 1);
    root = rootInsert(root, 4);
    root = rootInsert(root, 6);
    root = rootInsert(root, 7);
    inorder(root);
    cout << endl;
    cout << root->left->data << endl;
    cout << root->right->data << endl;
    cout << root->height << endl;
    return 0;
}