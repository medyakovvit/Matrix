#pragma once

#include "MatrixLib_global.h"
#include <vector>

template<typename T>
class Matrix
{
public:
    Matrix(int rows, int cols, T value = T());

    bool isValid() const { m_isValid; }
    int getRows() const { return m_rows; }
    int getColumns() const { return m_cols; }

    void setElement(int row, int col, T value);
    T getElement(int row, int col) const;

    void identity();

private:
    bool m_isValid = false;
    int m_rows = 0;
    int m_cols = 0;

    std::vector<T> m_data;
};

template<typename T>
Matrix<T>::Matrix(int rows, int cols, T value) : m_rows(rows), m_cols(cols)
{
    if (cols > 0 && rows > 0)
    {
        m_isValid = true;
        m_data.resize(rows * cols, value);
    }
}

template<typename T>
void Matrix<T>::setElement(int row, int col, T value)
{
    int elementIndex = row * col + col;

    if (elementIndex < m_data.size())
        m_data[elementIndex] = value;
}

template<typename T>
T Matrix<T>::getElement(int row, int col) const
{
    return m_data.at(row * col + col);
}

template<typename T>
void Matrix<T>::identity()
{
#if 1
    // Set all elements to zero first
    std::fill(m_data.begin(), m_data.end(), T(0));

    for(int row = 0, col = 0; row < m_rows && col < m_cols; row++, col++)
        m_data[row * col + col] = T(1);
#else
    for(int row = 0, col = 0; row < m_rows && col < m_cols; col++)
    {
        m_data[row * col + col] = row == col ? T(1) : T(0);

        if(col == m_cols - 1)
            row++;
    }
#endif
}

template<typename T>
Matrix<T> operator*(T scalar, const Matrix<T>& m)
{
    if(!m.isValid())
        return Matrix<T>(0, 0);

    Matrix<T> result(m.getRows(), m.getColumns());

    for(int i = 0; i < m.m_data.size(); i++)
        result.m_data[i] = scalar * m.m_data[i];
}
