#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <iomanip>
#include "matrix.cpp"
#include "color.hpp"

using namespace std;

SparseMatrix *sum(SparseMatrix *A, SparseMatrix *B)
{
    if (A->sizeColunms() != B->sizeColunms() || A->sizeRow() != B->sizeRow())
    {
        throw invalid_argument("the matrizes size not iqual");
    }

    SparseMatrix *result = new SparseMatrix(A->sizeRow(), B->sizeColunms());

    for (size_t i = 1; i <= A->sizeRow(); i++)
    {
        for (size_t j = 1; j <= B->sizeColunms(); j++)
        {
            result->insert(i, j, A->get(i, j) + B->get(i, j));
        }
    }

    return result;
}

SparseMatrix *multiply(SparseMatrix *A, SparseMatrix *B)
{
    if (A->sizeColunms() != B->sizeRow())
    {
        throw invalid_argument("the matrizes size not compatible");
    }

    SparseMatrix *result = new SparseMatrix(A->sizeRow(), B->sizeColunms());

    for (size_t i = 1; i <= A->sizeRow(); i++)
    {
        for (size_t j = 1; j <= B->sizeColunms(); j++)
        {
            double value = 0;

            for (size_t k = 1; k <= B->sizeRow(); k++)
            {
                value += A->get(i, k) * B->get(k, j);
            }
            result->insert(i, j, value);
        }
    }

    return result;
}

SparseMatrix *createM(ifstream &arc)
{
    string line, contend;

    while (getline(arc, line))
    {
        contend += line;
        contend += "\n";
    }

    stringstream ss(contend);

    unsigned r, c;
    ss >> r >> c;

    if (r * c > 900000000)
    {
        throw out_of_range("invalid result size");
    }

    unsigned i, j;
    double value;

    SparseMatrix *result = new SparseMatrix(r, c);

    while (ss >> i >> j >> value)
    {
        result->insert(i, j, value);
    }

    return result;
}

SparseMatrix *createC(unsigned r, unsigned c)
{
    if (r * c > 900000000)
    {
        throw out_of_range("invalid result size");
    }

    cout << "insert the values bellow\n";

    SparseMatrix *result = new SparseMatrix(r, c);

    for (size_t i = 1; i <= r; i++)
    {
        for (size_t j = 1; j <= c; j++)
        {
            double value;
            cin >> value;
            result->insert(i, j, value);
        }
    }
    cin.ignore();

    return result;
}

int main()
{
    cout << color::green << "Welcome, type --help to see the comands " << "\n";

    vector<SparseMatrix *> setMatrix;

    while (true)
    {
        cout << color::green << " >> ";
        string line, cmd;
        getline(cin, line);

        stringstream ss(line);
        ss >> cmd;

        cout << color::green << " << ";

        try
        {
            if (cmd == "exit")
            {
                break;
            }
            else if (cmd == "init")
            {
                unsigned k;
                ss >> k;
                setMatrix = vector<SparseMatrix *>(k, nullptr);
                cout << color::yellow << "$init: initialized " << k << " matrizes\n";
            }
            else if (cmd == "insert")
            {
                unsigned s, i, j;
                double value;
                ss >> s >> i >> j >> value;

                if (setMatrix.size() == 0)
                {
                    cerr << color::red << "fail: initialize the set of matrices\n";
                    continue;
                }

                if (setMatrix[s] == nullptr)
                {
                    cerr << color::red << "fail: matrix not created\n";
                    continue;
                }

                if (s >= setMatrix.size())
                {
                    cerr << color::red << "fail: inexistent matrix\n";
                    continue;
                }

                setMatrix[s]->insert(i, j, value);

                cout << color::yellow << "$insert: inserted in matrix[" << s << "]" << " at (" << i << ", " << j << ") value: " << value << "\n";
            }
            else if (cmd == "print")
            {
                unsigned s;
                ss >> s;

                if (setMatrix.size() == 0)
                {
                    cerr << color::red << "fail: initialize the set matriz\n";
                    continue;
                }

                if (setMatrix[s] == nullptr)
                {
                    cerr << color::red << "fail: matrix not created\n";
                    continue;
                }

                if (s >= setMatrix.size())
                {
                    cerr << color::red << "fail: inexistent matrix\n";
                    continue;
                }

                cout << color::yellow << "$print: showing the matrix[" << s << "]\n";

                cout << "$print[" << s << "]";
                cout << color::green << "\n";

                cout << setw(setMatrix[s]->sizeColunms() * 3) << setfill('-') << "\n";

                setMatrix[s]->print();

                cout << setw(setMatrix[s]->sizeColunms() * 3) << setfill('-') << "\n";
            }
            else if (cmd == "get")
            {
                unsigned s, i, j;
                ss >> s >> i >> j;

                if (setMatrix.size() == 0)
                {
                    cerr << color::red << "fail: initialize the set matriz\n";
                    continue;
                }

                if (setMatrix[s] == nullptr)
                {
                    cerr << color::red << "fail: matrix not created\n";
                    continue;
                }

                if (s >= setMatrix.size())
                {
                    cerr << color::red << "fail: inexistent matrix\n";
                    continue;
                }

                cout << color::yellow << "$get: matrix[" << s << "] at (" << i << ", " << j << ") value: " << setMatrix[s]->get(i, j) << "\n";
            }
            else if (cmd == "create")
            {
                unsigned s, n, m;
                ss >> s >> n >> m;

                if (setMatrix.size() == 0)
                {
                    cerr << color::red << "fail: initialize the set of matrices\n";
                    continue;
                }

                if (s >= setMatrix.size())
                {
                    cerr << color::red << "fail: inexistent matrix\n";
                    continue;
                }

                setMatrix[s] = new SparseMatrix(n, m);

                cout << color::yellow << "$create: created matrix with index: " << s << ", size: " << n << "x" << m << "\n";
            }
            else if (cmd == "show")
            {
                if (setMatrix.size() == 0)
                {
                    cerr << color::red << "fail: initialize the set of matrices first\n";
                    continue;
                }

                cout << color::yellow << "$show: available matrices\n";

                for (size_t i = 0; i < setMatrix.size(); i++)
                {
                    cout << color::green << "matrix[" << i << "] ";

                    if (setMatrix[i] == nullptr)
                    {
                        cout << "not created\n";
                    }
                    else
                    {
                        cout << "created " << setMatrix[i]->sizeRow() << " x " << setMatrix[i]->sizeColunms() << "\n";
                    }
                }
            }
            else if (cmd == "sum")
            {
                unsigned s, v;
                ss >> s >> v;

                if (setMatrix.size() == 0)
                {
                    cerr << color::red << "fail: initialize the set matriz\n";
                    continue;
                }

                if (setMatrix[s] == nullptr || setMatrix[v] == nullptr)
                {
                    cerr << color::red << "fail: matrix not create\n";
                    continue;
                }

                if (s >= setMatrix.size() || v >= setMatrix.size())
                {
                    cerr << color::red << "fail: inexistent matrix\n";
                    continue;
                }

                SparseMatrix *result = sum(setMatrix[s], setMatrix[v]);

                cout << color::yellow << "$sum: matrix " << s << " and " << v << ", result:";
                cout << color::green << "\n";

                result->print();

                cout << color::green << " do you wanna save the matrix?[s/n]: ";
                char ans;
                cin >> ans;

                if (ans == 's')
                {
                    setMatrix.push_back(result);
                    cout << color::green << " matrix save at the final of the set of matrices\n";
                }
                else
                {
                    cout << color::green << " matrix not save\n";
                }
                cin.ignore();
            }
            else if (cmd == "mult")
            {
                unsigned s, v;
                ss >> s >> v;

                if (setMatrix.size() == 0)
                {
                    cerr << color::red << "fail: initialize the set matriz\n";
                    continue;
                }

                if (setMatrix[s] == nullptr || setMatrix[v] == nullptr)
                {
                    cerr << color::red << "fail: matrix not create\n";
                    continue;
                }

                if (s >= setMatrix.size() || v >= setMatrix.size())
                {
                    cerr << color::red << "fail: inexistent matrix\n";
                    continue;
                }

                SparseMatrix *result = multiply(setMatrix[s], setMatrix[v]);

                cout << color::yellow << "$sum: multiply " << s << " and " << v << ", result:";
                cout << color::green << "\n";

                result->print();

                cout << color::green << " do you wanna save the matrix?[s/n]: ";
                char ans;
                cin >> ans;

                if (ans == 's')
                {
                    setMatrix.push_back(result);
                    cout << color::green << " matrix save at the final of the set of matrices\n";
                }
                else
                {
                    cout << color::green << " matrix not save\n";
                }
                cin.ignore();
            }
            else if (cmd == "--help")
            {
                stringstream form;

                form << color::green << "\n";

                form << left << setw(20) << setfill('.') << "init t" << setw(20) << "" << "init t matrices in a set" << '\n';
                form << left << setw(20) << setfill('.') << "create s m n" << setw(20)
                     << "" << "create a matriz of size m x n" << '\n';
                form << left << setw(20) << setfill('.') << "insert i j v" << setw(20)
                     << "" << "insert a value in the position i j" << '\n';
                form << left << setw(20) << setfill('.') << "print s" << setw(20)
                     << "" << "print the matrix at index s" << '\n';
                form << left << setw(20) << setfill('.') << "get i j" << setw(20)
                     << "" << "return the value at position i j" << '\n';
                form << left << setw(20) << setfill('.') << "clear s" << setw(20)
                     << "" << "clear the matrix at index s" << '\n';
                form << left << setw(20) << setfill('.') << "show" << setw(20)
                     << "" << "show all the matrices in the set of matrices" << '\n';
                form << left << setw(20) << setfill('.') << "print s" << setw(20)
                     << "" << "print the matrix at index s" << '\n';
                form << left << setw(20) << setfill('.') << "sumt s u" << setw(20)
                     << "" << "return the sum of matrices s and u" << '\n';
                form << left << setw(20) << setfill('.') << "mult s u" << setw(20)
                     << "" << "return the multiply of s * u" << '\n';
                form << left << setw(20) << setfill('.') << "dimension s" << setw(20)
                     << "" << "return the dimension of matrix at index s" << '\n';
                form << left << setw(20) << setfill('.') << "print s" << setw(20)
                     << "" << "print the matrix at index s" << '\n';
                form << left << setw(20) << setfill('.') << "read s m.txt" << setw(20)
                     << "" << "read a matrix in a .txt and put in the matrix s" << '\n';
                form << left << setw(20) << setfill('.') << "readc s m n" << setw(20)
                     << "" << "read a matrix of size m x and put in the matrix s" << '\n';
                form << left << setw(20) << setfill('.') << "allclear" << setw(20)
                     << "" << "clear all matrices and resize the set of matrices to 0" << '\n';
                form << left << setw(20) << setfill('.') << "exit" << setw(20)
                     << "" << "exit the program" << '\n';
                cout << form.str();
            }
            else if (cmd == "clear")
            {
                unsigned s;
                ss >> s;

                if (setMatrix.size() == 0)
                {
                    cerr << color::red << "fail: initialize the set matriz\n";
                    continue;
                }

                if (setMatrix[s] == nullptr)
                {
                    cerr << color::red << "fail: matrix not created\n";
                    continue;
                }

                if (s >= setMatrix.size())
                {
                    cerr << color::red << "fail: inexistent matrix\n";
                    continue;
                }

                delete setMatrix[s];
                setMatrix[s] = nullptr;

                cout << color::yellow << "$clear: matrix: " << s << "clared successful\n";
            }
            else if (cmd == "dimension")
            {
                unsigned s;
                ss >> s;

                if (setMatrix.size() == 0)
                {
                    cerr << color::red << "fail: initialize the set matriz\n";
                    continue;
                }

                if (setMatrix[s] == nullptr)
                {
                    cerr << color::red << "fail: matrix not created\n";
                    continue;
                }

                if (s >= setMatrix.size())
                {
                    cerr << color::red << "fail: inexistent matrix\n";
                    continue;
                }

                cout << color::yellow << "$dimension: matrix[" << s << "]" << " " << setMatrix[s]->sizeRow() << "x" << setMatrix[s]->sizeColunms() << "\n";
            }
            else if (cmd == "read")
            {
                unsigned s;
                ss >> s;

                if (setMatrix.size() == 0)
                {
                    cerr << color::red << "fail: initialize the set matriz\n";
                    continue;
                }

                if (s >= setMatrix.size())
                {
                    cerr << color::red << "fail: inexistent matrix\n";
                    continue;
                }

                string arq;
                ss >> arq;

                ifstream arc(arq);

                if (!arc.is_open())
                {
                    cerr << color::red << "fail: archive not opened\n";
                    continue;
                }

                setMatrix[s] = createM(arc);
                cout << color::yellow << "$read: matrix: " << arq << " in index [" << s << "] successful\n";
            }
            else if (cmd == "allclear")
            {

                for (size_t i = 0; i < setMatrix.size(); i++)
                {
                    delete setMatrix[i];
                    setMatrix[i] = nullptr;
                }
                setMatrix = vector<SparseMatrix *>(0);

                cout << color::yellow << "$allclear: all matrices clared successful\n";
            }
            else if (cmd == "readc")
            {
                unsigned s, r, c;
                ss >> s >> r >> c;

                if (setMatrix.size() == 0)
                {
                    cerr << color::red << "fail: initialize the set matriz\n";
                    continue;
                }

                if (s >= setMatrix.size())
                {
                    cerr << color::red << "fail: inexistent matrix\n";
                    continue;
                }

                setMatrix[s] = createC(r, c);
                cout << " << $read[" << s << "]" << " successful\n";

                cout << color::yellow << " << $read: matrix in index: [" << s << "] successful\n";
            }
            else
            {
                cerr << color::red << "fail: invalid comand\n";
            }
        }
        catch (const invalid_argument &arg)
        {
            cerr << color::red << "fail: " << arg.what() << "\n";
        }
        catch (const out_of_range &arg)
        {
            cerr << color::red << "fail: " << arg.what() << " of matrix\n";
        }
        catch (const std::exception &e)
        {
            std::cout << "fatal error: " << e.what() << std::endl;
        }
    }

    cout << color::red << "over\n";

    return 0;
}