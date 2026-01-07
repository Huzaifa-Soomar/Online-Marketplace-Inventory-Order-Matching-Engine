Below is an **updated README.md** that matches **your current project state, folder structure, and implemented functionality**.
You can **copy-paste this as-is**.

---

# Online Marketplace Inventory & Order Matching Engine

DSA Final Project (Semester 3)

## Overview

This project implements an **online marketplace backend** using core **Data Structures and Algorithms** concepts taught in DSA-1.
The system supports product catalog management, hierarchical categories, order placement, order matching using priority rules, and product recommendations based on co-purchase behavior.

The focus of the project is **correct data structure usage**, **clean logic**, and **demonstrable functionality**, not production-level completeness.

---

## Core Features Implemented

### 1. Product Catalog

* Products stored using a **custom HashMap** for fast lookup by product ID.
* Products grouped into a **hierarchical category tree**.
* Inventory report displaying all products.

### 2. Category Management

* Tree-based category hierarchy.
* Unlimited sub-categories (non-binary tree).
* Recursive traversal and search.

### 3. Order Book

* Separate **BUY** and **SELL** order books.
* Implemented using **custom Heap (priority queue)**.
* Supports:

  * Price priority
  * Time priority (FIFO for same price)
  * Partial order execution

### 4. Matching Engine

* Matches BUY and SELL orders **per product**.
* Matching rules:

  * Same product ID
  * Buy price ≥ sell price
  * Highest buy matched with lowest sell
* Supports multiple matches in a single run.
* Remaining quantities are reinserted into the order book.
* Executed matches are logged.

### 5. Recommendation Engine

* Uses a **graph (Co-Purchase Graph)**.
* Products are nodes.
* Edge weights represent frequency of being bought together.
* Returns **Top-K recommended products**.

### 6. Reporting

* Inventory report
* Best BUY / SELL order report
* Match execution log

### 7. Data Loading (File-based)

* Sample data loaded from `.txt` files:

  * categories.txt
  * products.txt
  * orders.txt
  * purchases.txt
* Enables realistic demo without hardcoding.

### 8. Interactive CLI

* Menu-driven interface
* Supports:

  * Viewing categories
  * Viewing inventory
  * Placing BUY / SELL orders
  * Running matching for a product
  * Viewing an order by ID
  * Demoing recommendations

---

## Data Structures Used

| Feature            | Data Structure        |
| ------------------ | --------------------- |
| Product catalog    | HashMap (custom)      |
| Category hierarchy | Tree                  |
| Order book         | Heap / Priority Queue |
| Order lookup by ID | HashMap               |
| Recommendations    | Graph                 |
| Matching flow      | Queue-like processing |

---

## Algorithms & Complexity

* **Product lookup**: O(1) average
* **Insert order**: O(log n)
* **Best order retrieval**: O(1)
* **Order matching**: O(log n) per match
* **Category search**: O(n)
* **Recommendation (Top-K)**: O(V log V)

---

## Project Structure

```
Project Files/
│
├── data/
│   ├── categories.txt
│   ├── products.txt
│   ├── orders.txt
│   ├── purchases.txt
│   ├── DataLoader.h
│   └── DataLoader.cpp
│
├── docs/
│   ├── DesignDoc.pdf
│   ├── UserManual.pdf
│   └── ProgressLog.md
│
├── src/
│   ├── catalog/
│   │   ├── Catalog.h / Catalog.cpp
│   │   ├── CategoryTree.h / CategoryTree.cpp
│   │   └── Product.h / Product.cpp
│   │
│   ├── matching/
│   │   └── MatchingEngine.h / MatchingEngine.cpp
│   │
│   ├── orderbook/
│   │   ├── Order.h / Order.cpp
│   │   └── OrderBook.h / OrderBook.cpp
│   │
│   ├── recommendation/
│   │   ├── CoPurchaseGraph.h
│   │   └── RecommendationEngine.h
│   │
│   ├── reports/
│   │   ├── Reports.h / Reports.cpp
│   │
│   └── utils/
│       ├── HashMap.h
│       └── Heap.h
│
├── release/
│   └── OnlineMarketplace_DSA_Final.zip
│
├── main.cpp
├── main.exe
├── tests.cpp
├── tests.exe
└── README.md
```

---

## Compilation

### Compile Main Program

Run from **project root**:

```
g++ -std=c++17 main.cpp src/catalog/*.cpp src/matching/*.cpp src/orderbook/*.cpp src/reports/*.cpp data/DataLoader.cpp -o main.exe
```

### Compile Tests

```
g++ -std=c++17 tests.cpp src/catalog/*.cpp src/matching/*.cpp src/orderbook/*.cpp src/reports/*.cpp data/DataLoader.cpp -o tests.exe
```

---

## Testing

### Unit & Integration Tests Cover:

* Order matching correctness
* Sequential matching behavior (concurrency simulation)
* Recommendation accuracy

Tests are runnable independently using `tests.exe`.

---

## Design Decisions

* Inventory stock is **display-only**, not enforced during matching to keep scope aligned with DSA-1.
* Orders for non-existent products are rejected.
* Recommendations return product IDs; mapping to names is handled via catalog.
* No advanced STL containers used for core structures.

---

## Educational Scope

This project demonstrates:

* Practical application of DSA concepts
* Clean modular design
* Algorithm correctness over feature completeness
* Clear separation of concerns

---

## Notes

* Persistence is file-based for demo only.
* No multithreading or real concurrency (as per course scope).
* System prioritizes **correct matching logic** and **data structure use**.

---

## License

Academic project — for educational use only.
