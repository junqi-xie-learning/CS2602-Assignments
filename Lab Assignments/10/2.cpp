#include "../../include/avl_tree.h"
using namespace std;
using namespace cs221;

struct Rational
{
    int numerator, denominator;

    Rational(int numer, int denom)
        : numerator{ numer }, denominator{ denom } { }
};

bool operator==(const Rational &r1, const Rational &r2)
{
    return r1.numerator * r2.denominator == r1.denominator * r2.numerator;
}

bool operator!=(const Rational &r1, const Rational &r2)
{
    return !(r1 == r2);
}

bool operator<(const Rational &r1, const Rational &r2)
{
    return r1.numerator * r2.denominator < r1.denominator * r2.numerator;
}

ostream &operator<<(ostream &os, const Rational &r)
{
    return os << r.numerator << '/' << r.denominator;
}


int main()
{
    int N = 0;
    cin >> N;

    AVLTree<Rational> tree;
    for (int i = 1; i <= N; ++i)
        for (int j = 0; j <= i; ++j)
            tree.insert(Rational{ j, i });

    tree.traverse();
    return 0;
}