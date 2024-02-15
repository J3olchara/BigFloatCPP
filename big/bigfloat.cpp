#include <string>
#include "bigfloat.hpp"
#include <iterator>
#include <algorithm>
#include <sstream>
#include <iostream>


inline std::string BigFloat::raw_number() {
    std::stringstream ss;
    std::copy(this->number.begin(), this->number.end(), std::ostream_iterator<int>(ss, ""));
    return ss.str();
}

int BigFloat::get_num(int index, BigFloat& to_num) { // 12345.678 0.12
    int real_part = static_cast<int>(this->number.size()) - static_cast<int>(this->power);
    int real_part_to = static_cast<int>(to_num.number.size()) - static_cast<int>(to_num.power);
    int idx = index - real_part_to + real_part;
    if (idx < 0 or idx >= this->number.size()) return 0;
    return this->number[idx];
}


std::string BigFloat::str()  {
    std::string answer = this->raw_number();
    size_t s_size = this->number.size() + 1;
    answer.push_back(answer[s_size - 2]);
    for (size_t i = s_size - 1; i > s_size - this->power - 1; --i) {
        answer[i] = answer[i - 1];
    }
    answer[s_size - this->power - 1] = '.';
    if (!this->power) {answer += '0';}
    if (this->minus) {answer = "-" + answer;}
    return answer;
}

BigFloat::BigFloat() {
    this->number = std::vector<int>({0});
    this->power = 0;
    this->minus = false;
}

BigFloat::BigFloat(std::string number) {
    this->number = std::vector<int>();
    this->power = 0;
    int size = static_cast<int>(number.size());
    this->minus = false;

    if (size >= 1) {
        size_t right_zeros_float = 0;
        size_t start = 0;
        if (number[start] == '-') {
            this->minus = true;
            start++;
        }
        while (start < size and number[start] == '0') {
            start++;
        }
        size_t dot_pos = start;
        while (dot_pos < size and number[dot_pos] != '.') {
            dot_pos++;
        }
        while (size - right_zeros_float - 1 > dot_pos and number[size - right_zeros_float - 1] == '0') {
            right_zeros_float++;
        }
        // pushing real part
        for (size_t i = start; i < dot_pos; ++i) {this->number.push_back(number[i] - '0');}
        if (start == dot_pos) {this->number.push_back(0);}
        // pushing float part
        for (size_t i = dot_pos + 1; i < size - right_zeros_float; ++i) {this->number.push_back(number[i] - '0');}

        if (dot_pos >= size) {size++;}
        this->power = size - right_zeros_float - dot_pos - 1;
        if (this->number.empty()) {new (this)BigFloat();}
        if (this->number[0] == 0 and this->power == 0 and this->minus) {this->minus = false;}
    } else {
        new (this)BigFloat();
    }

}

BigFloat::BigFloat(int number) : BigFloat(std::to_string(number)) {}
BigFloat::BigFloat(float number) : BigFloat(std::to_string(number)) {}
BigFloat::BigFloat(double number) : BigFloat(std::to_string(number)) {}
BigFloat::BigFloat(const std::vector<int>& real_part, const std::vector<int>& float_part) {
    this->power = float_part.size();
    this->number.reserve(real_part.size() + float_part.size());
    this->number.insert(this->number.end(), real_part.begin(), real_part.end());
    this->number.insert(this->number.end(), float_part.begin(), float_part.end());
    this->minus = false;
}

BigFloat BigFloat::operator-() {
    this->minus = not this->minus;
    return *this;
}
BigFloat BigFloat::operator+() {
    return *this;
}

BigFloat BigFloat::operator+(BigFloat &b) {
    if (not this->minus and     b.minus ) return *this - b;
    if (    this->minus and not b.minus ) return b - *this;
    if (    this->minus and     b.minus ) return -(*this + b);
    if (*this < b) return b + *this;
    // then *this - b and *this > b

    int additive = 0;
    std::vector<int> new_num(0);
    for (int i = static_cast<int>(this->number.size()) - 1; i >= 0; --i) {
        int sum = this->number[i] + b.get_num(i, *this) + additive;
        additive = sum / 10;
        new_num.push_back(sum % 10);
    }

    if (additive != 0) new_num.push_back(additive);
    std::reverse(new_num.begin(), new_num.end());
    BigFloat ans;
    ans.number = new_num;
    ans.power = std::max(this->power, b.power);
    ans.minus = this->minus;

    return ans;
}

BigFloat BigFloat::operator-(BigFloat &b) {
    if (not this->minus and     b.minus) {return *this + b;}
    if (    this->minus and     b.minus) {return b - *this;}
    if (    this->minus and not b.minus) {return -(*this + b);}
    if (*this < b) return -(b - *this);
    // then *this - b and *this > b

    std::vector<int> new_num;
    int additive = 0;
    for (int i = this->number.size() - 1; i >= 0; --i) {
        int sum = this->number[i] - b.get_num(i, *this) + additive;
        additive = 0;
        if (sum < 0) additive = -1;
        new_num.push_back(((sum % 10) + 10) % 10);
    }
    if (additive != 0) new_num.push_back(((additive % 10) + 10) % 10);
    std::reverse(new_num.begin(), new_num.end());

    BigFloat ans;
    ans.number = new_num;
    ans.power = std::max(this->power, b.power);
    ans.minus = this->minus;

    return BigFloat(ans.str());
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
    int real_size1 = static_cast<int>(this->number.size()) - static_cast<int>(this->power);
    int real_size2 = static_cast<int>(b.number.size()) - static_cast<int>(b.power);
    int real_size_diff = real_size1 - real_size2;
    if (this->minus and !b.minus) return false;
    if (!this->minus and b.minus) return true;
    if (real_size_diff && !this->minus && !b.minus) {
        return real_size_diff > 0;
    } else if (real_size_diff && this->minus && b.minus) {
        return real_size_diff < 0;
    }

    int i = 0;
    while (i < this->number.size() && i < b.number.size() && this->number[i] == b.number[i]) i += 1;

    if (i < this->number.size() && i < b.number.size()) return this->number[i] > b.number[i];
    if (this->number.size() > b.number.size())          return true;
    if (this->number.size() < b.number.size())          return false;
}

bool BigFloat::operator==(BigFloat& b) {
    return !(*this > b && b > *this);
}

std::ostream& operator<<(std::ostream& os, BigFloat& num) {
    return os << num.str();
}

