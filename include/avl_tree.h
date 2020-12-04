#ifndef AVL_TREE
#define AVL_TREE

#include <iostream>

// avl_tree.h:
//
// Class: AVLTree

namespace cs221
{
    template <class T>
    class AVLTree
    {
    protected:
        struct AVLNode
        {
            T data;
            AVLNode *left;
            AVLNode *right;
            int height;

            AVLNode(const T &element, AVLNode *lt = nullptr, AVLNode *rt = nullptr, int h = 1)
                : data{ element }, left{ lt }, right{ rt }, height{ h } { }
        };
        AVLNode *root;

        T *find(const T &x, AVLNode *t) const;
        void insert(const T &x, AVLNode *&t);
        bool remove(const T &x, AVLNode *&t);
        void clear(AVLNode *&t);
        void traverse(AVLNode *t) const;

        int height(AVLNode *t) const { return !t ? 0 : t->height; }
        void LL(AVLNode *&t);
        void RR(AVLNode *&t);
        void LR(AVLNode *&t) { RR(t->left); LL(t); }
        void RL(AVLNode *&t) { LL(t->right); RR(t); }
        bool adjust(AVLNode *&t, bool adjust_right);

    public:
        AVLTree() { root = nullptr; }
        ~AVLTree() { clear(); }
        void clear() { clear(root); }
        void traverse() const { traverse(root); }

        T *find(const T &x) const { return find(x, root); }
        void insert(const T &x) { insert(x, root); }
        void remove(const T &x) { remove(x, root); }
    };

    template <class T>
    T *AVLTree<T>::find(const T &x, AVLNode *t) const
    {
        if (!t)
            return nullptr;

        if (x == t->data)
            return &(t->data);
        else if (x < t->data)
            return find(x, t->left);
        else
            return find(x, t->right);
    }

    template <class T>
    void AVLTree<T>::LL(AVLNode *&t)
    {
        AVLNode *t1 = t->left;
        t->left = t1->right;
        t1->right = t;
        t->height = std::max(height(t->left), height(t->right)) + 1;
        t1->height = std::max(height(t1->left), height(t)) + 1;
        t = t1;
    }

    template <class T>
    void AVLTree<T>::RR(AVLNode *&t)
    {
        AVLNode *t1 = t->right;
        t->right = t1->left;
        t1->left = t;
        t->height = std::max(height(t->left), height(t->right)) + 1;
        t1->height = std::max(height(t1->right), height(t)) + 1;
        t = t1;
    }

    template <class T>
    void AVLTree<T>::insert(const T &x, AVLNode *&t)
    {
        if (!t)
            t = new AVLNode{ x };
        else if (x < t->data)
        {
            insert(x, t->left);
            if (height(t->left) - height(t->right) == 2)
                x < t->left->data ? LL(t) : LR(t);
        }
        else if (t->data < x)
        {
            insert(x, t->right);
            if (height(t->right) - height(t->left) == 2)
                t->right->data < x ? RR(t) : RL(t);
        }
        t->height = std::max(height(t->left), height(t->right)) + 1;
    }

    template <class T>
    bool AVLTree<T>::remove(const T &x, AVLNode *&t)
    {
        if (!t)
            return true;
        if (x == t->data)
        {
            if (!t->left || !t->right)
            {
                AVLNode *tmp = t;
                t = t->left ? t->left : t->right;
                delete tmp;
                return false;
            }
            else
            {
                AVLNode *tmp = t->right;
                while (tmp->left)
                    tmp = tmp->left;
                t->data = tmp->data;
                if (remove(tmp->data, t->right))
                    return true;
                return adjust(t, true);
            }
        }
        if (x < t->data)
        {
            if (remove(x, t->left))
                return true;
            return adjust(t, false);
        }
        else
        {
            if (remove(x, t->right))
                return true;
            return adjust(t, true);
        }
    }

    template <class T>
    bool AVLTree<T>::adjust(AVLNode *&t, bool adjust_right)
    {
        if (adjust_right)
        {
            if (height(t->left) - height(t->right) == 1)
                return true;
            else if (height(t->right) == height(t->left))
            {
                --t->height;
                return false;
            }
            else if (height(t->left->right) > height(t->left->left))
            {
                LR(t);
                return false;
            }
            else
            {
                LL(t);
                return height(t->right) != height(t->left);
            }
        }
        else
        {
            if (height(t->right) - height(t->left) == 1)
                return true;
            else if (height(t->right) == height(t->left))
            {
                --t->height;
                return false;
            }
            else if (height(t->right->left) > height(t->right->right))
            {
                RL(t);
                return false;
            }
            else
            {
                RR(t);
                return height(t->right) != height(t->left);
            }
        }
    }

    template <class T>
    void AVLTree<T>::clear(AVLNode *&t)
    {
        if (t == nullptr)
            return;
        
        clear(t->left);
        clear(t->right);
        delete t;
        t = nullptr;
    }

    template <class T>
    void AVLTree<T>::traverse(AVLNode *t) const
    {
        if (t == nullptr)
            return;
        traverse(t->left);
        std::cout << t->data << ' ';
        traverse(t->right);
    }

} // namespace cs221

#endif