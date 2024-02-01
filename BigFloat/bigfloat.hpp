#ifndef PROJECTCPP_BIGFLOAT_HPP
#define PROJECTCPP_BIGFLOAT_HPP

#include <string>
#include <sstream>


class BigFloat {
private:
    std::size_t dot_pos;
    std::size_t size;

public:
    std::string number;

    explicit BigFloat(std::string number) {
        this->number = std::move(number);
        this->size = this->number.size();

        bool found = false;
        int i = 0;
        for (; i < this->size && !found; ++i) {
            found = this->number[i] == '.';
        }

        if (found) this->dot_pos = i;
        else {
            this->dot_pos = this->size;
            this->number += ".0";
        }
    }

    explicit BigFloat(int number) {
        std::stringstream ss; ss << number;
        this->number = ss.str();
        this->size = this->number.size();

        bool found = false;
        int i = 0;
        for (; i < this->size && !found; ++i) {
            found = this->number[i] == '.';
        }

        if (found) this->dot_pos = i;
        else {
            this->dot_pos = this->size;
            this->number += ".0";
        }
    }
};


#endif //PROJECTCPP_BIGFLOAT_HPP
