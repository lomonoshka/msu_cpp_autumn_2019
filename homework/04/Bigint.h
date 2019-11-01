#pragma once
#include <string>

using namespace std;

class Bigint
{
    int* digit;
    size_t length;

    Bigint(const string& s);

    Bigint(const int &a);

    Bigint(int* a, const size_t& len);

    Bigint& operator = (const Bigint& next);

    Bigint operator + (const Bigint& next);

    Bigint operator - (const Bigint& next);

    Bigint operator - ();

    Bigint operator == (const Bigint& next);

    bool operator > (const Bigint& next);

    bool operator < (const Bigint& next);

    bool operator >= (const Bigint& next);

    bool operator <= (const Bigint& next);
};
