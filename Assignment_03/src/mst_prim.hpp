#pragma once
#include "csr.hpp"
#include "mst_kruskal.hpp"  // reuse MSTEdge / MSTResult

// Runs Prim's algorithm on an already-built CSR graph, starting from
// vertex 0 (as recommended for reproducibility), using a min-priority queue.
MSTResult prim_mst(const CSRGraph &g);
