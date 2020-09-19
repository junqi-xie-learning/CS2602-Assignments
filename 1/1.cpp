#include <iostream>
using namespace std;

template <class elemType>
class seqList
{
private:
    elemType *data;
    int currentLength;
    int maxSize;

public:
    seqList(int initSize);
    ~seqList() { delete[] data; }

    int length() const { return currentLength; }
    void insert(int i, const elemType &x);
    elemType remove(int i);
};

template <class elemType>
seqList<elemType>::seqList(int initSize)
{
    data = new elemType[initSize];
    maxSize = initSize;
    currentLength = 0;
}

template <class elemType>
void seqList<elemType>::insert(int i, const elemType &x)
{
    for (int j = currentLength; j > i; --j)
        data[j] = data[j - 1];
    data[i] = x;
    ++currentLength;
}

template <class elemType>
elemType seqList<elemType>::remove(int i)
{
    elemType result = data[i];
    for (int j = i; j < currentLength - 1; ++j)
        data[j] = data[j + 1];
    --currentLength;
    return result;
}


class Joseph
{
private:
    seqList<int> cycle;
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
        cycle.insert(i, i + 1);
    
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