#include <iostream>
#include <big/bigfloat.hpp>


int main() {
    BigFloat pi = BigFloat::get_pi(10);
    std::cout << pi << std::endl;
    return 0;
}
