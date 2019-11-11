#include "matrix.h"

using namespace std;

Matrix::Row::Row(const size_t& length, int* row)
{
    this->row = row;
    this->length = length;
}

Matrix::Row::Row(const Row &r)
{
    this->length = r.length;
    this->row = r.row;
}

const int& Matrix::Row::operator[](const size_t &j) const
{
    if(j >= this->length)
    {
        throw std::out_of_range("Index out of range.");
    }
    else
    {
    return row[j];
    }
}

int& Matrix::Row::operator[](const size_t &j)
{
    if(j >= this->length)
    {
        throw std::out_of_range("Index out of range.");
    }
    else
    {
    return row[j];
    }
}

Matrix::Matrix(const Matrix &m)
{
    this->rows = m.rows;
    this->columns = m.columns;
    this->matrix = new int[rows * columns];
    for(int i=0; i<rows; i++)
        for(int j=0; j<columns; j++)
        {
            matrix[i*columns + j] = m.matrix[i*columns + j];
        }
}

Matrix::Matrix(const size_t& rows, const size_t& columns)
{
    this->rows = rows;
    this->columns = columns;
    this->matrix = new int[rows * columns];
}

Matrix::~Matrix()
{
    this->rows = 0;
    this->columns = 0;
    delete[] this->matrix;
}

const Matrix::Row Matrix::operator[](const size_t &i) const
{
    if(i >= rows)
    {
        throw std::out_of_range("Index out of range.");
    }
    else
    {
        return Row(columns, matrix + i*columns);
    }
}

Matrix::Row Matrix::operator[](const size_t &i) 
{
    if(i >= rows)
    {
        throw std::out_of_range("Index out of range.");
    }
    else
    {
        return Row(columns, matrix + i*columns);
    }
}

Matrix& Matrix::operator*=(const int &a)
{
    for(int i=0; i<rows; i++)
        for(int j=0; j<columns; j++)
        {
            matrix[i*columns + j] *= a;
        }
    return *this;
}

bool Matrix::operator==(const Matrix &left) const
{
    if(this->columns != left.columns || this->rows != rows)
        return false;

    for(int i=0; i<rows; i++)
        for(int j=0; j<columns; j++)
        {
            if((*this)[i][j] != left[i][j])
                return false;
        }

        return true;
}

bool Matrix::operator!=(const Matrix &left) const
{
    return !(*this == left);
}

ostream& operator<<(ostream &s, const Matrix &m)
{
    for(int i=0; i<m.rows; i++)
    {
        for(int j=0; j<m.columns; j++)
            s<<m[i][j]<<" ";
        s<<endl;
    }

    return s;
}

const size_t& Matrix::get_columns() const
{
    return this->columns;
}

const size_t& Matrix::get_rows() const
{
    return this->rows;
}
