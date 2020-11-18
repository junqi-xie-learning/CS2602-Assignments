#include "tree.h"

// binary_search_tree.h:
//
// Base Class: BinaryTree (in "tree.h")
// Derived Class: BinarySearchTree, AVLTree

namespace cs221
{
    template <class T>
    class BinarySearchTree : public BinaryTree<T>
    {
    private:
        void insert(const T &x, typename BinaryTree<T>::Node *&t);
        void remove(const T &x, typename BinaryTree<T>::Node *&t);
        T *find(const T &x, typename BinaryTree<T>::Node *t) const;
        void makeEmpty(typename BinaryTree<T>::Node *t);

    public:
        T *find(const T &x) const { return find(x, this->root); }
        void insert(const T &x) { insert(x, this->root); };
        void remove(const T &x) { remove(x, this->root); };
    };

    template <class T>
    T *BinarySearchTree<T>::find(const T &x, typename BinaryTree<T>::Node *t) const
    {
        if (t == nullptr)
            return nullptr;

        if (t->data == x)
            return &(t->data);
        else if (x < t->data)
            return find(x, t->left);
        else
            return find(x, t->right);
    }

    template <class T>
    void BinarySearchTree<T>::insert(const T &x, typename BinaryTree<T>::Node *&t)
    {
        if (!t)
            t = new typename BinaryTree<T>::Node{x};
        else if (x < t->data)
            insert(x, t->left);
        else if (t->data < x)
            insert(x, t->right);
    }

    template <class T>
    void BinarySearchTree<T>::remove(const T &x, typename BinaryTree<T>::Node *&t)
    {
        if (!t)
            return;
        if (x < t->data)
            remove(x, t->left);
        else if (t->data < x)
            remove(x, t->right);
        else if (!t->left || !t->right)
        {
            typename BinaryTree<T>::Node *tmp = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete tmp;
        }
        else
        {
            typename BinaryTree<T>::Node *tmp = t->right;
            while (tmp->left != nullptr)
                tmp = tmp->left;
            t->data = tmp->data;
            remove(t->data, t->right);
        }
    }

} // namespace cs221