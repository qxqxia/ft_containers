#include <iostream>
using namespace std;

struct BstNode
{
    int     data;
    int     height;
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
    // if (root)
    // {
    //     inorder(root->left);
    //     std::cout << root->data << " ";
    //     inorder(root->right);
    // }
    if (!root)
    {
        //std::cout << '\n';
        return ;
    }
    //std::cout << "(go left) ";
    inorder(root->left);
    std::cout << root->data << " ";
    //std::cout << "(go right) ";
    inorder(root->right);

}

void preorder(BstNode *root)
{
    if (!root)
        return  ;
    std::cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
    
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

int rootGetBalanceFactor(BstNode* root){
    if (root == NULL)
        return 0;
    return (FindHeight(root->left) - FindHeight(root->right));

}

BstNode* LL_rotation(BstNode* root){                                                                    
    BstNode* curr; //P

    curr = root->left; //P is the left child of Q
    root->left = curr->right; // after rotation, B is now the left child of Q
    curr->right = root; //Q becomes the right child of P
    root->height = max(FindHeight(root->left), FindHeight(root->right)) + 1;
    curr->height = max(FindHeight(curr->left), FindHeight(curr->right)) + 1;
    return curr; //P is the new root now
}  

BstNode* RR_rotation(BstNode* root){ 
    BstNode* curr; //Q

    curr = root->right; //Q is the right child of P
    root->right = curr->left;//after rotation, B is now the right child of P
    curr->left = root; //P becomes the left child of Q
    root->height = max(FindHeight(root->left), FindHeight(root->right)) + 1;
    curr->height = max(FindHeight(curr->left), FindHeight(curr->right)) + 1;
    return curr;//return new root
}

BstNode* RL_rotation(BstNode* root){
    BstNode* curr;

    curr = root->right;
    curr->right = LL_rotation(curr);
    return (RR_rotation(curr));
}

BstNode* LR_rotation(BstNode* root){
    BstNode* curr;

    curr = root->left;
    curr->left = RR_rotation(curr);
    return (LL_rotation(curr));
}

BstNode* balance(BstNode* curr){
    int getBalance = rootGetBalanceFactor(curr);
    if (getBalance > 1)
    {
        if(rootGetBalanceFactor(curr->left) > 0){
            curr = LL_rotation(curr);
        }
        else
            curr = LR_rotation(curr);
    }
    else if (getBalance < -1)
    {
        if (rootGetBalanceFactor(curr->right) > 0)
            curr = RL_rotation(curr);
        else
            curr = RR_rotation(curr);
    }
    return curr;
}

int main()
{
    std::cout << __FUNCTION__ << std::endl;
    BstNode *root = NULL;

    root = Insert(root, 15);
    root = Insert(root, 10);
    root = Insert(root, 20);
    root = Insert(root, 25);
    root = Insert(root, 8);
    root = Insert(root, 12);
    root = Insert(root, 5);
    root = Insert(root, 3);
    
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

    if (IsBinarySearchTree(root)){
        cout << "Is Binary Search Tree.\n";
    }
    
    BstNode* n2 = balance(root);
    cout << n2->data << endl;
    
    inorder(n2);
    std::cout << '\n';

    preorder(n2);
    std::cout << '\n';
    
    postorder(n2);
    std::cout << '\n';
    
    cout << endl;
    //root = Delete(root, 10);
    //inorder(root);
    //cout << endl;
    int number;
    cout << "Enter number be searched\n";
    cin >> number;
    if (Search(root, number) == true)
        cout << "Found\n";
    else
        cout << "Not Found\n";
}
