#ifndef PROJECTCPP_BIGFLOAT_HPP
#define PROJECTCPP_BIGFLOAT_HPP

#include <string>
#include <vector>
#include <sstream>
#include <iostream>



class BigFloat {
public:
    std::size_t power;
    std::vector<int> number;
    bool minus;

    int get_num(int index, BigFloat& to_num);

    BigFloat();
    explicit BigFloat(std::string);
    explicit BigFloat(int);
    explicit BigFloat(float);
    explicit BigFloat(double);
    BigFloat(const std::vector<int>&, const std::vector<int>&);
    BigFloat operator-();
    BigFloat operator+();
    BigFloat operator+(BigFloat& b);
    BigFloat operator-(BigFloat& b);
    BigFloat operator*(BigFloat &b);
//    BigFloat operator/(BigFloat &b);

    BigFloat operator+=(BigFloat& b);
    BigFloat operator-=(BigFloat& b);
    BigFloat operator*=(BigFloat& b);
//    BigFloat operator/=(BigFloat& b);


    bool operator<(BigFloat&);
    bool operator<=(BigFloat&);
    bool operator>=(BigFloat&);
    bool operator>(BigFloat&);
    bool operator==(BigFloat&);
    bool operator!=(BigFloat& b);

    friend std::ostream& operator<< (std::ostream&, BigFloat&);

    std::string raw_number();
    std::string str();
};



#endif // PROJECTCPP_BIGFLOAT_HPP
