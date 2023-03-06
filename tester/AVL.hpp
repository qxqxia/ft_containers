#ifndef AVL_HPP
#define AVL_HPP

#include <iostream>
#include "utils.hpp"
#include "mapIterator.hpp"
#include <memory>
#include "iterator.hpp"

namespace ft
{
    // class ft::AvlNode
    /*template <class T>
    class ft::AvlNode
    {
        public:
            typedef T value_type;

        public:
            value_type *data;
            int height;
            ft::AvlNode *parent;
            ft::AvlNode *left;
            ft::AvlNode *right;

        public:
            ft::AvlNode() : data(nullptr), parent(nullptr), left(nullptr), right(nullptr), height(0) {}

            ft::AvlNode(value_type val) : data(val), parent(nullptr), left(nullptr), right(nullptr), height(0) {}

            ft::AvlNode(ft::AvlNode const &src) : data(src.data), parent(src.parent), left(src.left), right(src.right), height(src.height) {}

            virtual ~ft::AvlNode() {}

            ft::AvlNode &operator=(ft::AvlNode const &rhs)
            {
                if (this == &rhs)
                    return *this;
                data = rhs.value;
                left = rhs.left;
                right = rhs.right;
                parent = rhs.parent;
                height = rhs.height;
                return (*this);
            }
    };

    // why
    template <class T>
    bool operator==(const ft::AvlNode<T> &lhs, const ft::AvlNode<T> &rhs)
    {
        std::cout << "wow" << std::endl;
        if (lhs->data == nullptr && rhs->data == nullptr)
            return true;
        return (lhs->data == rhs.data);
    }

    template <class T>
    bool operator!=(const ft::AvlNode<T> &lhs, const ft::AvlNode<T> &rhs)
    {
        return (!(lhs == rhs));
    }*/

    // class AVL_tree
    template <class T,
              // class Compare,
              class Compare = std::less<typename T::first_type>,
              class Allocator = std::allocator<T>>
    class AVL_tree
    {
    public:
        typedef T value_type;
        typedef ft::AvlNode<const T> const_node;
        typedef Allocator pair_alloc;
        typedef typename Allocator::template rebind<ft::AvlNode<T>>::other node_alloc;

        typedef ft::mapIterator<T, ft::AvlNode<T>, Compare, AVL_tree> iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::mapIterator<const T, const ft::AvlNode<T>, Compare, AVL_tree> const_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
        typedef typename value_type::first_type key;
        typedef typename value_type::second_type value;

    private:
        ft::AvlNode<T> *_root;
        node_alloc n_alloc;
        pair_alloc p_alloc;
        int _size;
        Compare _comp;

    public:
        AVL_tree() : _root(nullptr), _size(0) {}
        AVL_tree(const AVL_tree &src) : _root(nullptr)
        {
            *this = assign(src);
        }
        /* destructor */
        ~AVL_tree() {}

        AVL_tree &assign(AVL_tree const &x)
        {
            deleteTree();
            p_alloc = x.p_alloc;
            n_alloc = x.n_alloc;
            _comp = x._comp;
            for (const_iterator it = x.begin(); it != x.end(); it++)
                insert(*it);
            _size = x._size;
            return *this;
        }

        /* size of tree */
        int size() const
        {
            return (_size);
        }

        bool empty()
        {
            if (_size == 0)
                return true;
            return false;
        }
        void deleteTree()
        {
            _root = _deleteTree(_root);
            _size = 0;
        }

        ft::AvlNode<T> *_deleteTree(ft::AvlNode<T> *node)
        {
            if (node)
            {
                _deleteTree(node->left);
                _deleteTree(node->right);
                deleteNode(node);
            }
            return nullptr;
        }

        void deleteNode(ft::AvlNode<T> *node)
        {
            p_alloc.destroy(node->data);
            p_alloc.deallocate(node->data, 1);
            node->data = NULL;
            n_alloc.deallocate(node, 1);
            node = NULL;
        }

        // clear the tree
        void clear() { _size = 0; }

        // end and begin
        iterator begin()
        {
            ft::AvlNode<T> *first = find(findMin(_root).first);
            return (iterator(first, this));
        }
        iterator end()
        {
            return (iterator(NULL, this));
        }
        const_iterator begin() const
        {
            ft::AvlNode<T> *first = find(findMin(_root).first);
            return (iterator(first, this));
        }
        const_iterator end() const
        {
            return (iterator(NULL, this));
        }

        // rend and rbegin
        reverse_iterator rbegin() { return reverse_iterator(end()); }
        reverse_iterator rend() { return (reverse_iterator(begin())); }
        const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
        const_reverse_iterator rend() const { return (const_reverse_iterator(begin())); }

        // create newNode
        ft::AvlNode<T> *GetNewNode(T node)
        {
            ft::AvlNode<T> *newNode = n_alloc.allocate(1);
            n_alloc.construct(newNode);
            newNode->data = p_alloc.allocate(1);
            p_alloc.construct(newNode->data, node);
            return (newNode);
        }

        // calculate the height of the node
        int height()
        {
            if (_root == nullptr)
                return (0);
            return (height(_root) - 1);
        }

        // checking if value already exist in the AVL tree
        bool doublecheck(key k) const { return (doublecheck(_root, k)); }

        bool insert(T value)
        {
            if (!doublecheck(_root, value.first))
            {
                _root = insert(_root, value);
                _root->parent = nullptr;
                _size++;
                return true;
            }
            return false;
        }
        // delete one node
        bool delete (key val)
        {
            if (doublecheck(_root, val))
            {
                _root = delete (_root, val);
                // _root->parent = nullptr;
                _size--;
                return true;
            }
            return false;
        }

        // find value, value != null, 0(log(n))
        ft::AvlNode<T> *find(key val)
        {
            if (doublecheck(_root, val))
                return (find(_root, val));
            return nullptr;
        }
        ft::AvlNode<T> *find(key val) const
        {
            if (doublecheck(_root, val))
                return (find(_root, val));
            return nullptr;
        }

        iterator bound(key val, std::string s)
        {
            ft::AvlNode<T> *tmp = nullptr;
            if (s == "lower")
            {
                lower_bound(_root, val, &tmp);
                if (!tmp)
                    return (iterator(nullptr, this));
                return iterator(tmp, this);
            }
            else
            {
                upper_bound(_root, val, &tmp);
                if (!tmp)
                    return (iterator(nullptr, this));
                return iterator(tmp, this);
            }
            return iterator(nullptr, this);
        }

        const_iterator bound(key val, std::string s) const
        {
            ft::AvlNode<T> *tmp = nullptr;
            if (s == "lower")
            {
                lower_bound(_root, val, &tmp);
                if (!tmp)
                    return (const_iterator(nullptr, this));
                return const_iterator(tmp, this);
            }
            else
            {
                upper_bound(_root, val, &tmp);
                if (!tmp)
                    return (const_iterator(nullptr, this));
                return const_iterator(tmp, this);
            }
            return iterator(nullptr, this);
        }

        // allocator methods
        size_t get_alloc() const { return (n_alloc.max_size()); }
        node_alloc get_allocator() const { return (n_alloc); }
        ft::AvlNode<T> *getRoot(void) const { return (_root); }

        // find max and min value
        ft::AvlNode<T> *findmin(ft::AvlNode<T> *node)
        {
            while (node->left != nullptr)
                node = node->left;
            return (node);
        }

        ft::AvlNode<T> *findmax(ft::AvlNode<T> *node)
        {
            while (node->right != nullptr)
                node = node->right;
            return (node);
        }

        ft::AvlNode<T> *findmin(ft::AvlNode<T> *node) const
        {
            while (node->left != nullptr)
                node = node->left;
            return (node);
        }
        ft::AvlNode<T> *findmax(ft::AvlNode<T> *node) const
        {
            while (node->right != nullptr)
                node = node->right;
            return (node);
        }

    private:
        // height overload
        int max(int left, int right)
        {
            if (left < right)
            {
                return right;
            }
            else
                return left;
        }

        int height(ft::AvlNode<T> *node)
        {
            if (node == nullptr)
                return -1;
            return max(height(node->left), height(node->right)) + 1;
        }

        // double check if value already exist in the tree
        // contains overload
        bool doublecheck(ft::AvlNode<T> *node, key k) const
        {
            if (node == nullptr)
                return false;
            bool cmp = _comp(node->data->first, k);
            bool cmp1 = _comp(k, node->data->first);
            if (!cmp1 && !cmp)
                return true;
            if (!cmp)
                return (doublecheck(node->left, k));
            if (cmp)
                return (doublecheck(node->right, k));
            return true;
        }

        int rootGetBalanceFactor(ft::AvlNode<T> *node)
        {
            if (node == nullptr)
            {
                return 0;
            }
            else
            {
                return (height(node->left) - height(node->right));
            }
        }

        void ResetParent(ft::AvlNode<T> *oldRoot, ft::AvlNode<T> *newRoot) const
        {
            if (!oldRoot->parent)
            {
                newRoot->parent = NULL;
                if (oldRoot->left)
                    oldRoot->left->parent = oldRoot;
                if (oldRoot->right)
                    oldRoot->right->parent = oldRoot;
                oldRoot->parent = newRoot;
                return;
            }
            newRoot->parent = oldRoot->parent;
            oldRoot->parent = newRoot;
            if (oldRoot->left)
                oldRoot->left->parent = oldRoot;
            if (oldRoot->right)
                oldRoot->right->parent = oldRoot;
        }

        ft::AvlNode<T> *LL_rotation(ft::AvlNode<T> *node)
        { // right rotation
            ft::AvlNode<T> *curr = node->left;

            node->left = curr->right;
            curr->right = node;
            ResetParent(node, curr);
            node->height = max(height(node->left), height(node->right)) + 1;
            curr->height = max(height(curr->left), height(curr->right)) + 1;
            return curr;
        }

        ft::AvlNode<T> *RR_rotation(ft::AvlNode<T> *node)
        {
            ft::AvlNode<T> *curr = node->right;

            node->right = curr->left;
            curr->left = node;
            ResetParent(node, curr);
            node->height = max(height(node->left), height(node->right)) + 1;
            curr->height = max(height(curr->left), height(curr->right)) + 1;
            return curr;
        }

        ft::AvlNode<T> *insert(ft::AvlNode<T> *node, T val)
        {
            if (node == nullptr)
            {
                // std::cout << "Value inserted successfully" << std::endl;
                return GetNewNode(val);
            }
            if (val.first < node->data->first)
            {
                node->left = insert(node->left, val);
                node->left->parent = node;
            }
            else if (val.first > node->data->first)
            {
                node->right = insert(node->right, val);
                node->right->parent = node;
            }
            else
            {
                std::cout << "No duplicate values allowed!" << std::endl;
                return node;
            }
            node->height = max(height(node->left), height(node->right)) + 1;
            int bf = rootGetBalanceFactor(node);
            // LL
            if (bf > 1 && val.first < node->left->data)
                return LL_rotation(node);
            // RR
            if (bf < -1 && val.first > node->right->data)
                return RR_rotation(node);
            // LR
            if (bf > 1 && val.first > node->left->data)
            {
                node->left = RR_rotation(node->left);
                return LL_rotation(node);
            }
            // RL
            if (bf < -1 && val.first < node->right->data)
            {
                node->right = LL_rotation(node->right);
                return RR_rotation(node);
            }
            return node;
        }

        /*pointer successor(pointer node) const
        {
            if (node->right != _null)
                return minVal(node->right);
            if (node->parent == _null || node == maxVal(this->_root))
                return _null;
            pointer tmp = node->parent;
            while (tmp != _null && node == tmp->right)
            {
                node = tmp;
                tmp = tmp->parent;
            }
            return tmp;
        }*/

        /*ft::ft::AvlNode<T> *delete (ft::ft::AvlNode<T> *node, key val)
        {
        }*/

        // overload find
        ft::AvlNode<T> *find(ft::AvlNode<T> *node, key val)
        {
            if (node == nullptr)
                return nullptr;
            bool cmp = _comp(node->data->first, val);
            bool cmp1 = _comp(val, node->data->first);
            if (!cmp && !cmp1)
                return node;
            if (!cmp)
                return (find(node->left, val));
            else if (cmp)
                return (find(node->right, val));
            return node;
        }

        ft::AvlNode<T> *find(ft::AvlNode<T> *node, key val) const
        {
            if (node == nullptr)
                return nullptr;
            bool cmp = _comp(node->data->first, val);
            bool cmp1 = _comp(val, node->data->first);
            if (!cmp && !cmp1)
                return node;
            if (!cmp)
                return (find(node->left, val));
            else if (cmp)
                return (find(node->right, val));
            return node;
        }

        void lower_bound(ft::AvlNode<T> *node, key val, ft::AvlNode<T> **pptr) const
        {
            if (node == nullptr)
                return;
            bool cmp = _comp(node->data->first, val);
            bool cmp1 = _comp(val, node->data->first);
            if (!cmp && !cmp1)
            {
                *pptr = node;
                return;
            }
            if (!cmp)
                lower_bound(node->left, val, pptr);
            if (*pptr == nullptr && !cmp)
            {
                *pptr = node;
                return;
            }
            if (cmp)
                lower_bound(node->right, val, pptr);
        }

        void upper_bound(ft::AvlNode<T> *node, key val, ft::AvlNode<T> **pptr) const
        {
            if (node == nullptr)
                return;
            bool cmp = _comp(node->data->first, val);
            bool cmp1 = _comp(val, node->data->first);
            if (!cmp && !cmp1)
            {
                *pptr = node->right;
                return;
            }
            if (!cmp)
                upper_bound(node->left, val, pptr);
            if (*pptr == nullptr && !cmp)
            {
                *pptr = node;
                return;
            }
            if (cmp)
                upper_bound(node->right, val, pptr);
        }

        T findMin(ft::AvlNode<T> *node)
        {
            if (node == nullptr)
                return (ft::make_pair(key(), value()));
            while (node->left != nullptr)
                node = node->left;
            return (*(node->data));
        }

        T findMax(ft::AvlNode<T> *node)
        {
            if (node == nullptr)
                return (ft::make_pair(key(), value()));
            while (node->right != nullptr)
                node = node->right;
            return (*(node->data));
        }

        T findMin(ft::AvlNode<T> *node) const
        {
            if (node == nullptr)
                return (ft::make_pair(key(), value()));
            while (node->left != nullptr)
                node = node->left;
            return (*(node->data));
        }

        T findMax(ft::AvlNode<T> *node) const
        {
            if (node == nullptr)
                return (ft::make_pair(key(), value()));
            while (node->right != nullptr)
                node = node->right;
            return (*(node->data));
        }

        /*int max(int left, int right)
        {
            if (left < right)
            {
                return right;
            }
            else
                return left;
        }*/

        /*height of the node
        int FindHeight(pointer root)
        {
            if (root == _null)
                return -1; // the height of leaf node is -1 + 1 = 0
            else
            {
                return max(FindHeight(root->left), FindHeight(root->right)) + 1;
            }
        }*/

        /*pointer searchNode(pointer root, value_type const &val) const
        {
            // We reached a leaf or root is empty
            if (root == _null)
                return 0;
            else
            {
                // Recursive loop until we find key
                if (val.first < root->value.first)
                    return searchNode(root->left, val);
                else if (val.first > root->value.first)
                    return searchNode(root->right, val);
                else
                    return root;
            }
        }*/

        /*pointer balance(pointer curr)
        {
            int getBalance = rootGetBalanceFactor(curr);
            if (getBalance > 1)
            {
                if (rootGetBalanceFactor(curr->left) > 0)
                {
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
        }*/

        /*pointer LL_rotation(pointer root)
        { // right rotation
            //               Q                               P              |
            //              / \     RIGHT ROTATION          / \             |
            //             P   C         ==>               A   Q            |
            //            / \                                 / \           |
            //           A   B                               B   C          |
            pointer curr; // P

            curr = root->left;        // P is the left child of Q
            root->left = curr->right; // after rotation, B is now the left child of Q
            curr->right = root;       // Q becomes the right child of P
            root->height = max(FindHeight(root->left), FindHeight(root->right)) + 1;
            curr->height = max(FindHeight(curr->left), FindHeight(curr->right)) + 1;
            return curr; // P is the new root now
        }*/

        /*pointer RR_rotation(pointer root)
        { // RR rotation
            //               p                               Q              |
            //              / \    LEFT ROTATION            / \             |
            //             A   Q        ==>                P   C            |
            //                / \                         / \               |
            //               B   C                       A   B              |

            pointer curr; // Q

            curr = root->right;       // Q is the right child of P
            root->right = curr->left; // after rotation, B is now the right child of P
            curr->left = root;        // P becomes the left child of Q
            root->height = max(FindHeight(root->left), FindHeight(root->right)) + 1;
            curr->height = max(FindHeight(curr->left), FindHeight(curr->right)) + 1;
            return curr; // return new root
        }*/

        /*pointer RL_rotation(pointer root)
        {
            // RL(D rotates to the right, then C rotates to the left):
            //              k3                         k3                          k2       |
            //             /  \                       /  \                        /  \      |
            //            A    k1                    A    k2                     k3   k1    |
            //                /  \       ==>             /  \         ==>       /  \  / \   |
            //               k2   B                     C    k1                A   C D   B  |
            //              /  \                            /  \                            |
            //             C    D                          D    B                           |

            pointer curr;

            curr = root->right;
            curr->right = LL_rotation(curr);
            return (RR_rotation(curr));
        }*/

        /*pointer LR_rotation(pointer root)
        {
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
        }*/

        /*void inorder(pointer root)
        {
            if (root == _null)
                return;
            else
            {
                inorder(root->left);
                std::cout << root->value << " ";
                inorder(root->right);
            }
        }*/

        /*pointer rootInsert(pointer root, pointer new_node){
            if (root == _null)
            {
                root = new_node;
                std::cout << "Value inserted successfully" << std::endl;
                return root;
            }
            if (new_node->value < root->value)
            {
                root->left = rootInsert(root->left, new_node);
            }
            else if (new_node->value > root->value)
            {
                root->right = rootInsert(root->right, new_node);
            }
            else
            {
                std::cout << "No duplicate values allowed!" << std::endl;
                return root;
            }
            root->height = max(FindHeight(root->left), FindHeight(root->right)) + 1;
            int bf = rootGetBalanceFactor(root);
            // LL
            if (bf > 1 && new_node->value < root->left->value)
                return LL_rotation(root);
            // RR
            if (bf < -1 && new_node->value > root->right->value)
                return RR_rotation(root);
            // LR
            if (bf > 1 && new_node->value > root->left->value)
                return LR_rotation(root);
            // RL
            if (bf < -1 && new_node->value < root->right->value)
            {
                root->right = LL_rotation(root->right);
                return (RR_rotation(root));
            }
            return root;
        }*/

        /*pointer rootDelete(pointer root, value_type value){
            //base case
            if (!root)
                return ;
            if (value < root->value){
                root->left = rootDelete(root->left, value);
            }
            else if(value > root->value){
                root->right = rootDelete(root->right, value);
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
                    //find the max value in th eleft subroot
                    while(tmp->right != NULL){
                        tmp = tmp->right;
                    }
                    root->value = tmp->value;
                    root->left = rootDelete(root->left, tmp->value);
                }
            }
            return root;
            }*/
    };
}

#endif
