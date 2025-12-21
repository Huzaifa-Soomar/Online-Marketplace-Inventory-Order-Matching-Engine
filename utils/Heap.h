#ifndef HEAP_2025_H
#define HEAP_2025_H

#include <vector>
using std::vector;

// This makes heap reusable:Heap<Order>  Heap<int>  Heap<anything>
template <typename T>
class Heap {
private:
    vector<T> arr;
    bool isMinHeap;

    bool compare(const T& a, const T& b) const {
        return isMinHeap ? a < b : b < a;
    }

    void heapifyUp(int i) {
        while (i > 0) {
            int p = (i - 1) / 2;
            if (compare(arr[i], arr[p])) {
                std::swap(arr[i], arr[p]);
                i = p;
            } else break;
        }
    }

    void heapifyDown(int i) {
        int n = arr.size();
        while (true) {
            int l = 2 * i + 1;
            int r = 2 * i + 2;
            int best = i;

            if (l < n && compare(arr[l], arr[best])) best = l;
            if (r < n && compare(arr[r], arr[best])) best = r;

            if (best != i) {
                std::swap(arr[i], arr[best]);
                i = best;
            } else break;
        }
    }

public:
    Heap(bool minheap = false) : isMinHeap(minheap) {}

    void push(const T& item) {
        arr.push_back(item);
        heapifyUp(arr.size() - 1);
    }

    T top() const { return arr.front(); }

    T pop() {
        T root = arr.front();
        arr[0] = arr.back();
        arr.pop_back();
        heapifyDown(0);
        return root;
    }

    bool empty() const { return arr.empty(); }
};

#endif
