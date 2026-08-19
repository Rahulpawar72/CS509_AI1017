#ifndef FLOYD_WARSHALL_HPP
#define FLOYD_WARSHALL_HPP

#include <climits>
#include <string>
#include <vector>

constexpr long long FW_INF = LLONG_MAX / 4;

// Loads the dense V x V matrix described in Section 6.1 ("INF" or an int
// per cell). Fills a flattened row-major `dist` array of length V*V.
// Returns false on any malformed/missing file.
bool load_fw_graph(const std::string &path, std::vector<long long> &dist, int &V);

// Runs Floyd-Warshall in place on the flattened V x V matrix `dist`.
// The diagonal check for negative cycles is part of this same call.
void run_floyd_warshall(std::vector<long long> &dist, int V, bool &neg_cycle);

#endif
