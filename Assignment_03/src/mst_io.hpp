#ifndef MST_IO_HPP
#define MST_IO_HPP

#include <string>
#include "csr.hpp"

// Reads the MST adjacency-list file format (Section 5.1):
//   V E
//   u0 degree n1 w1 n2 w2 ...
//   ...
// (undirected: every edge already appears in both endpoints' lists)
//
// Builds the per-vertex degree/neighbour/weight vectors and converts them
// to CSR via Assignment 1's adjlist_to_csr() -- the conversion logic itself
// is NOT reimplemented here, only reused. Pure file I/O / parsing, so this
// is setup work and must never be timed.
//
// undirected_E is set to the number of distinct undirected edges (g.E / 2),
// for reporting -- g.E itself counts each edge from both endpoints.
bool load_mst_graph(const std::string &path, CSRGraph &g, int &undirected_E);

#endif
