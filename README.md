# Online Marketplace System - DSA Final Project

A comprehensive online marketplace system implemented in C++ that demonstrates various data structures and algorithms including HashMaps, Heaps, Trees, and Graphs.

## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Data Structures Used](#data-structures-used)
- [Project Structure](#project-structure)
- [Compilation & Execution](#compilation--execution)
- [Usage](#usage)
- [Technical Details](#technical-details)
- [Components](#components)

## 🎯 Overview

This project implements a fully functional online marketplace system with the following core functionalities:

- **Product Catalog Management**: Hierarchical category system with product inventory
- **Order Matching Engine**: Price-time priority order matching using heaps
- **Recommendation System**: Graph-based co-purchase recommendations
- **Interactive CLI**: User-friendly command-line interface for marketplace operations

## ✨ Features

### 1. Catalog System
- Hierarchical category tree structure
- Product management with HashMap for O(1) lookups
- Category search and navigation
- Inventory tracking

### 2. Order Book & Matching
- Price-time priority order matching
- Separate heaps for buy and sell orders
- Automatic order matching when prices cross
- Partial order execution support

### 3. Recommendation Engine
- Graph-based co-purchase analysis
- Top-K product recommendations
- Weighted edge tracking for purchase frequency

### 4. Reporting System
- Inventory reports
- Order book visualization
- Transaction logging

## 🏗️ Data Structures Used

### 1. **HashMap** (`utils/HashMap.h`)
- Custom hash table implementation with chaining
- Used for O(1) product lookups in the catalog
- Handles collisions using linked lists

### 2. **Heap** (`utils/Heap.h`)
- Generic min/max heap implementation
- Used in OrderBook for maintaining order priority
- Supports both min-heap (sell orders) and max-heap (buy orders)

### 3. **CategoryTree** (`catalog/CategoryTree.h`)
- Tree data structure for hierarchical categories
- Supports nested categories (e.g., Electronics → Mobile → Smartphones)
- Recursive search and traversal

### 4. **CoPurchaseGraph** (`recommendation/CoPurchaseGraph.h`)
- Undirected weighted graph using adjacency lists
- Tracks co-purchase relationships between products
- Uses unordered_map for efficient edge lookups

## 📁 Project Structure

```
Final Project/
├── catalog/
│   ├── Catalog.h/cpp          # Product catalog with HashMap
│   ├── CategoryTree.h/cpp     # Hierarchical category tree
│   └── Product.h/cpp           # Product data structure
├── orderbook/
│   ├── OrderBook.h/cpp        # Order book with Heap
│   └── Order.h/cpp            # Order data structure
├── matching/
│   └── MatchingEngine.h/cpp    # Order matching logic
├── recommendation/
│   ├── RecommendationEngine.h # Recommendation system interface
│   └── CoPurchaseGraph.h      # Graph for co-purchase analysis
├── reports/
│   └── Reports.h/cpp          # Reporting utilities
├── utils/
│   ├── HashMap.h              # Custom hash table
│   └── Heap.h                 # Generic heap implementation
├── data/                      # CSV data files
├── main.cpp                   # Main program entry point
└── tests.cpp                  # Test suite
```

## 🔨 Compilation & Execution

### Prerequisites
- C++ compiler with C++11 support (g++, clang++, or MSVC)
- Standard C++ library

### Compilation

**Windows (PowerShell/CMD):**
```bash
g++ -std=c++11 -o marketplace main.cpp catalog/*.cpp orderbook/*.cpp matching/*.cpp reports/*.cpp
```

**Linux/Mac:**
```bash
g++ -std=c++11 -o marketplace main.cpp catalog/*.cpp orderbook/*.cpp matching/*.cpp reports/*.cpp
```

### Execution

```bash
./marketplace
# or on Windows:
marketplace.exe
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
7) Run matching for a product
8) Demo recommendations for sample data
9) Run core DSA demo (same as tests)
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

