#include "OrderBook.h"

void OrderBook::addOrder(const Order& o) {
    if (o.type == BUY)
        buyOrders.push(o);
    else
        sellOrders.push(o);
}

Order OrderBook::getBestBuy() const {
    return buyOrders.top();
}

Order OrderBook::getBestSell() const {
    return sellOrders.top();
}

Order OrderBook::removeBestBuy() {
    return buyOrders.pop();
}

Order OrderBook::removeBestSell() {
    return sellOrders.pop();
}
