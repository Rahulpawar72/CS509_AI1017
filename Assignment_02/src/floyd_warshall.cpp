#include "floyd_warshall.hpp"
#include <fstream>

bool load_fw_graph(const std::string &path, std::vector<long long> &dist, int &V) {
    std::ifstream in(path);
    if (!in) return false;

    int v;
    if (!(in >> v) || v <= 0) return false;

    dist.assign((size_t)v * (size_t)v, 0);
    std::string tok;
    for (int i = 0; i < v * v; i++) {
        if (!(in >> tok)) return false;
        dist[i] = (tok == "INF") ? FW_INF : std::stoll(tok);
    }
    V = v;
    return true;
}

void run_floyd_warshall(std::vector<long long> &dist, int V, bool &neg_cycle) {
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            long long dik = dist[i * V + k];
            if (dik >= FW_INF) continue;
            for (int j = 0; j < V; j++) {
                long long dkj = dist[k * V + j];
                if (dkj >= FW_INF) continue;
                long long nd = dik + dkj;
                if (nd < dist[i * V + j]) dist[i * V + j] = nd;
            }
        }
    }
    neg_cycle = false;
    for (int i = 0; i < V; i++)
        if (dist[i * V + i] < 0) { neg_cycle = true; break; }
}
