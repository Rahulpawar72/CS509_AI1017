#ifndef ASSIGNMENT_04_VERTEX_COLORING_HPP
#define ASSIGNMENT_04_VERTEX_COLORING_HPP

#include "csr.hpp"
#include <vector>

struct ColoringResult {
    std::vector<int> colors;
    int colors_used = 0;
    bool valid = false;
    double time_ms = 0.0;
};

ColoringResult greedy_coloring(const CSRGraph &graph);

#endif