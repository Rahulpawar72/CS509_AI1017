#include "pagerank.hpp"

#include <chrono>
#include <cmath>

PageRankResult page_rank(const CSRGraph &graph,
                         const PageRankSettings &settings)
{
    PageRankResult result;
    auto start_time = std::chrono::high_resolution_clock::now();

    // Initial rank for every vertex.
    double initial_rank = 1.0 / graph.V;
    result.ranks.assign(graph.V, initial_rank);

    std::vector<double> new_ranks(graph.V);

    for (int iteration = 1;
         iteration <= settings.max_iterations;
         iteration++)
    {
        // Random jump part.
        double random_jump =
            (1.0 - settings.damping) / graph.V;

        std::fill(new_ranks.begin(), new_ranks.end(), random_jump);

        // Find rank from dangling vertices.
        double dangling_rank = 0.0;

        for (int vertex = 0; vertex < graph.V; vertex++)
        {
            int start = graph.row_ptr[vertex];
            int end = graph.row_ptr[vertex + 1];
            int edges = end - start;

            if (edges == 0)
            {
                dangling_rank += result.ranks[vertex];
                continue;
            }

            double rank_per_edge =
                settings.damping * result.ranks[vertex] / edges;

            for (int edge = start; edge < end; edge++)
            {
                int destination = graph.col_idx[edge];
                new_ranks[destination] += rank_per_edge;
            }
        }

        // Distribute dangling rank and check convergence.
        double dangling_share =
            settings.damping * dangling_rank / graph.V;

        double change = 0.0;

        for (int vertex = 0; vertex < graph.V; vertex++)
        {
            new_ranks[vertex] += dangling_share;
            change += std::abs(
                new_ranks[vertex] - result.ranks[vertex]);
        }

        result.ranks.swap(new_ranks);
        result.iterations = iteration;

        if (change <= settings.tolerance)
        {
            result.converged = true;
            break;
        }
    }

    auto finish_time = std::chrono::high_resolution_clock::now();

    result.time_ms =
        std::chrono::duration<double, std::milli>(
            finish_time - start_time).count();

    return result;
}