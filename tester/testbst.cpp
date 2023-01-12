#include <iostream>
using namespace std;

struct BstNode
{
    int data;
    BstNode *left;
    BstNode *right;
};

BstNode *GetNewNode(int data)
{
    BstNode *newNode = new BstNode();
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

BstNode *Insert(BstNode *root, int data)
{
    if (root == NULL)
    {
        root = GetNewNode(data);
        return root;
    }
    else if (data <= root->data)
    {
        root->left = Insert(root->left, data);
    }
    else
    {
        root->right = Insert(root->right, data);
    }
    return root;
}

bool Search(BstNode *root, int data)
{
    if (root == NULL)
        return false;
    else if (root->data == data)
        return true;
    else if (data <= root->data)
        return Search(root->left, data);
    else
        return Search(root->right, data);
}

int FindMin(BstNode* root){
    if (root == NULL){
        cout << "Error: Tree is empty\n";
        return -1;
    }
    while(root->left != NULL){
        root = root->left;
    }
    return root->data;
    /*recursive solution
    if (root == NULL){
        cout << "Error: Tree is empty\n";
        return -1;
    }
    else if (root->left == NULL){
        return root->data;
    }
    //serach in left subtree
    return FindMax(root->left);*/
}

int FindMax(BstNode* root){
    //iterative solution
    if (root == NULL){
        cout << "Error: Tree is empty\n";
        return -1;
    }
    BstNode* current = root;
    while(current->right != NULL){
        current = current->right;
    }
    return current->data;
    /*recursive solution
    if (root == NULL){
        cout << "Error: Tree is empty\n";
        return -1;
    }
    else if (root->right == NULL){
        return root->data;
    }
    //serach in right subtree
    return FindMax(root->right);*/

}

int max(int left, int right){
    if (left < right){
        return right;
    }
    else
        return left;
}

int FindHeight(BstNode* root){
    if (root == NULL)
        return -1;
    return max(FindHeight(root->left), FindHeight(root->right)) + 1;
}

void inorder(BstNode *root)
{
    if (root)
    {
        inorder(root->left);
        std::cout << root->data << " ";
        inorder(root->right);
    }
}

void preorder(BstNode *root)
{
    if (root)
    {
        std::cout << root->data << " ";
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(BstNode *root)
{
    if (root)
    {
        postorder(root->left);
        postorder(root->right);
        std::cout << root->data << " ";
    }
}

int main()
{
    BstNode *root = NULL;

    root = Insert(root, 15);
    root = Insert(root, 10);
    root = Insert(root, 20);
    root = Insert(root, 25);
    root = Insert(root, 8);
    root = Insert(root, 12);
    inorder(root);
    cout << endl;
    preorder(root);
    cout << endl;
    postorder(root);
    cout << endl;
    int high1 = 0;
    high1 = FindHeight(root);
    cout << high1 << endl;
    int n = 0;
    n = FindMax(root);
    cout << n << endl;
    int n1= 0;
    n1 = FindMin(root);
    cout << n1 << endl;
    int number;
    cout << "Enter number be searched\n";
    cin >> number;
    if (Search(root, number) == true)
        cout << "Found\n";
    else
        cout << "Not Found\n";
}
