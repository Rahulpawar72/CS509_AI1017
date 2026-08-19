#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include "../../Assignment_01/src/csr.hpp"
#include "bellman_ford.hpp"
#include "floyd_warshall.hpp"

using Clock = std::chrono::steady_clock;

static double elapsed_ms(Clock::time_point t0, Clock::time_point t1) {
    return std::chrono::duration<double, std::milli>(t1 - t0).count();
}

static void print_usage(const char *prog) {
    std::cerr << "Usage: " << prog << " <bf|fw> <input_file>\n"
              << "  bf  Bellman-Ford  (weighted, directed, CSR adjacency-list input)\n"
              << "  fw  Floyd-Warshall (dense V x V matrix input)\n"
              << "Run with no arguments for the interactive menu.\n";
}

static int run_bf(const std::string &path) {
    CSRGraph g;
    int source;
    if (!load_bf_graph(path, g, source)) {
        std::cerr << "Error: invalid or missing input file: " << path << "\n";
        return 1;
    }

    std::vector<long long> dist;
    bool neg_cycle;

    auto t0 = Clock::now();
    run_bellman_ford(g, source, dist, neg_cycle);
    auto t1 = Clock::now();

    std::cout << "Algorithm: Bellman-Ford\n";
    std::cout << "Source: " << source << "\n";
    if (neg_cycle) {
        std::cout << "Negative cycle: true\n";
    } else {
        std::cout << "Vertex Distance\n";
        for (int i = 0; i < g.V; i++) {
            std::cout << i << " ";
            if (dist[i] >= BF_INF) std::cout << "INF\n";
            else std::cout << dist[i] << "\n";
        }
        std::cout << "Negative cycle: none\n";
    }
    std::cout << "Execution time: " << elapsed_ms(t0, t1) << " ms\n";
    return 0;
}

static int run_fw(const std::string &path) {
    std::vector<long long> dist;
    int V;
    if (!load_fw_graph(path, dist, V)) {
        std::cerr << "Error: invalid or missing input file: " << path << "\n";
        return 1;
    }

    bool neg_cycle;
    auto t0 = Clock::now();
    run_floyd_warshall(dist, V, neg_cycle);
    auto t1 = Clock::now();

    std::cout << "Algorithm: Floyd-Warshall\n";
    if (neg_cycle) {
        std::cout << "Negative cycle: true\n";
    } else {
        std::cout << "Distance matrix:\n";
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                long long val = dist[i * V + j];
                if (val >= FW_INF) std::cout << "INF";
                else std::cout << val;
                std::cout << (j == V - 1 ? '\n' : ' ');
            }
        }
        std::cout << "Negative cycle: none\n";
    }
    std::cout << "Execution time: " << elapsed_ms(t0, t1) << " ms\n";
    return 0;
}

// Each algorithm's test cases live in their own folder. To add a test case,
// just drop the file in the folder and add its name here -- nothing else
// needs to change.
static const std::string BF_DIR = "tests/bellman_ford";
static const std::vector<std::string> BF_TESTS = {
    "demo_bf_negative.txt",
    "demo_bf_negcycle.txt",
    "bf_10.txt",
    "bf_100.txt",
    "bf_10000.txt",
    "bf_50000.txt",
    "bf_100000.txt",
};

static const std::string FW_DIR = "tests/floyd_warshall";
static const std::vector<std::string> FW_TESTS = {
    "demo_fw_negative.txt",
    "demo_fw_negcycle.txt",
    "fw_10.txt",
    "fw_100.txt",
    "fw_500.txt",
    "fw_1000.txt",
    "fw_2000.txt",
};

// Shows the test cases for one algorithm and runs whichever one is picked.
// Stays in this submenu (so you can run several) until you choose "Back".
static void algorithm_submenu(const std::string &name, const std::string &dir,
                               const std::vector<std::string> &files,
                               int (*runner)(const std::string &)) {
    while (true) {
        std::cout << "\n--- " << name << " Test Cases ---\n";
        for (size_t i = 0; i < files.size(); i++)
            std::cout << " " << (i + 1) << ") " << files[i] << "\n";
        std::cout << " 0) Back\n"
                  << "Choice: ";
        int choice;
        if (!(std::cin >> choice)) return;
        if (choice == 0) return;
        if (choice < 1 || (size_t)choice > files.size()) {
            std::cout << "Unknown option.\n";
            continue;
        }
        std::string path = dir + "/" + files[choice - 1];
        std::cout << "\n--- Running: " << path << " ---\n";
        runner(path);
    }
}

static void interactive_menu() {
    while (true) {
        std::cout << "\n===== CS509 Assignment 2 =====\n"
                  << " 1) Bellman-Ford\n"
                  << " 2) Floyd-Warshall\n"
                  << " 0) Exit\n"
                  << "Choice: ";
        int choice;
        if (!(std::cin >> choice)) return;

        if (choice == 1) algorithm_submenu("Bellman-Ford", BF_DIR, BF_TESTS, run_bf);
        else if (choice == 2) algorithm_submenu("Floyd-Warshall", FW_DIR, FW_TESTS, run_fw);
        else if (choice == 0) return;
        else std::cout << "Unknown option.\n";
    }
}

int main(int argc, char **argv) {
    // Direct CLI mode: unchanged, for scripted/graded single runs.
    if (argc == 3) {
        std::string algo = argv[1], path = argv[2];
        if (algo == "bf") return run_bf(path);
        if (algo == "fw") return run_fw(path);
        std::cerr << "Error: unknown algorithm '" << algo << "'\n";
        print_usage(argv[0]);
        return 1;
    }
    if (argc != 1) {
        print_usage(argv[0]);
        return 1;
    }

    interactive_menu();
    return 0;
}
