#include "MatchingEngine.h"
#include "../reports/Reports.h"

#include <algorithm> // for std::min

MatchingEngine::MatchingEngine(Catalog* c, OrderBook* ob)
    : catalog(c), orderbook(ob) {}

void MatchingEngine::processOrders() {
    // Keep trying to match as long as there are buy and sell orders
    // and the best prices can cross.
    while (orderbook->hasBuyOrders() && orderbook->hasSellOrders()) {
        Order bestBuy = orderbook->getBestBuy();
        Order bestSell = orderbook->getBestSell();

        if (bestBuy.productId != bestSell.productId)
            break; // Different products at the top – skip for simplicity.

        if (bestBuy.price < bestSell.price)
            break; // No price crossing.

        matchSingleProduct(bestBuy.productId);
    }
}

void MatchingEngine::matchSingleProduct(int productId) {
    while (orderbook->hasBuyOrders() && orderbook->hasSellOrders()) {
        Order bestBuy = orderbook->getBestBuy();
        Order bestSell = orderbook->getBestSell();

        if (bestBuy.productId != productId || bestSell.productId != productId)
            break;

        if (bestBuy.price < bestSell.price)
            break; // No more matches possible for this product.

        // Remove from the book to execute the trade.
        orderbook->removeBestBuy();
        orderbook->removeBestSell();

        executeMatch(bestBuy, bestSell);
    }
}

void MatchingEngine::executeMatch(Order buy, Order sell) {
    int tradedQty = std::min(buy.quantity, sell.quantity);

    // Log the executed portion.
    Order execBuy = buy;
    Order execSell = sell;
    execBuy.quantity = tradedQty;
    execSell.quantity = tradedQty;
    Reports::matchLog(execBuy, execSell);

    // Handle remaining quantities by re-inserting them into the book.
    if (buy.quantity > tradedQty) {
        buy.quantity -= tradedQty;
        orderbook->addOrder(buy);
    }

    if (sell.quantity > tradedQty) {
        sell.quantity -= tradedQty;
        orderbook->addOrder(sell);
    }
}


