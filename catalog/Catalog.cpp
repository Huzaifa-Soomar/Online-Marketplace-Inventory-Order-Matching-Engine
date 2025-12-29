#include "Catalog.h"

Catalog::Catalog() : products(101) {}

void Catalog::addProduct(const Product& p) {
    products.insert(p.id, p);
    productList.push_back(p);
}

bool Catalog::removeProduct(int productId) {
    bool removed = products.remove(productId);
    if (removed) {
        // Also remove from productList (linear scan is fine for demo size).
        for (size_t i = 0; i < productList.size(); i++) {
            if (productList[i].id == productId) {
                productList.erase(productList.begin() + (long long)i);
                break;
            }
        }
    }
    return removed;
}

Product* Catalog::getProduct(int productId) {
    return products.search(productId);
}

CategoryTree& Catalog::getCategoryTree() {
    return categories;
}

const std::vector<Product>& Catalog::getAllProducts() const {
    return productList;
}