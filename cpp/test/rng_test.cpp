#include "common/rnd_gen.h"
#include <gtest/gtest.h>

TEST(TRndGenTest, CheckRng) {
    using namespace NCommon;
    TRndGen gen(17);
    uint32_t expected[] = {0, 24107, 16552, 12125, 9427, 13152, 21440, 3383, 6873, 16117};
    size_t cnt = sizeof(expected) / sizeof(expected[0]);
    for (size_t i = 0; i < cnt; i++) {
        EXPECT_EQ(gen.Next(), expected[i]);
    }
}
