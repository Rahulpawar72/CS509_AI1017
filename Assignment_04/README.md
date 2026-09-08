# Assignment 4: Vertex Coloring and PageRank

This folder contains the individual task from Assignment 4. Both algorithms
read adjacency-list files and use the CSR conversion from
`Assignment_01/src/csr_shared.cpp`; loading and conversion happen before the
algorithm timer starts.

## How to run on Windows

Open PowerShell and move into this folder:

```powershell
cd "d:\DESKTOP FOLDER\CS509_Singletask\Assignment_04"
```

Build the program:

```powershell
mingw32-make
```

### Interactive menu

Start the menu and choose Vertex Coloring or PageRank:

```powershell
.\assignment4.exe
```

### Run Vertex Coloring directly

```powershell
.\assignment4.exe color "tests\coloring\color_demo.txt"
.\assignment4.exe color "tests\coloring\color_10.txt"
.\assignment4.exe color "tests\coloring\color_100.txt"
```

### Run PageRank directly

```powershell
.\assignment4.exe pagerank "tests\pagerank\pagerank_demo.txt"
```

### Generate the report

The report uses every test file that exists in the test directories:

```powershell
.\assignment4.exe report
```

This creates `report_assignment4.md` in the Assignment 4 folder.

The current repository includes coloring cases for the demo, 10 vertices, and
100 vertices, plus the PageRank demo. Additional required-size files can be
added using the adjacency-list formats from the assignment handout.

To remove the executable before rebuilding:

```powershell
mingw32-make clean
```

Large graph files should remain sparse. The loader validates vertex IDs,
degrees, edge counts, reciprocal undirected edges, and PageRank settings before
the algorithm starts.

Vertex Coloring uses Welsh-Powell ordering followed by greedy coloring and
checks the final coloring. PageRank uses simultaneous updates, damping,
dangling-vertex redistribution, tolerance, and a maximum iteration limit.

## Run through the common wrapper

Build Assignment 4 first:

```powershell
cd "d:\DESKTOP FOLDER\CS509_Singletask\Assignment_04"
mingw32-make
```

Then build and start the common wrapper:

```powershell
cd "d:\DESKTOP FOLDER\CS509_Singletask\common_Wrapper"
g++ -Wall -Wextra -std=c++17 -o wrapper.exe main.cpp
.\wrapper.exe
```

In the wrapper menu, select:

```text
4. Assignment 04 (Individual)
1. Vertex Coloring or 2. PageRank
```

The wrapper detects the available test files automatically and launches the
Assignment 4 executable with the selected input file.