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

int BigFloat::sum_arrays_left(
    const std::vector<int>::iterator start1,
    const std::vector<int>::iterator end1,
    const std::vector<int>::iterator start2,
    const std::vector<int>::iterator end2,
    std::vector<int> &buff,
    int additive,
    bool reverse
) {
    int size1 = static_cast<int>(end1 - start1);
    int size2 = static_cast<int>(end2 - start2);
    int diff = size1 - size2;

    if (diff < 0)
        for (auto it = end2 - 1; it >= end2 + diff; --it) {buff.push_back(*it);
    } else
        for (auto it = end1 - 1; it >= end1 - diff; --it) {buff.push_back(*it);}
    for (int i = std::max(size1, size2) - abs(diff) - 1; i >= 0; --i) {
        int sum = *(start1 + i) + *(start2 + i) + additive;
        additive = sum / 10;
        buff.push_back(sum % 10);
    }

    if (reverse)
        std::reverse(buff.begin(), buff.end());
    return additive;
}

int BigFloat::sum_arrays_right(
    const std::vector<int>::iterator start1,
    const std::vector<int>::iterator end1,
    const std::vector<int>::iterator start2,
    const std::vector<int>::iterator end2,
    std::vector<int> &buff,
    int additive,
    bool reverse
) {
    int size1 = static_cast<int>(end1 - start1);
    int size2 = static_cast<int>(end2 - start2);
    int diff = size1 - size2;

    if (diff < 0) {
        for (int i = size2 - 1; i >= abs(diff); --i) { // 12 1234 1245
            int sum = *(start1 + i) + *(start2 + i - abs(diff)) + additive;
            additive = sum / 10;
            buff.push_back(sum % 10);
        }
        for (auto it = start1 + abs(diff) - 1; it >= start1; ++it) { buff.push_back(*it + additive); }
    } else {
        for (int i = size1 - 1; i >= abs(diff); --i) { // 1234 12 1245
            int sum = *(start2 + i) + *(start1 + i - abs(diff)) + additive;
            additive = sum / 10;
            buff.push_back(sum % 10);
        }
        for (auto it = start2 + abs(diff) - 1; it >= start2; ++it) { buff.push_back(*it + additive); }
    }

    if (reverse)
        std::reverse(buff.begin(), buff.end());
    return additive;
}


int BigFloat::sub_arrays_left(
    const std::vector<int>::iterator start1,
    const std::vector<int>::iterator end1,
    const std::vector<int>::iterator start2,
    const std::vector<int>::iterator end2,
    std::vector<int> &buff,
    int additive,
    bool reverse
) {
    int size1 = static_cast<int>(end1 - start1);
    int size2 = static_cast<int>(end2 - start2);
    int diff = size1 - size2;

    if (diff < 0)
        for (auto it = end2 - 1; it >= end2 + diff; --it) {
            int sum = 0 - *it + additive;
            buff.push_back(*it);
        } else
        for (auto it = end1 - 1; it >= end1 - diff; --it) {
            buff.push_back(*it);
        }
    for (int i = std::max(size1, size2) - abs(diff) - 1; i >= 0; --i) {
        int sum = *(start1 + i) - *(start2 + i) + additive;
        additive = 0;
        if (sum < 0) additive -= 1;
        buff.push_back((sum % 10 + 10) % 10);
    }

    if (reverse)
        std::reverse(buff.begin(), buff.end());
    return additive;

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
    if (not this->minus and b.minus) {return *this - b;}
    if (this->minus and not b.minus) {return b - *this;}
    if (this->minus and b.minus) {return -(*this + b);}

    int additive;
    std::vector<int> float_part;
    std::vector<int> real_part;
    additive = BigFloat::sum_arrays_left(
        this->number.end() - static_cast<int>(this->power) - 1, this->number.end(),
        b.number.end() - static_cast<int>(b.power) - 1, b.number.end(),
        float_part
        );
    additive = BigFloat::sum_arrays_right(
        this->number.begin(), this->number.end() - static_cast<int>(this->power),
        b.number.begin(), b.number.end() - static_cast<int>(b.power),
        real_part, additive, false
    );
    if (additive != 0) real_part.push_back(additive);
    std::reverse(real_part.begin(), real_part.end());

    return BigFloat(real_part, float_part);
}


BigFloat BigFloat::operator-(BigFloat &b) {
    if (not this->minus and b.minus) {return *this + b;}
    if (this->minus and b.minus) {return b - *this;}
    if (this->minus and not b.minus) {return -(*this + b);}
    // then *this - b

    int additive;
    std::vector<int> float_part;
    std::vector<int> real_part;
    additive = BigFloat::sub_arrays_left(
        this->number.end() - static_cast<int>(this->power) - 1, this->number.end(),
        b.number.end() - static_cast<int>(b.power) - 1, b.number.end(),
        float_part
    );
    additive = BigFloat::sub_arrays_left(
        this->number.begin(), this->number.end() - static_cast<int>(this->power),
        b.number.begin(), b.number.end() - static_cast<int>(b.power),
        real_part, additive, false
    );
    if (additive != 0) real_part.push_back(additive);
    std::reverse(real_part.begin(), real_part.end());

    return BigFloat(real_part, float_part);
}
