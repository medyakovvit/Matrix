#pragma once

#include "MatrixBase.h"

/// class Vector
///
/// Vector is considered as special case of matrix with number of rows equal to 1
template<typename T>
class Vector : public MatrixBase<T>
{
public:
    Vector(int dimension, T value = T()) : MatrixBase<T>(1, dimension, value) {}

    template<typename T>
    Vector(MatrixBase<T>const & m)
    {
        // One of dimensions of input matrix should be equal to 1
        if(m.getRows() == 1 || m.getColumns() == 1)
        {
            MatrixBase<T>::m_data = m.getData();
            MatrixBase<T>::m_isValid = m.isValid();
            MatrixBase<T>::m_rows = m.getRows();
            MatrixBase<T>::m_cols = m.getColumns();

            if(MatrixBase<T>::m_rows != 1)
                std::swap(MatrixBase<T>::m_rows, MatrixBase<T>::m_cols);
        }
    }

    void setElement(int element, T value);
    T getElement(int element) const;

    template<typename T>
    friend std::ostream &operator<<(std::ostream &os, const Vector<T>& v);
};

template<typename T>
void Vector<T>::setElement(int element, T value)
{
    if (element < MatrixBase<T>::m_data.size())
        MatrixBase<T>::m_data[element] = value;
}

template<typename T>
T Vector<T>::getElement(int element) const
{
    return MatrixBase<T>::m_data.at(element);
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const Vector<T>& v)
{
    os << "Vector" << std::endl;

    for (int row = 0; row < v.m_rows; row++)
    {
        os << v.m_data[row] << " ";
    }

    os << std::endl;

    return os;
}
