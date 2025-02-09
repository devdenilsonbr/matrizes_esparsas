#include <iostream>
#include "matrix.hpp"

SparseMatrix::SparseMatrix(size_t m, size_t n)
{
    if (m > 30000 || n > 30000)
    {
        throw std::out_of_range("invalid size");
    }
    rows = m;    // a matriz recebe a quantidade de linha
    colunms = n; // a matriz recebe a quantidade de colunas

    root = new Node;  // um node sentilena é criado
    root->row = 0;    // o sentinela recebe sua repectiva linha
    root->column = 0; // o sentilena recebe sua respectiva coluna

    Node *aux = root; // crio um auxiliar para criar os outros sentinelas

    for (size_t i = 1; i <= m; i++)
    {                             // itero para criar todos os sentinelas das linhas
        Node *newRoot = new Node; // crio um novo node sentilena para a recpectiva linha
        newRoot->column = 0;      // como estou criando os sentilenas das linhas, sua coluna é 0
        newRoot->row = i;         // linha do respectivo sentinela
        aux->down = newRoot;      // o aux que é o node criado anteriormente vai apontar para o proximo sentinela linha que foi criado
        newRoot->right = newRoot; // o sentinela linha que aponta para o lado direito aponta para ele mesmo
        aux = newRoot;            // o aux agora recebe o node que foi criado
    }

    aux->down = root; // como eh ciclico, o ultimo node sentinela linha aponta para o root
    aux = root;

    for (size_t i = 1; i <= n; i++)
    {                             // iteror para criar todas as colunas
        Node *newRoot = new Node; // repito o mesmo processo anterior para criar as colunas
        newRoot->column = i;      // ...
        newRoot->row = 0;         // ...
        aux->right = newRoot;     // ...
        newRoot->down = newRoot;  // ...
        aux = newRoot;            // ...
    }
    aux->right = root; // ...
}

void SparseMatrix::insert(unsigned i, unsigned j, double value)
{
    if (i > rows || j > colunms || i == 0 || j == 0)
    {
        throw std::out_of_range("invalid index");
    }

    if (value == 0)
        return;

    Node *auxRow = root->down; // crio um auxiliar para encontrar o node que vai apontar para o novo node

    while (auxRow->row != i)
    {                          // busco a respectiva linha verificando se a linha atual eh a requerida
        auxRow = auxRow->down; // percorro para a proxima
    }
    while (auxRow->right->column != 0 && auxRow->right->column <= j)
    {
        auxRow = auxRow->right;
    }

    if (auxRow->column == j)
    {
        auxRow->value = value;
        return;
    }

    Node *auxColumn = root;

    while (auxColumn->column != j)
    {
        auxColumn = auxColumn->right;
    }
    while (auxColumn->down->row != 0 && auxColumn->down->row <= i)
    {
        auxColumn = auxColumn->down;
    }

    Node *newNode = new Node(auxRow->right, auxColumn->down, i, j, value);
    auxRow->right = newNode;
    auxColumn->down = newNode;
}

void SparseMatrix::print(bool outline = 0, int spaces = 8)
{
    size_t totalWidth = (colunms * spaces) + (colunms - 1) * 3;

    if (outline) {
        std::cout << std::string(totalWidth, '-') << "\n";
    }

    Node *auxNode = root->down, *auxRow = root->down;

    for (size_t i = 0; i < rows; i++)
    {
        auxNode = auxRow;

        while (auxNode->right->column != 0)
        {
            int zeros = (auxNode->right->column - auxNode->column) - 1;

            for (int p = 0; p < zeros; p++)
            {
                std::cout << std::setw(spaces) << 0.0;
            }

            std::cout << std::setw(spaces) << std::fixed << std::setprecision(1) << auxNode->right->value;

            auxNode = auxNode->right;
        }

        int zeros = colunms - auxNode->column;

        for (int k = 0; k < zeros; k++)
        {
            std::cout << std::setw(spaces) << 0.0;
        }

        std::cout << "\n";

        auxRow = auxRow->down;
    }

    if (outline) {
        std::cout << std::string(totalWidth, '-') << "\n";
    }
}

double SparseMatrix::get(unsigned i, unsigned j)
{
    // validar se a posição esta dentro da matriz
    if (i > rows || j > colunms || i == 0 || j == 0)
    {
        throw std::out_of_range("invalid index");
    }

    // percorre a lista de linhas para encontrar a linha i
    Node *auxRow = root->down; // começa no sentinela da primeira linha

    while (auxRow->row != i) // loop ate encontrar o sentinela da linha i
    {
        auxRow = auxRow->down; // avança para o próximo sentinela de linha
    }

    // percorre a linha i(ultimo encontrado) para encontrar a coluna j
    Node *auxNode = auxRow->right; // começa no primeiro elemento da linha i

    while (auxNode->column != 0 && auxNode->column < j) // loop ate encontrar a coluna j ou atingir o final da linha
    {
        auxNode = auxNode->right; // avança para o proximo no na linha
    }

    // verifica se o no foi encontrado e se tem a coluna j
    // se isso for verdade significa que o valor esta na posição (i, j)
    // ao final retorna o valor, senão retorna 0.0
    return auxNode->column == j ? auxNode->value : 0.0;
}

size_t SparseMatrix::sizeRow() { return rows; }

size_t SparseMatrix::sizeColunms() { return colunms; }

double **SparseMatrix::toMatrix()
{

    double **m = new double *[rows];

    for (size_t i = 0; i < rows; i++)
    {
        m[i] = new double[colunms];
    }

    Node *auxNode = root->down, *auxRow = root->down;

    for (size_t i = 0; i < rows; i++)
    {
        auxNode = auxRow;

        size_t j = 0;

        while (auxNode->right->column != 0)
        {
            int zeros = (auxNode->right->column - auxNode->column) - 1;

            for (int p = 0; p < zeros; p++)
            {
                m[i][j] = 0; // numeros de zeros entre colunas
                j++;
            }

            m[i][j] = auxNode->right->value;
            j++;
            auxNode = auxNode->right;
        }

        int zeros = colunms - auxNode->column;

        for (int k = 0; k < zeros; k++)
        {
            m[i][j] = 0;
            j++;
        }

        auxRow = auxRow->down;
    }

    return m;
}

SparseMatrix::~SparseMatrix()
{
    Node *rowAux = root->down; // começa pelo primeiro sentinela de linha

    while (rowAux != root)
    {                                 // percorre todas as linhas
        Node *colAux = rowAux->right; // aponta para o primeiro elemento da linha

        while (colAux != rowAux)
        {                           // percorre os elementos da linha
            Node *temp = colAux;    // guarda o no atual
            colAux = colAux->right; // avança para o proximo no na linha
            delete temp;            // libera a memoria do no atual
        }
        Node *tempRow = rowAux; // guarda o sentinela da linha atual
        rowAux = rowAux->down;  // avança para a proxima linha
        delete tempRow;         // libera a memoria do sentinela da linha
    }

    // percore todas as colunas para deletar os sentinelas
    Node *colAux = root->right; // começa pelo primeiro sentinela de coluna

    while (colAux != root)
    {                           // percorre todas as colunas
        Node *tempCol = colAux; // guarda o sentinela da coluna atual
        colAux = colAux->right; // avança para o proximo sentinela de coluna
        delete tempCol;         // libera a memoria do sentinela da coluna
    }

    delete root; // deleta o no root, que é o sentinela principal
}