#include <gtest/gtest.h>

#include "math_utils.h"

TEST(CoverageTest, C0StatementCoverage) { EXPECT_TRUE(passes_exam(50, true)); }

TEST(CoverageTest, C1DecisionCoverage)
{
    EXPECT_FALSE(passes_exam(40, true));
    EXPECT_TRUE(passes_exam(50, true));
}

TEST(CoverageTest, C2ConditionCoverage)
{
    EXPECT_FALSE(passes_exam(40, false));
    EXPECT_FALSE(passes_exam(40, true));
    EXPECT_FALSE(passes_exam(50, false));
    EXPECT_TRUE(passes_exam(50, true));
}

TEST(CoverageTest, McdcCoverage)
{
    EXPECT_FALSE(passes_exam(40, true));
    EXPECT_TRUE(passes_exam(50, true));

    EXPECT_FALSE(passes_exam(50, false));
    EXPECT_TRUE(passes_exam(50, true));
}
