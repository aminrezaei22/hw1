#ifndef REPORT_H
#define REPORT_H

#include "station.h"

/**
 * @brief Prints the station table and the hottest reading.
 * @param stations Array of stations, one per row of the grid.
 * @param temps Flat grid of readings, row = station and column = day.
 * @param rows Number of stations.
 * @param cols Number of days.
 */
void print_report(const Station* stations, const double* temps, int rows, int cols);

#endif
