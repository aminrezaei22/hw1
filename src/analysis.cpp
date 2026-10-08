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

bool station_average(const double* temps, int rows, int cols, int station, double& average) {
    // check the row before the loop so we never index past the grid
    if (cols <= 0 || !in_bounds(station, 0, rows, cols)) {
        return false;
    }
    double sum = 0.0;
    for (int day = 0; day < cols; day++) {
        sum += temps[grid_index(station, day, cols)];
    }
    average = sum / cols;
    return true;
}
