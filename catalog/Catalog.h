#ifndef CATALOG_2025_H
#define CATALOG_2025_H

#include "../utils/HashMap.h"
#include <vector>
#include "Product.h"
#include "CategoryTree.h"

class Catalog {
private:
    HashMap<int, Product> products;  // productId → Product
    CategoryTree categories;
    std::vector<Product> productList; // For iteration / reporting

public:
    Catalog();
    void addProduct(const Product& p);
    bool removeProduct(int productId);
    Product* getProduct(int productId);
    CategoryTree& getCategoryTree();

    const std::vector<Product>& getAllProducts() const;
};

#endif
