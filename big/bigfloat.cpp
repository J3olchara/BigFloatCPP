#include "arithmetics.hpp"
#include "bigfloat.hpp"
#include <string>
#include <iterator>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <utility>

int BigFloat::get_index(int index, BigFloat& to_num) {
    int rps1 = this->raw_real_part_size();
    int rps2 = to_num.raw_real_part_size();
    if (rps1 > 0 and rps2 > 0 and rps1 >= rps2) return index;
    if (rps1 > 0 and rps2 > 0 and rps1 < rps2) return index + (rps1 - rps2);
    if (rps1 <= 0 and rps2 > 0) return index + (rps1 - rps2);
    if (rps1 > 0 and rps2 <= 0) return index;
    if (rps1 <= 0 and rps2 <= 0) return index + rps1 - 1;
}

BigFloat BigFloat::strip_right_zeros() {
    int rps = this->real_part_size();
    for (int i = static_cast<int>(this->number.size()) - 1; i >= rps and !*(this->number.end() - 1); --i) {
        this->number.pop_back();
        this->power--;
    }
    return *this;
}

int BigFloat::raw_real_part_size() {
    return static_cast<int>(this->number.size()) - static_cast<int>(this->power);
}
int BigFloat::real_part_size() {
    int n = this->raw_real_part_size();
    if (n <= 0) return 1;
    else return n;
}

std::string BigFloat::raw_number() {
    std::stringstream ss;
    std::copy(this->number.begin(), this->number.end(), std::ostream_iterator<int>(ss, ""));
    return ss.str();
}

int BigFloat::get_num(int index, BigFloat& to_num) { // 12345.678 0.12
    int idx = this->get_index(index, to_num);
    if (idx < 0 or idx >= this->number.size()) return 0;
    return this->number[idx];
}

std::string BigFloat::str()  {
    std::string answer;
    answer.reserve(this->number.size() + 1 + this->minus);
    if (this->minus) answer.push_back('-');
    int i = 0;

    // real part
    for (;i < this->raw_real_part_size(); ++i) answer.push_back(this->number[i] + '0');
    if (this->raw_real_part_size() <= 0) answer.push_back('0');

    answer.push_back('.');

    // float part
    for (int j = 0; this->number.size() + j < this->power; ++j) answer.push_back('0');
    for (;i < this->number.size(); ++i) answer.push_back(this->number[i] + '0');
    if (this->power == 0) answer.push_back('0');
    return answer;
}

BigFloat BigFloat::mul10(int n) {
    if (this->number.empty()) return *this;
    if (n >= 0) {
        for (int i = 0; i < n; ++i) {
            if (!this->power)
                this->number.push_back(0);
            else
                this->power--;
        }
        return *this;
    }
    for (int i = 0; i > n; --i) {
        if (!*(this->number.end() - 1))
            this->number.erase(this->number.end() - 1);
        else
            this->power++;
    }
    return *this;
}

BigFloat::BigFloat() {
    this->number = std::deque<int>();
    this->power = 0;
    this->minus = false;
}

BigFloat::BigFloat(std::string number) {
    this->number = std::deque<int>();
    this->power = 0;
    int size = static_cast<int>(number.size());
    this->minus = false;

    int i = 0;
    if (number[i] == '-') {
        this->minus = true;
        i++;
    }
    while (i < size && number[i] == '0') i++;
    // pushing real part
    while (i < size && number[i] != '.') {
        this->number.push_back(number[i] - '0');
        i++;
    }
    if (number[i] == '.') i++;
    else return;
    // pushing float part
    int right_zeros = 0;
    if (this->number.empty()) {
        while (i < size && number[i] == '0') {
            this->power++;
            i++;
        }
    }
    if (i >= size) this->power = 0;
    while (i < size) {
        this->number.push_back(number[i] - '0');
        if (number[i] - '0' != 0) right_zeros = 0;
        else right_zeros++;
        this->power++;
        i++;
    }
    this->power -= right_zeros;
    for (int i = 0; i < right_zeros; ++i) {
        this->number.erase(this->number.end() - 1);
    }
    if (this->number.empty() and this->minus) {this->minus = false;}
}

BigFloat::BigFloat(int number) : BigFloat(std::to_string(number)) {}
BigFloat::BigFloat(float number) : BigFloat(std::to_string(number)) {}
BigFloat::BigFloat(double number) : BigFloat(std::to_string(number)) {}

BigFloat BigFloat::operator-() {
    if (this->number.empty()) return *this;
    BigFloat cop = *this;
    cop.minus = not cop.minus;
    return cop;
}
BigFloat BigFloat::operator+() {
    return *this;
}


BigFloat operator+(BigFloat a, BigFloat& b) {
    return add(std::move(a), b);
}

BigFloat operator+(BigFloat a, BigFloat&& b) {
    return add(std::move(a), b);
}

BigFloat operator+(BigFloat a, int b) {
    BigFloat b2(b);
    BigFloat ans = add(std::move(a), b2);
    return ans;
}

BigFloat operator-(BigFloat a, BigFloat& b) {
    return sub(std::move(a), b);
}

BigFloat operator-(BigFloat a, BigFloat&& b) {
    return sub(std::move(a), b);
}

BigFloat operator-(BigFloat a, int b) {
    BigFloat b2(b);
    BigFloat ans = sub(std::move(a), b2);
    return ans;
}

BigFloat operator*(BigFloat a, BigFloat& b) {
    return mul(std::move(a), b);
}

BigFloat operator*(BigFloat a, BigFloat&& b) {
    return mul(std::move(a), b);
}

BigFloat operator*(BigFloat a, int b) {
    BigFloat b2(b);
    BigFloat ans = mul(std::move(a), b2);
    return ans;
}

BigFloat operator/(BigFloat a, BigFloat& b) {
    return div(std::move(a), b);
}

BigFloat operator/(BigFloat a, BigFloat&& b) {
    return div(std::move(a), b);
}

BigFloat operator/(BigFloat a, int b) {
    BigFloat b2(b);
    BigFloat ans = div(std::move(a), b2);
    return ans;
}

BigFloat& BigFloat::operator+=(BigFloat& b) {
    *this = *this + b;
    return *this;
}

BigFloat& BigFloat::operator+=(BigFloat&& b) {
    *this = *this + b;
    return *this;
}

BigFloat& BigFloat::operator+=(int b) {
    *this = *this + b;
    return *this;
}

BigFloat& BigFloat::operator-=(BigFloat& b) {
    *this = *this - b;
    return *this;
}

BigFloat& BigFloat::operator-=(BigFloat&& b) {
    *this = *this - b;
    return *this;
}

BigFloat& BigFloat::operator-=(int b) {
    *this = *this - b;
    return *this;
}

BigFloat& BigFloat::operator*=(BigFloat& b) {
    *this = *this * b;
    return *this;
}

BigFloat& BigFloat::operator*=(BigFloat&& b) {
    *this = *this * b;
    return *this;
}

BigFloat& BigFloat::operator*=(int b) {
    *this = *this * b;
    return *this;
}

BigFloat& BigFloat::operator/=(BigFloat& b) {
    *this = *this / b;
    return *this;
}

BigFloat& BigFloat::operator/=(BigFloat&& b) {
    *this = *this / b;
    return *this;
}

BigFloat& BigFloat::operator/=(int b) {
    *this = *this / b;
    return *this;
}


bool BigFloat::operator<(BigFloat& b) {
    return b > *this;
}

bool BigFloat::operator<=(BigFloat& b) {
    return !(*this > b);
}

bool BigFloat::operator>=(BigFloat& b) {
    return !(b > *this);
}

bool BigFloat::operator>(BigFloat& b) {
    if (    this->minus and not b.minus) return false;
    if (not this->minus and     b.minus) return true;
    int max_size = static_cast<int>(std::max(this->real_part_size(), b.real_part_size()) + std::max(this->power, b.power));
    int i = 0;
    while (i < max_size and this->get_num(i, b) == b.get_num(i, *this)) {
        i++;
    }
    if (i >= max_size) return false;
    bool ans = this->get_num(i, b) > b.get_num(i, *this);
    if (this->minus and b.minus) return !ans;
    return ans;
}

bool BigFloat::operator==(BigFloat& b) {
    return this->str() == b.str();
}

bool BigFloat::operator!=(BigFloat& b) {
    return not (*this == b);
}

BigFloat::operator bool() const {
    return !this->number.empty();
}

std::ostream& operator<<(std::ostream& os, BigFloat& num) {
    return os << num.str();
}

const BigFloat operator ""_bf(const char* bf, size_t size) {
    return BigFloat(std::string(bf, size));
}
const BigFloat operator ""_bf(const long double a) {
    return BigFloat(std::to_string(a));
}
const BigFloat operator ""_bf(unsigned long long a) {
    return BigFloat(std::to_string(a));
}