
#include "txqcom.h"
#include <gtest/gtest.h>

struct MyTestEnvironment : ::testing::Environment {
    int global_counter = 0;

    // 在所有测试开始前调用
    void SetUp() override {
        global_counter = 0;
        std::cout << "Global counter value at the begin: " << global_counter << std::endl;
    }

    // 在所有测试结束后调用
    void TearDown() override {
        std::cout << "Global counter value at the end: " << global_counter << std::endl;
    }
};

int main(int argc, char** argv) {
    START_APP(argv[0]);
    ::testing::InitGoogleTest(&argc, argv);

    // 注册自定义的测试环境
    ::testing::AddGlobalTestEnvironment(new MyTestEnvironment);
    END_APP(argv[0]);
    return RUN_ALL_TESTS();
}