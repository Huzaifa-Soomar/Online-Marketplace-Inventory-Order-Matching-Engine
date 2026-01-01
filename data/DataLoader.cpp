#include "DataLoader.h"
#include <fstream>

void loadCategories(const char* path, Catalog& catalog) {
    std::ifstream in(path);
    std::string parent, child;
    CategoryTree& ct = catalog.getCategoryTree();

    while (in >> parent >> child)
        ct.addCategory(parent, child);
}

void loadProducts(const char* path, Catalog& catalog) {
    std::ifstream in(path);
    int id, stock;
    double price;
    std::string name, category;

    while (in >> id >> name >> category >> price >> stock) {
        for (char& c : name) if (c == '_') c = ' ';
        catalog.addProduct(Product(id, name, category, price, stock));
    }
}

void loadOrders(const char* path, Catalog& catalog, OrderBook& ob, HashMap<int, Order>& index, int& nextOrderId) {
    std::ifstream in(path);
    int oid, pid, qty;
    double price;
    std::string type;

    while (in >> oid >> pid >> type >> qty >> price) {
        if (catalog.getProduct(pid) == nullptr) continue;

        OrderType t = (type == "BUY") ? BUY : SELL;
        Order o(oid, pid, t, qty, price, oid);
        ob.addOrder(o);
        index.insert(o.orderId, o);
        if (oid >= nextOrderId) nextOrderId = oid + 1;
    }
}

void loadPurchases(const char* path, RecommendationEngine& rec) {
    std::ifstream in(path);
    int a, b;
    while (in >> a >> b)
        rec.recordPurchasePair(a, b);
}
