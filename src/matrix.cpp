#include "matrix.h"
#include <cstdlib>

void initialize_matrix(int* matrix, int rows, int cols, int broken_cells) {
    std::memset(matrix, 0, rows * cols * sizeof(int)); // Initialize all cells to 0
    for (int i = 0; i < broken_cells; ++i) {
        int row = rand() % rows;
        int col = rand() % cols;
        matrix[row * cols + col] = -1; // Mark as broken
    }
}