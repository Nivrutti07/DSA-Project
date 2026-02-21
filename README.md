# 🛒 Online Shopping System – Data Structures & Algorithms (C++)

A comprehensive **console-based E-Commerce Management System** built in **C++**, demonstrating real-world applications of advanced **Data Structures and Algorithms (DSA)** in a practical business environment.

---

## 🎯 Project Overview

This project simulates a complete online shopping ecosystem involving:

- 🧑‍💼 Sellers  
- 🛍 Customers  
- 🚚 Delivery Partners  

The system integrates multiple core and advanced DSA concepts to model product management, searching, sorting, delivery routing, and priority-based order processing.

This project is designed to showcase strong problem-solving skills and practical DSA implementation for technical interviews and placements.

---

## ✨ Key Features

### 👨‍💼 Seller Portal
- Seller registration
- Add products (name, category, price, stock)
- View seller-specific products
- Monitor all system orders

### 🛍 Customer Portal
- Browse all products
- Substring search using **KMP Algorithm**
- Prefix search using **Trie**
- Sort products by price using **QuickSort**
- Place orders with delivery location selection
- Automatic stock management
- Shortest delivery distance calculation

### 🚚 Delivery Partner Portal
- View pending orders
- Compute shortest route using **Dijkstra’s Algorithm**
- Process deliveries by shortest distance using **Min-Heap**
- Update order status (Pending → Shipped → Delivered)
- Analyze network efficiency using **Prim & Kruskal MST**

---

## 🏗️ Data Structures Used

| Data Structure | Application |
|---------------|-------------|
| Linked List | Recently viewed product IDs |
| Stack | Undo operation history |
| Queue | Support ticket simulation |
| Binary Search Tree (BST) | Fast product ID validation |
| AVL Tree | Balanced indexing of order IDs |
| Trie | Efficient prefix-based product search |
| Min-Heap | Delivery priority queue |
| Graph (Adjacency List) | Delivery network modeling |
| Union-Find (Disjoint Set) | Kruskal’s MST implementation |
| Hash Maps | Seller, customer & partner management |

---

## 🧮 Algorithms Implemented

### 🔎 Searching Algorithms
- **KMP (Knuth-Morris-Pratt)** – Efficient substring matching
- **Trie-based Search** – Prefix-based lookup
- **BST Search** – O(log n) product validation

### 📊 Sorting
- **QuickSort** – Price-based sorting (Average O(n log n))

### 🌐 Graph Algorithms
- **DFS (Depth-First Search)** – Network traversal
- **BFS (Breadth-First Search)** – Network traversal
- **Dijkstra’s Algorithm** – Shortest path calculation
- **Prim’s Algorithm** – Minimum Spanning Tree
- **Kruskal’s Algorithm** – MST using Union-Find

### 🌳 Tree Operations
- AVL Rotations for self-balancing
- BST insert/search operations

---


## 👨‍💼 My Contribution – Seller Module

I was primarily responsible for designing and implementing the **Seller Management System**.

### Responsibilities:

- Developed seller registration functionality  
- Implemented product addition system (name, category, price, stock)  
- Integrated product storage using appropriate data structures  
- Connected product indexing with:
  - Binary Search Tree (Product ID validation)
  - Trie (Product name indexing)
- Ensured real-time stock updates after order placement  
- Designed seller-specific product viewing functionality  

### Technical Focus:

- Applied Object-Oriented Programming principles  
- Ensured modular and scalable code structure  
- Optimized product lookup operations  
- Maintained clean integration with overall system architecture  

This module demonstrates strong understanding of:
- Data organization  
- Tree-based indexing  
- Efficient insertion and validation logic  
- Real-world business logic implementation  

---

## 🚀 Getting Started

### 📌 Prerequisites
- C++ Compiler (C++11 or later)
- STL (Standard Template Library)

### 🔧 Compilation

```bash
g++ -std=c++11 E-commerce.cpp -o shopping_system
