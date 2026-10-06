#include <gtest/gtest.h>

#include "grid.h"

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
