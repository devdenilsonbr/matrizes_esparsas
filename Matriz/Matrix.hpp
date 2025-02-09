#ifndef MATRIX_HPP
#define MATRIX_HPP
#include "node.hpp"

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

    void print(bool outline, int spaces);

    size_t sizeRow();
    size_t sizeColunms();

    double **toMatrix();
};

#endif
