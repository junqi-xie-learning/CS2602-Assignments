#include "../../include/list.h"
using namespace std;
using namespace cs221;

int binary_search(const SeqList<int> &list, int x)
{
    if (x > list.visit(list.length() - 1))
        return -1;
        
    int low = 0, high = list.length() - 1;
    while (low < high)
    {
        int mid = (low + high) / 2;
        if (list.visit(mid) < x)
            low = mid + 1;
        else
            high = mid;
    }
    return list.visit(low);
}

int main()
{
    int n = 0, m = 0;
    cin >> n >> m;

    SeqList<int> list{ n };
    for (int i = 0; i < n; ++i)
    {
        int a = 0;
        cin >> a;
        list.append(a);
    }
    
    for (int i = 0; i < m; ++i)
    {
        int b = 0;
        cin >> b;
        cout << binary_search(list, b) << endl;
    }
}