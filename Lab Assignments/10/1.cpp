#include "../../include/sorting.h"
using namespace std;
using namespace cs221;

int main()
{
    int n = 0;
    cin >> n;

    int list[n] = { };
    for (int i = 0; i < n; ++i)
        cin >> list[i];

    quick_sort(list, n);
    for (int i = 0; i < n; ++i)
        cout << list[i] << ' ';
    return 0;
}