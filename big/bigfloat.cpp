#include <string>
#include "bigfloat.hpp"
#include <iterator>
#include <algorithm>
#include <sstream>


inline std::string BigFloat::raw_number() {
    std::stringstream ss;
    std::copy(this->number.begin(), this->number.end(), std::ostream_iterator<int>(ss, ""));
    return ss.str();
}

std::string BigFloat::str() {
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

BigFloat::BigFloat(int number) : BigFloat(std::to_string(number)) {};
BigFloat::BigFloat(float number) : BigFloat(std::to_string(number)) {}
BigFloat::BigFloat(double number) : BigFloat(std::to_string(number)) {}

BigFloat BigFloat::operator+(BigFloat &b) {
    if (not this->minus and b.minus) {return *this - b;}
    if (this->minus and not b.minus) {return b - *this;}
    int size1 = static_cast<int>(this->number.size());
    int size2 = static_cast<int>(b.number.size());
    int power1 = static_cast<int>(this->power);
    int power2 = static_cast<int>(b.power);
    int float_part_diff = power1 - power2;
    int real_part_diff = size1 - size2 - float_part_diff;
    std::vector<int> new_number;
    BigFloat *first = this;
    BigFloat *second = &b;


    // computing floating point parts
    if (float_part_diff < 0) {
        std::swap(first, second);
        std::swap(size1, size2);
        std::swap(power1, power2);
        real_part_diff = -float_part_diff;
    }
    int additive = 0;
    for (int i = size1 - 1; i >= size1 - float_part_diff; --i) {
        new_number.push_back(first->number[i]);
    }
    for (int i = size1 - float_part_diff - 1; i >= size1 - power1; --i) {
        int sum = first->number[i] + second->number[i - 1] + additive;
        additive = sum / 10;
        new_number.push_back(sum % 10);
    }

    // computing real parts
    if (real_part_diff < 0) {
        std::swap(first, second);
        std::swap(size1, size2);
        std::swap(power1, power2);
        real_part_diff = -real_part_diff;
    }
    for (int i = size1 - power1 - 1; i >= real_part_diff; --i) {
        int sum = first->number[i] + second->number[i - real_part_diff] + additive;
        additive = sum / 10;
        new_number.push_back(sum % 10);
    }
    for (int i = real_part_diff - 1; i >= 0; --i) {
        int num = first->number[i] + additive;
        additive = num / 10;
        new_number.push_back(num % 10);
    }
    if (additive) {new_number.push_back(additive);}
    std::reverse(new_number.begin(), new_number.end());
    BigFloat answer;
    answer.number = new_number;
    answer.power = std::max(power1, power2);

    return answer;
}
BigFloat BigFloat::operator-(BigFloat &b) {
    // todo: write this
    return *this;
}
