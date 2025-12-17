#include "Order.h"

Order::Order()
    : orderId(0), productId(0), type(BUY), quantity(0), price(0.0), timestamp(0) {}

Order::Order(int orderId, int productId, OrderType type, int quantity, double price, long long timestamp)
    : orderId(orderId), productId(productId), type(type), quantity(quantity), price(price), timestamp(timestamp) {}

// Defines "natural ordering": lower price is smaller.
// Tie-breaker: earlier timestamp should have higher priority,
// so earlier timestamp is considered "smaller" in sorting terms.
bool Order::operator<(const Order& other) const {
    if (price != other.price) return price < other.price;
    return timestamp < other.timestamp;
}
