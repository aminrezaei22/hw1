#include "analysis.h"

#include "grid.h"

int count_above(const double* temps, int rows, int cols, double threshold) {
    int count = 0;
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (temps[grid_index(row, col, cols)] > threshold) {
                count++;
            }
        }
    }
    return count;
}
