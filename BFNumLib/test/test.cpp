#include <gtest/gtest.h>
#include <bfnumlib.hpp>

using namespace BFNumLib;

TEST(BFNumLibTest, Construction)
{
    bfnum num1;
    EXPECT_EQ(num1.get_string(), "0");

    bfnum num2((int)1);
    EXPECT_EQ(num2.get_string(), "1");

    bfnum num3((long)12345);
    EXPECT_EQ(num3.get_string(), "12345");

    bfnum num4((long long)1234567);
    EXPECT_EQ(num4.get_string(), "1234567");

    bfnum num5(3124.23423, 12);
    EXPECT_EQ(num5.get_string(), "3124.234230000000");
}

TEST(BFNumLibTest, Assignment)
{
    bfnum num1(123);
    bfnum num2 = num1;
    EXPECT_EQ(num2.get_string(), "123");

    bfnum num3;
    num3 = (long long)312312;
    EXPECT_EQ(num3.get_string(), "312312");

    bfnum num4;
    num4 = (double)4234.42342;
    EXPECT_EQ(num4.get_string(10), "4234.4234200000");
}

TEST(BFNumLibTest, ComparisonOperators)
{
    bfnum num1(123);
    bfnum num2(234.32);
    EXPECT_EQ(num1 == num2, false);
    EXPECT_EQ(num1 == num1, true);
    EXPECT_EQ(num1 != num2, true);
    EXPECT_EQ(num1 != num1, false);

    bfnum num3(-123);
    bfnum num4(-234.32);
    EXPECT_EQ(num1 > num2, false);
    EXPECT_EQ(num1 < num2, true);
    EXPECT_EQ(num1 > num3, true);
    EXPECT_EQ(num1 > num4, true);
    EXPECT_EQ(num3 > num4, true);
    EXPECT_EQ(num3 < num4, false);
}

TEST(BFNumLibTest, ArithmeticOperators)
{
    bfnum num1(3123.534);
    bfnum num2(42.4);
    bfnum num3(-53.81);
    bfnum num4(0.5);
    bfnum null;

    EXPECT_EQ((num1 + num2).get_string(), "3165.934");
    EXPECT_EQ((num1 + num3).get_string(), "3069.724");

    EXPECT_EQ((num1 - num2).get_string(), "3081.134");
    EXPECT_EQ((num1 - num3).get_string(), "3177.344");
    EXPECT_EQ((num3 - num2).get_string(), "96.21");
    EXPECT_EQ((num2 - num1).get_string(), "-3081.134");

    EXPECT_EQ((num1 * num2).get_string(), "132437.8416");
    EXPECT_EQ((num1 * num3).get_string(), "-168077.36454");
    EXPECT_EQ((num1 * num4).get_string(), "1561.767");
    EXPECT_EQ((num1 * null).get_string(), "0");

    EXPECT_EQ((num1 / num2).get_string(10), "73.6682547169");
    EXPECT_EQ((null / num3).get_string(), "0");
    EXPECT_EQ((num4 / num1).get_string(10), "0.0001600750");
    EXPECT_EQ((num3 / num3).get_string(), "1");
}