#ifndef PROJECTCPP_BIGFLOAT_HPP
#define PROJECTCPP_BIGFLOAT_HPP

#include <string>
#include <vector>
#include <deque>
#include <sstream>
#include <iostream>



class BigFloat {
private:
    std::size_t power;
    std::deque<int> number;
    int precision = -1;
    bool minus;

    int get_index(int index, BigFloat& to_num);
    int raw_real_part_size();
    BigFloat strip_right_zeros();

public:
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
    friend BigFloat operator+(BigFloat a, BigFloat&& b);
    friend BigFloat operator-(BigFloat a, BigFloat&& b);
    friend BigFloat operator*(BigFloat a, BigFloat&& b);
    friend BigFloat operator/(BigFloat a, BigFloat&& b);
    friend BigFloat operator+(BigFloat a, int b);
    friend BigFloat operator-(BigFloat a, int b);
    friend BigFloat operator*(BigFloat a, int b);
    friend BigFloat operator/(BigFloat a, int b);

    BigFloat& operator+=(BigFloat& b);
    BigFloat& operator-=(BigFloat& b);
    BigFloat& operator*=(BigFloat& b);
    BigFloat& operator/=(BigFloat& b);
    BigFloat& operator+=(BigFloat&& b);
    BigFloat& operator-=(BigFloat&& b);
    BigFloat& operator*=(BigFloat&& b);
    BigFloat& operator/=(BigFloat&& b);
    BigFloat& operator+=(int b);
    BigFloat& operator-=(int b);
    BigFloat& operator*=(int b);
    BigFloat& operator/=(int b);
    static BigFloat get_pi(int precision);

    bool operator<(BigFloat&);
    bool operator<=(BigFloat&);
    bool operator>=(BigFloat&);
    bool operator>(BigFloat&);
    bool operator==(BigFloat&);
    bool operator!=(BigFloat& b);
    operator bool() const;

    int get_precision();
    std::deque<int> get_number();
    bool is_minus();
    std::size_t exp();
    void set_precision(int new_precision);
    void set_number(std::deque<int> new_number);
    void set_minus(bool new_minus);
    void set_exp(int new_exp);

    friend BigFloat add(BigFloat a, BigFloat& b);
    friend BigFloat sub(BigFloat a, BigFloat& b);
    friend BigFloat mul(BigFloat a, BigFloat& b);
    friend BigFloat div(BigFloat a, BigFloat& b);

    friend std::ostream& operator<< (std::ostream&, BigFloat&);

    std::string raw_number();
    std::string str();
    int real_part_size();
    int get_num(int index, BigFloat& to_num);
    BigFloat mul10(int n);
};

const BigFloat operator ""_bf(const char* bf, size_t size);
const BigFloat operator ""_bf(const long double a);
const BigFloat operator ""_bf(unsigned long long a);

#endif // PROJECTCPP_BIGFLOAT_HPP
