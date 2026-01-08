#include <iostream>
#include <vector>

#include "src/catalog/Catalog.h"
#include "src/catalog/CategoryTree.h"
#include "src/catalog/Product.h"

#include "src/orderbook/Order.h"
#include "src/orderbook/OrderBook.h"

#include "src/matching/MatchingEngine.h"

#include "src/recommendation/RecommendationEngine.h"
#include "src/reports/Reports.h"

#include "src/utils/HashMap.h"
#include "data/DataLoader.h"

using namespace std;

/* ---------- helpers ---------- */

void printCategoryTree(CategoryNode* node, int depth = 0) {
    if (!node) return;

    for (int i = 0; i < depth; i++)
        cout << "   ";
    cout << node->name << "\n";

    for (size_t i = 0; i < node->children.size(); i++)
        printCategoryTree(node->children[i], depth + 1);
}

const char* orderTypeStr(OrderType t) {
    return (t == BUY) ? "BUY" : "SELL";
}

void printOrder(const Order& o) {
    cout << "Order{id=" << o.orderId
         << ", product=" << o.productId
         << ", type=" << orderTypeStr(o.type)
         << ", qty=" << o.quantity
         << ", price=" << o.price
         << ", ts=" << o.timestamp
         << "}";
}

/* ---------- interactive CLI ---------- */

void interactiveMarketplace() {
    Catalog catalog;
    OrderBook orderBook;
    HashMap<int, Order> orderIndex;
    MatchingEngine engine(&catalog, &orderBook, &orderIndex);

    int nextOrderId = 1;

    loadCategories("data/categories.txt", catalog);
    loadProducts("data/products.txt", catalog);
    loadOrders("data/orders.txt", catalog, orderBook, orderIndex, nextOrderId);

    int choice = -1;

    while (choice != 0) {
        cout << "================ ONLINE MARKETPLACE (DSA PROJECT) ================\n";
        cout << "1) Show category tree\n";
        cout << "2) Show inventory (all products)\n";
        cout << "3) Lookup product by ID\n";
        cout << "4) Place BUY order\n";
        cout << "5) Place SELL order\n";
        cout << "6) View best BUY/SELL (top of order book)\n";
        cout << "7) View order by ID\n";
        cout << "8) Run matching for a product\n";
        cout << "9) Demo recommendations for sample data\n";
        cout << "0) Exit\n";
        cout << "Choose: ";
        cin >> choice;
        cout << "\n";

        if (!cin) {
            cin.clear();
            cin.ignore(10000, '\n');
            choice = -1;
            cout << "Invalid input.\n\n";
            continue;
        }

        if (choice == 1) {
            printCategoryTree(catalog.getCategoryTree().getRoot());
            cout << "\n";
        }
        else if (choice == 2) {
            Reports::inventoryReport(catalog);
        }
        else if (choice == 3) {
            int pid;
            cout << "Enter product ID: ";
            cin >> pid;

            Product* p = catalog.getProduct(pid);
            if (p)
                cout << "Product found: id=" << p->id
                     << ", name=" << p->name
                     << ", category=" << p->category
                     << ", price=" << p->price << "\n\n";
            else
                cout << "Product not found.\n\n";
        }
        else if (choice == 4 || choice == 5) {
            int pid, qty;
            double price;

            cout << "Enter product ID: ";
            cin >> pid;

            if (catalog.getProduct(pid) == nullptr) {
                cout << "Invalid product ID. Order rejected.\n\n";
                continue;
            }

            cout << "Enter quantity: ";
            cin >> qty;
            cout << "Enter price: ";
            cin >> price;

            OrderType type = (choice == 4) ? BUY : SELL;
            long long ts = nextOrderId;
            Order o(nextOrderId++, pid, type, qty, price, ts);

            orderBook.addOrder(o);
            orderIndex.insert(o.orderId, o);

            cout << "Order placed: ";
            printOrder(o);
            cout << "\n\n";
        }
        else if (choice == 6) {
            Reports::orderBookReport(orderBook);
        }
        else if (choice == 7) {
            int oid;
            cout << "Enter order ID: ";
            cin >> oid;

            Order* o = orderIndex.search(oid);
            if (o)
                printOrder(*o), cout << "\n\n";
            else
                cout << "Order not found.\n\n";
        }
        else if (choice == 8) {
            int pid;
            cout << "Enter product ID to match: ";
            cin >> pid;
            
            if (catalog.getProduct(pid) == nullptr) {
                cout << "Invalid product ID. Matching aborted.\n\n";
                continue;
            }
            engine.matchSingleProduct(pid);
            cout << "Matching complete.\n\n";
        }
        else if (choice == 9) {
            RecommendationEngine rec;
            loadPurchases("data/purchases.txt", rec);

            int pid, k;
            cout << "Enter product ID: ";
            cin >> pid;
            if (catalog.getProduct(pid) == nullptr) {
                cout << "Invalid product ID. Cannot generate recommendations.\n\n";
                continue;
            }

			cout << "Enter k: ";
			cin >> k;

			vector<int> top = rec.getRecommendations(pid, k);
			cout << "Recommendations: ";

			for (size_t i = 0; i < top.size(); i++) {
				Product* p = catalog.getProduct(top[i]);
				if (p)
					cout << p->name;
				else
					cout << top[i];

				if (i + 1 < top.size()) cout << ", ";
			}

			cout << "\n\n";
		}
        else if (choice == 0) {
            cout << "Exiting...\n";
        }
        else {
            cout << "Invalid option.\n\n";
        }
    }
}

int main() {
    interactiveMarketplace();
    return 0;
}