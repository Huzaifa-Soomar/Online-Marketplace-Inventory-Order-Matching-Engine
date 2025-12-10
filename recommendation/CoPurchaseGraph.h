#ifndef CO_PURCHASE_GRAPH_2025_H
#define CO_PURCHASE_GRAPH_2025_H

#include <vector>
#include <unordered_map>
using std::vector;
using std::unordered_map;

class CoPurchaseGraph {
private:
    unordered_map<int, vector<int>> adjList;
    unordered_map<int, unordered_map<int, int>> weight;

public:
    void addEdge(int p1, int p2);
    vector<int> getTopK(int productId, int k);
};

#endif
