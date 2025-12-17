#ifndef HASHMAP_2025_H
#define HASHMAP_2025_H

#include <vector>
#include <functional>
using std::vector;

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

    int hashFunction(const K& key) const {
        return (int)(std::hash<K>{}(key) % (size_t)capacity);
    }

public:
    HashMap(int cap = 101) {
        capacity = (cap <= 0) ? 101 : cap;
        table.resize(capacity, nullptr);
    }

    ~HashMap() {
        for (int i = 0; i < capacity; i++) {
            Node* cur = table[i];
            while (cur != nullptr) {
                Node* nxt = cur->next;
                delete cur;
                cur = nxt;
            }
            table[i] = nullptr;
        }
    }

    void insert(const K& key, const V& value) {
        int idx = hashFunction(key);

        Node* cur = table[idx];
        while (cur != nullptr) {
            if (cur->key == key) {
                cur->value = value;
                return;
            }
            cur = cur->next;
        }

        Node* n = new Node(key, value);
        n->next = table[idx];
        table[idx] = n;
    }

    bool remove(const K& key) {
        int idx = hashFunction(key);

        Node* cur = table[idx];
        Node* prev = nullptr;

        while (cur != nullptr) {
            if (cur->key == key) {
                if (prev == nullptr) table[idx] = cur->next;
                else prev->next = cur->next;

                delete cur;
                return true;
            }
            prev = cur;
            cur = cur->next;
        }
        return false;
    }

    V* search(const K& key) {
        int idx = hashFunction(key);

        Node* cur = table[idx];
        while (cur != nullptr) {
            if (cur->key == key) return &cur->value;
            cur = cur->next;
        }
        return nullptr;
    }
};

#endif