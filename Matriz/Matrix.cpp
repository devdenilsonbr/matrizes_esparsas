#include <iostream>
#include "Node.h"
#include "Matrix.h"

SparseMatrix::SparseMatrix(int m, int n) {
    rows = m;
    colunms = n;

    root->row = 0;
    root->colum = 0;

    Node *aux = root;

    for (int i=1; i<=m; i++) {
        Node *newRoot;
        newRoot->colum = 0;
        newRoot->row = i;
        aux->down = newRoot;
        aux = newRoot;
    }

    aux->down = root;
    aux->right = aux;
    aux = root;

    for (int i=1; i<=n; i++) {
        Node *newRoot;
        newRoot->colum = i;
        newRoot->row = 0;
        aux->right = newRoot;
        aux = newRoot;
    }
    aux->down = aux;
    aux->right = root;
}

Node *SparseMatrix::getRoot() {
    return root;
}

