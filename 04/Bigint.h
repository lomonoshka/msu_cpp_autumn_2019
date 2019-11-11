#pragma once
#include "list.cpp"
#include <string>

class Bigint
{
    static const int base = 10;
    int* digit;
    bool minus;
    size_t length;

    Bigint(list<int> &, bool);

    public:
        Bigint(const std::string &, bool);

        Bigint(const int &);

        Bigint(const Bigint &b);

        ~Bigint();

        Bigint& operator = (const Bigint &);

        friend Bigint operator + (const Bigint &, const Bigint &);

        friend Bigint operator - (const Bigint &, const Bigint &);

        friend Bigint operator - (const Bigint &);

        friend bool operator == (const Bigint &, const Bigint &);

        friend bool operator != (const Bigint&, const Bigint&);

        friend bool operator > (const Bigint &, const Bigint &);

        friend bool operator < (const Bigint &, const Bigint &);

        friend bool operator >= (const Bigint &, const Bigint &);

        friend bool operator <= (const Bigint &, const Bigint &);

        friend std::ostream& operator << (std::ostream &,const Bigint &);
};
