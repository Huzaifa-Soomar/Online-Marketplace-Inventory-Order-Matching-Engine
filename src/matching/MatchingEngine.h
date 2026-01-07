#ifndef MATCHING_ENGINE_2025_H
#define MATCHING_ENGINE_2025_H

#include "../catalog/Catalog.h"
#include "../orderbook/OrderBook.h"

class MatchingEngine {
private:
    Catalog* catalog;
    OrderBook* orderbook;
    HashMap<int, Order>* orderIndex;

public:
    MatchingEngine(Catalog* c, OrderBook* ob, HashMap<int, Order>* idx);

    void processOrders();
    void matchSingleProduct(int productId);
    void executeMatch(Order buy, Order sell);
};

#endif
