# CS509 Assignment 3 — Solo

Implementation of two Minimum Spanning Tree algorithms:

* **Kruskal's Algorithm**
* **Prim's Algorithm**

Both algorithms work on a weighted, undirected graph stored using CSR.

## Folder Structure

This assignment uses the CSR files from **Assignment_01**.

```text
your-repo/
├── Assignment_01/
│   └── src/
│       ├── csr.hpp
│       └── csr_shared.cpp
│
└── Assignment_03/
    ├── src/
    ├── tests/mst/
    ├── tools/
    └── Makefile
```

> `Assignment_01` and `Assignment_03` must be sibling folders.

## Build

```bash
cd Assignment_03
make
```

To build the graph generator:

```bash
make gen
```

## Run

### Menu Mode

```bash
./assignment3.exe
```

### Kruskal

```bash
./assignment3.exe kruskal tests/mst/mst_100000.txt
```

### Prim

```bash
./assignment3.exe prim tests/mst/mst_100000.txt
```

### Generate Report

```bash
./assignment3.exe report
```

This creates `report_mst.md`.

## Project Structure

```text
src/
├── main.cpp
├── mst_io.cpp / mst_io.hpp
├── mst_kruskal.cpp / mst_kruskal.hpp
└── mst_prim.cpp / mst_prim.hpp

tools/
└── graph_gen.cpp

tests/mst/
└── MST test files

Makefile
```

The CSR implementation is not copied into this folder. The project directly uses:

```text
Assignment_01/src/csr.hpp
Assignment_01/src/csr_shared.cpp
```

## Algorithms

**Kruskal's Algorithm**

* Extracts and sorts graph edges
* Uses DSU to build the MST

**Prim's Algorithm**

* Uses a priority queue
* Builds the MST directly from the CSR graph

## Results

| Test   |       V |       E | Kruskal |    Prim | Kruskal (ms) | Prim (ms) | Status |
| ------ | ------: | ------: | ------: | ------: | -----------: | --------: | ------ |
| demo   |       5 |       7 |      16 |      16 |        0.001 |     0.001 | Pass   |
| 10     |      10 |      30 |     177 |     177 |        0.002 |     0.002 | Pass   |
| 100    |     100 |     300 |    2105 |    2105 |        0.019 |     0.026 | Pass   |
| 10000  |  10,000 |  30,000 |  199747 |  199747 |        1.950 |     9.944 | Pass   |
| 50000  |  50,000 | 150,000 | 1013752 | 1013752 |        8.842 |    18.719 | Pass   |
| 100000 | 100,000 | 300,000 | 2024142 | 2024142 |       18.154 |    43.080 | Pass   |

Kruskal and Prim produce the same MST weight for all test cases.

