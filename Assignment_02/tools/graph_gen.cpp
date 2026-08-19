// Random test-file generator for Bellman-Ford / Floyd-Warshall.
// Optional utility -- not part of the main program or its menu.
//
// Usage:
//   graphgen bf <V> <E> <outfile> [source]   -> weighted directed adjacency list
//   graphgen fw <V> <density> <outfile>      -> dense V x V matrix (density in 0..1)
//
// Weights are always non-negative (1..20), so no negative-cycle check is
// needed to guarantee validity at any scale.
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

static std::mt19937 rng(std::random_device{}());

static int rand_weight() {
    static std::uniform_int_distribution<int> d(1, 20);
    return d(rng);
}

static void gen_bf(int V, int E, const std::string &outfile, int source) {
    std::uniform_int_distribution<int> pick(0, V - 1);
    std::vector<int> degree(V, 0);
    std::vector<std::vector<std::pair<int, int>>> adj(V);

    for (int i = 0; i < E; i++) {
        int u = pick(rng), v = pick(rng);
        while (v == u) v = pick(rng);
        adj[u].push_back({v, rand_weight()});
        degree[u]++;
    }

    std::ofstream f(outfile);
    f << V << " " << E << "\n";
    for (int u = 0; u < V; u++) {
        f << u << " " << degree[u];
        for (auto &nbr : adj[u]) f << " " << nbr.first << " " << nbr.second;
        f << "\n";
    }
    f << "SOURCE " << source << "\n";
}

static void gen_fw(int V, double density, const std::string &outfile) {
    std::uniform_real_distribution<double> coin(0.0, 1.0);
    std::ofstream f(outfile);
    f << V << "\n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i == j) f << 0;
            else if (coin(rng) < density) f << rand_weight();
            else f << "INF";
            f << (j == V - 1 ? '\n' : ' ');
        }
    }
}

int main(int argc, char **argv) {
    if (argc < 4) {
        std::cerr << "Usage:\n"
                  << "  " << argv[0] << " bf <V> <E> <outfile> [source]\n"
                  << "  " << argv[0] << " fw <V> <density> <outfile>\n";
        return 1;
    }
    std::string mode = argv[1];
    if (mode == "bf") {
        int V = std::stoi(argv[2]), E = std::stoi(argv[3]);
        std::string out = argv[4];
        int source = (argc > 5) ? std::stoi(argv[5]) : 0;
        gen_bf(V, E, out, source);
    } else if (mode == "fw") {
        int V = std::stoi(argv[2]);
        double density = std::stod(argv[3]);
        std::string out = argv[4];
        gen_fw(V, density, out);
    } else {
        std::cerr << "Unknown mode '" << mode << "'\n";
        return 1;
    }
    return 0;
}
