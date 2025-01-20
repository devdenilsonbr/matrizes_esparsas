#include <iostream>
#include "Matrix.hpp"

SparseMatrix::SparseMatrix(int m, int n) {
    rows = m;
    colunms = n;

    root = new Node;
    root->row = 0;
    root->column = 0;

    Node *aux = root;

    for (int i=1; i<=m; i++) {
        Node *newRoot = new Node;
        newRoot->column = 0;
        newRoot->row = i;
        aux->down = newRoot;
        newRoot->right = newRoot;
        aux = newRoot;
    }

    aux->down = root;
    aux->right = aux;
    aux = root;

    for (int i=1; i<=n; i++) {
        Node *newRoot = new Node;
        newRoot->column = i;
        newRoot->row = 0;
        aux->right = newRoot;
        newRoot->down = newRoot;
        aux = newRoot;
    }
    aux->down = aux;
    aux->right = root;
}

Node *SparseMatrix::getRoot() {
    return root;
}

void SparseMatrix::insert(int i, int j, double value) {
    Node *sentRow = root;
    
    while (sentRow->row != i) {
        sentRow = sentRow->down;
    }

    Node *sentColumn = root;

    while (sentColumn->column != j) {
        sentColumn = sentColumn->right;
    }

    Node *newNode = new Node;

    while(sentRow->right != sentRow) {
        sentRow = sentRow->right;
    }



}

