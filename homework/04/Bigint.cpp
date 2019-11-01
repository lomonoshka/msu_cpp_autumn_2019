#include "Bigint.h"

using namespace std;

Bigint::Bigint(const string& s)
{
    length = s.length();
    digit = new int [length];
    for(int i = 0; i < length;i++)
        digit[i] = s[i] - '0';
}

Bigint::Bigint(const int &a)
{
    int tmp = a;
    int tmp_digit[15];
    length = 0;

    while(tmp > 0)
    {
        tmp_digit[length] = tmp%10;
        tmp/=10;
        length++;
    }

    digit = new int [length];

    for(int i = 0; i < length; i++)
        digit[i] = tmp_digit[length-i-1];
}

Bigint::Bigint(int* a, const size_t& len)
{
    length = len;
    digit = new int [length];
    for(int i = 0; i < length;i++)
        digit[i] = a[i];
}

Bigint& operator = (const Bigint& next);

Bigint operator + (const Bigint& next);

Bigint operator - (const Bigint& next);

Bigint operator - ();

Bigint operator == (const Bigint& next);

bool operator > (const Bigint& next);

bool operator < (const Bigint& next);

bool operator >= (const Bigint& next);

bool operator <= (const Bigint& next);
