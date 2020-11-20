#include "../../include/stack.h"
#include "../../include/binary_search_tree.h"
using namespace std;
using namespace cs221;


template <class T>
class BST : public BinarySearchTree<T>
{
private:
    SeqStack<char> *find(const T &x, typename BinaryTree<T>::Node *t) const;

public:
    SeqStack<char> *find(const T &x) const;
};

template <class T>
SeqStack<char> *BST<T>::find(const T &x, typename BinaryTree<T>::Node *t) const
{
    if (t == nullptr)
        return nullptr;

    if (t->data == x)
        return new SeqStack<char>;
    else if (x < t->data)
    {
        SeqStack<char> *result = find(x, t->left);
        if (result)
            result->push('l');
        return result;
    }
    else
    {
        SeqStack<char> *result = find(x, t->right);
        if (result)
            result->push('r');
        return result;
    }
}

template <class T>
SeqStack<char> *BST<T>::find(const T &x) const
{
    SeqStack<char> *result = find(x, this->root);
    if (result)
        result->push('*');
    return result;
}


int main()
{
    int Q = 0;
    cin >> Q;

    BST<int> bst;
    for (int i = 0; i < Q; ++i)
    {
        char op = 0;
        int x = 0;
        cin >> op >> x;
        switch (op)
        {
        case '+':
            bst.insert(x);
            break;
        
        case '*':
        {
            SeqStack<char> *result = bst.find(x);
            if (result)
                while (!result->is_empty())
                    cout << result->pop();
            else
                cout << "Nothing.";
            cout << endl;
            delete result;
            break;
        }
        case '-':
            bst.remove(x);
            break;
        }
    }
    return 0;
}