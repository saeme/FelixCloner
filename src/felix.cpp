#include "felix.h"
#include "utils.h"
#include <iostream>
#include <thread>
#include <chrono>

void felix_process(int id, int* matrix, int rows, int cols, sem_t* sem) {
    while (true) {
        sem_wait(sem); // Lock access to the matrix
        bool fixed = false;

        // Search for broken cells and fix them
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                if (matrix[row * cols + col] == -1) {
                    matrix[row * cols + col] = 0; // Fix the cell
                    fixed = true;
                    std::cout << "Felix " << id << " fixed cell at (" << row << ", " << col << ")\n";
                    break;
                }
            }
            if (fixed) break; // Break outer loop if a cell was fixed
        }

        sem_post(sem); // Unlock access to the matrix

        if (!fixed) {
            std::cout << "Felix " << id << " has nothing to fix and is exiting.\n";
            break; // Exit if no broken cells were found
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate work delay
    }
}