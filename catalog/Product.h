#ifndef PRODUCT_2025_H
#define PRODUCT_2025_H

#include <string>
using std::string;

class Product {
public:
    int productId;
    string name;
    string category;
    double price;
    int stock;

    Product(int id = 0, string n = "", string cat = "", double p = 0.0, int s = 0);
};

#endif
