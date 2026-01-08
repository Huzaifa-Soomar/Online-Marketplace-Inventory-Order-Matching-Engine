#ifndef CO_PURCHASE_GRAPH_2025_H
#define CO_PURCHASE_GRAPH_2025_H

#include <vector>
#include <unordered_map>
#include <algorithm>
using std::vector;
using std::unordered_map;

class CoPurchaseGraph {
private:
    unordered_map<int, vector<int>> adjList;
    unordered_map<int, unordered_map<int, int>> weight;

    bool exists(int u, int v) {
        for (int x : adjList[u])
            if (x == v) return true;
        return false;
    }

public:
    void addEdge(int p1, int p2) {
        if (p1 == p2) return;

        if (!exists(p1, p2)) adjList[p1].push_back(p2);
        if (!exists(p2, p1)) adjList[p2].push_back(p1);

        weight[p1][p2]++;
        weight[p2][p1]++;
    }

    vector<int> getTopK(int productId, int k) {
        vector<int> neighbors = adjList[productId];

        std::sort(neighbors.begin(), neighbors.end(),
            [&](int a, int b) {
                return weight[productId][a] > weight[productId][b];
            });

        if ((int)neighbors.size() > k)
            neighbors.resize(k);

        return neighbors;
    }
};

#endif
