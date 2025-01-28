#include <iostream>
#include "Matrix.cpp"

using namespace std;

int main() { 
    SparseMatrix matriz = SparseMatrix(4, 3);

    for (int i=1; i<=4; i++) {
        for (int j = 1; j<=3; j++)
        matriz.insert(i, j, i+j);
    }

    matriz.print();

    SparseMatrix matriz1 = SparseMatrix(3, 3);
    matriz1.insert(2, 1, 9);
    matriz1.insert(1, 2, 7);

    cout << "\n";

    matriz1.print();
    
    return 0;
}
