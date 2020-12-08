#include "../../include/disjoint_set.h"
using namespace std;
using namespace cs221;

class Liquids : public DisjointSet
{
public:
    Liquids(int s)
        : DisjointSet{ s } { }
    void insert(int a, int b) { join(find(a), find(b)); }
    int count() const;
};

int Liquids::count() const
{
    int count = 0;
    for (int i = 1; i < size; ++i)
        if (parent[i] > 0)
            ++count;
    return count;
}

int pow2(int power, char num[])
{
    int length = 1;
    num[0] = '1';
    for (int i = 0; i < power; ++i)
    {
        int r = 0;
        for (int j = 0; j < length; ++j)
        {
            int tmp = (num[j] - '0') * 2 + r;
            num[j] = tmp % 10 + '0';
            if (tmp >= 10)
                r = tmp / 10;
            else
                r = 0;
        }
        if (r != 0)
        {
            num[length] = r + '0';
            ++length;
        }
    }
    return length;
}

int main()
{
    int n = 0, m = 0;
    cin >> n >> m;

    Liquids liquids{ n + 1 };
    int pow = 0;
    for (int i = 0; i < m; ++i)
    {
        int a = 0, b = 0;
        cin >> a >> b;
        liquids.insert(a, b);
    }

    char num[300];
    int length = pow2(liquids.count(), num);
    for (int i = length - 1; i >= 0; --i)
        cout << num[i];
    return 0;
}