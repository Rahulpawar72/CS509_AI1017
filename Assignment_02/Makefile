CXX = g++
CXXFLAGS = -O2 -Wall -Wextra -std=c++17 -I../Assignment_01/src

CSR_SRC = ../Assignment_01/src/csr_shared.cpp
SRC = src/main.cpp $(CSR_SRC) src/bellman_ford.cpp src/floyd_warshall.cpp

all: assignment2 graphgen

assignment2: $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $(SRC)

graphgen: tools/graph_gen.cpp
	$(CXX) $(CXXFLAGS) -o $@ tools/graph_gen.cpp

clean:
	rm -f assignment2 graphgen

.PHONY: all clean
