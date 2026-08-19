#ifndef CSR_HPP
#define CSR_HPP

#include <string>
#include <vector>

struct CSRGraph {
    int V = 0;
    int E = 0;
    std::vector<int> row_ptr;
    std::vector<int> col_idx;
    std::vector<int> weight;
};

CSRGraph adjlist_to_csr(int V,
                        const std::vector<int> &degree,
                        const std::vector<std::vector<int>> &nbr,
                        const std::vector<std::vector<int>> &wt);

bool load_bf_graph(const std::string &path, CSRGraph &g, int &source);

CSRGraph matrix_to_csr(const std::vector<std::vector<int>> &matrix);

#endif