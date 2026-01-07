#ifndef PRODUCT_2025_H
#define PRODUCT_2025_H

#include <string>
using std::string;

class Product {
public:
    int id;
    string name;
    string category;
    double price;
    int stock;

    Product();
    Product(int id, const string& name, const string& category, double price, int stock);
};

#endif
