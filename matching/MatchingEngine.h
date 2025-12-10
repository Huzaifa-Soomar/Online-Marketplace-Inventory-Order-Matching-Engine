#ifndef MATCHING_ENGINE_2025_H
#define MATCHING_ENGINE_2025_H

#include "../catalog/Catalog.h"
#include "../orderbook/OrderBook.h"

class MatchingEngine {
private:
    Catalog* catalog;
    OrderBook* orderbook;

public:
    MatchingEngine(Catalog* c, OrderBook* ob);

    void processOrders();
    void matchSingleProduct(int productId);
    void executeMatch(Order buy, Order sell);
};

#endif
