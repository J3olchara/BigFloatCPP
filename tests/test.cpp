#include <gtest/gtest.h>
#include <big/bigfloat.hpp>


class BigFloatStringConstructorParametersTests : public ::testing::TestWithParam<std::tuple<std::string, std::string>> {
};

TEST(BigFloatConstructorTests, NullConstructorTest) {
    BigFloat num;
    ASSERT_EQ(num.str(), "0.0");
}

TEST_P(BigFloatStringConstructorParametersTests, StringConstructorTests) {
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
    StringConstructorTests,
    BigFloatStringConstructorParametersTests,
    ::testing::Values(
        std::make_tuple("", "0.0"),
        std::make_tuple(".", "0.0"),
        std::make_tuple(".0", "0.0"),
        std::make_tuple(".0000", "0.0"),
        std::make_tuple(".123", "0.123"),
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


class BigFloatPlusOperatorParametersTests : public ::testing::TestWithParam<std::tuple<BigFloat, BigFloat, BigFloat>> {
};

TEST_P(BigFloatPlusOperatorParametersTests, PlusOperatorParametersTests) {
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
    PlusOperatorParametersTests,
    BigFloatPlusOperatorParametersTests,
    ::testing::Values(
        std::make_tuple("0.0", "0.0", "0.0"),
        std::make_tuple("12345.0", "0.0", "12345.0"),
        std::make_tuple("0.0", "54321.0", "54321.0"),
        std::make_tuple("12345.0", "54321.0", "66666.0"),
        std::make_tuple("555555.0", "555555.0", "1111110.0"),
        std::make_tuple("999999.999", "999999.999", "1999999.998"),
        std::make_tuple("10.123456789", "5.12", "15.243456789"),
        std::make_tuple("10.123456789", "5.0", "15.123456789"),
        std::make_tuple("10.123456789", "9.8766", "20.000056789")
    )
);


