#include <gtest/gtest.h>
#include <iostream>

TEST(TestTests, Test) {
    std::cout << "\n\n\nTest!!!!\n\n\n";
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
