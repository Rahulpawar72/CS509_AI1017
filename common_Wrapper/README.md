# Common Wrapper

The common wrapper provides one menu for running the assignment programs. It
currently includes Assignment 1, Assignment 2, Assignment 3, and Assignment 4.

## Windows PowerShell commands

Open PowerShell and move to the repository root:

```powershell
cd "d:\DESKTOP FOLDER\CS509_Singletask"
```

Build Assignment 4 first because the wrapper launches its executable:

```powershell
cd "d:\DESKTOP FOLDER\CS509_Singletask\Assignment_04"
mingw32-make
```

Build the wrapper:

```powershell
cd "d:\DESKTOP FOLDER\CS509_Singletask\common_Wrapper"
g++ -Wall -Wextra -std=c++17 -o wrapper.exe main.cpp
```

Start the wrapper:

```powershell
.\wrapper.exe
```

## Assignment 4 through the wrapper

Select these menu options:

```text
4. Assignment 04
1. Vertex Coloring
2. PageRank
```

The wrapper then displays only test files that exist. Currently available
Assignment 4 files are:

```text
Vertex Coloring: color_demo.txt, color_10.txt, color_100.txt
PageRank: pagerank_demo.txt
```

Choose a test number and press Enter. Select `0` to go back to the previous
menu or exit the wrapper.

## Run Assignment 4 directly

The wrapper is optional. Assignment 4 can also be run directly:

```powershell
cd "d:\DESKTOP FOLDER\CS509_Singletask\Assignment_04"
mingw32-make
.\assignment4.exe
```

Direct commands are also available:

```powershell
.\assignment4.exe color "tests\coloring\color_demo.txt"
.\assignment4.exe color "tests\coloring\color_10.txt"
.\assignment4.exe color "tests\coloring\color_100.txt"
.\assignment4.exe pagerank "tests\pagerank\pagerank_demo.txt"
.\assignment4.exe report
```

The wrapper resolves paths from either the repository root or the
`common_Wrapper` folder, including the workspace path containing spaces.