#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "csr.hpp"
#include "mst_io.hpp"
#include "mst_kruskal.hpp"
#include "mst_prim.hpp"

static const char *TESTS_DIR = "tests/mst";
static const char *TEST_FILES[] = {
    "demo_mst.txt",
    "mst_10.txt",
    "mst_100.txt",
    "mst_10000.txt",
    "mst_50000.txt",
    "mst_100000.txt",
};

static std::vector<std::string> list_txt_files(const std::string &dir) {
    std::vector<std::string> files;
    for (const char *name : TEST_FILES) {
        const std::string path = dir + "/" + name;
        std::ifstream in(path);
        if (in) files.push_back(path);
    }
    return files;
}

static std::string file_name(const std::string &path) {
    const size_t slash = path.find_last_of("/\\");
    return slash == std::string::npos ? path : path.substr(slash + 1);
}

static void print_mst_result(const char *label, const MSTResult &r) {
    std::cout << "Algorithm: " << label << "\n";
    std::cout << "MST edges:\n";
    for (const auto &e : r.edges)
        std::cout << e.u << " " << e.v << " " << e.w << "\n";
    std::cout << "Total MST weight: " << r.total_weight << "\n";
    std::cout << "Execution time: " << std::fixed << std::setprecision(3)
               << r.time_ms << " ms\n";
}

// ---------- Kruskal, standalone ----------

static void run_kruskal_and_print(const std::string &path) {
    CSRGraph g;
    int E;
    if (!load_mst_graph(path, g, E)) return;   // untimed setup
    MSTResult kr = kruskal_mst(g);
    print_mst_result("Kruskal's MST", kr);
}

static void menu_kruskal() {
    auto files = list_txt_files(TESTS_DIR);
    if (files.empty()) {
        std::cout << "No .txt test files found in " << TESTS_DIR << "\n";
        return;
    }
    while (true) {
        std::cout << "\n--- Kruskal's Algorithm Test Cases ---\n";
        for (size_t i = 0; i < files.size(); i++)
            std::cout << " " << (i + 1) << ") " << file_name(files[i]) << "\n";
        std::cout << " 0) Back\nChoice: ";
        int choice;
        if (!(std::cin >> choice)) return;
        if (choice == 0) return;
        if (choice < 1 || choice > static_cast<int>(files.size())) {
            std::cout << "Invalid choice.\n";
            continue;
        }
        std::cout << "\n";
        run_kruskal_and_print(files[choice - 1]);
    }
}

// ---------- Prim, standalone ----------

static void run_prim_and_print(const std::string &path) {
    CSRGraph g;
    int E;
    if (!load_mst_graph(path, g, E)) return;   // untimed setup
    MSTResult pr = prim_mst(g);
    print_mst_result("Prim's MST", pr);
}

static void menu_prim() {
    auto files = list_txt_files(TESTS_DIR);
    if (files.empty()) {
        std::cout << "No .txt test files found in " << TESTS_DIR << "\n";
        return;
    }
    while (true) {
        std::cout << "\n--- Prim's Algorithm Test Cases ---\n";
        for (size_t i = 0; i < files.size(); i++)
            std::cout << " " << (i + 1) << ") " << file_name(files[i]) << "\n";
        std::cout << " 0) Back\nChoice: ";
        int choice;
        if (!(std::cin >> choice)) return;
        if (choice == 0) return;
        if (choice < 1 || choice > static_cast<int>(files.size())) {
            std::cout << "Invalid choice.\n";
            continue;
        }
        std::cout << "\n";
        run_prim_and_print(files[choice - 1]);
    }
}

// ---------- report mode: runs BOTH, for the required comparison table ----------
// (Section 9.1 requires a single table with both algorithms' weights/times
// side by side, so report mode still runs both -- only the interactive
// menu and direct-mode calls were split apart per-algorithm.)

static void report_mode() {
    auto files = list_txt_files(TESTS_DIR);

    std::ofstream out("report_mst.md");
    out << "# MST Results (Kruskal vs Prim)\n\n";
    out << "| File | V | E | Kruskal Wt | Prim Wt | Kruskal Time (ms) | "
           "Prim Time (ms) | Equal? | Status |\n";
    out << "|---|---|---|---|---|---|---|---|---|\n";

    for (const auto &path : files) {
        CSRGraph g;
        int E;
        if (!load_mst_graph(path, g, E)) continue;   // untimed setup

        MSTResult kr = kruskal_mst(g);
        MSTResult pr = prim_mst(g);
        bool equal = kr.total_weight == pr.total_weight;

        out << "| " << file_name(path)
            << " | " << g.V << " | " << E
            << " | " << kr.total_weight << " | " << pr.total_weight
            << " | " << std::fixed << std::setprecision(3) << kr.time_ms
            << " | " << pr.time_ms
            << " | " << (equal ? "Yes" : "No")
            << " | " << (equal ? "Pass" : "Fail") << " |\n";

        std::cout << file_name(path)
                   << ": V=" << g.V << " E=" << E
                   << " Kruskal=" << kr.total_weight << " (" << kr.time_ms << " ms)"
                   << " Prim=" << pr.total_weight << " (" << pr.time_ms << " ms)"
                   << " Equal=" << (equal ? "Yes" : "No") << "\n";
    }
    std::cout << "\nWrote report_mst.md\n";
}

int main(int argc, char **argv) {
    // Direct mode: ./assignment3.exe kruskal tests/mst/mst_10.txt
    //              ./assignment3.exe prim    tests/mst/mst_10.txt
    if (argc == 3 && std::string(argv[1]) == "kruskal") {
        run_kruskal_and_print(argv[2]);
        return 0;
    }
    if (argc == 3 && std::string(argv[1]) == "prim") {
        run_prim_and_print(argv[2]);
        return 0;
    }
    // Report mode: ./assignment3.exe report
    if (argc == 2 && std::string(argv[1]) == "report") {
        report_mode();
        return 0;
    }

    while (true) {
        std::cout << "\n===== CS509 Assignment 3 (Solo: MST) =====\n";
        std::cout << " 1) Kruskal's Algorithm\n";
        std::cout << " 2) Prim's Algorithm\n";
        std::cout << " 3) Generate results table (report_mst.md)\n";
        std::cout << " 0) Exit\n";
        std::cout << "Choice: ";

        int choice;
        if (!(std::cin >> choice)) break;
        if (choice == 0) break;
        else if (choice == 1) menu_kruskal();
        else if (choice == 2) menu_prim();
        else if (choice == 3) report_mode();
        else std::cout << "Invalid choice.\n";
    }
    return 0;
}
