#include <gtest/gtest.h>

// 自定义测试夹具类，继承自 ::testing::Test
struct StackTest : ::testing::Test {
  static void SetUpTestSuite() {  std::cout << "init" << '\n';}
  static void TearDownTestSuite() { std::cout << "exit" << '\n'; }


    void SetUp() override {
      std::cout << "StackTest at the begin: " << std::endl;
    }

    // 在所有测试结束后调用
    void TearDown() override {
      std::cout << "StackTest at the end: " << std::endl;
    }
};

// 使用 TEST_F 宏基于测试夹具类定义测试用例
TEST_F(StackTest, PushAndPop) {
    EXPECT_EQ(5, 5);
}

// 使用 TEST_F 宏基于测试夹具类定义测试用例
TEST_F(StackTest, PushAndPop2) {
  EXPECT_EQ(6, 6);
}