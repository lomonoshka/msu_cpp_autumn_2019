#pragma once
#include <string>

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

Node *CreateTree(const std::string &expression);
double calculate(Node *pExpression);
void free(Node *pExpression);
