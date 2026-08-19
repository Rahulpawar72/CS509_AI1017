#pragma once
#include "csr.hpp"
#include <vector>

struct MSTEdge {
    int u, v;
    int w;
};

struct MSTResult {
    std::vector<MSTEdge> edges;
    long long total_weight = 0;   // long long accumulator, even though each weight is int
    double time_ms = 0.0;
};

// Runs Kruskal's algorithm on an already-built CSR graph.
// Edge-list extraction from the CSR and the sort by weight happen inside
// this call and are counted as part of Kruskal's measured execution time.
MSTResult kruskal_mst(const CSRGraph &g);
