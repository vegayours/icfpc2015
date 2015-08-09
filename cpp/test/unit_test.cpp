#include "common/unit.h"

#include <gtest/gtest.h>

TUnit MakeUnit() {
    return TUnit({
        TCellPos(0, 3),
        TCellPos(1, 3),
        TCellPos(2, 4),
        TCellPos(0, 4)
    }, TCellPos(0, 0));
}

TEST(TUnitSizeTest, TestAll) {
    TUnit unit = MakeUnit();

    EXPECT_EQ(0, unit.MinCol());
    EXPECT_EQ(2, unit.MaxCol());
    EXPECT_EQ(3, unit.MinRow());
    EXPECT_EQ(4, unit.MaxRow());

    EXPECT_EQ(3, unit.Width());
    EXPECT_EQ(2, unit.Height());
}

