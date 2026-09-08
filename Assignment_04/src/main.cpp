#include "graph_io.hpp"
#include "pagerank.hpp"
#include "vertex_coloring.hpp"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

namespace {

const std::vector<std::string> COLOR_TESTS = {
    "color_demo.txt", "color_10.txt", "color_100.txt",
    "color_10000.txt", "color_50000.txt", "color_100000.txt"
};

const std::vector<std::string> RANK_TESTS = {
    "pagerank_demo.txt", "pagerank_10.txt", "pagerank_100.txt",
    "pagerank_1000.txt", "pagerank_10000.txt", "pagerank_50000.txt"
};

void print_coloring(const ColoringResult &r)
{
    std::cout << "\nGreedy Vertex Coloring\n";

    for (size_t i = 0; i < r.colors.size(); i++)
        std::cout << i << " -> " << r.colors[i] << "\n";

    std::cout << "Colors: " << r.colors_used
              << "\nValid: " << (r.valid ? "Yes" : "No")
              << "\nTime: " << std::fixed << std::setprecision(3)
              << r.time_ms << " ms\n";
}

void print_pagerank(const PageRankResult &r)
{
    std::cout << "\nPageRank\n";

    for (size_t i = 0; i < r.ranks.size(); i++)
        std::cout << i << " -> "
                  << std::fixed << std::setprecision(6)
                  << r.ranks[i] << "\n";

    std::cout << "Iterations: " << r.iterations
              << "\nConverged: " << (r.converged ? "Yes" : "No")
              << "\nTime: " << std::setprecision(3)
              << r.time_ms << " ms\n";
}

void run_color(const std::string &file)
{
    CSRGraph graph;
    int edges;

    if (load_coloring_graph(file, graph, edges))
        print_coloring(greedy_coloring(graph));
}

void run_rank(const std::string &file)
{
    CSRGraph graph;
    PageRankSettings settings;

    if (load_pagerank_graph(file, graph, settings))
        print_pagerank(page_rank(graph, settings));
}

void menu(const std::string &folder,
          const std::vector<std::string> &tests,
          bool coloring)
{
    while (true)
    {
        std::vector<std::string> available_tests;
        for (const std::string &test : tests)
        {
            std::ifstream file(folder + "/" + test);
            if (file)
                available_tests.push_back(test);
        }

        std::cout << "\n";
        for (size_t i = 0; i < available_tests.size(); i++)
            std::cout << i + 1 << ") " << available_tests[i] << "\n";

        if (available_tests.empty())
            std::cout << "No test files found\n";

        std::cout << "0) Back\nChoice: ";

        int choice;
        std::cin >> choice;

        if (choice == 0) return;

        if (choice < 1 || choice > (int)available_tests.size())
        {
            std::cout << "Invalid choice\n";
            continue;
        }

        std::string file = folder + "/" + available_tests[choice - 1];

        if (coloring)
            run_color(file);
        else
            run_rank(file);
    }
}

void report()
{
    std::ofstream out("report_assignment4.md");

    out << "# Assignment 4 Results\n\n";
    out << "## Vertex Coloring\n\n";
    out << "| File | V | E | Colors | Valid | Time |\n";
    out << "|---|---:|---:|---:|---|---:|\n";

    for (const auto &name : COLOR_TESTS)
    {
        std::string file = "tests/coloring/" + name;
        std::ifstream exists(file);
        if (!exists)
            continue;

        CSRGraph graph;
        int edges;

        if (!load_coloring_graph(file, graph, edges))
            continue;

        ColoringResult r = greedy_coloring(graph);

        out << "| " << name << " | " << graph.V
            << " | " << edges << " | " << r.colors_used
            << " | " << (r.valid ? "Yes" : "No")
            << " | " << r.time_ms << " |\n";
    }

    out << "\n## PageRank\n\n";
    out << "| File | V | E | Damping | Iterations | Time |\n";
    out << "|---|---:|---:|---:|---:|---:|\n";

    for (const auto &name : RANK_TESTS)
    {
        std::string file = "tests/pagerank/" + name;
        std::ifstream exists(file);
        if (!exists)
            continue;

        CSRGraph graph;
        PageRankSettings settings;

        if (!load_pagerank_graph(file, graph, settings))
            continue;

        PageRankResult r = page_rank(graph, settings);

        out << "| " << name << " | " << graph.V
            << " | " << graph.E << " | " << settings.damping
            << " | " << r.iterations << " | " << r.time_ms << " |\n";
    }

    std::cout << "Report created.\n";
}

} // namespace


int main(int argc, char **argv)
{
    if (argc == 3 && std::string(argv[1]) == "color")
        run_color(argv[2]);

    else if (argc == 3 && std::string(argv[1]) == "pagerank")
        run_rank(argv[2]);

    else if (argc == 2 && std::string(argv[1]) == "report")
        report();

    else
    {
        while (true)
        {
            std::cout << "\n===== Assignment 4 =====\n"
                      << "1) Vertex Coloring\n"
                      << "2) PageRank\n"
                      << "0) Exit\nChoice: ";

            int choice;
            std::cin >> choice;

            if (choice == 0) break;

            if (choice == 1)
                menu("tests/coloring", COLOR_TESTS, true);
            else if (choice == 2)
                menu("tests/pagerank", RANK_TESTS, false);
            else
                std::cout << "Invalid choice\n";
        }
    }

    return 0;
}