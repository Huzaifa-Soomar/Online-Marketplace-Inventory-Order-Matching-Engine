#ifndef ORDER_2025_H
#define ORDER_2025_H

enum OrderType { BUY, SELL };

class Order {
public:
    int orderId;
    int productId;
    OrderType type; // BUY or SELL
    int quantity;
    double price;
    long long timestamp;

    Order();
    Order(int orderId, int productId, OrderType type, int quantity, double price, long long timestamp);

    bool operator<(const Order& other) const;
};

#endif
