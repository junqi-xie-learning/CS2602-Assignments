#include "../../include/list.h"
using namespace std;
using namespace cs221;


template <class T>
class StaticSet : public LinkList<T>
{
private:
    int comparison;

public:
    int get_comparison() const { return comparison; }
    void find(const T &x);
};

template <class T>
void StaticSet<T>::find(const T &x)
{
    for (typename LinkList<T>::Node *p = this->head; p->next; p = p->next)
    {
        ++comparison;
        if (p->next->data == x)
        {
            typename LinkList<T>::Node *delp = p->next;
            p->next = delp->next;
            delp->next = this->head->next;
            this->head->next = delp;
            return;
        }
    }
}


int main()
{
    int n = 0;
    cin >> n;

    StaticSet<int> set;
    for (int i = 0; i < n; ++i)
    {
        int elem = 0;
        cin >> elem;
        set.append(elem);
    }
    
    int m = 0;
    cin >> m;

    for (int i = 0; i < m; ++i)
    {
        int elem = 0;
        cin >> elem;
        set.find(elem);
    }
    cout << set.get_comparison() << endl;
    return 0;
}