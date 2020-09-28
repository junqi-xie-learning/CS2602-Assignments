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
    seqStack(int initSize = 10)
        : elem{ new elemType[initSize] }, maxSize{ initSize }, top_p{ -1 } { }
    seqStack(const seqStack &s);
    ~seqStack() { delete[] elem; }

    bool isEmpty() const { return top_p == -1; }
    bool size() const { return top_p + 1; }
    elemType top() const;
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
seqStack<elemType>::seqStack(const seqStack &s)
    : elem{ new elemType[s.maxSize] }, maxSize{ s.maxSize }, top_p{ s.top_p }
{
    for (int i = 0; i <= top_p; ++i)
        elem[i] = s.elem[i];
}

template <class elemType>
elemType seqStack<elemType>::top() const
{
    if (top_p == -1)
        throw outOfBound{ };
    return elem[top_p];
}

template <class elemType>
elemType seqStack<elemType>::pop()
{
    if (top_p == -1)
        throw outOfBound{ };
    elemType result = elem[top_p];
    --top_p;
    return result;
}

template <class elemType>
void seqStack<elemType>::push(const elemType& x)
{
    if (top_p == maxSize - 1)
        doubleSpace();
    ++top_p;
    elem[top_p] = x;
}


class parenStack
{
private:
    seqStack<char> s;

    bool is_left(char ch) const { return ch == '(' || ch == '[' || ch == '{'; }
    bool is_right(char ch) const { return ch == ')' || ch == ']' || ch == '}'; }
    bool is_match(char left, char right) const
        { return left == '(' && right == ')' || left == '[' && right == ']' || left == '{' && right == '}'; }

public:
    parenStack(int n)
        : s{ n } { }

    bool isEmpty() const { return s.isEmpty(); }
    bool isMatched() const;
    char top() const { return s.top(); }
    char pop() { return s.pop(); }
    void push(char x) { s.push(x); }
};

bool parenStack::isMatched() const
{
    seqStack<char> backup = s;
    seqStack<char> tmp{ s.size() + 1 };

    bool result = true;
    while (!backup.isEmpty())
    {
        char ch = backup.pop();
        if (is_right(ch))
            tmp.push(ch);
        else if (!tmp.isEmpty() && is_match(ch, tmp.top()))
            tmp.pop();
        else
        {
            result = false;
            break;
        }
    }
    return result && tmp.isEmpty();
}


int main()
{    
    int n = 0;
    cin >> n;

    parenStack ps{ n };

    for (int i = 0; i < n; ++i)
    {
        int op = 0;
        cin >> op;
 
        char ch = 0;
        switch (op)
        {
        case 1:
            cin >> ch;
            ps.push(ch);
            break;
        case 2:
            if (!ps.isEmpty())
                ps.pop();
            break;
        case 3:
            if (!ps.isEmpty())
                cout << ps.top() << endl;
            break;
        case 4:
            cout << (ps.isMatched() ? "YES" : "NO") << endl;
            break;
        }
    }
}