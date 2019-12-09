#include <QtTest>

#include "../MatrixLib/Matrix.h"
#include <iostream>

#include <armadillo>

using namespace arma;

class matrix : public QObject
{
    Q_OBJECT

public:
    matrix();
    ~matrix();

private slots:
    void multiplyScalar();
    void multiplyMatrices();
    void vectorsAddition();
    void matricesAddition();
};

matrix::matrix()
{

}

matrix::~matrix()
{

}

void matrix::multiplyScalar()
{
    int max = 10;

    for(int i = 0; i < max; i++)
    {
        int rows = i + 1;
        int cols = max - i;

        Mat<int> expectedM = randi<Mat<int>>(rows, cols, distr_param(-1000, 1000));
        int scalar = std::rand() % 1000;

        Matrix<int> tempM(rows, cols);

        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                tempM.setElement(i, j, expectedM.at(i, j));

        expectedM *= scalar;
        Matrix<int> resultM = tempM * scalar;

        QVERIFY2(resultM.isValid(), "Resulted matrix is not valid");
        QVERIFY2(resultM.getRows() == expectedM.n_rows, "Resulted matrix has wrong number of rows");
        QVERIFY2(resultM.getColumns() == expectedM.n_cols, "Resulted matrix has wrong number of columns");

        for(int row = 0; row < rows; row++)
            for(int col = 0; col < cols; col++)
                QCOMPARE(resultM.getElement(row, col), expectedM.at(row, col));
    }
}

void matrix::multiplyMatrices()
{
    int max = 10;

    for(int i = 0; i < max; i++)
    {
        int rows = i + 1;
        int cols = max - i;

        Mat<int> expectedM = randi<Mat<int>>(uword(rows), uword(cols), distr_param(-1000, 1000));
        Mat<int> matrix1 = randi<Mat<int>>(uword(cols), std::rand() % 9 + 1, distr_param(-1000, 1000));

        Matrix<int> tempM(rows, cols);
        Matrix<int> matrix2(matrix1.n_rows, matrix1.n_cols);

        // Copy elements to Matrix1
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                tempM.setElement(i, j, expectedM.at(i, j));

        // Copy elements to Matrix2
        for (int i = 0; i < cols; i++)
            for (int j = 0; j < matrix1.n_cols; j++)
                matrix2.setElement(i, j, matrix1.at(i, j));

        expectedM *= matrix1;
        Matrix<int> resultM = tempM * matrix2;

        QVERIFY2(resultM.isValid(), "Resulted matrix is not valid");
        QVERIFY2(resultM.getRows() == expectedM.n_rows, "Resulted matrix has wrong number of rows");
        QVERIFY2(resultM.getColumns() == expectedM.n_cols, "Resulted matrix has wrong number of columns");

        // Compare elements
        for(int row = 0; row < resultM.getRows(); row++)
            for(int col = 0; col < resultM.getColumns(); col++)
                QCOMPARE(resultM.getElement(row, col), expectedM.at(row, col));
    }
}

void matrix::vectorsAddition()
{
    int max = 10;

    for(int i = 1; i <= max; i++)
    {
        Col<int> armaVec1 = randi<Col<int>>(uword(i), distr_param(-1000, 1000));
        Col<int> armaVec2 = randi<Col<int>>(uword(i), distr_param(-1000, 1000));

        auto expectedVec = armaVec1 + armaVec2;

        Vector<int> vec1(i);
        for(int i = 0; i < vec1.getNumberOfElements(); i++)
            vec1.setElement(i, armaVec1.at(uword(i)));

        Vector<int> vec2(i);
        for(int i = 0; i < vec2.getNumberOfElements(); i++)
            vec2.setElement(i, armaVec2.at(uword(i)));

        Vector<int> resultedVec = vec1 + vec2;

        QVERIFY2(resultedVec.isValid(), "Resulted matrix is not valid");
        QVERIFY2(resultedVec.getNumberOfElements() == expectedVec.get_n_elem(), "Resulted vector has wrong number of elements");

        // Compare elements
        for(int i = 0; i < resultedVec.getNumberOfElements(); i++)
            QCOMPARE(resultedVec.getElement(i), expectedVec[i]);
    }
}

void matrix::matricesAddition()
{
    int max = 10;

    for(int i = 0; i < max; i++)
    {
        int rows = i + 1;
        int cols = max - i;

        Mat<int> armaMat1 = randi<Mat<int>>(uword(rows), uword(cols), distr_param(-1000, 1000));
        Mat<int> armaMat2 = randi<Mat<int>>(uword(rows), uword(cols), distr_param(-1000, 1000));

        auto expectedMat = armaMat1 + armaMat2;

        // Copy values from first arma matrix
        Matrix<int> mat1(rows, cols);
        for(int i = 0; i < rows; i++)
            for(int j = 0; j < cols; j++)
                mat1.setElement(i, j, armaMat1.at(uword(i), uword(j)));

        // Copy values from second arma matrix
        Matrix<int> mat2(rows, cols);
        for(int i = 0; i < rows; i++)
            for(int j = 0; j < cols; j++)
                mat2.setElement(i, j, armaMat2.at(uword(i), uword(j)));

        Matrix<int> resultedMat = mat1 + mat2;

        QVERIFY2(resultedMat.isValid(), "Resulted matrix is not valid");
        QVERIFY2(resultedMat.getRows() == expectedMat.get_n_rows() && resultedMat.getColumns() == expectedMat.get_n_cols(), "Resulted matrix has wrong size");

        // Compare elements
        for(int i = 0; i < resultedMat.getRows(); i++)
            for(int j = 0; j < resultedMat.getColumns(); j++)
                QCOMPARE(resultedMat.getElement(i, j), expectedMat.at(i, j));
    }
}

QTEST_APPLESS_MAIN(matrix)

#include "tst_matrix.moc"
