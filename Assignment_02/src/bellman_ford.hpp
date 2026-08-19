#ifndef BELLMAN_FORD_HPP
#define BELLMAN_FORD_HPP

#include <climits>
#include <vector>
#include "csr.hpp"

constexpr long long BF_INF = LLONG_MAX / 4;

// Runs Bellman-Ford from `source` on CSR graph g.
// dist is resized to g.V entries.
// The V-1 relaxation passes AND the extra negative-cycle check pass are
// both part of this call, so timing the call alone satisfies Section 10.
void run_bellman_ford(const CSRGraph &g, int source,
                       std::vector<long long> &dist, bool &neg_cycle);

#endif
