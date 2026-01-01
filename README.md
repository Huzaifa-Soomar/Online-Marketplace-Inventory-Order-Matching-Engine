# Online Marketplace System – DSA Final Project

A comprehensive online marketplace system implemented in C++ that demonstrates core data structures and algorithms including HashMaps, Heaps (Priority Queues), Trees, and Graphs.

---

## 📋 Table of Contents

- Overview
- Features
- Data Structures Used
- Project Structure
- Compilation & Execution
- Usage
- Technical Details
- Components
- Educational Scope & Design Decisions

---

## 🎯 Overview

This project implements an online marketplace system focused on demonstrating **Data Structures and Algorithms** concepts. The system supports:

- Product catalog management using hashing and trees
- Order matching using priority queues (heaps)
- Graph-based product recommendations
- Interactive command-line interface for demonstration and testing

All operations are performed **in-memory** and are intended for **educational purposes**.

---

## ✨ Features

### 1. Catalog System
- Hierarchical category management using a tree
- Product catalog with fast lookup using a custom HashMap
- Category search and traversal
- Inventory metadata display (ID, name, category, price)

### 2. Order Book & Matching
- Price–time priority order matching
- Separate priority queues for BUY and SELL orders
- Partial order execution supported
- Product-specific matching

### 3. Recommendation Engine
- Graph-based “frequently bought together” analysis
- Weighted edges based on co-purchase frequency
- Top-K product recommendations

### 4. Reporting
- Inventory listing
- Order book top-of-book view
- Match execution logging

---

## 🏗️ Data Structures Used

### **HashMap** (`utils/HashMap.h`)
- Custom hash table implementation with chaining
- Used for:
  - Product catalog lookup
  - Order lookup by ID
- Average-case O(1) operations

### **Heap / Priority Queue** (`utils/Heap.h`)
- Custom generic heap implementation
- Used as:
  - Max-heap for BUY orders
  - Min-heap for SELL orders
- Enforces price–time priority

### **CategoryTree** (`catalog/CategoryTree.h`)
- General (multi-child) tree
- Represents hierarchical product categories
- Supports recursive traversal and search

### **CoPurchaseGraph** (`recommendation/CoPurchaseGraph.h`)
- Undirected weighted graph
- Adjacency list representation
- Tracks co-purchase frequencies between products

---

## 📁 Project Structure

```
Final Project/
├── catalog/
│ ├── Catalog.h/cpp
│ ├── CategoryTree.h/cpp
│ └── Product.h/cpp
├── orderbook/
│ ├── OrderBook.h/cpp
│ └── Order.h/cpp
├── matching/
│ └── MatchingEngine.h/cpp
├── recommendation/
│ ├── RecommendationEngine.h
│ └── CoPurchaseGraph.h
├── reports/
│ └── Reports.h/cpp
├── utils/
│ ├── HashMap.h
│ └── Heap.h
├── data/
│ ├── categories.txt
│ ├── products.txt
│ ├── orders.txt
│ └── purchases.txt
│ └── DataLoader.h/cpp
│── main.exe
└── main.cpp
```


---

## 🔨 Compilation & Execution

### Prerequisites
- C++ compiler with **C++17** support
- Standard C++ library

### Compilation (Windows / Linux / macOS)

```bash
g++ -std=c++17 main.cpp catalog/*.cpp orderbook/*.cpp matching/*.cpp reports/*.cpp data/DataLoader.cpp -o main.exe
```

### Execution

```bash
./main.exe
```

## 💻 Usage

The program provides an interactive command-line interface with the following options:

```
================ ONLINE MARKETPLACE (DSA PROJECT) ================
1) Show category tree
2) Show inventory (all products)
3) Lookup product by ID
4) Place BUY order
5) Place SELL order
6) View best BUY/SELL (top of order book)
7) View order by ID
8) Run matching for a product
9) Demo recommendations for sample data
0) Exit
```

### Example Workflow

1. **View Categories**: Select option 1 to see the hierarchical category structure
2. **Add Products**: Products are pre-seeded, but you can view them with option 2
3. **Place Orders**: Use options 4 and 5 to place buy/sell orders
4. **Match Orders**: Use option 7 to execute order matching for a specific product
5. **View Recommendations**: Use option 8 to see product recommendations

## 🔧 Technical Details

### Order Matching Algorithm

The matching engine uses **price-time priority**:

1. **Price Priority**: Orders are first sorted by price
   - Buy orders: Higher price = higher priority (max-heap)
   - Sell orders: Lower price = higher priority (min-heap)

2. **Time Priority**: For orders with the same price, earlier timestamps get priority
   - Implemented in `Order::operator<()`:
     ```cpp
     if (price != other.price) return price < other.price;
     return timestamp > other.timestamp;  // Earlier timestamp = higher priority
     ```

3. **Matching Logic**: Orders match when:
   - Same product ID
   - Buy price ≥ Sell price
   - Partial fills are supported (remaining quantity re-inserted)

### Recommendation Algorithm

The recommendation system uses a **weighted graph** approach:

1. **Graph Construction**: Each co-purchase creates/updates an edge weight
2. **Top-K Selection**: For a given product, returns top K neighbors by edge weight
3. **Time Complexity**: O(V log V) for sorting neighbors, where V is the number of neighbors

### Time Complexities

| Operation | Data Structure | Complexity |
|-----------|---------------|------------|
| Product Lookup | HashMap | O(1) average |
| Add Order | Heap | O(log n) |
| Get Best Order | Heap | O(1) |
| Category Search | Tree | O(n) |
| Get Recommendations | Graph | O(V log V) |

## 🧩 Components

### Catalog (`catalog/`)
- **Catalog**: Manages products using HashMap for fast lookups
- **CategoryTree**: Maintains hierarchical category structure
- **Product**: Represents a product with ID, name, category, price, and stock

### OrderBook (`orderbook/`)
- **OrderBook**: Maintains separate heaps for buy and sell orders
- **Order**: Represents an order with ID, product, type, quantity, price, and timestamp

### Matching Engine (`matching/`)
- **MatchingEngine**: Processes orders and matches buy/sell orders when prices cross
- Supports partial fills and automatic re-insertion of remaining quantities

### Recommendation Engine (`recommendation/`)
- **RecommendationEngine**: Interface for product recommendations
- **CoPurchaseGraph**: Graph implementation tracking product co-purchases

### Utilities (`utils/`)
- **HashMap**: Custom hash table with chaining for collision resolution
- **Heap**: Generic heap supporting both min and max heaps

## 📊 Sample Data

The system comes with pre-seeded sample data:
- **Products**: iPhone 15, Dell XPS 13, Leather Jacket
- **Categories**: Electronics (Mobile, Laptop), Clothing (Jackets)
- **Sample Orders**: Various buy/sell orders for demonstration

## 🎓 Educational Purpose

This project demonstrates:
- **Data Structure Implementation**: Custom HashMap, Heap, Tree, Graph
- **Algorithm Design**: Order matching, graph traversal, sorting
- **Object-Oriented Design**: Modular component architecture
- **Real-World Application**: Practical marketplace system

## 📝 Notes

- Timestamps in orders are used for tie-breaking when prices are equal
- The system supports partial order execution
- All data structures are implemented from scratch (no STL containers for core structures)
- The project follows C++11 standards

## 👤 Author

DSA Theory Final Project - Semester 3

## 📄 License

Educational project for academic purposes.

