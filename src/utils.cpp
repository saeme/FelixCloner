#include "utils.h"
#include <iostream>

void cleanup_resources(int* matrix, size_t matrix_size, sem_t* sem) {
    if (matrix) {
        munmap(matrix, matrix_size); // Unmap shared memory
    }
    shm_unlink(SHM_NAME); // Remove shared memory object

    if (sem) {
        sem_close(sem); // Close semaphore
    }
    sem_unlink(SEM_NAME); // Remove semaphore

    std::cout << "Resources cleaned up successfully.\n";
}