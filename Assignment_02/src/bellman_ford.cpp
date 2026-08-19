#include "bellman_ford.hpp"

void run_bellman_ford(const CSRGraph &g, int source,
                       std::vector<long long> &dist, bool &neg_cycle) {
    int V = g.V;
    dist.assign(V, BF_INF);
    dist[source] = 0;

    // V-1 relaxation passes over every edge
    for (int iter = 0; iter < V - 1; iter++) {
        bool changed = false;
        for (int u = 0; u < V; u++) {
            if (dist[u] >= BF_INF) continue;
            for (int idx = g.row_ptr[u]; idx < g.row_ptr[u + 1]; idx++) {
                int v = g.col_idx[idx];
                long long nd = dist[u] + g.weight[idx];
                if (nd < dist[v]) { dist[v] = nd; changed = true; }
            }
        }
        if (!changed) break; // converged early
    }

    // Extra pass: any further relaxation means a negative cycle is reachable
    neg_cycle = false;
    for (int u = 0; u < V && !neg_cycle; u++) {
        if (dist[u] >= BF_INF) continue;
        for (int idx = g.row_ptr[u]; idx < g.row_ptr[u + 1]; idx++) {
            int v = g.col_idx[idx];
            if (dist[u] + g.weight[idx] < dist[v]) { neg_cycle = true; break; }
        }
    }
}
