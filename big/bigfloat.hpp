#ifndef PROJECTCPP_BIGFLOAT_HPP
#define PROJECTCPP_BIGFLOAT_HPP

#include <string>



class BigFloat {
public:
    std::size_t power;
    std::string number;

    std::string str();

    BigFloat();
    explicit BigFloat(std::string);

    explicit BigFloat(int);
    explicit BigFloat(float);
    explicit BigFloat(double);
};



#endif // PROJECTCPP_BIGFLOAT_HPP
