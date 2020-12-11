#include "../../include/binary_search_tree.h"
using namespace std;
using namespace cs221;


template <class T>
class BST : public BinarySearchTree<T>
{
public:
    T *smallest() const;
    void preorder() const;
};

template <class T>
T *BST<T>::smallest() const
{
    if (!this->root)
        return nullptr;

    typename BinaryTree<T>::Node *t = this->root;
    while (t->left)
        t = t->left;
    return &(t->data);
}

template <class T>
void BST<T>::preorder() const
{ 
    if (!this->root)
        cout << "Empty";
    
    this->preorder(this->root); 
    cout << endl;
}


int main()
{
    int Q = 0;
    cin >> Q;

    BST<int> bst;
    for (int i = 0; i < Q; ++i)
    {
        int op = 0, x = 0;
        cin >> op;
        switch (op)
        {
        case 0:
            cin >> x;
            bst.insert(x);
            break;
        
        case 1:
        {
            cin >> x;
            int *smallest = bst.smallest();
            while (smallest && *smallest <= x)
            {
                bst.remove(*smallest);
                smallest = bst.smallest();
            }
            break;
        }
        case 2:
            bst.preorder();
            break;
        }
    }
    return 0;
}