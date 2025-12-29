#include <iostream>
#include <vector>

#include "catalog/Catalog.h"
#include "catalog/CategoryTree.h"
#include "catalog/Product.h"

#include "orderbook/OrderBook.h"
#include "orderbook/Order.h"

#include "matching/MatchingEngine.h"

#include "recommendation/RecommendationEngine.h"
#include "reports/Reports.h"

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

/* ---------- core demo (for tests.cpp) ---------- */

void runAllTests() {
    cout << "===== DEMO: CORE DATA STRUCTURES =====\n\n";

    // 1) CategoryTree + Catalog (HashMap)
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

    // 2) OrderBook + Heap
    cout << "=== 2) OrderBook + Heap (Matching behavior) ===\n";

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

    // 3) Recommendation Engine
    cout << "=== 3) Recommendation Engine (Graph) ===\n";

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

/* ---------- interactive CLI ---------- */

void seedSampleData(Catalog& catalog) {
    CategoryTree& ct = catalog.getCategoryTree();

    ct.addCategory("ROOT", "Electronics");
    ct.addCategory("Electronics", "Mobile");
    ct.addCategory("Electronics", "Laptop");

    ct.addCategory("ROOT", "Clothing");
    ct.addCategory("Clothing", "Jackets");

    catalog.addProduct(Product(101, "iPhone 15", "Electronics/Mobile", 250000.0, 10));
    catalog.addProduct(Product(102, "Dell XPS 13", "Electronics/Laptop", 320000.0, 5));
    catalog.addProduct(Product(201, "Leather Jacket", "Clothing/Jackets", 15000.0, 20));
}

void interactiveMarketplace() {
    Catalog catalog;
    OrderBook orderBook;
    MatchingEngine engine(&catalog, &orderBook);

    seedSampleData(catalog);

    int choice = -1;
    int nextOrderId = 1;

    while (choice != 0) {
        cout << "================ ONLINE MARKETPLACE (DSA PROJECT) ================\n";
        cout << "1) Show category tree\n";
        cout << "2) Show inventory (all products)\n";
        cout << "3) Lookup product by ID\n";
        cout << "4) Place BUY order\n";
        cout << "5) Place SELL order\n";
        cout << "6) View best BUY/SELL (top of order book)\n";
        cout << "7) Run matching for a product\n";
        cout << "8) Demo recommendations for sample data\n";
        cout << "9) Run core DSA demo (same as tests)\n";
        cout << "0) Exit\n";
        cout << "Choose: ";
        cin >> choice;
        cout << "\n";

        if (!cin) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Try again.\n\n";
            choice = -1;
            continue;
        }

        if (choice == 1) {
            cout << "Category Tree:\n";
            printCategoryTree(catalog.getCategoryTree().getRoot());
            cout << "\n";
        } else if (choice == 2) {
            Reports::inventoryReport(catalog);
        } else if (choice == 3) {
            int pid;
            cout << "Enter product ID: ";
            cin >> pid;
            Product* p = catalog.getProduct(pid);
            if (p) {
                cout << "Product found: id=" << p->id
                     << ", name=" << p->name
                     << ", category=" << p->category
                     << ", price=" << p->price
                     << ", stock=" << p->stock << "\n\n";
            } else {
                cout << "Product not found.\n\n";
            }
        } else if (choice == 4 || choice == 5) {
            int pid, qty;
            double price;
            cout << "Enter product ID: ";
            cin >> pid;
            cout << "Enter quantity: ";
            cin >> qty;
            cout << "Enter price: ";
            cin >> price;

            OrderType type = (choice == 4) ? BUY : SELL;
            long long ts = nextOrderId; // simple monotonic timestamp
            Order o(nextOrderId++, pid, type, qty, price, ts);
            orderBook.addOrder(o);
            cout << "Order placed: ";
            printOrder(o);
            cout << "\n\n";
        } else if (choice == 6) {
            Reports::orderBookReport(orderBook);
        } else if (choice == 7) {
            int pid;
            cout << "Enter product ID to match: ";
            cin >> pid;
            cout << "Running matching engine for product " << pid << "...\n";
            engine.matchSingleProduct(pid);
            cout << "Done.\n\n";
        } else if (choice == 8) {
            RecommendationEngine demoRec;
            demoRec.recordPurchasePair(101, 102);
            demoRec.recordPurchasePair(101, 102);
            demoRec.recordPurchasePair(101, 102);
            demoRec.recordPurchasePair(101, 201);
            demoRec.recordPurchasePair(101, 301);
            demoRec.recordPurchasePair(101, 301);

            int k = 2;
            vector<int> top = demoRec.getRecommendations(101, k);
            cout << "Top-" << k << " recommendations for product 101: ";
            for (size_t i = 0; i < top.size(); i++) {
                cout << top[i];
                if (i + 1 < top.size()) cout << ", ";
            }
            cout << "\n\n";
        } else if (choice == 9) {
            runAllTests();
            cout << "\n";
        } else if (choice == 0) {
            cout << "Exiting...\n";
        } else {
            cout << "Unknown option. Try again.\n\n";
        }
    }
}

int main() {
    interactiveMarketplace();
    return 0;
}