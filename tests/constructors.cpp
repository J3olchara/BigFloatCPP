#include <gtest/gtest.h>
#include <big/bigfloat.hpp>
#include <string>


class BigFloatConstructorsTests : public ::testing::TestWithParam<std::tuple<
    std::string,
    std::deque<int>,
    size_t,
    bool
>> {
};

TEST(BigFloatConstructorsTests, ZeroTest) {
    BigFloat num;
    ASSERT_EQ(num.number, std::deque<int>());
}

TEST_P(BigFloatConstructorsTests, TestConstructorString) {
    std::string number = std::get<0>(GetParam());
    BigFloat real = BigFloat(number);
    std::deque exp_number = std::get<1>(GetParam());
    size_t exp_power = std::get<2>(GetParam());
    bool exp_minus = std::get<3>(GetParam());

    std::stringstream num;
    std::copy(real.number.begin(), real.number.end(), std::ostream_iterator<int>(num, ""));
    std::stringstream bad_message;
    bad_message << "Number " << number << " converted incorrectly: (raw_number) "
                << real.raw_number() << " correct is " << num.str() << std::endl;
    EXPECT_EQ(real.number, exp_number) << bad_message.str();
    bad_message.str("");
    bad_message << "Number " << number << " converted incorrectly: (power) "
                << real.power << " correct is " << exp_power << std::endl;
    EXPECT_EQ(real.power, exp_power) << bad_message.str();
    bad_message.str("");
    bad_message << "Number " << number << " converted incorrectly: (minus) "
                << real.minus << " correct is " << exp_minus << std::endl;
    EXPECT_EQ(real.minus, exp_minus) << bad_message.str();
}

INSTANTIATE_TEST_SUITE_P(
    TestConstructorString,
    BigFloatConstructorsTests,
    ::testing::Values(
        std::make_tuple("", std::deque<int>{}, 0ul, false),
        std::make_tuple("0", std::deque<int>{}, 0ul, false),
        std::make_tuple(".0", std::deque<int>{}, 0ul, false),
        std::make_tuple("0.0", std::deque<int>{}, 0ul, false),
        std::make_tuple(".0000", std::deque<int>{}, 0ul, false),
        std::make_tuple("0000.00000", std::deque<int>{}, 0ul, false),
        std::make_tuple(".123", std::deque<int>{1, 2, 3}, 3ul, false),
        std::make_tuple("1", std::deque<int>{1}, 0ul, false),
        std::make_tuple("0100.0000", std::deque<int>{1, 0, 0}, 0ul, false),
        std::make_tuple("00100.00100", std::deque<int>{1, 0, 0, 0, 0, 1}, 3ul, false),
        std::make_tuple("00000.00100", std::deque<int>{1}, 3ul, false),
        std::make_tuple("0.6789", std::deque<int>{6, 7, 8, 9}, 4ul, false),
        std::make_tuple("12345.0", std::deque<int>{1, 2, 3, 4, 5}, 0ul, false),
        std::make_tuple("12345.6789", std::deque<int>{1, 2, 3, 4, 5, 6, 7, 8, 9}, 4ul, false),
        std::make_tuple("-12345.6789", std::deque<int>{1, 2, 3, 4, 5, 6, 7, 8, 9}, 4ul, true),
        std::make_tuple("-0.0", std::deque<int>{}, 0ul, false)
    )
);
