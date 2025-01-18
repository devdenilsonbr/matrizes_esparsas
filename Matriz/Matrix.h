#ifndef MATRIX_H
#define MATRIX_H

class SparseMatrix{
private:
    int rows;
    int colunms;
    Node *root;
public:

    SparseMatrix(int m, int n);

    //~SparseMatrix();

    //void insert(int i, int j, double value);

    //double get(int i, int j);

    //void print();

    Node *getRoot();

};

#endif
