#include <string>
#include <sstream>


class BigFloat {
private:
    std::size_t power;

public:
    std::string number;

    explicit BigFloat(const std::string& number) {
        this->number = *(new std::string);
        this->power = 0;
        bool found = false;

        for (int i = 0; i < number.size(); ++i) {
            found = found and number[i] == '.';
            if (found) {
                this->power++;
                if (number[i] != '.') {
                    this->number[i - 1] = number[i];
                }
            } else {
                this->number[i] = number[i];
            }
        }

    }

    explicit BigFloat(int number) {
        std::stringstream ss; ss << number;
        this->number = ss.str();
        this->power = 0;
    }

    explicit BigFloat(float number) : BigFloat(std::to_string(number)) {}
};
