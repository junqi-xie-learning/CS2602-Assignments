#include "../../include/binary_tree.h"
#include <cstring>
using namespace std;
using namespace cs221;


template <class T>
class PreMidBinaryTree : public BinaryTree<T>
{
protected:
    typename BinaryTree<T>::Node *build_tree(T pre[], int pl, int pr, T mid[], int ml, int mr);

public:
    void build_tree(T pre[], int plen, T mid[], int mlen) { build_tree(pre, 0, plen - 1, mid, 0, mlen - 1); }
    void level_order(int count) const;
};

template <class T>
typename BinaryTree<T>::Node *PreMidBinaryTree<T>::build_tree(T pre[], int pl, int pr, T mid[], int ml, int mr)
{
    if (pl > pr)
        return nullptr;
    
    typename BinaryTree<T>::Node *p = new typename BinaryTree<T>::Node{ pre[pl] };
    if (!this->root)
        this->root = p;
    int pos = ml;
    while (mid[pos] != pre[pl])
        ++pos;
    int num = pos - ml;

    p->left = build_tree(pre, pl + 1, pl + num, mid, ml, pos - 1);
    p->right = build_tree(pre, pl + num + 1, pr, mid, pos + 1, mr);
    return p;
}

template <class T>
void PreMidBinaryTree<T>::level_order(int count) const
{
    LinkQueue<typename BinaryTree<T>::Node *> q;
    q.enqueue(this->root);

    while (!q.is_empty())
    {
        typename BinaryTree<T>::Node *tmp = q.dequeue();
        if (tmp)
        {
            cout << tmp->data << ' ';
            --count;
            q.enqueue(tmp->left);
            q.enqueue(tmp->right);
        }
        else
        {
            cout << "NULL ";
            q.enqueue(nullptr);
            q.enqueue(nullptr);
        }
        if (count == 0)
            return;
    }
}


int main()
{
    char pre[27], mid[27];
    cin >> pre >> mid;

    PreMidBinaryTree<char> tree;
    tree.build_tree(pre, strlen(pre), mid, strlen(mid));
    tree.level_order(strlen(pre));
    return 0;
}