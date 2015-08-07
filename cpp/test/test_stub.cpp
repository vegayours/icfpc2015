#include "stub_fun.h"

#include "gtest/gtest.h"

TEST(StubFunTest, CorrectAddition) {
    EXPECT_EQ(10, add(3, 7));
}

