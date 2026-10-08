#include <gtest/gtest.h>

#include "analysis.h"
#include "grid.h"
#include "station.h"

TEST(InBounds, InsideGrid) {
    EXPECT_TRUE(in_bounds(0, 0, 2, 3));
    EXPECT_TRUE(in_bounds(1, 1, 2, 3));
}

TEST(InBounds, LastValidAgainstFirstInvalid) {
    EXPECT_TRUE(in_bounds(1, 2, 2, 3));
    EXPECT_FALSE(in_bounds(2, 2, 2, 3));
    EXPECT_FALSE(in_bounds(1, 3, 2, 3));
}

TEST(InBounds, NegativeIndex) {
    EXPECT_FALSE(in_bounds(-1, 0, 2, 3));
    EXPECT_FALSE(in_bounds(0, -1, 2, 3));
}

TEST(InBounds, EmptyGrid) {
    EXPECT_FALSE(in_bounds(0, 0, 0, 3));
    EXPECT_FALSE(in_bounds(0, 0, 2, 0));
}

TEST(GridIndex, RowMajor) {
    EXPECT_EQ(grid_index(0, 0, 3), 0);
    EXPECT_EQ(grid_index(0, 2, 3), 2);
    EXPECT_EQ(grid_index(1, 0, 3), 3);
    EXPECT_EQ(grid_index(1, 2, 3), 5);
}

TEST(CountAbove, CountsStrictlyGreater) {
    const double grid[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    EXPECT_EQ(count_above(grid, 2, 3, 3.0), 3);
    EXPECT_EQ(count_above(grid, 2, 3, 6.0), 0);
    EXPECT_EQ(count_above(grid, 2, 3, 0.0), 6);
}

TEST(CountAbove, EmptyGrid) {
    const double grid[1] = {1.0};
    EXPECT_EQ(count_above(grid, 0, 3, 0.0), 0);
    EXPECT_EQ(count_above(grid, 2, 0, 0.0), 0);
}

TEST(FindStation, FindsByExactName) {
    const Station stations[2] = {{"Denton", 642.0}, {"Waco", 470.0}};
    const Station* found = find_station(stations, 2, "Waco");
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found, &stations[1]);
    EXPECT_DOUBLE_EQ(found->elevation_ft, 470.0);
}

TEST(FindStation, NotFoundReturnsNullptr) {
    const Station stations[2] = {{"Denton", 642.0}, {"Waco", 470.0}};
    EXPECT_EQ(find_station(stations, 2, "Austin"), nullptr);
    EXPECT_EQ(find_station(stations, 2, "waco"), nullptr);
    EXPECT_EQ(find_station(stations, 0, "Denton"), nullptr);
}

TEST(StationAverage, AveragesOneRow) {
    const double grid[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    double avg = 0.0;
    EXPECT_TRUE(station_average(grid, 2, 3, 0, avg));
    EXPECT_DOUBLE_EQ(avg, 2.0);
    EXPECT_TRUE(station_average(grid, 2, 3, 1, avg));
    EXPECT_DOUBLE_EQ(avg, 5.0);
}

TEST(StationAverage, FailureLeavesAverageAlone) {
    const double grid[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    double avg = -1.0;
    EXPECT_FALSE(station_average(grid, 2, 3, 2, avg));
    EXPECT_FALSE(station_average(grid, 2, 3, -1, avg));
    EXPECT_FALSE(station_average(grid, 2, 0, 0, avg));
    EXPECT_FALSE(station_average(grid, 0, 3, 0, avg));
    EXPECT_DOUBLE_EQ(avg, -1.0);
}

TEST(DayAverage, AveragesOneColumn) {
    const double grid[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    double avg = 0.0;
    EXPECT_TRUE(day_average(grid, 2, 3, 0, avg));
    EXPECT_DOUBLE_EQ(avg, 2.5);
    EXPECT_TRUE(day_average(grid, 2, 3, 2, avg));
    EXPECT_DOUBLE_EQ(avg, 4.5);
}

TEST(DayAverage, FailureLeavesAverageAlone) {
    const double grid[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    double avg = -1.0;
    EXPECT_FALSE(day_average(grid, 2, 3, 3, avg));
    EXPECT_FALSE(day_average(grid, 2, 3, -1, avg));
    EXPECT_FALSE(day_average(grid, 0, 3, 0, avg));
    EXPECT_DOUBLE_EQ(avg, -1.0);
}

TEST(FindHottest, FindsHighestReading) {
    const double grid[6] = {1.0, 9.0, 3.0, 4.0, 5.0, 6.0};
    int row = -1;
    int col = -1;
    EXPECT_TRUE(find_hottest(grid, 2, 3, row, col));
    EXPECT_EQ(row, 0);
    EXPECT_EQ(col, 1);
}

TEST(FindHottest, FirstInRowMajorOrderWinsTie) {
    const double grid[4] = {5.0, 1.0, 5.0, 5.0};
    int row = -1;
    int col = -1;
    EXPECT_TRUE(find_hottest(grid, 2, 2, row, col));
    EXPECT_EQ(row, 0);
    EXPECT_EQ(col, 0);
}

TEST(FindHottest, EmptyGridLeavesOutputsAlone) {
    const double grid[1] = {1.0};
    int row = -1;
    int col = -1;
    EXPECT_FALSE(find_hottest(grid, 0, 3, row, col));
    EXPECT_FALSE(find_hottest(grid, 2, 0, row, col));
    EXPECT_EQ(row, -1);
    EXPECT_EQ(col, -1);
}
