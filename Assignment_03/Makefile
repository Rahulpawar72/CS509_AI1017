CXX      = g++
CXXFLAGS = -O2 -Wall -Wextra -std=c++17 -I../Assignment_01/src

# The shared CSR implementation is compiled straight from Assignment 1's folder -- Assignment 3
# does not keep its own copy of it, per the assignment's instruction to
# call the existing CSR conversion function rather than reimplement it.
CSR_SRC  = ../Assignment_01/src/csr_shared.cpp

SRC      = src/main.cpp $(CSR_SRC) src/mst_io.cpp src/mst_kruskal.cpp src/mst_prim.cpp
TARGET   = assignment3.exe

GEN_SRC    = tools/graph_gen.cpp
GEN_TARGET = graph_gen.exe

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

gen: $(GEN_TARGET)

$(GEN_TARGET): $(GEN_SRC)
	$(CXX) -O2 -Wall -Wextra -std=c++17 -o $(GEN_TARGET) $(GEN_SRC)

clean:
	rm -f $(TARGET) $(GEN_TARGET)

.PHONY: all gen clean
