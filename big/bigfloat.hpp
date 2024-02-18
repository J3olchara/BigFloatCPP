#ifndef PROJECTCPP_BIGFLOAT_HPP
#define PROJECTCPP_BIGFLOAT_HPP

#include <string>
#include <vector>
#include <deque>
#include <sstream>
#include <iostream>



class BigFloat {
public:
    std::size_t power;
    std::deque<int> number;
    bool minus;

    BigFloat();
    explicit BigFloat(std::string);
    explicit BigFloat(int);
    explicit BigFloat(float);
    explicit BigFloat(double);
    BigFloat operator-();
    BigFloat operator+();
    friend BigFloat operator+(BigFloat a, BigFloat& b);
    friend BigFloat operator-(BigFloat a, BigFloat& b);
    friend BigFloat operator*(BigFloat a, BigFloat& b);
    friend BigFloat operator/(BigFloat a, BigFloat& b);

    BigFloat& operator+=(BigFloat& b);
    BigFloat& operator-=(BigFloat& b);
    BigFloat& operator*=(BigFloat& b);
    BigFloat& operator/=(BigFloat& b);

    bool operator<(BigFloat&);
    bool operator<=(BigFloat&);
    bool operator>=(BigFloat&);
    bool operator>(BigFloat&);
    bool operator==(BigFloat&);
    bool operator!=(BigFloat& b);
    operator bool() const;

    friend std::ostream& operator<< (std::ostream&, BigFloat&);

    std::string raw_number();
    std::string str();
    int get_num(int index, BigFloat& to_num);
    int get_index(int index, BigFloat& to_num);
    int real_part_size();
    int raw_real_part_size();
    BigFloat mul10(int n);
    BigFloat strip_right_zeros();
};



#endif // PROJECTCPP_BIGFLOAT_HPP
