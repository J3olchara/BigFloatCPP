#include <gtest/gtest.h>
#include <big/bigfloat.hpp>
#include <string>

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
        std::make_tuple(BigFloat("0"), BigFloat("0.01"), false),
        std::make_tuple(BigFloat("-1"), BigFloat("10"), false),
        std::make_tuple(BigFloat("-9999"), BigFloat("0"), false),
        std::make_tuple(BigFloat("-1234"), BigFloat("-123"), false),
        std::make_tuple(BigFloat("12345.12"), BigFloat("12345.1200001"), false),
        std::make_tuple(BigFloat("12345.12"), BigFloat("12345.121"), false),
        std::make_tuple(BigFloat("12345"), BigFloat("54321"), false),
        std::make_tuple(BigFloat("11111"), BigFloat("11121"), false),
        std::make_tuple(BigFloat("-1234.56789"), BigFloat("-1234.5678"), false),
        std::make_tuple(BigFloat("-1234.56789"), BigFloat("-1234.56788"), false),
        std::make_tuple(BigFloat("0.0010012345"), BigFloat("0.0050061725"), false),
        std::make_tuple(BigFloat("0.010012345"), BigFloat("0.0050061725"), true),
        std::make_tuple(BigFloat("1"), BigFloat("0"), true),
        std::make_tuple(BigFloat("0"), BigFloat("-9999"), true),
        std::make_tuple(BigFloat("-1"), BigFloat("-9999"), true),
        std::make_tuple(BigFloat("-1"), BigFloat("-123.123456789"), true),
        std::make_tuple(BigFloat("99999999999"), BigFloat("0"), true)
    )
);
