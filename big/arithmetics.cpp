#include "arithmetics.hpp"
#include "bigfloat.hpp"
#include <chrono>
#include <thread>

const static int Precision = 100;


BigFloat add(BigFloat a, BigFloat& b) {
    if (not a.minus and     b.minus) {BigFloat tmp = -b;    return sub(a, tmp);  }
    if (    a.minus and not b.minus) {BigFloat tmp = -a;    return sub(b, tmp);  }
    if (    a.minus and     b.minus) {BigFloat tmp = -a;    return -add(-b, tmp);}
    if (a.number.empty()) return b;
    if (b.number.empty()) return a;
    if (a < b) return add(b, a);
    // then *this + b and *this > b

    std::deque<int> new_num;
    int additive = 0;
    int right_zero_counter = 0;
    int max_rps = static_cast<int>(std::max(a.real_part_size(), b.real_part_size()));
    int max_power = static_cast<int>(std::max(a.power, b.power));
    int max_size = max_rps + max_power;
    for (int i = max_size - 1; i >= 0; --i) {
        int n1 = a.get_num(i, b);
        int n2 = b.get_num(i, a);
        int sum = n1 + n2 + additive;
        if (!n1 and !n2 and i >= max_rps) right_zero_counter++;
        else if (!n1 and !n2 and i < max_rps) right_zero_counter = 0;
        additive = sum / 10;
        new_num.push_front(sum % 10);
    }
    if (additive != 0) new_num.push_front(additive);
    for (int i = 0; i < right_zero_counter; ++i) new_num.pop_back();

    a.number = new_num;
    a.power = std::max(a.power, b.power);
    return a;
}

BigFloat sub(BigFloat a, BigFloat& b) {
    if (not a.minus and     b.minus) {BigFloat tmp = -b;        return add(a, tmp);     }
    if (    a.minus and not b.minus) {BigFloat tmp = -a;        return -add(tmp, b); }
    if (    a.minus and     b.minus) {BigFloat tmp = -b;        return -sub(-a, tmp);}
    if (a < b) return -sub(b, a);
    if (a.number.empty()) return -b;
    if (b.number.empty()) return a;
    // then *this - b and *this > b

    std::deque<int> new_num;
    int additive = 0, right_zero_counter = 0;
    bool found = false;
    int max_size = static_cast<int>(std::max(a.real_part_size(), b.real_part_size()) + std::max(a.power, b.power));
    for (int i = max_size - 1; i >= 0; --i) {
        int n1 = a.get_num(i, b);
        int n2 = b.get_num(i, a);
        if (!n1 and !n2 and !found) right_zero_counter++;
        else found = true;
        int sum = n1 - n2 + additive;
        additive = 0;
        if (sum < 0) additive = -1;
        new_num.push_front(((sum % 10) + 10) % 10);
    }
    if (additive != 0) new_num.push_front(((additive % 10) + 10) % 10);
    for (int i = 0; i < right_zero_counter; ++i) new_num.pop_back();

    a.number = new_num;
    a.power = std::max(a.power, b.power);
    return BigFloat(a.str());
}

BigFloat mul(BigFloat a, BigFloat& b) {
    if (a < b) return b * a;
    // then *this * b and *this > b

    std::vector<BigFloat> dp(10, BigFloat(-1));
    dp[0] = BigFloat(0);

    BigFloat ans;
    int max_size = std::max(a.real_part_size(), b.real_part_size()) + std::max(a.power, b.power);
    for (int i = 0; i < max_size; ++i) {
        int n = b.get_num(i, a);
        int tmp = n;
        BigFloat sum;
        if (BigFloat(-1) != dp[n]) {
            sum = dp[n];
        } else {
            while (n > 0) {
                sum += a;
                n -= 1;
            }
            dp[tmp] = sum;
        }
        int idx = a.real_part_size() - i - 1;
        sum.mul10(idx);
        std::cout << sum << ' ' << tmp << ' ' << a.real_part_size() - i - 1 << std::endl;

        ans += sum;
    }
    ans.minus = a.minus ^ b.minus;
    ans = BigFloat(ans.str());


    return ans;

}

BigFloat div(BigFloat a, BigFloat& b) {
    if (!a) return a;
    if (!b) throw "Zero division error!";
    BigFloat q;
    BigFloat k(1);
    BigFloat tmp = b;
    while (a >= tmp) {
        tmp.mul10(1);
        k.mul10(1);
        if (a < tmp) {
            tmp.mul10(-1);
            k.mul10(-1);
            break;
        }
    }
    for (int i = 0; q.power < Precision and a; ++i) {
//        std::cout << a << '\t' << tmp << '\t' << q << '\t' << k << std::endl;
        while (a >= tmp) {
//            std::cout << a << '\t' << tmp << '\t';
            a -= tmp;
            q += k;
//            std::cout << k << ' ' << q << std::endl;
//            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
//        std::cout << std::endl;
        k.mul10(-1);
        tmp.mul10(-1);
    }
    return q;
}
