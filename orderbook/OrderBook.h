#ifndef ORDER_BOOK_2025_H
#define ORDER_BOOK_2025_H

#include "../utils/Heap.h"
#include "Order.h"

class OrderBook {
private:
    Heap<Order> buyOrders;   // Max-heap
    Heap<Order> sellOrders;  // Min-heap

public:
    OrderBook();
    void addOrder(const Order& o);
    Order getBestBuy() const;
    Order getBestSell() const;
    Order removeBestBuy();
    Order removeBestSell();
};

#endif
