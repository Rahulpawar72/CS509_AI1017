#include "mst_prim.hpp"
#include <chrono>
#include <limits>
#include <queue>
#include <vector>

MSTResult prim_mst(const CSRGraph &g) {
    MSTResult result;
    auto t0 = std::chrono::high_resolution_clock::now();

    const int V = g.V;
    std::vector<char> in_tree(V, 0);
    std::vector<int> key(V, std::numeric_limits<int>::max());
    std::vector<int> parent(V, -1);

    using QItem = std::pair<int, int>;  // {edge weight, vertex}
    std::priority_queue<QItem, std::vector<QItem>, std::greater<QItem>> pq;

    const int start = 0;  // recommended start vertex, for reproducibility
    key[start] = 0;
    pq.push({0, start});

    int included = 0;
    while (!pq.empty() && included < V) {
        QItem current = pq.top();
        pq.pop();
        const int w = current.first;
        const int u = current.second;
        if (in_tree[u]) continue;  // stale entry
        in_tree[u] = 1;
        included++;
        if (parent[u] != -1) {
            result.edges.push_back({parent[u], u, w});
            result.total_weight += w;
        }
        for (int k = g.row_ptr[u]; k < g.row_ptr[u + 1]; k++) {
            int v = g.col_idx[k];
            int wt = g.weight[k];
            if (!in_tree[v] && wt < key[v]) {
                key[v] = wt;
                parent[v] = u;
                pq.push({wt, v});
            }
        }
    }

    auto t1 = std::chrono::high_resolution_clock::now();
    result.time_ms = std::chrono::duration<double, std::milli>(t1 - t0).count();
    return result;
}
