#include <gtest/gtest.h>
#include "kt-serial/details/singleton.h"

TEST(SingletonTest, SingletonTest) {
    int& a = KtSerial::Singleton<int>::getInstance();
    int& b = KtSerial::Singleton<int>::getInstance();
    a = 2093;
    EXPECT_EQ(b, 2093);
}