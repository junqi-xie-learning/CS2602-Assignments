#include "../../include/tree.h"
#include "../../include/list.h"
#include <cstring>
using namespace std;
using namespace cs221;


template <class T>
class CompleteBinaryTree : public BinaryTree<T>
{
public:
    void build_tree(T elem[], int length);
    bool is_complete() const;
};

template <class T>
void CompleteBinaryTree<T>::build_tree(T elem[], int length)
{
    SeqList<typename BinaryTree<T>::Node *> nodes{ length };
    nodes.append(new typename BinaryTree<T>::Node{ });
    this->root = nodes.visit(0);

    for (int i = 1; i < length; ++i)
    {
        nodes.append(new typename BinaryTree<T>::Node{ });
        int p = elem[i];
        if (!nodes.visit(p)->left)
            nodes.visit(p)->left = nodes.visit(i);
        else
            nodes.visit(p)->right = nodes.visit(i);
    }
}

template <class T>
bool CompleteBinaryTree<T>::is_complete() const
{
    if (!this->root)
        return true;
    
    LinkQueue<typename BinaryTree<T>::Node *> q;

    // Label
    int index = 1;
    q.enqueue(this->root);
    while (!q.is_empty())
    {
        typename BinaryTree<T>::Node *tmp = q.dequeue();
        tmp->data = index;
        ++index;
        if (tmp->left)
            q.enqueue(tmp->left);
        if (tmp->right)
            q.enqueue(tmp->right);
    }

    // Check
    q.enqueue(this->root);
    while (!q.is_empty())
    {
        typename BinaryTree<T>::Node *tmp = q.dequeue();
        if (tmp->left)
        {
            if (tmp->left->data != 2 * tmp->data)
                return false;
            q.enqueue(tmp->left);
        }
        if (tmp->right)
        {
            if (tmp->right->data != 2 * tmp->data + 1)
                return false;
            q.enqueue(tmp->right);
        }
    }
    return true;
}


int main()
{
    int length = 0;
    cin >> length;

    int elem[length] = { };
    for (int i = 1; i < length; ++i)
        cin >> elem[i];
    
    CompleteBinaryTree<int> tree;
    tree.build_tree(elem, length);
    cout << (tree.is_complete() ? "true" : "false") << endl;
}