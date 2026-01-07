#include <iostream>
#include <vector>

#include "src/catalog/Catalog.h"
#include "src/orderbook/Order.h"
#include "src/orderbook/OrderBook.h"
#include "src/matching/MatchingEngine.h"
#include "src/recommendation/RecommendationEngine.h"
#include "src/utils/HashMap.h"

using std::cout;
using std::endl;


void printResult(const std::string& name, bool pass) {
    cout << (pass ? "[PASS] " : "[FAIL] ") << name << endl;
}


bool unitTestMatchingCorrectness() {
    OrderBook ob;
    HashMap<int, Order> orderIndex;
    Catalog catalog;
    MatchingEngine engine(&catalog, &ob, &orderIndex);

    ob.addOrder(Order(1, 101, BUY, 2, 260000, 1));
    orderIndex.insert(1, Order(1, 101, BUY, 2, 260000, 1));

    ob.addOrder(Order(2, 101, SELL, 1, 250000, 2));
    orderIndex.insert(2, Order(2, 101, SELL, 1, 250000, 2));

    engine.matchSingleProduct(101);

    bool buyStillExists = (orderIndex.search(1) != nullptr);
    bool sellRemoved = (orderIndex.search(2) == nullptr);

    return buyStillExists && sellRemoved;
}

bool unitTestRecommendationEngine() {
    RecommendationEngine rec;

    rec.recordPurchasePair(101, 102);
    rec.recordPurchasePair(101, 102);
    rec.recordPurchasePair(101, 201);

    std::vector<int> top = rec.getRecommendations(101, 1);

    return (!top.empty() && top[0] == 102);
}


bool integrationTestEndToEndMatching() {
    Catalog catalog;
    catalog.addProduct(Product(101, "Phone", "Electronics", 200000, 10));

    OrderBook ob;
    HashMap<int, Order> orderIndex;
    MatchingEngine engine(&catalog, &ob, &orderIndex);

    Order b1(1, 101, BUY, 2, 260000, 1);
    Order s1(2, 101, SELL, 2, 250000, 2);

    ob.addOrder(b1);
    ob.addOrder(s1);
    orderIndex.insert(1, b1);
    orderIndex.insert(2, s1);

    engine.matchSingleProduct(101);

    return orderIndex.search(1) == nullptr &&
           orderIndex.search(2) == nullptr;
}

bool integrationTestSequentialSimulation() {
    Catalog catalog;
    catalog.addProduct(Product(101, "Phone", "Electronics", 200000, 10));

    OrderBook ob;
    HashMap<int, Order> orderIndex;
    MatchingEngine engine(&catalog, &ob, &orderIndex);

    Order b1(1, 101, BUY, 1, 260000, 1);
    ob.addOrder(b1);
    orderIndex.insert(1, b1);

    Order s1(2, 101, SELL, 1, 250000, 2);
    ob.addOrder(s1);
    orderIndex.insert(2, s1);

    engine.matchSingleProduct(101);

    return orderIndex.search(1) == nullptr &&
           orderIndex.search(2) == nullptr;
}

bool integrationTestRecommendationWithCatalog() {
    Catalog catalog;
    catalog.addProduct(Product(101, "Phone", "Electronics", 200000, 10));
    catalog.addProduct(Product(102, "Charger", "Electronics", 3000, 50));

    RecommendationEngine rec;
    rec.recordPurchasePair(101, 102);
    rec.recordPurchasePair(101, 102);

    std::vector<int> recs = rec.getRecommendations(101, 1);
    if (recs.empty()) return false;

    Product* p = catalog.getProduct(recs[0]);
    return p != nullptr && p->name == "Charger";
}


int main() {
    cout << "===== RUNNING TESTS =====\n\n";

    printResult("Unit Test: Matching correctness",
                unitTestMatchingCorrectness());

    printResult("Unit Test: Recommendation engine",
                unitTestRecommendationEngine());

    printResult("Integration Test: End-to-end matching",
                integrationTestEndToEndMatching());

    printResult("Integration Test: Sequential concurrency simulation",
                integrationTestSequentialSimulation());

    printResult("Integration Test: Recommendation + catalog",
                integrationTestRecommendationWithCatalog());

    cout << "\n===== TESTING COMPLETE =====\n";
    return 0;
}
