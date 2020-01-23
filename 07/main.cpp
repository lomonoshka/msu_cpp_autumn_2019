#include <iostream>
#include "vector.h"
#include "cassert"

using namespace std;

int main()
{
    Vector<double> v;
    v.resize(100);
    for(int i=0; i<100; i++)
        v[i] = i/10;

    for(int i=0; i<99; i++)
        v.push_back(-i/10);

    assert(v.capacity() == 200);
    assert(v.size() == 199);
    for(int i=0; i<150; i++)
        v.pop_back();
    assert(v.size() == 49);

    v.clear();
    assert(v.size() == 0);

    v.reserve(1000);
    assert(v.begin() == v.end());
    assert(v.capacity() >= 1000);
    for(int i=0; i<10; i++)
        v.push_back(i);
    assert(v.begin() != v.end());

    return 0;
}
