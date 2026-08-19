#include "mst_io.hpp"
#include <fstream>
#include <iostream>

bool load_mst_graph(const std::string &path, CSRGraph &g, int &undirected_E) {
    std::ifstream in(path);
    if (!in) {
        std::cerr << "Error: cannot open input file: " << path << "\n";
        return false;
    }

    int V, E;
    if (!(in >> V >> E) || V <= 0) {
        std::cerr << "Error: malformed header in " << path << "\n";
        return false;
    }

    std::vector<int> degree(V, 0);
    std::vector<std::vector<int>> nbr(V), wt(V);

    for (int line = 0; line < V; line++) {
        int u, d;
        if (!(in >> u >> d) || u < 0 || u >= V) {
            std::cerr << "Error: malformed adjacency line in " << path << "\n";
            return false;
        }
        degree[u] = d;
        nbr[u].resize(d);
        wt[u].resize(d);
        for (int j = 0; j < d; j++) {
            if (!(in >> nbr[u][j] >> wt[u][j]) || nbr[u][j] < 0 || nbr[u][j] >= V) {
                std::cerr << "Error: malformed neighbour entry for vertex " << u << "\n";
                return false;
            }
        }
    }

    // A valid MST input with V > 1 cannot contain an isolated vertex.
    if (V > 1) {
        for (int u = 0; u < V; u++) {
            if (degree[u] == 0) {
                std::cerr << "Error: vertex " << u << " is isolated; MST input must be connected\n";
                return false;
            }
        }
    }

    g = adjlist_to_csr(V, degree, nbr, wt);
    undirected_E = g.E / 2;                   // each undirected edge stored twice
    return true;
}
