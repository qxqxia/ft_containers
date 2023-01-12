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

BstNode* FindMin(BstNode* root){
    if (root == NULL){
        cout << "Error: Tree is empty\n";
        return root;
    }
    while(root->left != NULL){
        root = root->left;
    }
    return root;
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

BstNode* FindMax(BstNode* root){
    //iterative solution
    if (root == NULL){
        cout << "Error: Tree is empty\n";
        return root;
    }
    BstNode* current = root;
    while(current->right != NULL){
        current = current->right;
    }
    return current;
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

BstNode* Delete(BstNode* root, int data){
    if (root == NULL)
        return root;
    else if(data < root->data){
        root->left = Delete(root->left, data);
    }
    else if(data > root->data){
        root->right = Delete(root->right, data);
    }
    else{
        //case 1: no child
        if (root->left == NULL && root->right == NULL){
            delete root;
            root = NULL;
        }
        //case 2:one child
        else if(root->left == NULL){
            BstNode* tmp = root;
            root = root->right;
            delete tmp;
        }
        else if(root->right == NULL){
            BstNode* tmp = root;
            root = root->left;
            delete tmp;
        }
        //case 3: two child
        else{
            BstNode* tmp = FindMin(root->right);
            root->data = tmp->data;
            root->right = Delete(root->right, tmp->data);
        }
    }
    return root;
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

bool IsSubtreeLesser(BstNode* root, int value){
    if (root == NULL)
        return true;
    if (root->data <= value 
    && IsSubtreeLesser(root->left, value) 
    && IsSubtreeLesser(root->right, value)){
        return true;
    }
    else
        return false; 
}

bool IsSubtreeGreater(BstNode* root, int value){
    if (root == NULL)
        return true;
    if (root->data > value
    && IsSubtreeGreater(root->left, value)
    && IsSubtreeGreater(root->right, value)){
        return true;
    }
    else
        return false;
}

bool IsBinarySearchTree(BstNode* root){
    if (root == NULL)
        return true;
    if(IsSubtreeLesser(root->left, root->data) //all nodes at left are lesser than root
    && IsSubtreeGreater(root->right, root->data)//all nodes at right are greater than root
    && IsBinarySearchTree(root->left) //left subtree is bst
    && IsBinarySearchTree(root->right))//right subtree is bst
    {
        return true;
    }
    else
        return false;
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
    int high1 = FindHeight(root);
    cout << high1 << endl;
    BstNode *n = FindMax(root);
    cout << n->data << endl;
    BstNode *n1 = FindMin(root);
    cout << n1->data << endl;
    root = Delete(root, 10);
    inorder(root);
    cout << endl;
    int number;
    cout << "Enter number be searched\n";
    cin >> number;
    if (Search(root, number) == true)
        cout << "Found\n";
    else
        cout << "Not Found\n";
}
