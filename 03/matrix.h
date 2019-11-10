#include <cstdio>
#include <stdexcept>
#include <iostream>

using namespace std;

class Matrix
{
    class Row
    {
        int* row;
        size_t length;

    public:
        Row(const size_t&, int*);
        Row(const Row&);
        int& operator[](const size_t&) const;

    };

    size_t rows;
    size_t columns;
    int* matrix;

public:

    Matrix(const size_t&, const size_t&);
    Matrix(const Matrix&);
    ~Matrix();
    const Row operator[](const size_t&) const;
    Matrix& operator*=(const int&);
    bool operator==(const Matrix&) const;
    bool operator!=(const Matrix&) const;
    size_t& get_rows();
    size_t& get_columns();
    friend ostream& operator<<(ostream&, const Matrix&);

};
