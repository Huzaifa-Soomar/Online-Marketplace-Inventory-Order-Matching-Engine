#include "MatchingEngine.h"
#include "../reports/Reports.h"

#include <algorithm> // for std::min
#include <vector>

MatchingEngine::MatchingEngine(Catalog* c, OrderBook* ob, HashMap<int, Order>* idx)
    : catalog(c), orderbook(ob), orderIndex(idx) {}


void MatchingEngine::processOrders() {
    while (orderbook->hasBuyOrders() && orderbook->hasSellOrders()) {
        int pid = orderbook->getBestBuy().productId;
        matchSingleProduct(pid);
        break;
    }
}

void MatchingEngine::matchSingleProduct(int productId) {
    std::vector<Order> skippedBuys;
    std::vector<Order> skippedSells;

    while (orderbook->hasBuyOrders()) {
        Order b = orderbook->getBestBuy();
        if (b.productId == productId) break;
        skippedBuys.push_back(orderbook->removeBestBuy());
    }

    while (orderbook->hasSellOrders()) {
        Order s = orderbook->getBestSell();
        if (s.productId == productId) break;
        skippedSells.push_back(orderbook->removeBestSell());
    }

    while (orderbook->hasBuyOrders() && orderbook->hasSellOrders()) {
        Order bestBuy = orderbook->getBestBuy();
        Order bestSell = orderbook->getBestSell();

        if (bestBuy.productId != productId || bestSell.productId != productId)
            break;

        if (bestBuy.price < bestSell.price)
            break;

        orderbook->removeBestBuy();
        orderbook->removeBestSell();
        executeMatch(bestBuy, bestSell);
    }

    for (const Order& o : skippedBuys)
        orderbook->addOrder(o);

    for (const Order& o : skippedSells)
        orderbook->addOrder(o);
}

void MatchingEngine::executeMatch(Order buy, Order sell) {
    int tradedQty = std::min(buy.quantity, sell.quantity);

    Order execBuy = buy;
    Order execSell = sell;
    execBuy.quantity = tradedQty;
    execSell.quantity = tradedQty;
    Reports::matchLog(execBuy, execSell);

    if (buy.quantity == tradedQty) {
        orderIndex->remove(buy.orderId);
    } else {
        buy.quantity -= tradedQty;
        orderIndex->insert(buy.orderId, buy);
        orderbook->addOrder(buy);
    }

    if (sell.quantity == tradedQty) {
        orderIndex->remove(sell.orderId);
    } else {
        sell.quantity -= tradedQty;
        orderIndex->insert(sell.orderId, sell);
        orderbook->addOrder(sell);
    }
}