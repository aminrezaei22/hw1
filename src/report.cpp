#include "report.h"

#include <iomanip>
#include <iostream>

#include "analysis.h"
#include "grid.h"

void print_report(const Station* stations, const double* temps, int rows, int cols) {
    std::cout << "=== Weather Station Report ===\n";
    for (int station = 0; station < rows; station++) {
        std::cout << std::left << std::setw(12) << stations[station].name
                  << std::right << std::setw(7) << std::fixed << std::setprecision(0)
                  << stations[station].elevation_ft << " ft";
        double avg = 0.0;
        if (station_average(temps, rows, cols, station, avg)) {
            std::cout << "   avg " << std::setw(6) << std::setprecision(2) << avg << " F";
        }
        std::cout << "\n";
    }

    int hot_row = 0;
    int hot_col = 0;
    if (find_hottest(temps, rows, cols, hot_row, hot_col)) {
        // days are shown 1-based for the reader
        std::cout << "Hottest reading: " << std::setprecision(1)
                  << temps[grid_index(hot_row, hot_col, cols)] << " F at "
                  << stations[hot_row].name << " (day " << hot_col + 1 << ")\n";
    }
}
