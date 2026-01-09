#include <gtest/gtest.h>

TEST(DeloreanDB, Test) {
    EXPECT_STRNE("Hello world", "From world");
    EXPECT_EQ(42, 42);
}