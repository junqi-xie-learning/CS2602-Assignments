#include "../../include/list.h"
using namespace std;
using namespace cs221;

int binary_search(const SeqList<int> &array, int x)
{
    if (x > array.visit(array.length() - 1))
        return -1;
        
    int low = 0, high = array.length() - 1;
    while (low < high)
    {
        int mid = (low + high) / 2;
        if (array.visit(mid) < x)
            low = mid + 1;
        else
            high = mid;
    }
    return array.visit(low);
}

int main()
{
    int n = 0, m = 0;
    cin >> n >> m;

    SeqList<int> array{ n };
    for (int i = 0; i < n; ++i)
    {
        int a = 0;
        cin >> a;
        array.append(a);
    }
    
    for (int i = 0; i < m; ++i)
    {
        int b = 0;
        cin >> b;
        cout << binary_search(array, b) << endl;
    }
}