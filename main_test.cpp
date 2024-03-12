#include <iostream>
#include "src/lib/gtest_lite.h"

int main() {
    TEST(Test, test1) {
        EXPECT_EQ(true, true);
    } END

    return gtest_lite::Test::getTest().failed >=1;
}
