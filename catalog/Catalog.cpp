#include "Catalog.h"

Catalog::Catalog() : products(101) {}

void Catalog::addProduct(const Product& p) {
    products.insert(p.id, p);
}

bool Catalog::removeProduct(int productId) {
    return products.remove(productId);
}

Product* Catalog::getProduct(int productId) {
    return products.search(productId);
}

CategoryTree& Catalog::getCategoryTree() {
    return categories;
}