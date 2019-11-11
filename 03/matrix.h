#include <cstdio>
#include <stdexcept>
#include <iostream>

class Matrix
{
    class Row
    {
        int* row;
        size_t length;

    public:
        Row(const size_t&, int*);
        Row(const Row&);
        const int& operator[](const size_t&) const;
        int& operator[](const size_t&);

    };

    size_t rows;
    size_t columns;
    int* matrix;

public:

    Matrix(const size_t&, const size_t&);
    Matrix(const Matrix&);
    ~Matrix();
    const Row operator[](const size_t&) const;
    Row operator[](const size_t&);
    Matrix& operator*=(const int&);
    bool operator==(const Matrix&) const;
    bool operator!=(const Matrix&) const;
    const size_t& get_rows() const;
    const size_t& get_columns() const;
    friend std::ostream& operator<<(std::ostream&, const Matrix&);

};
