#ifndef PROJECTCPP_BIGFLOAT_HPP
#define PROJECTCPP_BIGFLOAT_HPP

#include <string>
#include <vector>



class BigFloat {
public:
    std::size_t power;
    std::vector<int> number;
    bool minus;

    BigFloat();
    explicit BigFloat(std::string);
    explicit BigFloat(int);
    explicit BigFloat(float);
    explicit BigFloat(double);

    BigFloat operator+(BigFloat &b);
    BigFloat operator-(BigFloat &b);
//    BigFloat operator*(BigFloat &b);
//    BigFloat operator/(BigFloat &b);

    std::string raw_number();
    std::string str();
};



#endif // PROJECTCPP_BIGFLOAT_HPP
