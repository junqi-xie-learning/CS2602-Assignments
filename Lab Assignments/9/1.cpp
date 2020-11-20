#include "../../include/list.h"
#include "../../include/hash_table.h"
#include "../../include/pair.h"
using namespace std;
using namespace cs221;

int main()
{
    int n = 0;
    cin >> n;

    SeqList<int> *sets[4];
    for (int i = 0; i < 4; ++i)
        sets[i] = new SeqList<int>{ n };

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < 4; ++j)
        {
            int temp;
            cin >> temp;
            sets[j]->append(temp);
        }
    
    HashTable<Pair<int, int>> table{ 49999 };
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
        {
            int partial_sum = sets[0]->visit(i) + sets[1]->visit(j);
            if (!table.find(partial_sum))
                table.insert({ partial_sum, 1 });
            else
                ++table.find(partial_sum)->value;
        }
    
    int counter = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
        {
            int partial_sum = -(sets[2]->visit(i) + sets[3]->visit(j));
            if (table.find(partial_sum))
                counter += table.find(partial_sum)->value;
        }
    cout << counter;
    return 0;
}