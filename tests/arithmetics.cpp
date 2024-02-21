#include <gtest/gtest.h>
#include <big/bigfloat.hpp>
#include <string>
#include <iostream>


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
        std::make_tuple("0.1", "0.1", "0.2"),
        std::make_tuple("100000.0", "100000.0", "200000.0"),
        std::make_tuple("1111110.123456789", "9.8766", "1111120.000056789"),
        std::make_tuple("-1111110.123456789", "-9.8766", "-1111120.000056789"),
        std::make_tuple("1234", "0.5", "1234.5")
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
        std::make_tuple("9999.999999", "0.1", "9999.899999"),
        std::make_tuple("0.3454259025", "0.10012345", "0.2453024525"),
        std::make_tuple("0.0450555525", "0.040049380", "0.0050061725"),
        std::make_tuple("0.0450555525", "0.010012345", "0.0350432075"),
        std::make_tuple("10.123456", "20.123455", "-9.999999"),
        std::make_tuple("0.0050061725", "0.0050061725", "0.0"),
        std::make_tuple("0.0050061725", "0.0010012345", "0.0040049380")

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
        std::make_tuple("1.0", "4.0", "4.0"),
        std::make_tuple("1000", "1000", "1000000"),
        std::make_tuple("100.12345", "100.12345", "10024.7052399025"),
        std::make_tuple("100.12", "100.1", "10022.012"),
        std::make_tuple("0.12345", "100000", "12345"),
        std::make_tuple("0.12345", "0.1", "0.012345"),
        std::make_tuple("1.2345", "0.00001", "0.000012345"),
        std::make_tuple("0.12345", "1000000", "123450"),
        std::make_tuple("0.0012345", "1000000", "1234.5")

    )
);

class DivisionTests : public ::testing::TestWithParam<std::tuple<
    std::string,
    std::string,
    std::string
>> {
};

TEST_P(DivisionTests, Default) {
    BigFloat a(std::get<0>(GetParam()));
    BigFloat b(std::get<1>(GetParam()));
    BigFloat expected(std::get<2>(GetParam()));
    BigFloat real = a / b;

    std::stringstream bad_message;
    bad_message << a.str() << " / " << b.str() << " = " << real.str() << " computed incorrectly\n"
                << "correct answer is: " << expected.str() << ' ' << real.raw_number();
    EXPECT_EQ(real.str(), expected.str()) << bad_message.str();
}

INSTANTIATE_TEST_SUITE_P(
    Default,
    DivisionTests,
    ::testing::Values(
        std::make_tuple("0", "123456789", "0"),
        std::make_tuple("1000000", "1000", "1000"),
        std::make_tuple("10024.7052399025", "100.12345", "100.12345"),
        std::make_tuple("10022.012","100.12", "100.1"),
        std::make_tuple("12345", "0.12345", "100000"),
        std::make_tuple("123450", "0.12345", "1000000"),
        std::make_tuple("1", "1", "1")

    )
);

class Mul10Tests : public ::testing::TestWithParam<std::tuple<
    std::string,
    int,
    std::string
>> {
};

TEST_P(Mul10Tests, Default) {
    BigFloat a(std::get<0>(GetParam()));
    int n = std::get<1>(GetParam());
    BigFloat expected(std::get<2>(GetParam()));

    BigFloat real = a.mul10(n);

    std::stringstream bad_message;
    bad_message << a.str() << " * 10^(" << n << ") = " << real.str() << " computed incorrectly\n"
                << "correct answer is: " << expected.str() << ' ' << real.raw_number();
    EXPECT_EQ(real.str(), expected.str()) << bad_message.str();
}

INSTANTIATE_TEST_SUITE_P(
    Default,
    Mul10Tests,
    ::testing::Values(
        std::make_tuple("0.1", -1, "0.01"),
        std::make_tuple("1000", -3, "1.0"),
        std::make_tuple("0.1", -3, "0.0001"),
        std::make_tuple("0.1", 1, "1.0"),
        std::make_tuple("1", 1, "10"),
        std::make_tuple("0.1", 3, "100.0")
    )
);
