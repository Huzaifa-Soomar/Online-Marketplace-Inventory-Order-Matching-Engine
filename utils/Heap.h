#ifndef HEAP_2025_H
#define HEAP_2025_H

#include <vector>
using std::vector;

template <typename T>
class Heap {
private:
    vector<T> arr;
    bool isMinHeap;

    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    Heap(bool minheap = false);
    void push(const T& item);
    T top() const;
    T pop();
    bool empty() const;
};

#endif
