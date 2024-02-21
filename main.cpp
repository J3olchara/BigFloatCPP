#include <iostream>
#include <big/bigfloat.hpp>


//void *$(){[&](...){$:[](){({$:;_:[](){},""[+-(&&$<&&_)];});}();}([=](){});}

int main() {
    BigFloat a(4);
    BigFloat b(51);
    BigFloat pi = BigFloat::get_pi(200);
    std::cout << pi << std::endl;
    BigFloat a1("3.14");
    BigFloat b1("0.0000001");
    BigFloat ans = a1 + b1;
    std::cout << ans.raw_number();
    return 0;
}
