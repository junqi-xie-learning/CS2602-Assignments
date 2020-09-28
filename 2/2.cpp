#include <iostream>
using namespace std;

class outOfBound { };

template <class elemType>
class seqStack
{
private:
    elemType* elem;
    int top_p;
    int maxSize;

    void doubleSpace();

public:
    seqStack(int initSize = 10);
    ~seqStack() { delete[] elem; }

    elemType pop();
    void push(const elemType& x);
};

template <class elemType>
void seqStack<elemType>::doubleSpace()
{
    elemType* tmp = elem;
    elem = new elemType[2 * maxSize];
    for (int i = 0; i < maxSize; ++i)
        elem[i] = tmp[i];
    maxSize *= 2;
    delete[] tmp;
}

template <class elemType>
seqStack<elemType>::seqStack(int initSize)
{
    elem = new elemType[initSize];
    maxSize = initSize;
    top_p = -1;
}

template <class elemType>
elemType seqStack<elemType>::pop()
{
    if (top_p == -1)
        throw outOfBound{ };
    return elem[top_p--];
}

template <class elemType>
void seqStack<elemType>::push(const elemType& x)
{
    if (top_p == maxSize - 1)
        doubleSpace();
    ++top_p;
    elem[top_p] = x;
}


int main()
{
    int N = 0;
    cin >> N;
    seqStack<int> s{ N };

    for (int i = 0; i < N; ++i)
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
            try 
            {
                if (num == s.pop())
                    cout << "YES" << endl;
                else
                    cout << "NO" << endl;
            }
            catch (outOfBound)
            {
                cout << "ERROR" << endl;
            }
            break;
        }
    }
}