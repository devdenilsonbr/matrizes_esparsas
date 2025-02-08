#include <iostream>
#include "Matrix.cpp"

using namespace std;

// g++ -o main.out main.cpp && ./main.out

int main()
{
    SparseMatrix matriz = SparseMatrix(4, 3);
    // SparseMatrix matriz = SparseMatrix(3000, 3000);
    // SparseMatrix matriz2 = SparseMatrix(-1, 0);

    // matriz2.insert(2, 2, 9);

    for (int i = 1; i <= 4; i++) // i <= 100
    {
        for (int j = 1; j <= 3; j++) //j <= 10
        {
            matriz.insert(i, j, i + j);
        }
    }

    cout << "Matriz(A):" << endl;

    matriz.print();

    SparseMatrix matriz1 = SparseMatrix(3, 3);

    matriz1.insert(2, 1, 9);
    matriz1.insert(1, 2, 7);

    double **m = matriz.toMatrix();

    matriz1.insert(2, 1, 9);
    matriz1.insert(1, 2, 7);

    // for (size_t i = 0; i < matriz.sizeRow(); i++)
    // {
    //     for (size_t j = 0; j < matriz.sizeColunms(); j++)
    //     {
    //         std::cout << m[i][j] << " ";
    //     }
    //     std::cout << "\n";
    // }

    std::cout << "\n";

    cout << "\nMatriz(B):" << endl;
    matriz1.print();

    cout << "\n";

    cout << "Matriz(B):" << endl;
    cout << "get(2, 1): " << matriz1.get(2, 1) << endl;
    cout << "get(1, 2): " << matriz1.get(1, 2) << endl;

    cout << "\n";

    SparseMatrix multiply_result = SparseMatrix::multiply(matriz, matriz1);

    cout << "multiplicação (Matriz A * Matriz B):\n";
    multiply_result.print();

    cout << "\n";

    SparseMatrix multiply_sum = SparseMatrix::sum(matriz, matriz);

    cout << "soma (Matriz A + Matriz A):\n";
    multiply_sum.print();

    return 0;
}
