#include <gtest/gtest.h>
#include <big/bigfloat.hpp>
#include <string>


class BigFloatConstructorsTests : public ::testing::TestWithParam<std::tuple<
    std::string,
    std::string
    >> {
};

TEST(BigFloatConstructorsTests, ZeroTest) {
    BigFloat num;
    ASSERT_EQ(num.str(), "0.0");
}

TEST_P(BigFloatConstructorsTests, TestConstructorString) {
    std::string expected = std::get<1>(GetParam());
    std::string number = std::get<0>(GetParam());

    BigFloat created(number);
    std::string created_str = created.str();
    std::stringstream bad_message;
    bad_message << "Number " << number << " converted incorrectly: " << created_str
                << " " << created.power << ' ' << created.raw_number();
    EXPECT_EQ(created_str, expected) << bad_message.str();
}

INSTANTIATE_TEST_SUITE_P(
    TestConstructorString,
    BigFloatConstructorsTests,
    ::testing::Values(
        std::make_tuple("", "0.0"),
        std::make_tuple(".", "0.0"),
        std::make_tuple(".0", "0.0"),
        std::make_tuple(".0000", "0.0"),
        std::make_tuple(".123", "0.123"),
        std::make_tuple("0", "0.0"),
        std::make_tuple("1", "1.0"),
        std::make_tuple("0.0", "0.0"),
        std::make_tuple("0.0000", "0.0"),
        std::make_tuple("0000.0000", "0.0"),
        std::make_tuple("0100.0000", "100.0"),
        std::make_tuple("0100.0000", "100.0"),
        std::make_tuple("00100.00100", "100.001"),
        std::make_tuple("12345.6789", "12345.6789"),
        std::make_tuple("12345.0", "12345.0"),
        std::make_tuple("-12345.6789", "-12345.6789"),
        std::make_tuple("-0.0", "0.0")
        )
);


class PlusTests : public ::testing::TestWithParam<std::tuple<
    std::string,
    std::string,
    std::string
    >> {
};

TEST_P(PlusTests, Tests) {
    BigFloat a(std::get<0>(GetParam()));
    BigFloat b(std::get<1>(GetParam()));
    BigFloat expected(std::get<2>(GetParam()));
    BigFloat real = a + b;

    std::stringstream bad_message;
    bad_message << a.str() << " + " << b.str() << " = " << real.str() << " computed incorrectly\n"
                << "correct answer is: " << expected.str() << ' ' << real.raw_number();
    EXPECT_EQ(real.str(), expected.str()) << bad_message.str();
}

INSTANTIATE_TEST_SUITE_P(
    Default,
    PlusTests,
    ::testing::Values(
        std::make_tuple("0.0", "0.0", "0.0"),
        std::make_tuple("12345.0", "0.0", "12345.0"),
        std::make_tuple("0.0", "54321.0", "54321.0"),
        std::make_tuple("12345.0", "54321.0", "66666.0"),
        std::make_tuple("555555.0", "555555.0", "1111110.0"),
        std::make_tuple("999999.999", "999999.999", "1999999.998"),
        std::make_tuple("10.123456789", "5.12", "15.243456789"),
        std::make_tuple("10.123456789", "5.0", "15.123456789"),
        std::make_tuple("10.123456789", "9.8766", "20.000056789"),
        std::make_tuple("1111110.123456789", "9.8766", "1111120.000056789")
    )
);

class MinusTests : public ::testing::TestWithParam<std::tuple<
    std::string,
    std::string,
    std::string
>> {
};

TEST_P(MinusTests, Default) {
    BigFloat a(std::get<0>(GetParam()));
    BigFloat b(std::get<1>(GetParam()));
    BigFloat expected(std::get<2>(GetParam()));
    BigFloat real = a - b;

    std::stringstream bad_message;
    bad_message << a.str() << " - " << b.str() << " = " << real.str() << " computed incorrectly\n"
                << "correct answer is: " << expected.str() << ' ' << real.raw_number();
    EXPECT_EQ(real.str(), expected.str()) << bad_message.str();
}

INSTANTIATE_TEST_SUITE_P(
    Default,
    MinusTests,
    ::testing::Values(
        std::make_tuple("0.0", "0.0", "0.0"),
        std::make_tuple("1", "0", "1.0"),
        std::make_tuple("10.123", "10", "0.123"),
        std::make_tuple("10.123", "0.124", "9.999"),
        std::make_tuple("10.12345", "10.12345", "0.0"),
        std::make_tuple("0.0", "10.123", "-10.123"),
        std::make_tuple("10.123456", "20.123457", "-9.999999")
    )
);

class ArraysLeftSumTests : public ::testing::TestWithParam<std::tuple<
    std::vector<int>,
    std::vector<int>,
    std::vector<int>,
    int
    >> {};


TEST_P(ArraysLeftSumTests, LeftSumTest) {
    std::vector<int> a = std::get<0>(GetParam());
    std::vector<int> b = std::get<1>(GetParam());
    std::vector<int> expected = std::get<2>(GetParam());
    int expected_additive = std::get<3>(GetParam());
    std::vector<int> sum;
    int additive = BigFloat::sum_arrays_left(a.begin(), a.end(), b.begin(), b.end(), sum);


    EXPECT_EQ(additive, expected_additive) << "incorrect additive " << additive << " correct is " << expected_additive;
    EXPECT_EQ(sum, expected);
}

INSTANTIATE_TEST_SUITE_P(
    LeftSumTest,
    ArraysLeftSumTests,
    ::testing::Values(
        std::make_tuple(
            std::vector<int>{1, 2, 3, 4},
            std::vector<int>{1, 2},
            std::vector<int>{2, 4, 3, 4},
            0
        ),
        std::make_tuple(
            std::vector<int>{1, 2},
            std::vector<int>{1, 2, 3, 4},
            std::vector<int>{2, 4, 3, 4},
            0
        ),
        std::make_tuple(
            std::vector<int>{1, 2, 3, 4},
            std::vector<int>{1, 2, 3, 4},
            std::vector<int>{2, 4, 6, 8},
            0
        ),
        std::make_tuple(
            std::vector<int>{1, 2, 3, 4, 5},
            std::vector<int>{1, 2, 3, 4, 5},
            std::vector<int>{2, 4, 6, 9, 0},
            0
        ),
        std::make_tuple(
            std::vector<int>{9, 9, 9, 9, 9},
            std::vector<int>{9, 9, 9, 9, 9},
            std::vector<int>{9, 9, 9, 9, 8},
            1
        ),
        std::make_tuple(
            std::vector<int>{9},
            std::vector<int>{1, 2, 3, 4},
            std::vector<int>{0, 2, 3, 4},
            1
        ),
        std::make_tuple(
            std::vector<int>{1, 2, 3, 4, 5},
            std::vector<int>{0},
            std::vector<int>{1, 2, 3, 4, 5},
            0
        ),
        std::make_tuple(
            std::vector<int>{5},
            std::vector<int>{5},
            std::vector<int>{0},
            1
        )
    )
);

class ArraysRightSumTests : public ::testing::TestWithParam<std::tuple<
    std::vector<int>,
    std::vector<int>,
    std::vector<int>,
    int
>> {};

TEST_P(ArraysRightSumTests, RightSumTests) {
    std::vector<int> a = std::get<0>(GetParam());
    std::vector<int> b = std::get<1>(GetParam());
    std::vector<int> expected = std::get<2>(GetParam());
    int expected_additive = std::get<3>(GetParam());
    std::vector<int> sum;
    int additive = BigFloat::sum_arrays_right(a.begin(), a.end(), b.begin(), b.end(), sum);


    EXPECT_EQ(additive, expected_additive) << "incorrect additive " << additive << " correct is " << expected_additive;
    EXPECT_EQ(sum, expected);
}

INSTANTIATE_TEST_SUITE_P(
    Default,
    ArraysRightSumTests,
    ::testing::Values(
        std::make_tuple(
            std::vector<int>{1, 2, 3, 4},
            std::vector<int>{1, 2},
            std::vector<int>{1, 2, 4, 6},
            0
        ),
        std::make_tuple(
            std::vector<int>{1, 2},
            std::vector<int>{1, 2, 3, 4},
            std::vector<int>{1, 2, 4, 6},
            0
        ),
        std::make_tuple(
            std::vector<int>{1, 2, 3, 4},
            std::vector<int>{1, 2, 3, 4},
            std::vector<int>{2, 4, 6, 8},
            0
        ),
        std::make_tuple(
            std::vector<int>{1, 2, 3, 4, 5},
            std::vector<int>{1, 2, 3, 4, 5},
            std::vector<int>{2, 4, 6, 9, 0},
            0
        ),
        std::make_tuple(
            std::vector<int>{9, 9, 9, 9, 9},
            std::vector<int>{9, 9, 9, 9, 9},
            std::vector<int>{9, 9, 9, 9, 8},
            1
        ),
        std::make_tuple(
            std::vector<int>{5},
            std::vector<int>{5},
            std::vector<int>{0},
            1
        )
    )
);

class ArraysLeftSubTests : public ::testing::TestWithParam<std::tuple<
    std::vector<int>,
    std::vector<int>,
    std::vector<int>,
    int
>> {};

TEST_P(ArraysLeftSubTests, LeftSubTest) {
    std::vector<int> a = std::get<0>(GetParam());
    std::vector<int> b = std::get<1>(GetParam());
    std::vector<int> expected = std::get<2>(GetParam());
    int expected_additive = std::get<3>(GetParam());
    std::vector<int> sub;
    int additive = BigFloat::sub_arrays_left(a.begin(), a.end(), b.begin(), b.end(), sub);


    EXPECT_EQ(additive, expected_additive) << "incorrect additive " << additive << " correct is " << expected_additive;
    EXPECT_EQ(sub, expected);
}

INSTANTIATE_TEST_SUITE_P(
    Default,
    ArraysLeftSubTests,
    ::testing::Values(
        std::make_tuple(
            std::vector<int>{1, 2, 3, 4},
            std::vector<int>{1, 2},
            std::vector<int>{0, 0, 3, 4},
            0
        ),
        std::make_tuple(
            std::vector<int>{1, 2},
            std::vector<int>{1, 2, 3, 4},
            std::vector<int>{9, 9, 6, 6},
            -1
        ),
        std::make_tuple(
            std::vector<int>{1, 2, 3, 4},
            std::vector<int>{1, 2, 3, 4},
            std::vector<int>{0, 0, 0, 0},
            0
        ),
        std::make_tuple(
            std::vector<int>{1, 2, 3, 4, 5},
            std::vector<int>{1, 2, 3, 4, 5},
            std::vector<int>{0, 0, 0, 0, 0},
            0
        ),
        std::make_tuple(
            std::vector<int>{9, 9, 9, 9, 9},
            std::vector<int>{9, 9, 9, 9, 9},
            std::vector<int>{9, 9, 9, 9, 8},
            1
        ),
        std::make_tuple(
            std::vector<int>{5},
            std::vector<int>{5},
            std::vector<int>{0},
            1
        )
    )
);

class ArraysRightSubTests : public ::testing::TestWithParam<std::tuple<
    std::vector<int>,
    std::vector<int>,
    std::vector<int>,
    int
>> {};

TEST_P(ArraysRightSubTests, RightSubTest) {
    std::vector<int> a = std::get<0>(GetParam());
    std::vector<int> b = std::get<1>(GetParam());
    std::vector<int> expected = std::get<2>(GetParam());
    int expected_additive = std::get<3>(GetParam());
    std::vector<int> sub;
    int additive = BigFloat::sub_arrays_left(a.begin(), a.end(), b.begin(), b.end(), sub);


    EXPECT_EQ(additive, expected_additive) << "incorrect additive " << additive << " correct is " << expected_additive;
    EXPECT_EQ(sub, expected);
}

INSTANTIATE_TEST_SUITE_P(
    Default,
    ArraysRightSubTests,
    ::testing::Values(
        std::make_tuple(
            std::vector<int>{1, 2, 3, 4},
            std::vector<int>{1, 2},
            std::vector<int>{1, 2, 2, 2},
            0
        ),
        std::make_tuple(
            std::vector<int>{1, 2},
            std::vector<int>{1, 2, 3, 4},
            std::vector<int>{1, 2, 2, 2},
            -1
        ),
        std::make_tuple(
            std::vector<int>{1, 2, 3, 4},
            std::vector<int>{1, 2, 3, 4},
            std::vector<int>{0},
            0
        ),
        std::make_tuple(
            std::vector<int>{1, 2, 3, 4, 5},
            std::vector<int>{1, 2, 3, 4, 5},
            std::vector<int>{0, 0, 0, 0, 0},
            0
        ),
        std::make_tuple(
            std::vector<int>{9, 9, 9, 9, 9},
            std::vector<int>{9, 9, 9, 9, 9},
            std::vector<int>{9, 9, 9, 9, 8},
            1
        ),
        std::make_tuple(
            std::vector<int>{5},
            std::vector<int>{5},
            std::vector<int>{0},
            1
        )
    )
);

