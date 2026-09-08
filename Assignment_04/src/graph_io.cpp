#include "graph_io.hpp"

#include <fstream>
#include <iostream>
#include <vector>

namespace {

int count_edges(const std::vector<int> &degree)
{
    int total = 0;
    for (int d : degree) total += d;
    return total;
}

bool has_vertex(const std::vector<int> &list, int vertex)
{
    for (int v : list)
        if (v == vertex) return true;
    return false;
}

bool read_graph(const std::string &path, CSRGraph &graph,
                int &edge_count, bool undirected)
{
    std::ifstream file(path);

    if (!file)
    {
        std::cerr << "Cannot open file\n";
        return false;
    }

    int V;
    if (!(file >> V >> edge_count) || V <= 0 || edge_count < 0)
        return false;

    std::vector<int> degree(V);
    std::vector<std::vector<int>> neighbours(V);
    std::vector<std::vector<int>> weights(V);

    for (int i = 0; i < V; i++)
    {
        int vertex, count;
        file >> vertex >> count;

        if (vertex < 0 || vertex >= V || count < 0)
            return false;

        degree[vertex] = count;
        neighbours[vertex].resize(count);
        weights[vertex].assign(count, 0);

        for (int j = 0; j < count; j++)
        {
            file >> neighbours[vertex][j];

            if (neighbours[vertex][j] < 0 ||
                neighbours[vertex][j] >= V ||
                neighbours[vertex][j] == vertex)
                return false;
        }
    }

    int edges = count_edges(degree);

    if (undirected && edges != 2 * edge_count)
        return false;

    if (!undirected && edges != edge_count)
        return false;

    if (undirected)
    {
        for (int v = 0; v < V; v++)
            for (int n : neighbours[v])
                if (!has_vertex(neighbours[n], v))
                    return false;
    }

    graph = adjlist_to_csr(V, degree, neighbours, weights);
    return true;
}

} // namespace


bool load_coloring_graph(const std::string &path,
                         CSRGraph &graph,
                         int &edges)
{
    return read_graph(path, graph, edges, true);
}


bool load_pagerank_graph(const std::string &path,
                         CSRGraph &graph,
                         PageRankSettings &settings)
{
    int edges;

    if (!read_graph(path, graph, edges, false))
        return false;

    std::ifstream file(path);

    int V, ignored;
    file >> V >> ignored;

    // Skip adjacency list.
    for (int i = 0; i < V; i++)
    {
        int vertex, count;
        file >> vertex >> count;

        for (int j = 0; j < count; j++)
            file >> ignored;
    }

    std::string label;

    file >> label >> settings.damping;
    if (label != "DAMPING" ||
        settings.damping <= 0 || settings.damping >= 1)
        return false;

    file >> label >> settings.tolerance;
    if (label != "TOLERANCE" || settings.tolerance <= 0)
        return false;

    file >> label >> settings.max_iterations;
    if (label != "MAX_ITERATIONS" ||
        settings.max_iterations <= 0)
        return false;

    return true;
}