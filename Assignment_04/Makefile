CXX      = g++
CXXFLAGS = -O2 -Wall -Wextra -std=c++17 -I../Assignment_01/src

CSR_SRC = ../Assignment_01/src/csr_shared.cpp
SRC = src/main.cpp src/graph_io.cpp src/vertex_coloring.cpp src/pagerank.cpp $(CSR_SRC)
TARGET = assignment4.exe

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	-del /Q $(TARGET) 2>NUL

.PHONY: all clean