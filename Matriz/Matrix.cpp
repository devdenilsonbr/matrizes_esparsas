#include <iostream>
#include "Matrix.hpp"

SparseMatrix::SparseMatrix(int m, int n) {
    rows = m; // a matriz recebe a quantidade de linha
    colunms = n; // a matriz recebe a quantidade de colunas

    root = new Node; // um node sentilena é criado
    root->row = 0; // o sentinela recebe sua repectiva linha
    root->column = 0; // o sentilena recebe sua respectiva coluna

    Node *aux = root; // crio um auxiliar para criar os outros sentinelas

    for (int i=1; i<=m; i++) { // itero para criar todos os sentinelas das linhas
        Node *newRoot = new Node; // crio um novo node sentilena para a recpectiva linha
        newRoot->column = 0; // como estou criando os sentilenas das linhas, sua coluna é 0
        newRoot->row = i; // linha do respectivo sentinela
        aux->down = newRoot; // o aux que é o node criado anteriormente vai apontar para o proximo sentinela linha que foi criado
        newRoot->right = newRoot; // o sentinela linha que aponta para o lado direito aponta para ele mesmo
        aux = newRoot; // o aux agora recebe o node que foi criado
    }

    aux->down = root; // como eh ciclico, o ultimo node sentinela linha aponta para o root
    aux->right = aux; // o sentinela linha aponta para ele mesmo
    aux = root;

    for (int i=1; i<=n; i++) { // iteror para criar todas as colunas
        Node *newRoot = new Node; // repito o mesmo processo anterior para criar as colunas
        newRoot->column = i; // ...
        newRoot->row = 0; // ...
        aux->right = newRoot; // ...
        newRoot->down = newRoot; // ...
        aux = newRoot; // ...
    }
    aux->down = aux; // ...
    aux->right = root; // ...
}

void SparseMatrix::insert(int i, int j, double value) {
    Node *auxRow = root->down; // crio um auxiliar para encontrar o node que vai apontar para o novo node

    while(auxRow->row != i) { // busco a respectiva linha verificando se a linha atual eh a requerida
        auxRow = auxRow->down; // percorro para a proxima
    }
    while(auxRow->right->column != 0 && auxRow->right->column <= j) {
        auxRow = auxRow->right;
    }
    
    Node *auxColumn = root;

    while(auxColumn->column != j) {
        auxColumn = auxColumn->right;
    }
    while(auxColumn->down->row != 0 && auxColumn->down->row <= i) {
        auxColumn = auxColumn->down;
    }

    if (auxRow == auxColumn) {
        auxRow->value = value;
        return;
    }

    Node *newNode = new Node(auxRow->right, auxColumn->down, i, j, value);
    auxRow->right = newNode;
    auxColumn->down = newNode;
}

