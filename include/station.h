#ifndef STATION_H
#define STATION_H

#include <string>

struct Station {
    std::string name;
    double elevation_ft;
};

/**
 * @brief Finds the first station whose name matches exactly.
 * @param stations Array of stations.
 * @param count Number of stations in the array.
 * @param name Name to look for (case-sensitive).
 * @return Pointer to the matching station, or nullptr when there is none.
 */
const Station* find_station(const Station* stations, int count, const std::string& name);

#endif
