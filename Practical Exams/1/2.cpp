#include "../../include/stack.h"
using namespace std;
using namespace cs221;

int main()
{
    char str[1000];
    cin >> str;

    SeqStack<SeqStack<char> *> stacks;
    stacks.push(new SeqStack<char>);

    for (const char *p = str; *p; ++p)
    {
        if ('a' <= *p && *p <= 'z')
            stacks.top()->push(*p);
        else if (*p == '(')
            stacks.push(new SeqStack<char>);
        else if (*p == ')')
        {
            SeqStack<char> *s = stacks.pop();
            while (!s->is_empty())
                stacks.top()->push(s->pop());
            delete s;
        }
    }

    SeqStack<char> output;
    SeqStack<char> *s = stacks.pop();
    while (!s->is_empty())
        output.push(s->pop());
    delete s;
    while (!output.is_empty())
        cout << output.pop();
    return 0;
}