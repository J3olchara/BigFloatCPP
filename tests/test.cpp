#include <gtest/gtest.h>
#include <big/bigfloat.hpp>
#include <string>

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
    size_t rps1 = num.real_part_size() < 1 ? 1 : num.real_part_size();
    size_t rps2 = num_to.real_part_size() < 1 ? 1 : num_to.real_part_size();
    size_t nums_size = std::max(rps1, rps2) + std::max(num_to.exp(), num.exp());
    std::vector<int> real(nums_size);
    for (int i = 0; i < nums_size; ++i) {
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
        std::make_tuple(BigFloat("12345"), BigFloat("12345.678"), std::vector<int>({1, 2, 3, 4, 5, 0, 0, 0})),
        std::make_tuple(BigFloat("0.00001"), BigFloat("12345.678"), std::vector<int>({0, 0, 0, 0, 0, 0, 0, 0, 0, 1})),
        std::make_tuple(BigFloat("12345.678"), BigFloat("0.00001"), std::vector<int>({1, 2, 3, 4, 5, 6, 7, 8, 0, 0})),
        std::make_tuple(BigFloat("11100"), BigFloat("0.00001"), std::vector<int>({1, 1, 1, 0, 0, 0, 0, 0, 0, 0})),
        std::make_tuple(BigFloat("0.001"), BigFloat("0.00001"), std::vector<int>({0, 0, 0, 1, 0, 0})),
        std::make_tuple(BigFloat("0.001111"), BigFloat("0.01001"), std::vector<int>({0, 0, 0, 1, 1, 1, 1})),
        std::make_tuple(BigFloat("11"), BigFloat("100000"), std::vector<int>({0, 0, 0, 0, 1, 1})),
        std::make_tuple(BigFloat("0.00001"), BigFloat("1.2345"), std::vector<int>({0, 0, 0, 0, 0, 1})),
        std::make_tuple(BigFloat("0.12345"), BigFloat("0.1"), std::vector<int>({0, 1, 2, 3, 4, 5})),
        std::make_tuple(BigFloat("100000"), BigFloat("11"), std::vector<int>({1, 0, 0, 0, 0, 0}))
    )
);


class StrTests : public ::testing::TestWithParam<std::tuple<
    std::string,
    std::string
    >> {
    // test requires stable BigFloat Constructor
};


TEST_P(StrTests, Default) {
    BigFloat num(std::get<0>(GetParam()));
    std::string expected = std::get<1>(GetParam());

    std::stringstream bad_message;
    bad_message << num.raw_number() << " converted in str incorrectly: " << num.str() << std::endl
                << "Correct str is: " << expected << std::endl;
    EXPECT_EQ(num.str(), expected) << bad_message.str();
}

INSTANTIATE_TEST_SUITE_P(
    Default,
    StrTests,
    ::testing::Values(
        std::make_tuple("0", "0.0"),
        std::make_tuple("123", "123.0"),
        std::make_tuple("1234.5678", "1234.5678"),
        std::make_tuple("0.1234", "0.1234"),
        std::make_tuple("-0.000456", "-0.000456")
        )
);
