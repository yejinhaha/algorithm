#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

class UnionFind {
public:
    UnionFind(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; ++i) parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    bool unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            }
            else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            }
            else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
            return true;
        }
        return false;
    }

private:
    vector<int> parent, rank;
};

vector<Edge> kruskalMST(int n, vector<Edge>& edges) {
    sort(edges.begin(), edges.end());
    UnionFind uf(n);
    vector<Edge> mst;
    for (const Edge& edge : edges) {
        if (uf.unite(edge.u, edge.v)) {
            mst.push_back(edge);
            if (mst.size() == n - 1) break;
        }
    }
    return mst;
}

int main() {
    // Define the edges of the graph (vertex pairs and weights)
    vector<Edge> edges = {
        {0, 1, 8}, {0, 3, 2}, {0, 4, 4}, {1, 2, 1}, {1, 5, 2},
        {1, 3, 4}, {2, 5, 1}, {3, 4, 3}, {3, 5, 7}, {4, 5, 9}
    };

    auto start = high_resolution_clock::now();

    vector<Edge> mst = kruskalMST(6, edges);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Minimum Spanning Tree Edges:\n";
    for (const Edge& edge : mst) {
        cout << "(" << edge.u << ", " << edge.v << ", " << edge.weight << ")\n";
    }

    cout << "Running time: " << duration.count() << " microseconds\n";
    return 0;
}
