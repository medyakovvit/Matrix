#pragma once

#include "MatrixLib_global.h"
#include "Vector.h"

/// class Matrix
///
/// Matrix class which can contain usual functionality for matrices like vreate identity matrix,
/// inverse, transpose and etc.
template<typename T>
class Matrix : public MatrixBase<T>
{
public:
    Matrix(int rows, int cols, T value = T()) : MatrixBase<T>(rows, cols, value) {}

    template<typename T>
    Matrix(MatrixBase<T>const &m)
    {
        MatrixBase<T>::m_data = m.getData();
        MatrixBase<T>::m_isValid = m.isValid();
        MatrixBase<T>::m_rows = m.getRows();
        MatrixBase<T>::m_cols = m.getColumns();
    }

    void setElement(int row, int col, T value);
    T getElement(int row, int col) const;

    void identity();
};

template<typename T>
void Matrix<T>::setElement(int row, int col, T value)
{
    int elementIndex = row * MatrixBase<T>::m_cols + col;

    if (elementIndex < MatrixBase<T>::m_data.size())
        MatrixBase<T>::m_data[elementIndex] = value;
}

template<typename T>
T Matrix<T>::getElement(int row, int col) const
{
    return MatrixBase<T>::m_data.at(row * MatrixBase<T>::m_cols + col);
}

template<typename T>
void Matrix<T>::identity()
{
#if 1
    // Set all elements to zero first
    std::fill(MatrixBase<T>::m_data.begin(), MatrixBase<T>::m_data.end(), T(0));

    for(int row = 0, col = 0; row < MatrixBase<T>::m_rows && col < MatrixBase<T>::m_cols; row++, col++)
        MatrixBase<T>::m_data[row * MatrixBase<T>::m_cols + col] = T(1);
#else
    for(int row = 0, col = 0; row < m_rows && col < m_cols; col++)
    {
        m_data[row * MatrixBase<T>::m_cols + col] = row == col ? T(1) : T(0);

        if(col == m_cols - 1)
        {
            row++;
            col = 0;
        }
    }
#endif
}
