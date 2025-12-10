#ifndef CATALOG_2025_H
#define CATALOG_2025_H

#include "../utils/HashMap.h"
#include "Product.h"
#include "CategoryTree.h"

class Catalog {
private:
    HashMap<int, Product> products;  // productId → Product
    CategoryTree categories;

public:
    Catalog();
    void addProduct(const Product& p);
    bool removeProduct(int productId);
    Product* getProduct(int productId);
    CategoryTree& getCategoryTree();
};

#endif
