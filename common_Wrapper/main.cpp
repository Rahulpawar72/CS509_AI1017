#include <chrono>
#include <iostream>
#include <io.h>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;
using namespace chrono;

// The wrapper can be started from the repository root or from common_Wrapper.
// Use the path that exists in the current working directory.
string projectPath(const string &relativePath)
{
    const vector<string> candidates = {
        relativePath,
        "..\\" + relativePath
    };

    for (const string &candidate : candidates)
    {
        if (_access(candidate.c_str(), 0) == 0)
        {
            char absolutePath[4096];
            if (GetFullPathNameA(candidate.c_str(), sizeof(absolutePath),
                                 absolutePath, nullptr) != 0)
                return absolutePath;
            return candidate;
        }
    }

    char absolutePath[4096];
    if (GetFullPathNameA(relativePath.c_str(), sizeof(absolutePath),
                         absolutePath, nullptr) != 0)
        return absolutePath;

    return relativePath;
}

string repoRootPath()
{
    static const vector<string> rootChecks = {
        "Assignment_01",
        "Assignment_02",
        "Assignment_03",
        "Assignment_04"
    };

    for (const string &name : rootChecks)
    {
        const string candidate = projectPath(name);
        const size_t pos = candidate.rfind("\\" + name);
        if (pos != string::npos)
            return candidate.substr(0, pos);
    }

    return projectPath("..");
}

void runProgram(const string &name, const string &exe,
                const string &flag = "", const string &inputPath = "")
{
    cout << "\n========== " << name << " ==========" << "\n";

    auto start = high_resolution_clock::now();

    char previousDir[4096];
    GetCurrentDirectoryA(sizeof(previousDir), previousDir);
    const string repoRoot = repoRootPath();
    SetCurrentDirectoryA(repoRoot.c_str());

    string commandLine = "\"" + exe + "\"";
    if (!flag.empty())
    {
        commandLine += " " + flag;
        if (!inputPath.empty())
            commandLine += " \"" + inputPath + "\"";
    }

    vector<char> commandBuffer(commandLine.begin(), commandLine.end());
    commandBuffer.push_back('\0');

    STARTUPINFOA startupInfo = {};
    startupInfo.cb = sizeof(startupInfo);
    PROCESS_INFORMATION processInfo = {};

    DWORD status = 1;
    bool started = CreateProcessA(
        nullptr,
        commandBuffer.data(),
        nullptr,
        nullptr,
        FALSE,
        0,
        nullptr,
        nullptr,
        &startupInfo,
        &processInfo
    ) != 0;

    if (started)
    {
        WaitForSingleObject(processInfo.hProcess, INFINITE);
        GetExitCodeProcess(processInfo.hProcess, &status);
        CloseHandle(processInfo.hProcess);
        CloseHandle(processInfo.hThread);
    }

    SetCurrentDirectoryA(previousDir);

    auto stop = high_resolution_clock::now();

    if (status == 0)
        cout << name << " executed successfully.\n";
    else
        cout << "Failed to execute " << name << endl;

    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "Execution Time: "
         << duration.count()
         << " ms\n";
}

// ============================================================
// Assignment 01 configuration
// ============================================================
const string A1_SIMPLE_EXE = projectPath("Assignment_01\\src\\simple_gemm.exe");
const string A1_BLOCK_EXE  = projectPath("Assignment_01\\src\\blocking.exe");
const string A1_CSR_EXE    = projectPath("Assignment_01\\src\\CSR.exe");

// ============================================================
// Assignment 02 configuration
// ============================================================
const string A2_EXE    = projectPath("Assignment_02\\assignment2.exe");
const string A2_BF_DIR = projectPath("Assignment_02\\tests\\bellman_ford");
const string A2_FW_DIR = projectPath("Assignment_02\\tests\\floyd_warshall");

const vector<string> BF_TESTS = {
    "demo_bf_negative.txt",
    "demo_bf_negcycle.txt",
    "bf_10.txt",
    "bf_100.txt",
    "bf_10000.txt",
    "bf_50000.txt",
    "bf_100000.txt"
};

const vector<string> FW_TESTS = {
    "demo_fw_negative.txt",
    "demo_fw_negcycle.txt",
    "fw_10.txt",
    "fw_100.txt",
    "fw_500.txt",
    "fw_1000.txt",
    "fw_2000.txt"
};

// ============================================================
// Assignment 03 configuration
// SOLO ONLY - MST
// ============================================================
const string A3_EXE     = projectPath("Assignment_03\\assignment3.exe");
const string A3_MST_DIR = projectPath("Assignment_03\\tests\\mst");

const vector<string> MST_TESTS = {
    "demo_mst.txt",
    "mst_10.txt",
    "mst_100.txt",
    "mst_10000.txt",
    "mst_50000.txt",
    "mst_100000.txt"
};

// ============================================================
// Assignment 04 configuration
// ============================================================
const string A4_EXE          = projectPath("Assignment_04\\assignment4.exe");
const string A4_COLOR_DIR    = projectPath("Assignment_04\\tests\\coloring");
const string A4_PAGERANK_DIR = projectPath("Assignment_04\\tests\\pagerank");

const vector<string> COLORING_TESTS = {
    "color_demo.txt", "color_10.txt", "color_100.txt",
    "color_10000.txt", "color_50000.txt", "color_100000.txt"
};

const vector<string> PAGERANK_TESTS = {
    "pagerank_demo.txt", "pagerank_10.txt", "pagerank_100.txt",
    "pagerank_1000.txt", "pagerank_10000.txt", "pagerank_50000.txt"
};

// ============================================================
// Generic test submenu
// ============================================================
void runTestSubmenu(
    const string &exe,
    const string &algoName,
    const string &flag,
    const string &dir,
    const vector<string> &tests)
{
    while (true)
    {
        cout << "\n--- " << algoName << " Test Cases ---\n";

        vector<string> available_tests;
        for (const string &test : tests)
        {
            const string path = dir + "\\" + test;
            if (_access(path.c_str(), 0) == 0)
                available_tests.push_back(test);
        }

        for (size_t i = 0; i < available_tests.size(); i++)
            cout << " " << (i + 1) << ") " << available_tests[i] << "\n";

        if (available_tests.empty())
            cout << " No test files found.\n";

        cout << " 0) Back\n";
        cout << "Choice: ";

        int choice;
        if (!(cin >> choice))
            return;

        if (choice == 0)
            return;

        if (choice < 1 || static_cast<size_t>(choice) > available_tests.size())
        {
            cout << "Invalid choice!\n";
            continue;
        }

        const string path = dir + "\\" + available_tests[choice - 1];
        runProgram(algoName + " - " + available_tests[choice - 1], exe, flag, path);
    }
}

// ============================================================
// Assignment 01 menu
// ============================================================
void assignment1Menu()
{
    while (true)
    {
        cout << "\n========== Assignment 01 ==========" << "\n";
        cout << "1. Simple GEMM\n";
        cout << "2. Blocking GEMM\n";
        cout << "3. CSR Conversion\n";
        cout << "4. Run All\n";
        cout << "0. Back\n";
        cout << "Enter your choice: ";

        int choice;
        if (!(cin >> choice))
            return;

        if (choice == 0)
            return;

        if (choice == 1)
            runProgram("Simple GEMM", A1_SIMPLE_EXE);
        else if (choice == 2)
            runProgram("Blocking GEMM", A1_BLOCK_EXE);
        else if (choice == 3)
            runProgram("CSR Conversion", A1_CSR_EXE);
        else if (choice == 4)
        {
            runProgram("Simple GEMM", A1_SIMPLE_EXE);
            runProgram("Blocking GEMM", A1_BLOCK_EXE);
            runProgram("CSR Conversion", A1_CSR_EXE);
        }
        else
        {
            cout << "Invalid choice!\n";
        }
    }
}

// ============================================================
// Assignment 02 menu
// ============================================================
void assignment2Menu()
{
    while (true)
    {
        cout << "\n========== Assignment 02 ==========" << "\n";
        cout << "1. Bellman-Ford\n";
        cout << "2. Floyd-Warshall\n";
        cout << "0. Back\n";
        cout << "Enter your choice: ";

        int choice;
        if (!(cin >> choice))
            return;

        if (choice == 1)
            runTestSubmenu(A2_EXE, "Bellman-Ford", "bf", A2_BF_DIR, BF_TESTS);
        else if (choice == 2)
            runTestSubmenu(A2_EXE, "Floyd-Warshall", "fw", A2_FW_DIR, FW_TESTS);
        else if (choice == 0)
            return;
        else
            cout << "Invalid choice!\n";
    }
}

// ============================================================
// Assignment 03 menu
// ============================================================
void assignment3Menu()
{
    while (true)
    {
        cout << "\n========== Assignment 03 (Solo) ==========" << "\n";
        cout << "1. Kruskal's Algorithm\n";
        cout << "2. Prim's Algorithm\n";
        cout << "0. Back\n";
        cout << "Enter your choice: ";

        int choice;
        if (!(cin >> choice))
            return;

        if (choice == 1)
            runTestSubmenu(A3_EXE, "Kruskal's Algorithm", "kruskal", A3_MST_DIR, MST_TESTS);
        else if (choice == 2)
            runTestSubmenu(A3_EXE, "Prim's Algorithm", "prim", A3_MST_DIR, MST_TESTS);
        else if (choice == 0)
            return;
        else
            cout << "Invalid choice!\n";
    }
}

// ============================================================
// Assignment 04 menu
// ============================================================
void assignment4Menu()
{
    while (true)
    {
        cout << "\n========== Assignment 04 ==========" << "\n";
        cout << "1. Vertex Coloring\n";
        cout << "2. PageRank\n";
        cout << "0. Back\n";
        cout << "Enter your choice: ";

        int choice;
        if (!(cin >> choice))
            return;

        if (choice == 1)
            runTestSubmenu(A4_EXE, "Vertex Coloring", "color", A4_COLOR_DIR, COLORING_TESTS);
        else if (choice == 2)
            runTestSubmenu(A4_EXE, "PageRank", "pagerank", A4_PAGERANK_DIR, PAGERANK_TESTS);
        else if (choice == 0)
            return;
        else
            cout << "Invalid choice!\n";
    }
}

int main()
{
    while (true)
    {
        cout << "\n========== CS509 Assignments ==========" << "\n";
        cout << "1. Assignment 01\n";
        cout << "2. Assignment 02\n";
        cout << "3. Assignment 03\n";
        cout << "4. Assignment 04\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        if (!(cin >> choice))
            break;

        if (choice == 0)
            break;

        if (choice == 1)
            assignment1Menu();
        else if (choice == 2)
            assignment2Menu();
        else if (choice == 3)
            assignment3Menu();
        else if (choice == 4)
            assignment4Menu();
        else
            cout << "Invalid choice!\n";
    }

    return 0;
}