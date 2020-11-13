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

        Pair(Key k, Value v = Value{ })
            : key{ k }, value{ v } { }
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