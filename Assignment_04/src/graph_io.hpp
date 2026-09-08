#ifndef ASSIGNMENT_04_GRAPH_IO_HPP
#define ASSIGNMENT_04_GRAPH_IO_HPP

#include "csr.hpp"
#include <string>

struct PageRankSettings {
    double damping = 0.85;
    double tolerance = 0.0001;
    int max_iterations = 100;
};

bool load_coloring_graph(const std::string &path, CSRGraph &graph,
                         int &undirected_edges);
bool load_pagerank_graph(const std::string &path, CSRGraph &graph,
                         PageRankSettings &settings);

#endif