#ifndef ORDER_2025_H
#define ORDER_2025_H

#include <string>
using std::string;

enum OrderType { BUY, SELL };

class Order {
public:
    int orderId;
    int productId;
    OrderType type;
    int quantity;
    double price;
    long long timestamp;

    Order(int id = 0, int pid = 0, OrderType t = BUY,
          int qty = 0, double pr = 0.0, long long ts = 0);

    // Comparison for heap
    bool operator<(const Order& other) const {
        if (price == other.price)
            return timestamp > other.timestamp; // earlier first
        return price < other.price;
    }
};

#endif
