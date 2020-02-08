#pragma once

#include <vector>
#include <iostream>

/// class MatrixBase
///
/// Class contains base functionality for matrices. Elements of matrix are placed in vector
/// instead of using "array of arrays" way.
template<typename T>
class MatrixBase
{
public:
    MatrixBase() {}
    MatrixBase(int rows, int cols, T value = T());

    bool isValid() const { return m_isValid; }
    size_t size() { return m_data.size(); }

    int getRows() const { return m_rows; }
    int getColumns() const { return m_cols; }

    MatrixBase<T> operator*(T scalar);

    template<typename T>
    friend MatrixBase<T> operator*(const MatrixBase<T>& first, const MatrixBase<T>& second);

    template<typename T>
    friend MatrixBase<T> operator+(const MatrixBase<T>& first, const MatrixBase<T>& second);

    template<typename T>
    friend std::ostream &operator<<(std::ostream &os, const MatrixBase<T>& m);

    const std::vector<T>& getData() const { return m_data; }

protected:
    bool m_isValid = false;
    int m_rows = 0;
    int m_cols = 0;

    std::vector<T> m_data;
};

template<typename T>
MatrixBase<T>::MatrixBase(int rows, int cols, T value) : m_rows(rows), m_cols(cols)
{
    if (m_cols > 0 && m_rows > 0)
    {
        m_isValid = true;
        m_data.resize(m_rows * m_cols, value);
    }
}

template<typename T>
MatrixBase<T> MatrixBase<T>::operator*(T scalar)
{
    if(!isValid())
        return MatrixBase<T>(0, 0);

    MatrixBase<T> result(m_rows, m_cols);

    for(int i = 0; i < m_data.size(); i++)
        result.m_data[i] = scalar * m_data[i];

    return result;
}

template<typename T>
MatrixBase<T> operator*(const MatrixBase<T>& first, const MatrixBase<T>& second)
{
    // Check input matrices
    if (!first.isValid() || !second.isValid())
        return MatrixBase<T>(0, 0);

    if (first.getColumns() != second.getRows())
        return MatrixBase<T>(0, 0);

    int resultRows = first.getRows();
    int resultCols = second.getColumns();
    MatrixBase<T> result(resultRows, resultCols);

    for(int rrow = 0; rrow < resultRows; rrow++)
    {
        for(int rcol = 0; rcol < resultCols; rcol++)
        {
            int idx = rrow * resultCols + rcol;

            for(int col = 0; col < first.getColumns(); col++)
            {
                int firstMatrixElement = rrow * first.getColumns() + col;
                int secondMatrixElement = col * second.getColumns() + rcol;
                result.m_data[idx] += first.m_data[firstMatrixElement] * second.m_data[secondMatrixElement];
            }
        }
    }

    return result;
}

template<typename T>
MatrixBase<T> operator+(const MatrixBase<T>& first, const MatrixBase<T>& second)
{
    if (!first.isValid() || !second.isValid())
        return MatrixBase<T>(0, 0);

    if (first.getRows() != second.getRows() || first.getColumns() != second.getColumns())
        return MatrixBase<T>(0, 0);

    MatrixBase<T> result(first.getRows(), first.getColumns());

    for(int i = 0; i < result.m_data.size(); i++)
        result.m_data[i] = first.m_data[i] + second.m_data[i];

    return result;
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const MatrixBase<T>& m)
{
    if (m.isValid())
    {
        for (int row = 0, col = 0; row < m.m_rows && col < m.m_cols;)
        {
            os << m.m_data[row * m.m_cols + col] << " ";

            if (col == m.m_cols - 1)
            {
                col = 0;
                row++;
                os << std::endl;
            }
            else
                col++;
        }
    }
    else
        os << "not valid";

    return os;
}
