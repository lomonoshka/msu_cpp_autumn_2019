#pragma once
#include "list.cpp"
#include <string>

using namespace std;

class Bigint
{
    static const int base = 10;
    int* digit;
    bool minus;
    size_t length;

    public:
        Bigint(const string &, bool);

        Bigint(const int &);

        Bigint(list<int> &, bool);

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

        friend ostream& operator << (ostream &,const Bigint &);
};
