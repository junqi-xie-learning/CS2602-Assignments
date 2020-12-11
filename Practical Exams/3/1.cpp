#include "../../include/sorting.h"
using namespace std;
using namespace cs221;


struct Student
{
    int number, score;
};

bool operator<(const Student &s1, const Student &s2)
{
    if (s1.score == s2.score)
        return s1.number > s2.number;
    return s1.score < s2.score;
}

bool operator>=(const Student &s1, const Student &s2)
{
    return !(s1 < s2);
}

bool operator<=(const Student &s1, const Student &s2)
{
    if (s1.score == s2.score)
        return s1.number >= s2.number;
    return s1.score < s2.score;
}

istream &operator>>(istream &is, Student &s)
{
    return is >> s.number >> s.score;
}

ostream &operator<<(ostream &os, const Student &s)
{
    return os << s.number << ' ' << s.score;
}


int main()
{
    int n = 0;
    cin >> n;

    Student *s = new Student[n];
    for (int i = 0; i < n; ++i)
        cin >> s[i];
    
    quick_sort(s, n);
    for (int i = n - 1; i >= 0; --i)
        cout << s[i] << endl;
    return 0;
}