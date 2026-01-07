#include "Order.h"

Order::Order()
    : orderId(0), productId(0), type(BUY), quantity(0), price(0.0), timestamp(0) {}

Order::Order(int orderId, int productId, OrderType type, int quantity, double price, long long timestamp)
    : orderId(orderId), productId(productId), type(type), quantity(quantity), price(price), timestamp(timestamp) {}

// Defines "natural ordering" used by Heap:
// - For price: lower price is considered "smaller".
// - For ties: later timestamp is considered "smaller",
//   so that earlier timestamps get higher priority in a max-heap
//   (price–time priority rule).
bool Order::operator<(const Order& other) const {
    if (price != other.price) return price < other.price;
    return timestamp > other.timestamp;
}
