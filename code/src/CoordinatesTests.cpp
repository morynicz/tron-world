#include "tronWorld/Coordinates.hpp"
#include "gtest/gtest.h"

TEST(CoordsTests, addition)
{
  Coordinates2d x1{ 1, 4 };
  Coordinates2d x2{ 6, 8 };
  Coordinates2d xe{ 7, 12 };

  EXPECT_EQ(x1 + x2, xe);
}