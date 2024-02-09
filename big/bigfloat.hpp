#ifndef PROJECTCPP_BIGFLOAT_HPP
#define PROJECTCPP_BIGFLOAT_HPP

#include <string>
#include <vector>



class BigFloat {
public:
    std::size_t power;
    std::vector<int> number;
    bool minus;

    static int sum_arrays_left(
        std::vector<int>::iterator, std::vector<int>::iterator,
        std::vector<int>::iterator, std::vector<int>::iterator,
        std::vector<int>&, int = 0, bool = true
    );
    static int sum_arrays_right(
        std::vector<int>::iterator, std::vector<int>::iterator,
        std::vector<int>::iterator, std::vector<int>::iterator,
        std::vector<int>&, int = 0, bool = false
    );
    static int sub_arrays_left(
        std::vector<int>::iterator, std::vector<int>::iterator,
        std::vector<int>::iterator, std::vector<int>::iterator,
        std::vector<int>&, int = 0, bool = true
    );
//    static int sub_arrays_right(
//        std::vector<int>::iterator, std::vector<int>::iterator,
//        std::vector<int>::iterator, std::vector<int>::iterator,
//        std::vector<int>&, int = 0, bool = false
//    );

    BigFloat();
    explicit BigFloat(std::string);
    explicit BigFloat(int);
    explicit BigFloat(float);
    explicit BigFloat(double);
    BigFloat(const std::vector<int>&, const std::vector<int>&);

    BigFloat operator-();
    BigFloat operator+();
    BigFloat operator+(BigFloat&);
    BigFloat operator-(BigFloat&);
//    BigFloat operator*(BigFloat &b);
//    BigFloat operator/(BigFloat &b);

    std::string raw_number();
    std::string str();
};



#endif // PROJECTCPP_BIGFLOAT_HPP
