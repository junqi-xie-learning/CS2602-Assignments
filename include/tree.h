#ifndef TREE
#define TREE

#include "stack.h"
#include "queue.h"

// tree.h:
//
// Class: BinaryTree, Tree

namespace cs221
{
    template <class T>
    class Tree;

    template <class T>
    class BinaryTree
    {
        friend class Tree<T>;
    protected:
        struct Node
        {
            T data;
            Node *left, *right;
            Node(const T &item, Node *l = nullptr, Node *r = nullptr)
                : data{ item }, left{ l }, right{ r } { }
            Node()
                : left{ nullptr }, right{ nullptr } { }
            ~Node() { }
        };
        Node *root;

        Node *find(Node *t, const T &x) const;
        void clear(Node *&t);

        void preorder(Node *t) const;
        void midorder(Node *t) const;
        void postorder(Node *t) const;

    public:
        BinaryTree()
            : root{ nullptr } { }

        ~BinaryTree() { clear(); }
        void create_tree(const T &flag);
        void clear() { clear(root); }

        bool is_empty() const { return root == nullptr; }

        void preorder() const { preorder(root); }
        void midorder() const { midorder(root); }
        void postorder() const { postorder(root); }

        void level_order() const;
        void preorder_iterative() const;
        void midorder_iterative() const;
        void postorder_iterative() const;
    };

    template <class T>
    typename BinaryTree<T>::Node *BinaryTree<T>::find(BinaryTree<T>::Node *t, const T &x) const
    {
        if (t == nullptr)
            return nullptr;
        if (t->data == x)
            return t;
        
        Node *tmp = find(x, t->left);
        if (tmp)
            return tmp;
        else
            return find(x, t->right);
    }

    template <class T>
    void BinaryTree<T>::create_tree(const T &flag)
    {
        LinkQueue<Node *> q;
        T x;
        std::cin >> x;
        root = new Node{ x };
        q.enqueue(root);

        while (!q.is_empty())
        {
            Node *tmp = q.dequeue();
            T left_data, right_data;
            std::cin >> left_data >> right_data;
            if (left_data != flag)
            {
                tmp->left = new Node{left_data};
                q.enqueue(tmp->left);
            }
            if (right_data != flag)
            {
                tmp->right = new Node{right_data};
                q.enqueue(tmp->right);
            }
        }
    }

    template <class T>
    void BinaryTree<T>::clear(BinaryTree<T>::Node *&t)
    {
        if (t == nullptr)
            return;
        
        clear(t->left);
        clear(t->right);
        delete t;
        t = nullptr;
    }

    template <class T>
    void BinaryTree<T>::preorder(BinaryTree<T>::Node *t) const
    {
        if (t == nullptr)
            return;
        std::cout << t->data << ' ';
        preorder(t->left);
        preorder(t->right);
    }

    template <class T>
    void BinaryTree<T>::midorder(BinaryTree<T>::Node *t) const
    {
        if (t == nullptr)
            return;
        midorder(t->left);
        std::cout << t->data << ' ';
        midorder(t->right);
    }

    template <class T>
    void BinaryTree<T>::postorder(BinaryTree<T>::Node *t) const
    {
        if (t == nullptr)
            return;
        postorder(t->left);
        postorder(t->right);
        std::cout << t->data << ' ';
    }

    template <class T>
    void BinaryTree<T>::level_order() const
    {
        LinkQueue<Node *> q;
        q.enqueue(root);

        while (!q.is_empty())
        {
            Node *tmp = q.dequeue();
            std::cout << tmp->data << ' ';
            if (tmp->left)
                q.enqueue(tmp->left);
            if (tmp->right)
                q.enqueue(tmp->right);
        }
    }

    template <class T>
    void BinaryTree<T>::preorder_iterative() const
    {
        LinkStack<Node *> s;
        s.push(root);

        while (!s.is_empty())
        {
            Node *tmp = s.pop();
            std::cout << tmp->data << ' ';
            if (tmp->right)
                s.push(tmp->right);
            if (tmp->left)
                s.push(tmp->left);
        }
    }

    template <class T>
    void BinaryTree<T>::midorder_iterative() const
    {   
        LinkStack<Node *> s1;
        LinkStack<int> s2;
        s1.push(root);
        s2.push(0);
    
        while (!s1.is_empty())
        {
            Node *tmp = s1.pop();
            switch (s2.pop())
            {
            case 0:
                s1.push(tmp);
                s2.push(1);
                if (tmp->left)
                {
                    s1.push(tmp->left);
                    s2.push(0);
                }
                break;
            case 1:
                std::cout << tmp->data << ' ';
                if (tmp->right)
                {
                    s1.push(tmp->right);
                    s2.push(0);
                }
                break;
            }
        }
    }

    template <class T>
    void BinaryTree<T>::postorder_iterative() const
    {
        LinkStack<Node *> s1;
        LinkStack<int> s2;
        s1.push(root);
        s2.push(0);

        while (!s1.is_empty())
        {
            Node *tmp = s1.pop();
            switch(s2.pop())
            {
            case 0:
                s1.push(tmp);
                s2.push(1);
                if (tmp->left)
                {
                    s1.push(tmp->left);
                    s2.push(0);
                }
                break;
            case 1:
                s1.push(tmp);
                s2.push(2);
                if (tmp->right)
                {
                    s1.push(tmp->right);
                    s2.push(0);
                }
                break;
            case 2:
                std::cout << tmp->data << ' ';
                break;
            }
        }
    }


    template <class T>
    class Tree
    {
    protected:
        BinaryTree<T> rep;
    
    public:
        Tree()
            : rep{ } { }
        
        void create_tree(const T &flag);

        void preorder() const { rep.preorder(); }
        void postorder() const { rep.midorder(); }
    };

    template <class T>
    void Tree<T>::create_tree(const T &flag)
    {
        LinkQueue<typename BinaryTree<T>::Node *> q;
        T x;
        std::cin >> x;
        rep.root = new typename BinaryTree<T>::Node{ x };
        q.enqueue(rep.root);

        while (!q.is_empty())
        {
            typename BinaryTree<T>::Node *tmp = q.dequeue();
            bool first = true;
            while (std::cin >> x && x != flag)
            {
                typename BinaryTree<T>::Node *next_node = new typename BinaryTree<T>::Node{ x };
                if (first)
                {
                    tmp->left = next_node;
                    first = false;
                }
                else
                    tmp->right = next_node;
                q.enqueue(next_node);
                tmp = next_node;
            }
        }
    }

} // namespace cs221

#endif