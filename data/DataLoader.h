#ifndef DATA_LOADER_2025_H
#define DATA_LOADER_2025_H

#include "../src/catalog/Catalog.h"
#include "../src/orderbook/OrderBook.h"
#include "../src/utils/HashMap.h"
#include "../src/recommendation/RecommendationEngine.h"

void loadCategories(const char* path, Catalog& catalog);
void loadProducts(const char* path, Catalog& catalog);
void loadOrders(const char* path, Catalog& catalog, OrderBook& ob, HashMap<int, Order>& index, int& nextOrderId);
void loadPurchases(const char* path, RecommendationEngine& rec);

#endif
