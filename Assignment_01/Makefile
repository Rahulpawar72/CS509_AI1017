CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

CSR_SRC = src/csr_shared.cpp

all: src/simple_gemm src/blocking src/CSR

src/simple_gemm: src/gemm.cpp
	$(CXX) $(CXXFLAGS) -o src/simple_gemm src/gemm.cpp

src/blocking: src/blocking.cpp
	$(CXX) $(CXXFLAGS) -o src/blocking src/blocking.cpp

src/CSR: src/csr_driver.cpp $(CSR_SRC)
	$(CXX) $(CXXFLAGS) -o src/CSR src/csr_driver.cpp $(CSR_SRC)

clean:
	rm -f src/simple_gemm src/blocking src/CSR

.PHONY: all clean
