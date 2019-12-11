#include <cassert>
#include <iostream>
#include "format.h"

int main() {

    assert(format("{0} + {0} = {1}", "one", 2) == "one + one = 2");

    assert(format("{0}hello{1}", "hey", 5) == "heyhello5");

    assert(format("oooo{0}oooo", "000") == "oooo000oooo");

    bool error = false;
    try
    {
        auto t = format("{", 1);
    }
    catch(const std::runtime_error& e)
    {
        error = true;
    }
    assert(error);

    error = false;
    try
    {
        auto t = format("{asdas}sdfsd{1}", 1, 2);
    }
    catch(const std::runtime_error& e)
    {
        error = true;
    }
    assert(error);

    std::cout<<"Done."<<std::endl;

    return 0;
}
