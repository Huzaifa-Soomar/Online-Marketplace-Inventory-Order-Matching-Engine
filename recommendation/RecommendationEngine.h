#ifndef RECOMMEND_ENGINE_2025_H
#define RECOMMEND_ENGINE_2025_H

#include "CoPurchaseGraph.h"

class RecommendationEngine {
private:
    CoPurchaseGraph graph;

public:
    void recordPurchasePair(int p1, int p2);
    vector<int> getRecommendations(int productId, int k);
};

#endif
