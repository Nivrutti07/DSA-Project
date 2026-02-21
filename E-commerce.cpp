#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <tuple>
#include <cmath>
#include <iomanip>
#include <climits>
#include <string>
#include <limits>

using namespace std;

// =============== UI HELPERS (BEAUTIFIED INTERFACE) ===============

void printSeparator(char ch = '-') {
    cout << string(60, ch) << "\n";
}

void printSectionTitle(const string& title) {
    printSeparator('=');
    cout << "  " << title << "\n";
    printSeparator('=');
}

void printSubTitle(const string& title) {
    printSeparator('-');
    cout << "  " << title << "\n";
    printSeparator('-');
}

// ==================== BASIC DATA STRUCTURES ====================

// 1. LINKED LIST
template<typename T>
class LinkedList {
    struct Node {
        T data;
        Node* next;
        Node(T val) : data(val), next(nullptr) {}
    };
    Node* head;
public:
    LinkedList() : head(nullptr) {}
    void insertBack(T data) {
        Node* newNode = new Node(data);
        if (!head) head = newNode;
        else {
            Node* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
    }
    bool empty() const { return head == nullptr; }
    void display() const {
        Node* temp = head;
        while (temp) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }
};

// 2. STACK (Array-based)
template<typename T>
class StackArr {
    vector<T> arr;
public:
    void push(T data) { arr.push_back(data); }
    T pop() {
        if (arr.empty()) return T();
        T val = arr.back();
        arr.pop_back();
        return val;
    }
    T top() const { return arr.empty() ? T() : arr.back(); }
    bool isEmpty() const { return arr.empty(); }
};

// 3. QUEUE (Array-based)
template<typename T>
class QueueArr {
    vector<T> arr;
    size_t frontIdx;
public:
    QueueArr() : frontIdx(0) {}
    void enqueue(T data) { arr.push_back(data); }
    T dequeue() {
        if (frontIdx >= arr.size()) return T();
        return arr[frontIdx++];
    }
    bool isEmpty() const { return frontIdx >= arr.size(); }
};

// 4. BINARY SEARCH TREE (generic, used for product IDs)
template<typename T>
class BST {
    struct Node {
        T data;
        Node *left, *right;
        Node(T val) : data(val), left(nullptr), right(nullptr) {}
    };
    Node* root;

    bool search(Node* node, T data) const {
        if (!node) return false;
        if (node->data == data) return true;
        return data < node->data
               ? search(node->left, data)
               : search(node->right, data);  // FIX: pass data in both branches
    }

    void inorder(Node* node) const {
        if (!node) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

public:
    BST() : root(nullptr) {}
    void insert(T data) {
        root = insert(root, data);
    }

    Node* insert(Node* node, T data) {
        if (!node) return new Node(data);
        if (data < node->data) node->left = insert(node->left, data);
        else if (data > node->data) node->right = insert(node->right, data);
        return node;
    }

    bool contains(T data) const { return search(root, data); }
    void printInorder() const { inorder(root); cout << "\n"; }
};

// 5. AVL TREE (for balanced integer keys – used for order IDs demo)
class AVLTree {
    struct Node {
        int data, height;
        Node *left, *right;
        Node(int val) : data(val), height(1), left(nullptr), right(nullptr) {}
    };
    Node* root;

    int height(Node* n) const { return n ? n->height : 0; }
    int balance(Node* n) const { return n ? height(n->left) - height(n->right) : 0; }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y;
    }

    Node* insert(Node* node, int data) {
        if (!node) return new Node(data);
        if (data < node->data) node->left = insert(node->left, data);
        else if (data > node->data) node->right = insert(node->right, data);
        else return node;

        node->height = 1 + max(height(node->left), height(node->right));
        int bal = balance(node);

        if (bal > 1 && data < node->left->data) return rightRotate(node);
        if (bal < -1 && data > node->right->data) return leftRotate(node);
        if (bal > 1 && data > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (bal < -1 && data < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    void inorder(Node* node) const {
        if (!node) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

public:
    AVLTree() : root(nullptr) {}
    void insert(int data) { root = insert(root, data); }
    void printInorder() const { inorder(root); cout << "\n"; }
};

// 6. TRIE (for product name prefix search)
class Trie {
    struct Node {
        unordered_map<char, Node*> children;
        bool isEnd;
        Node() : isEnd(false) {}
    };
    Node* root;

public:
    Trie() : root(new Node()) {}

    void insert(const string& word) {
        Node* curr = root;
        for (char c : word) {
            if (!curr->children[c])
                curr->children[c] = new Node();
            curr = curr->children[c];
        }
        curr->isEnd = true;
    }

    bool search(const string& word) const {
        Node* curr = root;
        for (char c : word) {
            auto it = curr->children.find(c);
            if (it == curr->children.end()) return false;
            curr = it->second;
        }
        return curr->isEnd;
    }

    bool startsWith(const string& prefix) const {
        Node* curr = root;
        for (char c : prefix) {
            auto it = curr->children.find(c);
            if (it == curr->children.end()) return false;
            curr = it->second;
        }
        return true;
    }
};

// 7. MIN HEAP (for order priority by distance)
class MinHeap {
    vector<pair<int,int>> heap; // {distance, orderIndex}

    void heapifyUp(int idx) {
        while (idx > 0) {
            int parent = (idx - 1) / 2;
            if (heap[idx].first < heap[parent].first) {
                swap(heap[idx], heap[parent]);
                idx = parent;
            } else break;
        }
    }

    void heapifyDown(int idx) {
        int size = (int)heap.size();
        while (idx < size) {
            int left = 2 * idx + 1;
            int right = 2 * idx + 2;
            int smallest = idx;

            if (left < size && heap[left].first < heap[smallest].first)
                smallest = left;
            if (right < size && heap[right].first < heap[smallest].first)
                smallest = right;

            if (smallest != idx) {
                swap(heap[idx], heap[smallest]);
                idx = smallest;
            } else break;
        }
    }

public:
    void insert(int dist, int orderIndex) {
        heap.push_back({dist, orderIndex});
        heapifyUp((int)heap.size() - 1);
    }

    pair<int,int> extractMin() {
        if (heap.empty()) return {-1,-1};
        auto minVal = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) heapifyDown(0);
        return minVal;
    }

    bool isEmpty() const { return heap.empty(); }
};

// 8. UNION-FIND (Disjoint Set Union – used in Kruskal)
class UnionFind {
    vector<int> parent, rankv;
public:
    UnionFind(int n = 0) {
        reset(n);
    }
    void reset(int n) {
        parent.resize(n);
        rankv.assign(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return;

        if (rankv[px] < rankv[py])
            parent[px] = py;
        else if (rankv[px] > rankv[py])
            parent[py] = px;
        else {
            parent[py] = px;
            rankv[px]++;
        }
    }
};

// ==================== GRAPH & ALGORITHMS ====================

class Graph {
    int V;
    vector<vector<pair<int, int>>> adj; // {neighbor, weight}

public:
    Graph(int vertices = 0) : V(vertices) {
        adj.assign(V, {});
    }

    void reset(int vertices) {
        V = vertices;
        adj.assign(V, {});
    }

    void addEdge(int u, int v, int w) {
        if (u < 0 || v < 0 || u >= V || v >= V) return;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w}); // undirected
    }

    // DFS (for connectivity diagnostics)
    void DFSUtil(int v, vector<bool>& visited) const {
        visited[v] = true;
        cout << v << " ";
        for (auto& p : adj[v]) {
            if (!visited[p.first])
                DFSUtil(p.first, visited);
        }
    }

    void DFS(int start) const {
        vector<bool> visited(V, false);
        if (start < 0 || start >= V) return;
        DFSUtil(start, visited);
        cout << "\n";
    }

    // BFS
    void BFS(int start) const {
        if (start < 0 || start >= V) return;
        vector<bool> visited(V, false);
        queue<int> q;
        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            cout << v << " ";

            for (auto& p : adj[v]) {
                if (!visited[p.first]) {
                    visited[p.first] = true;
                    q.push(p.first);
                }
            }
        }
        cout << "\n";
    }

    // DIJKSTRA: returns {dist, parent}
    pair<vector<int>, vector<int>> dijkstra(int src) const {
        vector<int> dist(V, INT_MAX), parent(V, -1);
        using P = pair<int,int>;
        priority_queue<P, vector<P>, greater<P>> pq;

        if (src < 0 || src >= V) return {dist, parent};

        dist[src] = 0;
        pq.push({0, src});

        while (!pq.empty()) {
            int u = pq.top().second;
            int d = pq.top().first;
            pq.pop();
            if (d != dist[u]) continue;

            for (auto& p : adj[u]) {
                int v = p.first;
                int w = p.second;
                if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }
        return {dist, parent};
    }

    // PRIM MST
    int primMST() const {
        if (V == 0) return 0;
        vector<int> key(V, INT_MAX);
        vector<bool> inMST(V, false);
        using P = pair<int,int>;
        priority_queue<P, vector<P>, greater<P>> pq;

        key[0] = 0;
        pq.push({0, 0});
        int mstWeight = 0;

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            if (inMST[u]) continue;
            inMST[u] = true;
            mstWeight += key[u];

            for (auto& p : adj[u]) {
                int v = p.first;
                int weight = p.second;
                if (!inMST[v] && weight < key[v]) {
                    key[v] = weight;
                    pq.push({key[v], v});
                }
            }
        }
        return mstWeight;
    }

    // KRUSKAL MST (using Union-Find)
    int kruskalMST() const {
        vector<tuple<int, int, int>> edges; // {weight, u, v}

        for (int u = 0; u < V; u++) {
            for (auto& p : adj[u]) {
                if (u < p.first) // avoid duplicates
                    edges.push_back({p.second, u, p.first});
            }
        }

        sort(edges.begin(), edges.end());
        UnionFind uf(V);
        int mstWeight = 0;

        for (auto& e : edges) {
            int w, u, v;
            tie(w, u, v) = e;
            if (uf.find(u) != uf.find(v)) {
                uf.unite(u, v);
                mstWeight += w;
            }
        }
        return mstWeight;
    }

    int vertices() const { return V; }
};

// ==================== SORTING ALGORITHMS ====================

class Sorting {
public:
    static void quickSort(vector<int>& arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }

private:
    static int partition(vector<int>& arr, int low, int high) {
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return i + 1;
    }
};

// ==================== STRING SEARCH ALGORITHMS ====================

class StringSearch {
public:
    // KMP
    static vector<int> computeLPS(const string& pattern) {
        int m = (int)pattern.length();
        vector<int> lps(m, 0);
        int len = 0, i = 1;

        while (i < m) {
            if (pattern[i] == pattern[len]) {
                len++;
                lps[i] = len;
                i++;
            } else {
                if (len != 0)
                    len = lps[len - 1];
                else {
                    lps[i] = 0;
                    i++;
                }
            }
        }
        return lps;
    }

    static int KMP(const string& text, const string& pattern) {
        int n = (int)text.length(), m = (int)pattern.length();
        if (m == 0) return 0;
        vector<int> lps = computeLPS(pattern);
        int i = 0, j = 0;

        while (i < n) {
            if (pattern[j] == text[i]) {
                i++;
                j++;
            }
            if (j == m) return i - j;
            else if (i < n && pattern[j] != text[i]) {
                if (j != 0)
                    j = lps[j - 1];
                else
                    i++;
            }
        }
        return -1;
    }
};

// ==================== SHOPPING SYSTEM DOMAIN ====================

struct Product {
    int id;
    string name;
    string category;
    double price;
    int stock;
    int sellerId;

    Product() {}
    Product(int i, string n, string c, double p, int s, int sid)
        : id(i), name(std::move(n)), category(std::move(c)),
          price(p), stock(s), sellerId(sid) {}

    void display() const {
        cout << "ID: " << setw(3) << id
             << " | Name: " << setw(20) << left << name << right
             << " | Category: " << setw(12) << left << category << right
             << " | Price: $" << fixed << setprecision(2) << setw(7) << price
             << " | Stock: " << setw(4) << stock << "\n";
    }
};

struct Order {
    int orderId;
    int productId;
    int customerId;
    int quantity;
    string status;
    int deliveryLocation; // index in locations array
    int distance;         // distance from warehouse for priority

    Order() {}
    Order(int oid, int pid, int cid, int qty, int loc, int dist)
        : orderId(oid), productId(pid), customerId(cid),
          quantity(qty), status("Pending"),
          deliveryLocation(loc), distance(dist) {}

    void display() const {
        cout << "Order ID: " << setw(3) << orderId
             << " | Product ID: " << setw(3) << productId
             << " | Customer ID: " << setw(3) << customerId
             << " | Qty: " << setw(3) << quantity
             << " | Status: " << setw(10) << left << status << right
             << " | Distance: " << setw(3) << distance << " km\n";
    }
};

class ShoppingSystem {
private:
    vector<Product> products;
    vector<Order> orders;
    map<int, string> sellers;
    map<int, string> customers;
    map<int, string> deliveryPartners;

    // Locations for delivery partners (index -> real place name)
    vector<string> locations;
    Graph deliveryGraph;
    Trie productTrie;
    BST<int> productIdIndex;   // for fast product ID existence check
    AVLTree orderIdIndex;      // to show balanced indexing of orders
    MinHeap deliveryPriority;  // distance-based order priority
    int productIdCounter;
    int orderIdCounter;

    static string toLower(string s) {
        for (char& c : s) c = (char)tolower((unsigned char)c);
        return s;
    }

public:
    ShoppingSystem()
        : productIdCounter(1),
          orderIdCounter(1),
          locations({
              "Central Warehouse",
              "Downtown Market",
              "City Mall",
              "Tech Park",
              "Airport",
              "University Campus",
              "Old Town",
              "Suburban Hub"
          }),
          deliveryGraph((int)locations.size())
    {
        initializeDeliveryNetwork();
    }

    void initializeDeliveryNetwork() {
        // Create realistic delivery network with locations and distances (km)
        auto L = [&](int i){return i;};
        deliveryGraph.addEdge(L(0), L(1), 5);   // Warehouse - Downtown
        deliveryGraph.addEdge(L(0), L(2), 8);   // Warehouse - City Mall
        deliveryGraph.addEdge(L(1), L(2), 3);   // Downtown - City Mall
        deliveryGraph.addEdge(L(1), L(3), 6);   // Downtown - Tech Park
        deliveryGraph.addEdge(L(2), L(4), 10);  // City Mall - Airport
        deliveryGraph.addEdge(L(3), L(4), 7);   // Tech Park - Airport
        deliveryGraph.addEdge(L(2), L(5), 4);   // City Mall - University
        deliveryGraph.addEdge(L(5), L(6), 6);   // University - Old Town
        deliveryGraph.addEdge(L(6), L(7), 5);   // Old Town - Suburban Hub
        deliveryGraph.addEdge(L(0), L(7), 12);  // Warehouse - Suburban Hub
    }

    // ---------- Utility functions ----------

    void printLocations() const {
        printSubTitle("AVAILABLE DELIVERY LOCATIONS");
        for (int i = 0; i < (int)locations.size(); ++i) {
            cout << "  [" << i << "] " << locations[i] << "\n";
        }
    }

    void printPath(const vector<int>& parent, int dest) const {
        vector<int> path;
        int cur = dest;
        while (cur != -1) {
            path.push_back(cur);
            cur = parent[cur];
        }
        reverse(path.begin(), path.end());
        for (size_t i = 0; i < path.size(); ++i) {
            cout << locations[path[i]];
            if (i + 1 < path.size()) cout << " -> ";
        }
        cout << "\n";
    }

    // ---------- SELLER FUNCTIONS ----------

    void registerSeller(int id, const string& name) {
        sellers[id] = name;
        cout << "\n[+] Seller registered: " << name << " (ID: " << id << ")\n";
    }

    void addProduct(const string& name, const string& category,
                    double price, int stock, int sellerId) {
        Product p(productIdCounter++, name, category, price, stock, sellerId);
        products.push_back(p);
        productTrie.insert(toLower(name));
        productIdIndex.insert(p.id);
        cout << "\n[+] Product added successfully!\n";
        printSubTitle("PRODUCT DETAILS");
        p.display();
    }

    void viewSellerProducts(int sellerId) const {
        printSectionTitle("PRODUCTS BY SELLER " + to_string(sellerId));
        bool any = false;
        for (const auto& p : products) {
            if (p.sellerId == sellerId) {
                p.display();
                any = true;
            }
        }
        if (!any) cout << "(No products found for this seller.)\n";
    }

    void viewAllOrders() const {
        printSectionTitle("ALL ORDERS");
        if (orders.empty()) {
            cout << "(No orders yet)\n";
            return;
        }
        for (const auto& o : orders) {
            o.display();
        }
    }

    // ---------- CUSTOMER FUNCTIONS ----------

    void registerCustomer(int id, const string& name) {
        customers[id] = name;
        cout << "\n[+] Customer registered: " << name << " (ID: " << id << ")\n";
    }

    void searchProductsByNameSubstring(const string& query) const {
        printSectionTitle("SEARCH RESULTS (SUBSTRING USING KMP)");
        bool found = false;
        string q = toLower(query);
        for (const auto& p : products) {
            string nameLower = toLower(p.name);
            if (StringSearch::KMP(nameLower, q) != -1) {
                p.display();
                found = true;
            }
        }
        if (!found) cout << "No products found containing \"" << query << "\".\n";
    }

    void searchProductsByPrefix(const string& prefix) const {
        printSectionTitle("SEARCH RESULTS (PREFIX USING TRIE)");
        string pre = toLower(prefix);
        if (!productTrie.startsWith(pre)) {
            cout << "No product names start with \"" << prefix << "\".\n";
            return;
        }
        bool found = false;
        for (const auto& p : products) {
            string nameLower = toLower(p.name);
            if (nameLower.rfind(pre, 0) == 0) { // starts with
                p.display();
                found = true;
            }
        }
        if (!found) cout << "No products found (unexpected, trie says prefix exists).\n";
    }

    void displayAllProducts() const {
        printSectionTitle("ALL PRODUCTS");
        if (products.empty()) {
            cout << "(No products yet)\n";
            return;
        }
        for (const auto& p : products)
            p.display();
    }

    void sortProductsByPrice() const {
        if (products.empty()) {
            cout << "No products to sort.\n";
            return;
        }

        // Copy prices and sort using QuickSort
        vector<int> prices;
        for (const auto& p : products)
            prices.push_back((int)round(p.price * 100)); // store cents

        Sorting::quickSort(prices, 0, (int)prices.size() - 1);

        printSectionTitle("PRODUCTS SORTED BY PRICE (ASC, QUICKSORT)");
        vector<bool> printed(products.size(), false);
        for (int cents : prices) {
            double price = cents / 100.0;
            for (size_t i = 0; i < products.size(); ++i) {
                if (!printed[i] && fabs(products[i].price - price) < 1e-6) {
                    products[i].display();
                    printed[i] = true;
                    break;
                }
            }
        }
    }

    void placeOrder(int customerId, int productId, int quantity, int locationIdx) {
        if (locationIdx < 0 || locationIdx >= (int)locations.size()) {
            cout << "\n[!] Invalid delivery location.\n";
            return;
        }

        if (!productIdIndex.contains(productId)) {
            cout << "\n[!] Product ID " << productId << " does not exist.\n";
            return;
        }

        for (auto& p : products) {
            if (p.id == productId) {
                if (p.stock >= quantity) {
                    auto res = deliveryGraph.dijkstra(0); // 0 = Central Warehouse
                    vector<int>& dist = res.first;
                    int d = dist[locationIdx];
                    if (d == INT_MAX) {
                        cout << "\n[!] No delivery path to " << locations[locationIdx] << ".\n";
                        return;
                    }
                    Order o(orderIdCounter++, productId, customerId, quantity, locationIdx, d);
                    orders.push_back(o);
                    orderIdIndex.insert(o.orderId);
                    deliveryPriority.insert(d, (int)orders.size() - 1);
                    p.stock -= quantity;
                    cout << "\n[+] Order placed successfully!\n";
                    printSubTitle("ORDER SUMMARY");
                    o.display();
                    cout << "Delivery location: " << locations[locationIdx] << "\n";
                    cout << "Shortest distance from Warehouse: " << d << " km\n";
                    return;
                } else {
                    cout << "\n[!] Insufficient stock!\n";
                    return;
                }
            }
        }
        cout << "\n[!] Product not found!\n";
    }

    // ---------- DELIVERY PARTNER FUNCTIONS ----------

    void registerDeliveryPartner(int id, const string& name) {
        deliveryPartners[id] = name;
        cout << "\n[+] Delivery Partner registered: " << name << " (ID: " << id << ")\n";
    }

    void viewPendingOrders() const {
        printSectionTitle("PENDING ORDERS");
        bool any = false;
        for (const auto& o : orders) {
            if (o.status == "Pending") {
                o.display();
                cout << "  -> Delivery Location: " << locations[o.deliveryLocation] << "\n";
                any = true;
            }
        }
        if (!any) cout << "(No pending orders.)\n";
    }

    void calculateShortestPath(int start, int end) const {
        if (start < 0 || end < 0 || start >= (int)locations.size() || end >= (int)locations.size()) {
            cout << "\n[!] Invalid locations.\n";
            return;
        }

        printSectionTitle("SHORTEST DELIVERY ROUTE (DIJKSTRA)");
        cout << "From: " << locations[start] << "\n";
        cout << "To  : " << locations[end] << "\n";

        auto res = deliveryGraph.dijkstra(start);
        const vector<int>& dist = res.first;
        const vector<int>& parent = res.second;

        if (dist[end] != INT_MAX) {
            cout << "Shortest Distance: " << dist[end] << " km\n";
            cout << "Route: ";
            printPath(parent, end);
        } else {
            cout << "No path exists between these locations.\n";
        }
    }

    void updateOrderStatus(int orderId, const string& status) {
        for (auto& o : orders) {
            if (o.orderId == orderId) {
                o.status = status;
                cout << "\n[+] Order " << orderId << " status updated to: " << status << "\n";
                return;
            }
        }
        cout << "\n[!] Order not found!\n";
    }

    void processNextDeliveryByShortestDistance() {
        printSectionTitle("PROCESS NEXT DELIVERY (MIN-HEAP BY DISTANCE)");
        while (!deliveryPriority.isEmpty()) {
            auto top = deliveryPriority.extractMin();
            int dist = top.first;
            int idx = top.second;
            if (idx < 0 || idx >= (int)orders.size()) continue;

            Order& o = orders[idx];
            if (o.status != "Pending") continue;

            cout << "Next order to deliver (closest, " << dist << " km):\n";
            o.display();
            cout << "Delivery location: " << locations[o.deliveryLocation] << "\n";
            cout << "\nMark as Shipped? (1 = Yes, 0 = No): ";
            int ch;
            cin >> ch;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (ch == 1) {
                o.status = "Shipped";
                cout << "\n[+] Order shipped.\n";
            } else {
                cout << "\n[i] Order left as Pending.\n";
            }
            return;
        }
        cout << "(No pending orders in priority queue.)\n";
    }

    void showNetworkMSTInfo() const {
        printSectionTitle("DELIVERY NETWORK MST INFO (PRIM & KRUSKAL + UNION-FIND)");
        int primW = deliveryGraph.primMST();
        int kruskalW = deliveryGraph.kruskalMST();
        cout << "Total road length using Prim's MST   : " << primW << " km\n";
        cout << "Total road length using Kruskal's MST: " << kruskalW << " km\n";
    }

    // ---------- DIAGNOSTIC / DSA DEMO FUNCTIONS ----------

    void demonstrateDataStructures() {
        printSectionTitle("DEMONSTRATING DATA STRUCTURES & ALGORITHMS");

        // Linked List
        printSubTitle("1. LINKED LIST (RECENTLY VIEWED PRODUCT IDS)");
        LinkedList<int> ll;
        if (!products.empty()) {
            for (size_t i = 0; i < products.size() && i < 3; ++i)
                ll.insertBack(products[i].id);
        } else {
            // Simulate some IDs if no products yet
            ll.insertBack(1);
            ll.insertBack(2);
            ll.insertBack(3);
        }
        ll.display();

        // Stack
        printSubTitle("2. STACK (UNDO LAST 3 SIMPLE OPERATIONS)");
        StackArr<string> st;
        st.push("Add Product");
        st.push("Place Order");
        st.push("Update Status");
        while (!st.isEmpty()) {
            cout << "Undo operation: " << st.pop() << "\n";
        }

        // Queue
        printSubTitle("3. QUEUE (SUPPORT TICKET QUEUE)");
        QueueArr<int> q;
        q.enqueue(101);
        q.enqueue(102);
        q.enqueue(103);
        while (!q.isEmpty()) {
            cout << "Serving support ticket: " << q.dequeue() << "\n";
        }

        // BST
        printSubTitle("4. BST INORDER TRAVERSAL OF PRODUCT IDS");
        if (!products.empty()) {
            BST<int> tempBST;
            for (const auto& p : products) tempBST.insert(p.id);
            tempBST.printInorder();
        } else {
            productIdIndex.printInorder();
        }

        // AVL
        printSubTitle("5. AVL TREE INORDER TRAVERSAL OF ORDER IDS");
        orderIdIndex.printInorder();

        // Graph DFS/BFS
        printSubTitle("6. GRAPH TRAVERSAL FROM CENTRAL WAREHOUSE (INDEX 0)");
        cout << "DFS order: ";
        deliveryGraph.DFS(0);
        cout << "BFS order: ";
        deliveryGraph.BFS(0);

        // MST info (uses Union-Find via Kruskal internally)
        printSubTitle("7. DELIVERY NETWORK MINIMUM SPANNING TREE");
        showNetworkMSTInfo();

        cout << "\n(Above demos and system features showcase: Linked List, Stack, Queue,\n"
                "BST, AVL Tree, Graph + DFS/BFS, Dijkstra shortest path, MST (Prim/Kruskal\n"
                "with Union-Find), Trie, KMP string search, QuickSort for prices, and\n"
                "a Min-Heap for delivery priority.)\n";
    }
};

// ==================== INTERACTIVE FRONTEND (CONSOLE) ====================

void sellerMenu(ShoppingSystem& system) {
    printSectionTitle("SELLER PORTAL");
    int sellerId;
    string sellerName;
    cout << "Enter Seller ID: ";
    cin >> sellerId;
    cout << "Enter Seller Name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, sellerName);
    system.registerSeller(sellerId, sellerName);

    while (true) {
        printSubTitle("SELLER MENU");
        cout << "1. Add Product\n";
        cout << "2. View My Products\n";
        cout << "3. View All Orders\n";
        cout << "4. Back to Main Menu\n";
        cout << "Enter choice: ";
        int sellerChoice;
        cin >> sellerChoice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (sellerChoice == 1) {
            string name, category;
            double price;
            int stock;
            cout << "\n--- ADD NEW PRODUCT ---\n";
            cout << "Product Name: ";
            getline(cin, name);
            cout << "Category    : ";
            getline(cin, category);
            cout << "Price       : ";
            cin >> price;
            cout << "Stock       : ";
            cin >> stock;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system.addProduct(name, category, price, stock, sellerId);
        } else if (sellerChoice == 2) {
            system.viewSellerProducts(sellerId);
        } else if (sellerChoice == 3) {
            system.viewAllOrders();
        } else if (sellerChoice == 4) {
            cout << "\n[<-] Returning to Main Menu...\n";
            break;
        } else {
            cout << "\n[!] Invalid choice.\n";
        }
    }
}

void customerMenu(ShoppingSystem& system) {
    printSectionTitle("CUSTOMER PORTAL");
    int customerId;
    string customerName;
    cout << "Enter Customer ID: ";
    cin >> customerId;
    cout << "Enter Customer Name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, customerName);
    system.registerCustomer(customerId, customerName);

    while (true) {
        printSubTitle("CUSTOMER MENU");
        cout << "1. View All Products\n";
        cout << "2. Search Products (substring, KMP)\n";
        cout << "3. Search Products (name prefix, Trie)\n";
        cout << "4. Sort Products by Price (QuickSort)\n";
        cout << "5. Place Order\n";
        cout << "6. Back to Main Menu\n";
        cout << "Enter choice: ";
        int custChoice;
        cin >> custChoice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (custChoice == 1) {
            system.displayAllProducts();
        } else if (custChoice == 2) {
            string query;
            cout << "\nEnter product name substring to search: ";
            getline(cin, query);
            system.searchProductsByNameSubstring(query);
        } else if (custChoice == 3) {
            string prefix;
            cout << "\nEnter product name prefix: ";
            getline(cin, prefix);
            system.searchProductsByPrefix(prefix);
        } else if (custChoice == 4) {
            system.sortProductsByPrice();
        } else if (custChoice == 5) {
            int productId, quantity, locationIdx;
            cout << "\n--- PLACE ORDER ---\n";
            cout << "Enter Product ID : ";
            cin >> productId;
            cout << "Enter Quantity   : ";
            cin >> quantity;
            system.printLocations();
            cout << "Enter Location ID: ";
            cin >> locationIdx;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system.placeOrder(customerId, productId, quantity, locationIdx);
        } else if (custChoice == 6) {
            cout << "\n[<-] Returning to Main Menu...\n";
            break;
        } else {
            cout << "\n[!] Invalid choice.\n";
        }
    }
}

void deliveryPartnerMenu(ShoppingSystem& system) {
    printSectionTitle("DELIVERY PARTNER PORTAL");
    int partnerId;
    string partnerName;
    cout << "Enter Partner ID: ";
    cin >> partnerId;
    cout << "Enter Partner Name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, partnerName);
    system.registerDeliveryPartner(partnerId, partnerName);

    while (true) {
        printSubTitle("DELIVERY PARTNER MENU");
        cout << "1. View Pending Orders\n";
        cout << "2. Calculate Shortest Delivery Path (Dijkstra)\n";
        cout << "3. Update Order Status\n";
        cout << "4. Process Next Delivery by Shortest Distance (Min-Heap)\n";
        cout << "5. View Delivery Network MST Info (Prim/Kruskal)\n";
        cout << "6. Back to Main Menu\n";
        cout << "Enter choice: ";
        int delChoice;
        cin >> delChoice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (delChoice == 1) {
            system.viewPendingOrders();
        } else if (delChoice == 2) {
            int start, end;
            system.printLocations();
            cout << "\nEnter Start Location ID: ";
            cin >> start;
            cout << "Enter End   Location ID: ";
            cin >> end;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system.calculateShortestPath(start, end);
        } else if (delChoice == 3) {
            int orderId;
            string status;
            cout << "\nEnter Order ID: ";
            cin >> orderId;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter Status (Pending/Shipped/Delivered): ";
            getline(cin, status);
            system.updateOrderStatus(orderId, status);
        } else if (delChoice == 4) {
            system.processNextDeliveryByShortestDistance();
        } else if (delChoice == 5) {
            system.showNetworkMSTInfo();
        } else if (delChoice == 6) {
            cout << "\n[<-] Returning to Main Menu...\n";
            break;
        } else {
            cout << "\n[!] Invalid choice.\n";
        }
    }
}

// ==================== MAIN FUNCTION ====================

int main() {

    ShoppingSystem system;

    printSeparator();

    while (true) {
        printSubTitle("MAIN MENU");
        cout << "1. Seller Login\n";
        cout << "2. Customer Login\n";
        cout << "3. Delivery Partner Login\n";
        cout << "4. Demonstrate Data Structures & Algorithms\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        int choice;
        if (!(cin >> choice)) {
            cout << "\n[!] Invalid input. Exiting.\n";
            break;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) {
            sellerMenu(system);
        } else if (choice == 2) {
            customerMenu(system);
        } else if (choice == 3) {
            deliveryPartnerMenu(system);
        } else if (choice == 4) {
            system.demonstrateDataStructures();
        } else if (choice == 5) {
            cout << "\nThank you for using the Online Shopping System!\n";
            printSeparator('=');
            break;
        } else {
            cout << "\n[!] Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
