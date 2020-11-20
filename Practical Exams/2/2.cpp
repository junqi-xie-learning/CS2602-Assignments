#include "../../include/binary_search_tree.h"
using namespace std;
using namespace cs221;


template <class T>
class LCABinarySearchTree : public BinarySearchTree<T>
{
private:
    T *LCA(const T &u, const T &v, typename BinaryTree<T>::Node *t) const;
public:
    T *LCA(const T &u, const T &v) const { return LCA(u, v, this->root); }
};

template <class T>
T *LCABinarySearchTree<T>::LCA(const T &u, const T &v, typename BinaryTree<T>::Node *t) const
{
    if (u < t->data && v < t->data)
        return LCA(u, v, t->left);
    else if (t->data < u && t->data < v)
        return LCA(u, v, t->right);
    else
        return &(t->data);
}


int main()
{
    int n = 0;
    cin >> n;

    LCABinarySearchTree<int> bst;
    for (int i = 0; i < n; ++i)
    {
        int tmp = 0;
        cin >> tmp;
        bst.insert(tmp);
    }

    int u = 0, v = 0;
    cin >> u >> v;
    cout << *bst.LCA(u, v);
    return 0;
}