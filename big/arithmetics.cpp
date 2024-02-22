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
    int max_rps = static_cast<int>(std::max(a.real_part_size(), b.real_part_size()));
    int max_power = static_cast<int>(std::max(a.power, b.power));
    int additive = 0, max_size = max_rps + max_power;
    for (int i = max_size - 1; i >= 0; --i) {
        int n1 = a.get_num(i, b);
        int n2 = b.get_num(i, a);
        int sum = n1 + n2 + additive;
        additive = sum / 10;
        new_num.push_front(sum % 10);
    }
    if (additive != 0) new_num.push_front(additive);

    a.number = new_num;
    a.power = std::max(a.power, b.power);
    return BigFloat(a.str());
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
        while (a >= tmp) {
            a -= tmp;
            q += k;
        }
        k.mul10(-1);
        tmp.mul10(-1);
    }
    return q;
}

BigFloat BigFloat::get_pi(int precision) {
    BigFloat pi, under(1), tmp(1), min(1);
    min.power = precision + 1;
    for (int i = 0; tmp > min; ++i) {
        BigFloat k1(i);
        BigFloat right;
        BigFloat k2(4);
        right += k2 / (k1 * 8 + 1);
        k2 /= 2;
        right -= k2 / (k1 * 8 + 4);
        k2 /= 2;
        right -= k2 / (k1 * 8 + 5);
        right -= k2 / (k1 * 8 + 6);
        tmp = k2 / under * right;
        pi += tmp;
        under *= 16;
        if (abs(right.raw_real_part_size()) > precision) break;
    }

    return pi;
}
