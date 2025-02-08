#include <iostream>
#include "Matrix.cpp"
#include <fstream>

int main() { 
    SparseMatrix matriz = SparseMatrix(3000, 3000);
    // SparseMatrix matriz2 = SparseMatrix(-1, 0);

    // matriz2.insert(2, 2, 9);

    for (int i=1; i<=100; i++) {
        for (int j = 1; j<=10; j++)
        matriz.insert(i, j, i+j);
    }

   //J matriz.print();

    SparseMatrix matriz1 = SparseMatrix(3, 3);
    matriz1.insert(2, 1, 9);
    matriz1.insert(1, 2, 7);

    double** m = matriz.toMatrix();

    // std::cout << matriz1.get(1, 2);

    for (size_t i = 0; i < matriz.sizeRow(); i++) {
        for (size_t j = 0; j<matriz.sizeColunms(); j++) {
            std::cout << m[i][j] << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\n";

    
    
    return 0;
}
