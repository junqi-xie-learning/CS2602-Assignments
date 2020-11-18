#include <iostream>
using namespace std;

template <class T>
class HuffmanTree
{
private:
    struct Node
    {
        T data;
        long long int weight;
        int left, right;
        int parent;
    };

    Node *elem;
    int length;

public:
    HuffmanTree(const T data[], const long long int weight[], int size);
    ~HuffmanTree() { delete[] elem; }
    int get_length(const T &x);
};

template <class T>
HuffmanTree<T>::HuffmanTree(const T data[], const long long int weight[], int size)
    : length{ 2 * size }, elem{ new Node[2 * size] }
{
    for (int i = size; i < length; ++i)
        elem[i] = Node{ data[i - size], weight[i - size] };

    long long int max = 1;
    for (int i = 0; i < size; ++i)
        max += weight[i];
    
    long long int min1 = 0, min2 = 0;
    int index1 = 0, index2 = 0;
    for (int i = size - 1; i > 0; --i)
    {
        min1 = max, min2 = max;
        for (int j = i + 1; j < length; ++j)
            if (elem[j].parent == 0)
                if (elem[j].weight < min1)
                {
                    min2 = min1;
                    min1 = elem[j].weight;
                    index2 = index1;
                    index1 = j;
                }
                else if (elem[j].weight < min2)
                {
                    min2 = elem[j].weight;
                    index2 = j;
                }
        
        elem[i] = Node{ T{ }, min1 + min2, index1, index2 };
        elem[index1].parent = i, elem[index2].parent = i;
    }
}

template <class T>
int HuffmanTree<T>::get_length(const T &x)
{
    int index = length / 2;
    while (elem[index].data != x)
        ++index;

    int code_length = 0;
    while (index != 1)
    {
        index = elem[index].parent;
        ++code_length;
    }
    return code_length;
}

int main()
{
    int N = 0;
    cin >> N;

    int *data = new int[N];
    long long int *weight = new long long int[N];
    for (int i = 0; i < N; ++i)
    {
        data[i] = i;
        cin >> weight[i];
    }

    HuffmanTree<int> tree{ data, weight, N };
    long long int total = 0;
    for (int i = 0; i < N; ++i)
        total += weight[i] * tree.get_length(i);
    cout << total;
    return 0;
}