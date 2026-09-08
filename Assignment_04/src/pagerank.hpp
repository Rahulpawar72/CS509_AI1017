#ifndef ASSIGNMENT_04_PAGERANK_HPP
#define ASSIGNMENT_04_PAGERANK_HPP

#include "csr.hpp"
#include "graph_io.hpp"
#include <vector>

struct PageRankResult {
    std::vector<double> ranks;
    int iterations = 0;
    bool converged = false;
    double time_ms = 0.0;
};

PageRankResult page_rank(const CSRGraph &graph, const PageRankSettings &settings);

#endif