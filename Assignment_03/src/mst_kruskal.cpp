#include "mst_kruskal.hpp"
#include <algorithm>
#include <chrono>
#include <numeric>

namespace {

// Disjoint Set Union (Union-Find) with path compression + union by rank.
struct DSU {
    std::vector<int> parent, rnk;
    explicit DSU(int n) : parent(n), rnk(n, 0) {
        std::iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        while (parent[x] != x) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }
    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (rnk[a] < rnk[b]) std::swap(a, b);
        parent[b] = a;
        if (rnk[a] == rnk[b]) rnk[a]++;
        return true;
    }
};

}  // namespace

MSTResult kruskal_mst(const CSRGraph &g) {
    MSTResult result;
    auto t0 = std::chrono::high_resolution_clock::now();

    // Extract each undirected edge exactly once (u < v) from the CSR arrays.
    std::vector<MSTEdge> edges;
    edges.reserve(static_cast<size_t>(g.E));
    for (int u = 0; u < g.V; u++) {
        for (int k = g.row_ptr[u]; k < g.row_ptr[u + 1]; k++) {
            int v = g.col_idx[k];
            if (v > u) edges.push_back({u, v, g.weight[k]});
        }
    }

    std::sort(edges.begin(), edges.end(),
              [](const MSTEdge &a, const MSTEdge &b) { return a.w < b.w; });

    DSU dsu(g.V);
    result.edges.reserve(g.V > 0 ? static_cast<size_t>(g.V - 1) : 0);
    for (const auto &e : edges) {
        if (static_cast<int>(result.edges.size()) == g.V - 1) break;
        if (dsu.unite(e.u, e.v)) {
            result.edges.push_back(e);
            result.total_weight += e.w;
        }
    }

    auto t1 = std::chrono::high_resolution_clock::now();
    result.time_ms = std::chrono::duration<double, std::milli>(t1 - t0).count();
    return result;
}
