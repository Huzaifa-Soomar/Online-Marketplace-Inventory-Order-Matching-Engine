#include "Reports.h"

#include <iostream>

using std::cout;
using std::endl;

void Reports::inventoryReport(const Catalog& c) {
    cout << "===== INVENTORY REPORT =====\n";
    const std::vector<Product>& all = c.getAllProducts();

    if (all.empty()) {
        cout << "No products in catalog.\n\n";
        return;
    }

    for (size_t i = 0; i < all.size(); i++) {
        const Product& p = all[i];
        cout << "Product ID: " << p.id
             << ", Name: " << p.name
             << ", Category: " << p.category
             << ", Price: " << p.price << "\n";
    }
    cout << "\n";
}

void Reports::orderBookReport(const OrderBook& ob) {
    cout << "===== ORDER BOOK REPORT =====\n";

    // We only have access to top-of-book, not full depth, but that is enough
    // to demonstrate the heap behavior.
    if (!ob.hasBuyOrders() && !ob.hasSellOrders()) {
        cout << "Order book is empty.\n\n";
        return;
    }

    if (ob.hasBuyOrders()) {
        Order bestBuy = ob.getBestBuy();
        cout << "Best BUY -> "
             << "orderId=" << bestBuy.orderId
             << ", productId=" << bestBuy.productId
             << ", qty=" << bestBuy.quantity
             << ", price=" << bestBuy.price << "\n";
    } else {
        cout << "No BUY orders.\n";
    }

    if (ob.hasSellOrders()) {
        Order bestSell = ob.getBestSell();
        cout << "Best SELL -> "
             << "orderId=" << bestSell.orderId
             << ", productId=" << bestSell.productId
             << ", qty=" << bestSell.quantity
             << ", price=" << bestSell.price << "\n";
    } else {
        cout << "No SELL orders.\n";
    }

    cout << "\n";
}

void Reports::matchLog(const Order& buy, const Order& sell) {
    cout << "MATCH EXECUTED: "
         << "BUY(orderId=" << buy.orderId
         << ", productId=" << buy.productId
         << ", qty=" << buy.quantity
         << ", price=" << buy.price << ") "
         << "<--> "
         << "SELL(orderId=" << sell.orderId
         << ", productId=" << sell.productId
         << ", qty=" << sell.quantity
         << ", price=" << sell.price << ")\n";
}


