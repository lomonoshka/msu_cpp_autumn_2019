#include <iostream>
#include <string>
#include "calculator.cpp"

double Calculate(const std::string &expression)
{
    Node *pExpression = CreateTree(expression);
    const double result = calculate(pExpression);
    free(pExpression);

    return result;
}

void print_res(const std::string &expression)
{
    try
    {
        const double result = Calculate(expression);
        std::cout << "'" << expression << "' = " << result << std::endl;
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Error in '" << expression << "': " << ex.what() << std::endl;
    }
}

int main()
{
    print_res("12/");
    print_res("10 / 11                / 12");
    print_res("252 + 17 / 45 / 2");
    print_res("42 + 42 / 2 * 2");
    print_res(" 4 * 4 + 3 * 3 + 2 * 2 ");

    return 0;
}
