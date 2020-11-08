#include "Bigint.h"

#include <iomanip>
#include <iostream>

bool check_string(const std::string &number) {
    if (number.empty() || (number.size() == 1 && number[0] == '-')) {
        return false;
    }
    auto it_begin = (number[0] == '-') ? next(begin(number)) : begin(number);
    auto it = std::find_if(it_begin, end(number), [](const char &c) {
        return !isdigit(c);
    });
    return it == number.end();
}

int64_t ctoi(const char *begin, const char *end) {
    int64_t result = 0;
    while (begin != end) {
        result = result * 10 + *begin - '0';
        ++begin;
    }
    return result;
}

Bigint::Bigint(const std::string &str_number) {
    if (!check_string(str_number)) {
        throw std::invalid_argument(str_number);
    } else {
        is_positive_ = str_number[0] != '-';
        auto begin_str = (is_positive_) ? str_number.c_str() : str_number.c_str() + 1;
        auto end_str = str_number.c_str() + str_number.size();

        if ((end_str - begin_str) % power == 0) {
            digits_.reserve((end_str - begin_str) / power);
        } else {
            digits_.reserve((end_str - begin_str) / power + 1);
        }

        auto pointer = end_str;
        for (pointer; pointer > begin_str + power; pointer -= power) {
            digits_.push_back(ctoi(pointer - power, pointer));
        }
        if (begin_str != pointer) {
            digits_.push_back(ctoi(begin_str, pointer));
        }
    }
}

Bigint::Bigint(int number) {
    is_positive_ = number > 0;
    number = is_positive_ ? number : -number;
    size_t length = (number == 0) ? 1u : static_cast<size_t>(log10(number) + 1);
    digits_.resize(length % power == 0 ? length / power : length / power + 1);

    for (size_t &digit : digits_) {
        digit = number % base;
        number /= base;
    }
}

std::ostream &operator<<(std::ostream &os, const Bigint &rhs) {
    if (!rhs.is_positive_) {
        os << "-";
    }
    os << *std::rbegin(rhs.digits_);
    for (auto it = std::next(std::rbegin(rhs.digits_)); it != std::rend(rhs.digits_); ++it) {
        os << std::setfill('0') << std::setw(power);
        os << *it;
    }
    return os;
}

Bigint::operator std::string() const {
    std::stringstream ss;
    ss << *this;
    return ss.str();
}

bool operator==(const Bigint &lhs, const Bigint &rhs) {
    if (lhs.is_positive_ != rhs.is_positive_ ||
        lhs.digits_.size() != rhs.digits_.size()) {
        return false;
    }

    for (size_t i = 0; i < lhs.digits_.size(); ++i) {
        if (lhs.digits_[i] != rhs.digits_[i]) {
            return false;
        }
    }
    return true;
}

bool operator<(const Bigint &lhs, const Bigint &rhs) {
    if (lhs.is_positive_ != rhs.is_positive_) {
        return rhs.is_positive_;
    } else if (lhs.digits_.size() != rhs.digits_.size()) {
        return !lhs.is_positive_ ^ (lhs.digits_.size() < rhs.digits_.size());
    } else {
        return !lhs.is_positive_ ^ abs_compare(lhs, rhs);
    }
}

//compare two Bigint on absalute value. Return true if lhs abs(lhs) < abs(rhs)
bool abs_compare(const Bigint &lhs, const Bigint &rhs) {
    if (lhs.digits_.size() != rhs.digits_.size()) {
        return lhs.digits_.size() < rhs.digits_.size();
    } else {
        for (size_t i = lhs.digits_.size(); i > 0; --i) {
            if (lhs.digits_[i - 1] < rhs.digits_[i - 1]) {
                return true;
            }
            if (lhs.digits_[i - 1] > rhs.digits_[i - 1])
                return false;
        }
        return false;
    }
}

bool operator!=(const Bigint &lhs, const Bigint &rhs) {
    return !(lhs == rhs);
}

bool operator<=(const Bigint &lhs, const Bigint &rhs) {
    return (lhs < rhs || lhs == rhs);
}

bool operator>(const Bigint &lhs, const Bigint &rhs) {
    return !(lhs <= rhs);
}

bool operator>=(const Bigint &lhs, const Bigint &rhs) {
    return !(lhs < rhs);
}

const Bigint Bigint::operator-() const {
    Bigint result(*this);
    result.is_positive_ = !result.is_positive_;
    return result;
}

void Bigint::remove_leading_zeros() {
    while (this->digits_.size() > 1 && this->digits_.back() == 0) {
        this->digits_.pop_back();
    }
}

// These functions were created to avoid excess copy with unary operator -, for example A - (-B).
// You shouldn't use it if you just want to add or substract two Bigint, insted use euqivalent operators + and -
Bigint addition_without_sign(const Bigint &lhs, const Bigint &rhs, bool is_positive) {
    bool res = 0;
    Bigint result;
    result.is_positive_ = is_positive;
    result.digits_.reserve(lhs.digits_.size() + 1);

    for (size_t i = 0; i < rhs.digits_.size(); ++i) {
        if (rhs.digits_[i] > base - lhs.digits_[i]) {
            result.digits_.push_back(lhs.digits_[i] - (base - rhs.digits_[i]) + res);
            res = 1;
        } else if (base - res > lhs.digits_[i] + rhs.digits_[i] ) {
            result.digits_.push_back(lhs.digits_[i] + rhs.digits_[i] + res);
            res = 0;
        } else {
            result.digits_.push_back(lhs.digits_[i] + rhs.digits_[i] - (base - res));
            res = 1;
        }
    }
    for (size_t i = rhs.digits_.size(); i < lhs.digits_.size(); ++i) {
        if (lhs.digits_[i] > base - res) {
            result.digits_.push_back(lhs.digits_[i] - (base - res));
        } else {
            result.digits_.push_back(lhs.digits_[i] + res);
            res = 0;
        }
    }

    if (res) {
        result.digits_.push_back(res);
    }

    return result;
}

Bigint difference_without_sign(const Bigint &lhs, const Bigint &rhs, bool is_positive) {
    bool res = 0;
    Bigint result;
    result.is_positive_ = is_positive;
    result.digits_.reserve(lhs.digits_.size());
    for (size_t i = 0; i < rhs.digits_.size(); ++i) {
        if (lhs.digits_[i] < rhs.digits_[i] + res) {
            result.digits_.push_back(lhs.digits_[i] + (base - rhs.digits_[i] - res));
            res = 1;
        } else {
            result.digits_.push_back(lhs.digits_[i] - res - rhs.digits_[i]);
            res = 0;
        }
    }
    for (size_t i = rhs.digits_.size(); i < lhs.digits_.size(); ++i) {
        if (lhs.digits_[i] < res) {
            result.digits_.push_back(base - res);
        } else {
            result.digits_.push_back(lhs.digits_[i] - res);
            res = 0;
        }
    }
    result.remove_leading_zeros();
    return result;
}

Bigint operator+(const Bigint &lhs, const Bigint &rhs) {
    if (lhs.is_positive_ == rhs.is_positive_) {
        if (lhs.digits_.size() < rhs.digits_.size()) {
            return addition_without_sign(rhs, lhs, lhs.is_positive_);
        } else {
            return addition_without_sign(lhs, rhs, lhs.is_positive_);
        }
    } else if (abs_compare(lhs, rhs)) {
        return difference_without_sign(rhs, lhs, rhs.is_positive_);
    } else {
        return difference_without_sign(lhs, rhs, lhs.is_positive_);
    }
}

Bigint operator-(const Bigint &lhs, const Bigint &rhs) {
    if (lhs.is_positive_ != rhs.is_positive_) {
        return addition_without_sign(lhs, rhs, lhs.is_positive_);
    } else if (abs_compare(lhs, rhs)) {
        return difference_without_sign(rhs, lhs, !rhs.is_positive_);
    } else {
        return difference_without_sign(lhs, rhs, lhs.is_positive_);
    }
}

