#include <string>
#include "bigfloat.hpp"
#include <iostream>


std::string BigFloat::str() {
    std::string answer = this->number;
    size_t s_size = this->number.size() + 1;
    answer += answer[s_size - 2];
    for (size_t i = s_size - 1; i > s_size - this->power - 1; --i) {
        answer[i] = answer[i - 1];
    }
    answer[s_size - this->power - 1] = '.';
    if (!this->power) {answer += '0';}
    return answer;
}

BigFloat::BigFloat() {
    this->number = "0";
    this->power = 0;
}

BigFloat::BigFloat(std::string number) {
    this->number = std::string();
    this->power = 0;
    int size = number.size();

    if (size >= 1) {
        size_t right_zeros_float = 0;
        size_t start = 0;
        while (start < size and number[start] == '0') {
            ++start;
        }
        size_t dot_pos = start;
        while (dot_pos < size and number[dot_pos] != '.') {
            ++dot_pos;
        }
        while (size - right_zeros_float - 1 > dot_pos and number[size - right_zeros_float - 1] == '0') {
            ++right_zeros_float;
        }
        for (size_t i = start; i < dot_pos; ++i) {this->number.push_back(number[i]);}
        for (size_t i = dot_pos + 1; i < size - right_zeros_float; ++i) {this->number.push_back(number[i]);}

        if (dot_pos >= size) {size++;}
        this->power = size - right_zeros_float - dot_pos - 1;
        if (this->number.empty()) {new (this)BigFloat();}
    } else {
        new (this)BigFloat();
    }

}

BigFloat::BigFloat(int number) : BigFloat(std::to_string(number)) {};
BigFloat::BigFloat(float number) : BigFloat(std::to_string(number)) {}
BigFloat::BigFloat(double number) : BigFloat(std::to_string(number)) {}
