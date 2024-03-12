#include <iostream>
#include "src/lib/gtest_lite.h"

int main() {
    TEST(Test, test1) {
        EXPECT_EQ(true, false);
    } END
    TEST(Test, test2) {
        EXPECT_EQ(true, true);
    } END
    TEST(Test, test3) {
        EXPECT_EQ(true, false);
    } END

    return gtest_lite::Test::getTest().failed >=1;
}
