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

bool day_average(const double* temps, int rows, int cols, int day, double& average) {
    if (rows <= 0 || !in_bounds(0, day, rows, cols)) {
        return false;
    }
    double sum = 0.0;
    for (int station = 0; station < rows; station++) {
        sum += temps[grid_index(station, day, cols)];
    }
    average = sum / rows;
    return true;
}

bool find_hottest(const double* temps, int rows, int cols, int& hot_row, int& hot_col) {
    if (rows <= 0 || cols <= 0) {
        return false;
    }
    int best_row = 0;
    int best_col = 0;
    double best = temps[grid_index(0, 0, cols)];
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            double value = temps[grid_index(row, col, cols)];
            // strictly greater so the first reading keeps a tie
            if (value > best) {
                best = value;
                best_row = row;
                best_col = col;
            }
        }
    }
    hot_row = best_row;
    hot_col = best_col;
    return true;
}
