#include <gtest/gtest.h>
#include <big/bigfloat.hpp>


class BigFloatStringConstructorParametersTests : public ::testing::TestWithParam<std::tuple<std::string, std::string>> {

};
TEST(BigFloatConstructorTests, NullConstructorTest) {
    BigFloat num;
    ASSERT_EQ(num.str(), "0.0");
}

TEST_P(BigFloatStringConstructorParametersTests, StringConstructorTests) {
    std::string excepted = std::get<1>(GetParam());
    std::string number = std::get<0>(GetParam());

    BigFloat created(number);
    std::string created_str = created.str();
    EXPECT_EQ(created_str, excepted) << "Number " << number << " converted incorrectly: " << created_str;
}

INSTANTIATE_TEST_SUITE_P(
    StringConstructorTests,
    BigFloatStringConstructorParametersTests,
    ::testing::Values(
        std::make_tuple("", "0.0"),
        std::make_tuple(".", "0.0"),
        std::make_tuple(".0", "0.0"),
        std::make_tuple(".0000", "0.0"),
        std::make_tuple("0.0", "0.0"),
        std::make_tuple("0.0000", "0.0"),
        std::make_tuple("0000.0000", "0.0"),
        std::make_tuple("0100.0000", "100.0"),
        std::make_tuple("0100.0000", "100.0"),
        std::make_tuple("00100.00100", "100.001"),
        std::make_tuple("12345.6789", "12345.6789")
        )
);

