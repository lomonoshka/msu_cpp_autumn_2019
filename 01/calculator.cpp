#include <ctype.h>
#include <stdexcept>
#include <memory>
#include <cmath>
#include <cassert>

enum class Operation
{
    NOP,
    ADD,
    SUB,
    MUL,
    DIV
};

struct Node
{
    double value = 0;
    Operation op = Operation::NOP;
    Node *pLeft = nullptr;
    Node *pRight = nullptr;
};

Node *ParseAtom(std::string &str);
Node *ParseMulDiv(std::string &str);
Node *ParseAddSub(std::string &str);
Node *CreateTree(const std::string &expression);
double calculate(Node *pExpression);
void clear(Node *pExpression);

void SkipSpaces(std::string &expression)
{
    size_t numSize = 0;
    while (numSize < expression.size()
           && (expression[numSize] == ' '))
    {
        ++numSize;
    }
    expression = expression.substr(numSize);
}

bool ParseDouble(std::string &expression, double &result)
{
    std::string remainingStr = expression;
    SkipSpaces(remainingStr);

    size_t numSize = 0;
    if (remainingStr.size() > 0 && isdigit(remainingStr[0]))
    {
        while (numSize < remainingStr.size()
               && isdigit(remainingStr[numSize]))
        {
            ++numSize;
        }
        result = std::stod(remainingStr.substr(0, numSize));
        expression = remainingStr.substr(numSize);
        return true;
    }

    return false;
}

bool ParseOperator(std::string &expression, Operation &op)
{
    std::string remainingStr = expression;
    SkipSpaces(remainingStr);
    if (remainingStr.empty())
    {
        op = Operation::NOP;
        return false;
    }

    switch (remainingStr[0])
    {
    case '+':
        op = Operation::ADD; break;
    case '-':
        op = Operation::SUB; break;
    case '*':
        op = Operation::MUL; break;
    case '/':
        op = Operation::DIV; break;
    default:
        op = Operation::NOP; break;
    }

    const bool succeed = (op != Operation::NOP);
    if (succeed)
    {
        expression = remainingStr.substr(1);
    }
    return succeed;
}

Node *ParseAddSub(std::string &str)
{
    Node *left = ParseMulDiv(str);
    while (true)
    {
        Operation op = Operation::NOP;

        std::string remainingStr = str;
        if (!ParseOperator(remainingStr, op))
        {
            return left;
        }
        switch (op)
        {
        case Operation::ADD:
        case Operation::SUB:
            break;
        default:
            return left;
        }
        str = remainingStr;

        Node *right = nullptr;
        try
        {
            right = ParseMulDiv(str);
        }
        catch (...)
        {
            (left);
            throw;
        }

        try
        {
            Node *expr = new Node;
            expr->pLeft = left;
            expr->pRight = right;
            expr->op = op;
            left = expr;
        }
        catch (...)
        {
            clear(left);
            clear(right);
            throw;
        }
    }

    return left;
}

Node *ParseMulDiv(std::string &str)
{
    Node *left = ParseAtom(str);
    while (true)
    {
        Operation op = Operation::NOP;

        std::string remainingStr = str;
        if (!ParseOperator(remainingStr, op))
        {
            return left;
        }
        switch (op)
        {
        case Operation::MUL:
        case Operation::DIV:
            break;
        default:
            return left;
        }
        str = remainingStr;

        Node *right = nullptr;
        try
        {
            right = ParseAtom(str);
        }
        catch (...)
        {
            clear(left);
            throw;
        }

        try
        {
            Node *expr = new Node;
            expr->pLeft = left;
            expr->pRight = right;
            expr->op = op;
            left = expr;
        }
        catch (...)
        {
            clear(left);
            clear(right);
            throw;
        }
    }

    return left;
}

Node *ParseAtom(std::string &str)
{
    Node *expr = new Node;
    if (!ParseDouble(str, expr->value))
    {
        clear(expr);
        throw std::invalid_argument("Expected number at: " + str);
    }
    return expr;
}

Node *CreateTree(const std::string &expression)
{
    std::string remainingStr = expression;
    Node *pExpr = ParseAddSub(remainingStr);

    SkipSpaces(remainingStr);
    if (!remainingStr.empty())
    {
        const auto message = "Unexpected symbol at: " + remainingStr;
        throw std::runtime_error(message);
    }

    return pExpr;
}

double calculate(Node *pExpr)
{
    if (pExpr->op == Operation::NOP)
    {
        return pExpr->value;
    }
    assert(pExpr->pLeft);
    assert(pExpr->pRight);
    calculate(pExpr->pLeft);
    calculate(pExpr->pRight);

    switch (pExpr->op)
    {
    case Operation::ADD:
        pExpr->value = pExpr->pLeft->value + pExpr->pRight->value;
        break;
    case Operation::SUB:
        pExpr->value = pExpr->pLeft->value - pExpr->pRight->value;
        break;
    case Operation::MUL:
        pExpr->value = pExpr->pLeft->value * pExpr->pRight->value;
        break;
    case Operation::DIV:
        pExpr->value = pExpr->pLeft->value / pExpr->pRight->value;
        break;
    case Operation::NOP:
        assert(false);
        break;
    }

    return pExpr->value;
}

void clear(Node *node)
{
    if (node)
    {
        if (node->pLeft)
        {
            clear(node->pLeft);
        }
        if (node->pRight)
        {
            clear(node->pRight);
        }
        delete node;
    }
}
