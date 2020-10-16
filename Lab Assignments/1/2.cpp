#include "../../include/list.h"
using namespace std;
using namespace cs221;

int main()
{
    int n = 0, m = 0;
    cin >> n >> m;

    LinkList<int> list;
    for (int i = 0; i < n; ++i)
    {
        int number = 0;
        cin >> number;
        list.append(number);
    }

    for (int i = 0; i < m; ++i)
    {
        int token = 0;
        cin >> token;

        int x = 0, y = 0;
        switch (token)
        {
        case 1:
            cin >> x >> y;
            list.insert(x, y);
            break;
        case 2:
            cin >> x;
            list.remove(x - 1);
            break;
        }
    }

    list.traverse();
    return 0;
}