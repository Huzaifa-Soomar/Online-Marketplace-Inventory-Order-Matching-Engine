#include "Product.h"

Product::Product() : id(0), name(""), category(""), price(0.0), stock(0) {}

Product::Product(int id, const string& name, const string& category, double price, int stock)
    : id(id), name(name), category(category), price(price), stock(stock) {}
