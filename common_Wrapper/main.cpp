#include <iostream>
#include <cstdlib>
#include <chrono>
#include <string>
#include <vector>
using namespace std;
using namespace chrono;

void runProgram(const string &name, const string &command)
{
    cout << "\n========== " << name << " ==========\n";
    auto start = high_resolution_clock::now();
    int status = system(command.c_str());
    auto stop = high_resolution_clock::now();
    if (status == 0)
        cout << name << " executed successfully.\n";
    else
        cout << "Failed to execute " << name << endl;
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Execution Time: " << duration.count() << " ms\n";
}

// ============================================================
// Assignment 02 config — adjust these two paths if your repo
// layout differs. Everything else (menus, adding new algorithms
// later) works off these.
// ============================================================
const string A2_EXE    = "Assignment_02\\assignment2.exe";
const string A2_BF_DIR = "Assignment_02\\tests\\bellman_ford";
const string A2_FW_DIR = "Assignment_02\\tests\\floyd_warshall";

const vector<string> BF_TESTS = {
    "demo_bf_negative.txt",
    "demo_bf_negcycle.txt",
    "bf_10.txt",
    "bf_100.txt",
    "bf_10000.txt",
    "bf_50000.txt",
    "bf_100000.txt",
};

const vector<string> FW_TESTS = {
    "demo_fw_negative.txt",
    "demo_fw_negcycle.txt",
    "fw_10.txt",
    "fw_100.txt",
    "fw_500.txt",
    "fw_1000.txt",
    "fw_2000.txt",
};

// ============================================================
// Assignment 03 (SOLO ONLY — MST) config. Buddy tasks (Gradient
// Descent, Maxflow-Mincut) are a separate submission and are
// intentionally NOT wired into this wrapper.
// ============================================================
const string A3_EXE     = "Assignment_03\\assignment3.exe";
const string A3_MST_DIR = "Assignment_03\\tests\\mst";

const vector<string> MST_TESTS = {
    "demo_mst.txt",
    "mst_10.txt",
    "mst_100.txt",
    "mst_10000.txt",
    "mst_50000.txt",
    "mst_100000.txt",
};

const string A1_SIMPLE_EXE = "Assignment_01\\src\\simple_gemm.exe";
const string A1_BLOCK_EXE  = "Assignment_01\\src\\blocking.exe";
const string A1_CSR_EXE    = "Assignment_01\\src\\CSR.exe";

// Generic third-level menu: pick a test file, run
// "assignmentN <flag> <path>". Loops so you can run several
// test cases back to back before going Back.
void runTestSubmenu(const string &exe, const string &algoName, const string &flag,
                     const string &dir, const vector<string> &tests)
{
    while (true)
    {
        cout << "\n--- " << algoName << " Test Cases ---\n";
        for (size_t i = 0; i < tests.size(); i++)
            cout << " " << (i + 1) << ") " << tests[i] << "\n";
        cout << " 0) Back\n";
        cout << "Choice: ";
        int c;
        if (!(cin >> c)) return;
        if (c == 0) return;
        if (c < 1 || (size_t)c > tests.size())
        {
            cout << "Invalid choice!\n";
            continue;
        }
        string path = dir + "\\" + tests[c - 1];
        string cmd  = exe + " " + flag + " " + path;
        runProgram(algoName + " - " + tests[c - 1], cmd);
    }
}

void assignment1Menu()
{
    while (true)
    {
        cout << "\n========== Assignment 01 ==========\n";
        cout << "1. Simple GEMM\n";
        cout << "2. Blocking GEMM\n";
        cout << "3. CSR Conversion\n";
        cout << "4. Run All\n";
        cout << "0. Back\n";
        cout << "Enter your choice: ";

        int choice;
        if (!(cin >> choice)) return;

        if (choice == 0) return;
        if (choice == 1)
            runProgram("Simple GEMM", A1_SIMPLE_EXE);
        else if (choice == 2)
            runProgram("Blocking GEMM", A1_BLOCK_EXE);
        else if (choice == 3)
            runProgram("CSR Conversion", A1_CSR_EXE);
        else if (choice == 4) {
            runProgram("Simple GEMM", A1_SIMPLE_EXE);
            runProgram("Blocking GEMM", A1_BLOCK_EXE);
            runProgram("CSR Conversion", A1_CSR_EXE);
        } else
            cout << "Invalid choice!\n";
    }
}

// Second-level menu: which algorithm.
// To add a new algorithm later (e.g. Triangle Counting):
//   1) add its test-file vector above (like BF_TESTS)
//   2) add one "else if" branch below calling runTestSubmenu
void assignment2Menu()
{
    while (true)
    {
        cout << "\n========== Assignment 02 ==========\n";
        cout << "1. Bellman-Ford\n";
        cout << "2. Floyd-Warshall\n";
        cout << "0. Back\n";
        cout << "Enter your choice: ";
        int c;
        if (!(cin >> c)) return;

        if (c == 1)
            runTestSubmenu(A2_EXE, "Bellman-Ford", "bf", A2_BF_DIR, BF_TESTS);
        else if (c == 2)
            runTestSubmenu(A2_EXE, "Floyd-Warshall", "fw", A2_FW_DIR, FW_TESTS);
        else if (c == 0)
            return;
        else
            cout << "Invalid choice!\n";
    }
}

// Second-level menu for Assignment 03 (solo). Kruskal and Prim are separate
// algorithm choices, each with their own test-case submenu -- mirrors
// Assignment 02's Bellman-Ford / Floyd-Warshall pattern exactly.
void assignment3Menu()
{
    while (true)
    {
        cout << "\n========== Assignment 03 (Solo) ==========\n";
        cout << "1. Kruskal's Algorithm\n";
        cout << "2. Prim's Algorithm\n";
        cout << "0. Back\n";
        cout << "Enter your choice: ";
        int c;
        if (!(cin >> c)) return;

        if (c == 1)
            runTestSubmenu(A3_EXE, "Kruskal's Algorithm", "kruskal", A3_MST_DIR, MST_TESTS);
        else if (c == 2)
            runTestSubmenu(A3_EXE, "Prim's Algorithm", "prim", A3_MST_DIR, MST_TESTS);
        else if (c == 0)
            return;
        else
            cout << "Invalid choice!\n";
    }
}

int main()
{
    while (true) {
        cout << "\n========== CS509 Assignments ==========\n";
        cout << "1. Assignment 01\n";
        cout << "2. Assignment 02\n";
        cout << "3. Assignment 03\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        if (!(cin >> choice)) break;
        if (choice == 0) break;
        if (choice == 1)
            assignment1Menu();
        else if (choice == 2)
            assignment2Menu();
        else if (choice == 3)
            assignment3Menu();
        else
            cout << "Invalid choice!\n";
    }
    return 0;
}
