#ifndef REPORTS_2025_H
#define REPORTS_2025_H

#include "../catalog/Catalog.h"
#include "../orderbook/OrderBook.h"

class Reports {
public:
    static void inventoryReport(const Catalog& c);
    static void orderBookReport(const OrderBook& ob);
    static void matchLog(const Order& buy, const Order& sell);
};

#endif
