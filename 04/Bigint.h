#pragma once
#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

const uint16_t power = 4;
const size_t base = pow(10, power);

class Bigint {
   public:
    Bigint(const std::string &str_number);
    Bigint(int);

    Bigint(const Bigint &b) = default;
    ~Bigint() = default;
    Bigint &operator=(const Bigint &rhs) = default;

    friend Bigint addition_without_sign(const Bigint &lhs, const Bigint &rhs, bool is_positive);
    friend Bigint difference_without_sign(const Bigint &lhs, const Bigint &rhs, bool is_positive);

    friend Bigint operator+(const Bigint &lhs, const Bigint &rhs);
    friend Bigint operator-(const Bigint &lhs, const Bigint &rhs);
    friend Bigint operator*(const Bigint &lhs, const Bigint &rhs);
    friend Bigint operator/(const Bigint &lhs, const Bigint &rhs);
    const Bigint operator-() const;

    friend bool operator==(const Bigint &lhs, const Bigint &rhs);
    friend bool operator!=(const Bigint &lhs, const Bigint &rhs);
    friend bool operator>(const Bigint &lhs, const Bigint &rhs);
    friend bool operator<(const Bigint &lhs, const Bigint &rhs);
    friend bool operator>=(const Bigint &lhs, const Bigint &rhs);
    friend bool operator<=(const Bigint &lhs, const Bigint &rhs);
    friend bool abs_compare(const Bigint &lhs, const Bigint &rhs);

    friend std::ostream &operator<<(std::ostream &os, const Bigint &rhs);
    operator std::string() const;
    void remove_leading_zeros();

   private:
    Bigint() = default;

   private:
    std::vector<size_t> digits_;
    bool is_positive_;
};
