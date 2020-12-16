#include "../../include/queue.h"
using namespace std;
using namespace cs221;

int main()
{
    int n = 0, m = 0;
    cin >> n >> m;

    int **map = new int*[n]{ };
    for (int i = 0; i < n; ++i)
        map[i] = new int[m]{ };
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> map[i][j];

    int countries = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
        {
            if (map[i][j])
                continue;
            
            ++countries;
            SeqQueue<int> qx, qy;
            qx.enqueue(i), qy.enqueue(j);

            while (!qx.is_empty())
            {
                int x = qx.dequeue(), y = qy.dequeue();
                map[x][y] = 1;
                if (x - 1 >= 0 && !map[x - 1][y])
                    qx.enqueue(x - 1), qy.enqueue(y);
                if (x + 1 < n && !map[x + 1][y])
                    qx.enqueue(x + 1), qy.enqueue(y);
                if (y - 1 >= 0 && !map[x][y - 1])
                    qx.enqueue(x), qy.enqueue(y - 1);
                if (y + 1 < m && !map[x][y + 1])
                    qx.enqueue(x), qy.enqueue(y + 1);
            }
        }
    
    cout << countries << endl;
    for (int i = 0; i < n; ++i)
        delete[] map[i];
    delete[] map;
    return 0;
}