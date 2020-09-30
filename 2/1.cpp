#include "../include/stack.h"
using namespace std;
using namespace cs221;

class ParenStack
{
private:
    SeqStack<char> s;

    bool left(char ch) const { return ch == '(' || ch == '[' || ch == '{'; }
    bool right(char ch) const { return ch == ')' || ch == ']' || ch == '}'; }
    bool match(char left, char right) const
        { return left == '(' && right == ')' || left == '[' && right == ']' || left == '{' && right == '}'; }

public:
    ParenStack(int n)
        : s{ n } { }

    bool is_empty() const { return s.is_empty(); }
    bool is_matched() const;
    char top() const { return s.top(); }
    char pop() { return s.pop(); }
    void push(char x) { s.push(x); }
};

bool ParenStack::is_matched() const
{
    SeqStack<char> backup = s;
    LinkStack<char> tmp;

    bool result = true;
    while (!backup.is_empty())
    {
        char ch = backup.pop();
        if (right(ch))
            tmp.push(ch);
        else if (!tmp.is_empty() && match(ch, tmp.top()))
            tmp.pop();
        else
        {
            result = false;
            break;
        }
    }
    return result && tmp.is_empty();
}


int main()
{    
    int n = 0;
    cin >> n;

    ParenStack ps{ n };

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
            if (!ps.is_empty())
                ps.pop();
            break;
        case 3:
            if (!ps.is_empty())
                cout << ps.top() << endl;
            break;
        case 4:
            cout << (ps.is_matched() ? "YES" : "NO") << endl;
            break;
        }
    }
}