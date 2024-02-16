#include <gtest/gtest.h>
#include <big/bigfloat.hpp>
#include <string>
#include <iostream>


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
        std::make_tuple("100.12", "100120.0", "100220.12"),
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
        std::make_tuple("10.123456", "20.123455", "-9.999999"),
        std::make_tuple("10.123", "10.123456", "-0.000456"),
        std::make_tuple("9999.999999", "999.999", "9000.000999"),
        std::make_tuple("10.123456", "20.123455", "-9.999999")
    )
);

class MultipleTests : public ::testing::TestWithParam<std::tuple<
    std::string,
    std::string,
    std::string
>> {
};

TEST_P(MultipleTests, Default) {
    BigFloat a(std::get<0>(GetParam()));
    BigFloat b(std::get<1>(GetParam()));
    BigFloat expected(std::get<2>(GetParam()));
    BigFloat real = a * b;

    std::stringstream bad_message;
    bad_message << a.str() << " * " << b.str() << " = " << real.str() << " computed incorrectly\n"
                << "correct answer is: " << expected.str() << ' ' << real.raw_number();
    EXPECT_EQ(real.str(), expected.str()) << bad_message.str();
}

INSTANTIATE_TEST_SUITE_P(
    Default,
    MultipleTests,
    ::testing::Values(
        std::make_tuple("0", "0", "0"),
        std::make_tuple("999999999999", "0", "0"),
        std::make_tuple("1000", "1000", "1000000"),
        std::make_tuple("100.12345", "100.12345", "10024.7052399025"),
        std::make_tuple("100.12", "100.1", "10022.012"),
        std::make_tuple("0.12345", "100000", "12345"),
        std::make_tuple("0.12345", "1000000", "123450")
    )
);

class GtTests : public ::testing::TestWithParam<std::tuple<
    BigFloat,
    BigFloat,
    bool
>> {
};

TEST_P(GtTests, Default) {
    BigFloat a(std::get<0>(GetParam()));
    BigFloat b(std::get<1>(GetParam()));
    bool expected = std::get<2>(GetParam());
    bool real = a > b;

    EXPECT_EQ(real, expected) << a.str() << " > " << b.str() << " is not " << real << " " << a.raw_number() << ' ' << b.raw_number();

}

INSTANTIATE_TEST_SUITE_P(
    Default,
    GtTests,
    ::testing::Values(
        std::make_tuple(BigFloat("0"), BigFloat("0"), false),
        std::make_tuple(BigFloat("-1"), BigFloat("10"), false),
        std::make_tuple(BigFloat("-9999"), BigFloat("0"), false),
        std::make_tuple(BigFloat("-1234"), BigFloat("-123"), false),
        std::make_tuple(BigFloat("12345.12"), BigFloat("12345.1200001"), false),
        std::make_tuple(BigFloat("12345.12"), BigFloat("12345.121"), false),
        std::make_tuple(BigFloat("12345"), BigFloat("54321"), false),
        std::make_tuple(BigFloat("11111"), BigFloat("11121"), false),
        std::make_tuple(BigFloat("1"), BigFloat("0"), true),
        std::make_tuple(BigFloat("0"), BigFloat("-9999"), true),
        std::make_tuple(BigFloat("-1"), BigFloat("-9999"), true),
        std::make_tuple(BigFloat("-1"), BigFloat("-123.123456789"), true),
        std::make_tuple(BigFloat("-1234.56789"), BigFloat("-1234.5678"), true),
        std::make_tuple(BigFloat("-1234.56789"), BigFloat("-1234.56788"), true),
        std::make_tuple(BigFloat("99999999999"), BigFloat("0"), true)
    )
);

class GetNumTests : public ::testing::TestWithParam<std::tuple<
    BigFloat,
    BigFloat,
    std::vector<int>
>> {
};

TEST_P(GetNumTests, Default) {
    BigFloat num(std::get<0>(GetParam()));
    BigFloat num_to(std::get<1>(GetParam()));
    std::vector<int> expected = (std::get<2>(GetParam()));
    std::vector<int> real(num_to.number.size());
    for (int i = 0; i < num_to.number.size(); ++i) {
        real[i] = num.get_num(i, num_to);
    }

    EXPECT_EQ(real, expected);

}

INSTANTIATE_TEST_SUITE_P(
    Default,
    GetNumTests,
    ::testing::Values(
        std::make_tuple(BigFloat("0.12"), BigFloat("12345.678"), std::vector<int>({0, 0, 0, 0, 0, 1, 2, 0})),
        std::make_tuple(BigFloat("0.123"), BigFloat("12345.678"), std::vector<int>({0, 0, 0, 0, 0, 1, 2, 3})),
        std::make_tuple(BigFloat("1"), BigFloat("12345.678"), std::vector<int>({0, 0, 0, 0, 1, 0, 0, 0})),
        std::make_tuple(BigFloat("12345"), BigFloat("12345.678"), std::vector<int>({1, 2, 3, 4, 5, 0, 0, 0}))
    )
);



