// Random connected weighted undirected graph generator for MST test inputs.
//
// Usage: graph_gen <V> <E> <output_file> [seed]
//
// Guarantees connectivity by first building a random spanning tree
// (V-1 edges), then adding random extra edges (avoiding duplicates and
// self-loops) until E edges exist or the graph is dense enough that no
// more distinct edges are available.
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <random>
#include <unordered_set>
#include <vector>

int main(int argc, char **argv) {
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <V> <E> <output_file> [seed]\n";
        return 1;
    }

    long long V = std::atoll(argv[1]);
    long long E = std::atoll(argv[2]);
    std::string outPath = argv[3];
    unsigned seed = argc > 4 ? static_cast<unsigned>(std::atoll(argv[4])) : 42u;

    if (V < 1) {
        std::cerr << "V must be >= 1\n";
        return 1;
    }

    long long maxE = V * (V - 1) / 2;
    if (E < V - 1) E = V - 1;   // must be connected
    if (E > maxE) E = maxE;

    std::mt19937_64 rng(seed);
    std::uniform_int_distribution<long long> weightDist(1, 100);
    std::uniform_int_distribution<long long> vDist(0, V - 1);

    std::unordered_set<long long> used;
    used.reserve(static_cast<size_t>(E * 2));
    std::vector<std::vector<std::pair<long long, long long>>> adj(V);

    auto edgeKey = [V](long long a, long long b) { return a * V + b; };

    auto addEdge = [&](long long u, long long v, long long w) -> bool {
        if (u == v) return false;
        if (u > v) std::swap(u, v);
        long long key = edgeKey(u, v);
        if (!used.insert(key).second) return false;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
        return true;
    };

    // 1) Random spanning tree -> guarantees the graph is connected.
    std::vector<long long> order(V);
    for (long long i = 0; i < V; i++) order[i] = i;
    std::shuffle(order.begin(), order.end(), rng);
    for (long long i = 1; i < V; i++) {
        std::uniform_int_distribution<long long> pick(0, i - 1);
        long long j = pick(rng);
        addEdge(order[i], order[j], weightDist(rng));
    }

    // 2) Fill in extra random edges up to E, sparse (typically E ~ 2V-4V).
    long long edgesSoFar = V - 1;
    long long maxAttempts = std::max<long long>(E * 20, 100000);
    long long attempts = 0;
    while (edgesSoFar < E && attempts < maxAttempts) {
        long long u = vDist(rng), v = vDist(rng);
        if (addEdge(u, v, weightDist(rng))) edgesSoFar++;
        attempts++;
    }

    std::ofstream fout(outPath);
    if (!fout) {
        std::cerr << "Cannot open output file: " << outPath << "\n";
        return 1;
    }
    fout << V << " " << edgesSoFar << "\n";
    for (long long u = 0; u < V; u++) {
        fout << u << " " << adj[u].size();
        for (auto &pr : adj[u]) fout << " " << pr.first << " " << pr.second;
        fout << "\n";
    }

    std::cerr << "Wrote " << outPath << " : V=" << V << " E=" << edgesSoFar << "\n";
    return 0;
}
