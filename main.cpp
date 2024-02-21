#include <iostream>
#include <big/bigfloat.hpp>
#include <chrono>




int main() {
    clock_t start = clock();
    BigFloat pi = BigFloat::get_pi(100);
    clock_t end = clock();
    float time_to_compute = static_cast<float>(end - start) / CLOCKS_PER_SEC;
    std::cout << "PI: " << pi << std::endl;
    std::cout << "To compute pi required " << time_to_compute << " seconds";
    return 0;
}
