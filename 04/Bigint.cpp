#include "Bigint.h"
#include <iostream>

using namespace std;

Bigint::Bigint(const string& s, bool minus = false)
{
    this->minus = minus;
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
    minus = a<0;
    if(minus)
        tmp = -tmp;

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

Bigint::Bigint(list<int> &l, bool minus = false)
{
    while(l.get_tail()->data == 0 && l.get_tail() != l.get_head())
        l.pop();

    node<int> *tmp = l.get_head();
    this->length = l.get_length();
    digit = new int [this->length];
    int i =  this->length - 1;
    while(tmp)
    {

        digit[i] = tmp->data;
        tmp = tmp->next;
        i--;
    }
    this->minus = minus;
}

Bigint::Bigint(const Bigint &copy)
{
    length = copy.length;
    digit = new int [length];
    minus = copy.minus;
    for(int i = 0; i < length; i++)
        digit[i] = copy.digit[i];
}

Bigint::~Bigint()
{
    length = 0;
    delete[] digit;
    digit = nullptr;
}

Bigint& Bigint::operator = (const Bigint& right)
{
    if(this == &right)
        return *this;

    int *new_digit = new int [right.length];
    delete[] digit;
    digit = new_digit;
    length = right.length;
    minus = right.minus;

    for(int i = 0; i < right.length; i++)
        new_digit[i] = right.digit[i];

    return *this;
}

Bigint operator + (const Bigint& left, const Bigint& right)
{

    if(left < right)
        return right + left;

    if(!(left.minus == right.minus))
        return (left.minus)? (right - (-left)): (left - (-right));

    list<int> new_digit;
    int res = 0;
    int i = left.length-1, j = right.length - 1;
    for(i, j; i >= 0; i--, j--)
    {
        int sum = 0;
        if(j >= 0)
            sum = (left.digit[i] + right.digit[j] + res);
        else
            sum = (left.digit[i] + res);
        new_digit.append(sum % 10);
        res = sum / 10;
    }

    if(res > 0)
        new_digit.append(res);

    return Bigint(new_digit, left.minus);
}

Bigint operator - (const Bigint& left, const Bigint& right)
{
    if(left < right)
        return -(right - left);

    if(!(left.minus == right.minus))
        return (left.minus)? (right + (-left)): (left + (-right));

    if(left == right)
        return Bigint(0);

    list<int> new_digit;
    int res = 0;
    int i = left.length-1, j = right.length - 1;
    for(i, j; i >= 0; i--, j--)
    {

        int dif = 0;
        if(j >= 0)
            dif = (left.digit[i] - right.digit[j] + res);
        else
            dif = (left.digit[i] + res);

        new_digit.append((dif + 10) % 10);
        (dif < 0)? res = -1: res = 0;
    }

    return Bigint(new_digit, left.minus);
}

Bigint operator - (const Bigint& right)
{
    Bigint tmp(right);
    tmp.minus = !tmp.minus;
    return tmp;
}

bool operator == (const Bigint& left, const Bigint& right)
{
    if(left.minus != right.minus || left.length != right.length)
        return false;

    for(int i = 0; i<right.length; i++)
        if(left.digit[i] != right.digit[i])
            return false;

    return true;
}

bool operator != (const Bigint& left, const Bigint& right)
{
    cout<<left<<" "<<right<<endl;
    return !(left == right);
}

bool operator > (const Bigint& left, const Bigint& right)
{
    if(left.minus != right.minus)
    {
        return !left.minus;
    }
    else
    {
        if(left.length > right.length)
            return (!left.minus);

        if(left.length < right.length)
            return left.minus;

        if(left.length == right.length)
        {
            for(int i = 0; i<left.length; i++)
            {
                if(left.digit[i] > right.digit[i])
                    return (!left.minus);

                if(left.digit[i] < right.digit[i])
                    return left.minus;
            }
        }
    }

    return false;
}

bool operator < (const Bigint& left, const Bigint& right)
{
    return !(left > right || left == right);

}

bool operator >= (const Bigint& left, const Bigint& right)
{
    return !(left < right);
}

bool operator <= (const Bigint& left, const Bigint& right)
{
    return !(left > right);
}

ostream& operator << (ostream & out,const Bigint & a)
{
    if(a.minus)
        out<<"-";

    for(int i = 0; i < a.length; i++)
        out << a.digit[i];

    return out;

}
