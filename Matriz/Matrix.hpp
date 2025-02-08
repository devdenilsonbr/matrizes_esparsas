#ifndef MATRIX_HPP
#define MATRIX_HPP
#include "Node.hpp"

class SparseMatrix
{
private:
    size_t rows;
    size_t colunms;
    Node *root;

public:
    SparseMatrix(size_t m, size_t n);

    ~SparseMatrix();

    void insert(unsigned i, unsigned j, double value);

    double get(unsigned i, unsigned j);

    void print();

    size_t sizeRow();
    size_t sizeColunms();

    double **toMatrix();

    static SparseMatrix multiply(SparseMatrix &A, SparseMatrix &B);
    static SparseMatrix sum(SparseMatrix &A, SparseMatrix &B);
};

#endif
