#include <QtTest>

#include "../MatrixLib/Matrix.h"

// add necessary includes here

class matrix : public QObject
{
    Q_OBJECT

public:
    matrix();
    ~matrix();

private slots:
    void test_case1();

};

matrix::matrix()
{

}

matrix::~matrix()
{

}

void matrix::test_case1()
{
    Matrix<int> m(5, 5, 0);
}

QTEST_APPLESS_MAIN(matrix)

#include "tst_matrix.moc"
