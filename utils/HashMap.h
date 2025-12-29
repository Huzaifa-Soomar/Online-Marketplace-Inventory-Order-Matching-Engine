#ifndef HASHMAP_2025_H
#define HASHMAP_2025_H

#include <vector>
#include <functional>  // Needed for hash function.
using std::vector;

template<typename K, typename V>
class HashMap {
private:
    struct Node {
        K key;
        V value;
        Node* next;  // Needed for collissions -> when same hash value is returned for different indexes.
        Node(K k, V v) : key(k), value(v), next(nullptr) {}
    };

    vector<Node*> table;  // Hash-table -> containing head pointer for each bucket's linked list.
    int capacity;  // Total number of buckets.

    int hashFunction(const K& key) const {
        return (int)(std::hash<K>{}(key) % (size_t)capacity);
    }

public:
    HashMap(int cap = 101) {
        capacity = (cap <= 0) ? 101 : cap;  // Ensures capacity is valid, i.e. > 0.
        table.resize(capacity, nullptr);
    }

    ~HashMap() {
        for (int i = 0; i < capacity; i++) {
            Node* cur = table[i];  // Starts at head of first bucket.
            while (cur != nullptr) {  // Deletes each bucket/linked list.
                Node* nxt = cur->next;
                delete cur;
                cur = nxt;
            }
            table[i] = nullptr;
        }
    }

    void insert(const K& key, const V& value) {
        int idx = hashFunction(key);  // Get bucket index.

        Node* cur = table[idx];
        while (cur != nullptr) {  // Traverse entire linked list.
            if (cur->key == key) {  // If key already exists.
                cur->value = value;  // Update value.
                return;
            }
            cur = cur->next;  // Traverse.
        }

        Node* n = new Node(key, value);  // Else, create new node.
        n->next = table[idx];  // Insert at head.
        table[idx] = n;  // Update head.
    }

    bool remove(const K& key) {
        int idx = hashFunction(key);

        Node* cur = table[idx];
        Node* prev = nullptr;

        while (cur != nullptr) {
            if (cur->key == key) {
                if (prev == nullptr) table[idx] = cur->next;  // If key is at head of list.
                else prev->next = cur->next;  // Relink list.

                delete cur;
                return true;
            }
            prev = cur;
            cur = cur->next;
        }
        return false;  // Key not found.
    }

    V* search(const K& key) {
        int idx = hashFunction(key);

        Node* cur = table[idx];
        while (cur != nullptr) {
            if (cur->key == key) return &cur->value;
            cur = cur->next;
        }
        return nullptr;  // Not found.
    }
};

#endif