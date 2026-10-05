#ifndef GRID_H
#define GRID_H

/**
 * @brief Checks whether a row and column are inside the grid.
 * @param row Row to check.
 * @param col Column to check.
 * @param rows Number of rows in the grid.
 * @param cols Number of columns in the grid.
 * @return true only when 0 <= row < rows and 0 <= col < cols.
 */
bool in_bounds(int row, int col, int rows, int cols);

#endif
