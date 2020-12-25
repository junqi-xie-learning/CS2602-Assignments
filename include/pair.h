#ifndef PAIR
#define PAIR

// pair.h:
//
// Class: Pair
// Parameter: Key (Comparable), Value

namespace cs221
{
    template <class Key, class Value>
    struct Pair
    {
        Key key;
        Value value;

        Pair(Key k = Key{ }, Value v = Value{ })
            : key{ k }, value{ v } { }
        operator Key() const { return key; }
    };

    template <class Key, class Value>
    bool operator==(const Pair<Key, Value> &p1, const Pair<Key, Value> &p2)
    {
        return p1.key == p2.key;
    }

    template <class Key, class Value>
    bool operator!=(const Pair<Key, Value> &p1, const Pair<Key, Value> &p2)
    {
        return p1.key != p2.key;
    }

    template <class Key, class Value>
    bool operator<(const Pair<Key, Value> &p1, const Pair<Key, Value> &p2)
    {
        return p1.key < p2.key;
    }

    template <class Key, class Value>
    bool operator<=(const Pair<Key, Value> &p1, const Pair<Key, Value> &p2)
    {
        return p1.key <= p2.key;
    }

    template <class Key, class Value>
    bool operator>(const Pair<Key, Value> &p1, const Pair<Key, Value> &p2)
    {
        return p1.key > p2.key;
    }

    template <class Key, class Value>
    bool operator>=(const Pair<Key, Value> &p1, const Pair<Key, Value> &p2)
    {
        return p1.key >= p2.key;
    }

} // namespace cs221

#endif