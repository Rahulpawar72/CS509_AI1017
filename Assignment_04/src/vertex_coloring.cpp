#include "vertex_coloring.hpp"

#include <algorithm>
#include <chrono>
#include <numeric>

ColoringResult greedy_coloring(const CSRGraph &graph)
{
    ColoringResult result;

    auto start_time = std::chrono::high_resolution_clock::now();

    // Store vertices in descending order of degree.
    std::vector<int> vertices(graph.V);

    std::iota(vertices.begin(), vertices.end(), 0);

    std::sort(vertices.begin(), vertices.end(),
        [&](int a, int b)
        {
            int degree_a = graph.row_ptr[a + 1] - graph.row_ptr[a];
            int degree_b = graph.row_ptr[b + 1] - graph.row_ptr[b];

            // Higher degree comes first.
            if (degree_a != degree_b)
                return degree_a > degree_b;

            // If degrees are equal, smaller vertex number comes first.
            return a < b;
        }
    );

    // -1 means the vertex has not been colored yet.
    result.colors.assign(graph.V, -1);

    // Stores which vertex last blocked each color.
    std::vector<int> blocked_color(graph.V, -1);

    // Color each vertex.
    for (int vertex : vertices)
    {
        int start = graph.row_ptr[vertex];
        int end = graph.row_ptr[vertex + 1];

        // Mark the colors already used by this vertex's neighbors.
        for (int edge = start; edge < end; edge++)
        {
            int neighbor = graph.col_idx[edge];
            int neighbor_color = result.colors[neighbor];

            if (neighbor_color != -1)
                blocked_color[neighbor_color] = vertex;
        }

        // Find the first color not used by any neighbor.
        int color = 0;

        while (color < graph.V &&
               blocked_color[color] == vertex)
        {
            color++;
        }

        result.colors[vertex] = color;

        // Keep track of the number of colors used.
        result.colors_used =
            std::max(result.colors_used, color + 1);
    }

    // Check whether the coloring is valid.
    result.valid = true;

    for (int vertex = 0; vertex < graph.V; vertex++)
    {
        for (int edge = graph.row_ptr[vertex];
             edge < graph.row_ptr[vertex + 1];
             edge++)
        {
            int neighbor = graph.col_idx[edge];

            if (result.colors[vertex] == result.colors[neighbor])
            {
                result.valid = false;
            }
        }
    }

    auto finish_time = std::chrono::high_resolution_clock::now();

    result.time_ms =
        std::chrono::duration<double, std::milli>(
            finish_time - start_time
        ).count();

    return result;
}