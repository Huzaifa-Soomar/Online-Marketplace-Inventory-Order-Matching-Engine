#include <iostream>
#include <vector>

#include "catalog/Catalog.h"
#include "catalog/CategoryTree.h"
#include "catalog/Product.h"

#include "orderbook/OrderBook.h"
#include "orderbook/Order.h"

#include "recommendation/RecommendationEngine.h"

using namespace std;

/* ---------- helpers ---------- */

void printCategoryTree(CategoryNode* node, int depth = 0) {
    if (!node) return;

    for (int i = 0; i < depth; i++)
        cout << "   ";
    cout << node->name << "\n";

    for (size_t i = 0; i < node->children.size(); i++) {
        printCategoryTree(node->children[i], depth + 1);
    }
}

const char* orderTypeStr(OrderType t) {
    return (t == BUY) ? "BUY" : "SELL";
}

void printOrder(const Order& o) {
    cout << "Order{id=" << o.orderId
         << ", product=" << o.productId
         << ", type=" << orderTypeStr(o.type)
         << ", qty=" << o.quantity
         << ", price=" << o.price
         << ", ts=" << o.timestamp
         << "}";
}

/* ---------- test runner ---------- */

void runAllTests() {
    cout << "===== WEEK 12 DEMO: CORE FEATURES =====\n\n";

    /* --------------------------------------------------
       1) CategoryTree + HashMap (Catalog)
       -------------------------------------------------- */
    cout << "=== 1) CategoryTree + Catalog (HashMap) ===\n";

    Catalog catalog;
    CategoryTree& ct = catalog.getCategoryTree();

    ct.addCategory("ROOT", "Electronics");
    ct.addCategory("Electronics", "Mobile");
    ct.addCategory("Electronics", "Laptop");
    ct.addCategory("Electronics", "Tablet");

    ct.addCategory("ROOT", "Clothing");
    ct.addCategory("Clothing", "Jackets");
    ct.addCategory("Clothing", "Trousers");
    ct.addCategory("Clothing", "T-shirts");

    cout << "\nCategory Tree:\n";
    printCategoryTree(ct.getRoot());

    cout << "\nSearch 'Electronics': "
         << (ct.searchCategory("Electronics") ? "FOUND" : "NOT FOUND") << "\n";
    cout << "Search 'Shoes': "
         << (ct.searchCategory("Shoes") ? "FOUND" : "NOT FOUND") << "\n\n";

    catalog.addProduct(Product(101, "iPhone 15", "Electronics/Mobile", 250000.0, 10));
    catalog.addProduct(Product(102, "Dell XPS 13", "Electronics/Laptop", 320000.0, 5));
    catalog.addProduct(Product(201, "Leather Jacket", "Clothing/Jackets", 15000.0, 20));

    Product* p = catalog.getProduct(102);
    if (p)
        cout << "Lookup productId=102 => "
             << p->name << ", " << p->category
             << ", price=" << p->price
             << ", stock=" << p->stock << "\n";
    else
        cout << "Lookup productId=102 => NOT FOUND\n";

    cout << "Lookup productId=999 => "
         << (catalog.getProduct(999) ? "FOUND" : "NOT FOUND") << "\n\n";

    /* --------------------------------------------------
       2) OrderBook + Heap (Matching behavior)
       -------------------------------------------------- */
    cout << "=== 2) OrderBook + Heap (Matching) ===\n";

    OrderBook ob;

    ob.addOrder(Order(1, 101, BUY,  2, 255000.0, 1001));
    ob.addOrder(Order(2, 101, BUY,  1, 260000.0, 1002));
    ob.addOrder(Order(3, 101, SELL, 1, 265000.0, 1003));
    ob.addOrder(Order(4, 101, SELL, 3, 250000.0, 1004));

    cout << "Best BUY: ";
    printOrder(ob.getBestBuy());
    cout << "\n";

    cout << "Best SELL: ";
    printOrder(ob.getBestSell());
    cout << "\n";

    cout << "\nPop Best BUY: ";
    printOrder(ob.removeBestBuy());
    cout << "\n";

    cout << "Now Best BUY: ";
    printOrder(ob.getBestBuy());
    cout << "\n";

    cout << "\nPop Best SELL: ";
    printOrder(ob.removeBestSell());
    cout << "\n";

    cout << "Now Best SELL: ";
    printOrder(ob.getBestSell());
    cout << "\n\n";

    /* --------------------------------------------------
       3) Recommendation Engine (Graph)
       -------------------------------------------------- */
    cout << "=== 3) Recommendation Engine ===\n";

    RecommendationEngine rec;

    rec.recordPurchasePair(101, 102);
    rec.recordPurchasePair(101, 102);
    rec.recordPurchasePair(101, 102);

    rec.recordPurchasePair(101, 201);

    rec.recordPurchasePair(101, 301);
    rec.recordPurchasePair(101, 301);

    int k = 2;
    vector<int> top = rec.getRecommendations(101, k);

    cout << "Top-" << k << " recommendations for product 101: ";
    for (size_t i = 0; i < top.size(); i++) {
        cout << top[i];
        if (i + 1 < top.size()) cout << ", ";
    }
    cout << "\n\n";

    cout << "===== DEMO COMPLETE =====\n";
}