#ifndef ANALYSIS_H
#define ANALYSIS_H

/**
 * @brief Counts the readings strictly greater than a threshold.
 * @param temps Flat grid of readings.
 * @param rows Number of rows (stations).
 * @param cols Number of columns (days).
 * @param threshold Value a reading has to beat.
 * @return How many readings are above the threshold.
 */
int count_above(const double* temps, int rows, int cols, double threshold);

#endif
