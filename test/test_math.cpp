#include <gtest/gtest.h>

#include "math_utils.h"

TEST(AddTest, PositiveNumbers)
{
    EXPECT_EQ(add(2, 3), 5);
}

TEST(AddTest, NegativeNumbers)
{
    EXPECT_EQ(add(-2, -3), -5);
}

TEST(AddTest, MixedNumbers)
{
    EXPECT_EQ(add(-2, 3), 1);
}
