#ifndef HASHMAP_2025_H
#define HASHMAP_2025_H

#include <vector>

template<typename K, typename V>
class HashMap {
private:
    struct Node {
        K key;
        V value;
        Node* next;
        Node(K k, V v) : key(k), value(v), next(nullptr) {}
    };

    vector<Node*> table;
    int capacity;

    int hashFunction(const K& key) const;

public:
    HashMap(int cap = 101);
    void insert(const K& key, const V& value);
    bool remove(const K& key);
    V* search(const K& key);
};

#endif
