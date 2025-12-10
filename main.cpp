#include <iostream>
#include "catalog/Catalog.h"
#include "orderbook/OrderBook.h"
#include "matching/MatchingEngine.h"
#include "recommendation/RecommendationEngine.h"

using namespace std;

int main() {
    cout << "=== Online Marketplace Engine ===" << endl;

    // Load catalog
    Catalog catalog;
    catalog.loadProducts("data/products.csv");

    // Load orders
    OrderBook orderBook;
    orderBook.loadOrders("data/orders.csv");

    // Matching engine
    MatchingEngine matcher(&catalog, &orderBook);
    matcher.matchOrders();

    // Recommendation engine
    RecommendationEngine recommender;
    recommender.loadHistory("data/buyer_history.csv");
    recommender.buildGraph();
    recommender.showTopK(1, 3);

    cout << "=== System Finished ===" << endl;
    return 0;
}
