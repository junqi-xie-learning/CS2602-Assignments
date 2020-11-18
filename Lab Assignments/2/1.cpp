#include "../../include/list.h"
using namespace std;
using namespace cs221;

class Joseph
{
private:
    SeqList<int> cycle;
    int size;
    int gap;

public:
    Joseph(int n, int m)
        :cycle{ n }, size{ n }, gap{ m } { }
    
    void simulate();
};

void Joseph::simulate()
{
    for (int i = 0; i < size; ++i)
        cycle.append(i + 1);
    
    int current = 1;
    while (cycle.length() != 0)
    {
        current = (current + gap - 1) % cycle.length();
        cout << cycle.remove(current) << ' ';
    }
}


int main()
{
    int n = 0, m = 0;
    cin >> n >> m;

    Joseph obj(n, m);
    obj.simulate();

    return 0;
}