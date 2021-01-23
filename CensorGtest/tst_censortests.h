#ifndef TST_CENSORTESTS_H
#define TST_CENSORTESTS_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

using namespace testing;

TEST(CensorGtests, CensorTests)
{
    EXPECT_EQ(1, 1);
    ASSERT_THAT(0, Eq(0));
}

//включаю файл с функцией, которую буду тестировать
#include "../Censor/Functions.hpp"

TEST(CensorGtests, test1) {
    bool res = simpleTestWor();
    ASSERT_EQ(res, true);
}

TEST(CensorGtests, test2) {
    bool res = simpleTestWor();
    ASSERT_EQ(res, true);
}

#endif // TST_CENSORTESTS_H
