#include "gtest/gtest.h"
#include "../include/matrix.h"
#include "../include/utils.h"
#include "../include/felix.h"
#include <vector>
#include <cstring>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

// Fixture for shared memory tests
class MatrixTest : public ::testing::Test {
protected:
    int rows = 5;
    int cols = 5;
    size_t matrix_size = rows * cols * sizeof(int);
    int shm_fd;
    int* matrix;

    void SetUp() override {
        // Create shared memory for testing
        shm_fd = shm_open("/test_matrix_shm", O_CREAT | O_RDWR, 0666);
        ftruncate(shm_fd, matrix_size);
        matrix = (int*)mmap(nullptr, matrix_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    }

    void TearDown() override {
        // Clean up shared memory
        munmap(matrix, matrix_size);
        shm_unlink("/test_matrix_shm");
    }
};

// Test matrix initialization
TEST_F(MatrixTest, InitializeMatrix) {
    int broken_cells = 3;
    initialize_matrix(matrix, rows, cols, broken_cells);

    int broken_count = 0;
    for (int i = 0; i < rows * cols; ++i) {
        if (matrix[i] == -1) {
            ++broken_count;
        }
    }

    EXPECT_EQ(broken_count, broken_cells); // Check the number of broken cells
}

// Test Felix process logic
TEST_F(MatrixTest, FelixFixesBrokenCells) {
    // Initialize matrix with one broken cell
    matrix[0] = -1; // Broken cell at (0, 0)

    // Simulate Felix fixing the broken cell
    sem_t sem;
    sem_init(&sem, 1, 1); // Initialize semaphore for testing
    felix_process(0, matrix, rows, cols, &sem);

    // Verify the broken cell was fixed
    EXPECT_EQ(matrix[0], 0); // Cell should now be fixed

    sem_destroy(&sem); // Clean up semaphore
}

// Test shared memory cleanup
TEST(CleanupTest, CleanupResources) {
    const char* shm_name = "/cleanup_test_shm";
    const char* sem_name = "/cleanup_test_sem";

    // Create shared memory and semaphore
    int shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, sizeof(int));
    int* matrix = (int*)mmap(nullptr, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    sem_t* sem = sem_open(sem_name, O_CREAT, 0666, 1);

    // Cleanup resources
    cleanup_resources(matrix, sizeof(int), sem);

    // Verify cleanup
    EXPECT_EQ(shm_unlink(shm_name), -1); // Shared memory should no longer exist
    EXPECT_EQ(sem_unlink(sem_name), -1); // Semaphore should no longer exist
}