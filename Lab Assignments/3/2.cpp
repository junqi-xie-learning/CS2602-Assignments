#include "../../include/stack.h"
using namespace std;
using namespace cs221;

int main()
{
    int n = 0;
    cin >> n;
    SeqStack<int> s{ n };

    for (int i = 0; i < n; ++i)
    {
        int op = 0, num = 0;
        cin >> op >> num;
        switch (op)
        {
        case 1:
            s.push(num);
            cout << "OK" << endl;
            break;
        case 2:
            if (s.is_empty())
                cout << "ERROR" << endl;
            else if (num == s.pop())
                cout << "YES" << endl;
            else
                cout << "NO" << endl;
            break;
        }
    }
    return 0;
}