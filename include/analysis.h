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

/**
 * @brief Averages one station's row of readings.
 * @param temps Flat grid of readings.
 * @param rows Number of rows (stations).
 * @param cols Number of columns (days).
 * @param station Row to average.
 * @param average Set to the average when the call succeeds.
 * @return false if the station is out of range or cols <= 0, otherwise true.
 */
bool station_average(const double* temps, int rows, int cols, int station, double& average);

/**
 * @brief Averages one day's column of readings across all stations.
 * @param temps Flat grid of readings.
 * @param rows Number of rows (stations).
 * @param cols Number of columns (days).
 * @param day Column to average.
 * @param average Set to the average when the call succeeds.
 * @return false if the day is out of range or rows <= 0, otherwise true.
 */
bool day_average(const double* temps, int rows, int cols, int day, double& average);

#endif
