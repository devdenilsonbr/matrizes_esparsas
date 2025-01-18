#include <iostream>
#include "Matrix.cpp"

using namespace std;

int main() {
    SparseMatrix matriz = SparseMatrix(3, 2);

    Node *aux = matriz.getRoot();

    for (int i=0; i<10; i++) {
        cout << aux->colum << " ";
        aux = aux->down;
    }

    aux = matriz.getRoot();

    for (int i=0; i<10; i++) {
        cout << aux->row << " ";
        aux = aux->right;
    }

    return 0;
}
