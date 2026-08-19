#include <fstream>
#include <iostream>
#include <vector>
#include "csr.hpp"

using namespace std;

int main() {
    ifstream fin("./Assignment_01/input/input_csr.txt");
    ofstream fout("./Assignment_01/output/output.txt");

    if (!fin) {
        cerr << "Error: Cannot open ./Assignment_01/input/input_csr.txt" << endl;
        return 1;
    }

    int rows, cols;
    fin >> rows >> cols;
    vector<vector<int>> matrix(rows, vector<int>(cols));

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            fin >> matrix[i][j];

    CSRGraph g = matrix_to_csr(matrix);

    fout << "Values:\n";
    for (int x : g.weight)
        fout << x << " ";
    fout << "\n\nColumn Index:\n";
    for (int x : g.col_idx)
        fout << x << " ";
    fout << "\n\nRow Pointer:\n";
    for (int x : g.row_ptr)
        fout << x << " ";

    cout << "CSR conversion completed successfully." << endl;
    cout << "Output written to output.txt" << endl;
    return 0;
}