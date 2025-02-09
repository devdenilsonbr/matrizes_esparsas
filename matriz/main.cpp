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

                if (!(ss >> k))
                {
                    cerr << color::yellow << "usage: init <number_of_matrices>\n";
                    continue;
                }

                if (setMatrix.size() != 0)
                {
                    cerr << color::red << "fail: the matrices set has already been initialized\n";
                    continue;
                }

                setMatrix = vector<SparseMatrix *>(k, nullptr);
                cout << color::yellow << "$init: initialized " << k << " matrizes\n";
            }
            else if (cmd == "insert")
            {
                unsigned s, i, j;
                double value;

                if (!(ss >> s >> i >> j >> value))
                {
                    cerr << color::yellow << "usage: insert <matrix_index> <row> <col> <value>\n";
                    continue;
                }

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

                if (!(ss >> s))
                {
                    cerr << color::yellow << "usage: print <matrix_index>\n";
                    continue;
                }

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

                bool write = true;

                if (setMatrix[s]->sizeRow() >= 5000 || setMatrix[s]->sizeColunms() >= 5000)
                {
                    cout << color::green << "the chosen matrix is too large, do you want to write/print to the console anyway? [s/n]: ";

                    char ans;
                    cin >> ans;

                    ans = std::tolower(ans);

                    write = ans == 's' ? true : false;
                }

                std::string content = setMatrix[s]->print(write, true);

                cout << color::green << "Do you want to save the matrix content to file? [s/n]: ";
                char ans;
                cin >> ans;

                ans = std::tolower(ans);

                if (ans == 's')
                {
                    string filename;

                    cout << color::green << "Enter the filename to save the matrix content: ";
                    cin >> filename;

                    std::string filePath = "data/print/" + filename + "-pt.txt";

                    std::ofstream outFile(filePath);

                    if (outFile.is_open())
                    {
                        outFile << content;
                        outFile.close();
                        cout << color::green << "Matrix content saved to " << filePath << "\n";
                    }
                    else
                    {
                        cerr << color::red << "Failed to open the file for saving\n";
                    }
                }
                else
                {
                    cout << color::green << "Matrix content not saved\n";
                }
                cin.ignore();
            }
            else if (cmd == "get")
            {
                unsigned s, i, j;

                if (!(ss >> s >> i >> j))
                {
                    cerr << color::yellow << "usage: get <matrix_index> <row> <col>\n";
                    continue;
                }

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
            else if (cmd == "create" || cmd == "new")
            {
                unsigned s, n, m;

                if (!(ss >> s >> n >> m))
                {
                    cerr << color::yellow << "usage: create <index> <rows> <cols>\n";
                    continue;
                }

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

                if (!(ss >> s >> v))
                {
                    cerr << color::yellow << "usage: sum <matrix_index> <other_matrix_index>\n";
                    continue;
                }

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

                ans = std::tolower(ans);

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

                if (!(ss >> s >> v))
                {
                    cerr << color::yellow << "usage: mult <matrix_index> <other_matrix_index>\n";
                    continue;
                }

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

                ans = std::tolower(ans);

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
            else if (cmd == "--help" || cmd == "help")
            {
                stringstream form;

                form << color::green << "\n";

                std::vector<std::pair<std::string, std::string>> commands = {
                    {"init t", "init t matrices in a set"},
                    {"create s m n", "create a matrix of size m x n"},
                    {"insert i j v", "insert a value in the position i j"},
                    {"print s", "print the matrix at index s"},
                    {"get i j", "return the value at position i j"},
                    {"clear s", "clear the matrix at index s"},
                    {"show", "show all the matrices in the set of matrices"},
                    {"sum s u", "return the sum of matrices s and u"},
                    {"mult s u", "return the multiply of s * u"},
                    {"dimension s", "return the dimension of matrix at index s"},
                    {"read s m.txt", "read a matrix in a .txt and put in the matrix s"},
                    {"readc s m n", "read a matrix of size m x n and put in the matrix s"},
                    {"allclear", "clear all matrices and resize the set of matrices to 0"},
                    {"exit", "exit the program"}};

                for (const auto &cmd : commands)
                {
                    form << left << setw(20) << setfill('.') << cmd.first
                         << setw(20) << cmd.second << '\n';
                }

                cout << form.str();
            }
            else if (cmd == "clear")
            {
                unsigned s;

                if (!(ss >> s))
                {
                    cerr << color::yellow << "usage: clear <matrix_index>\n";
                    continue;
                }

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

                cout << color::yellow << "$clear: matrix: " << s << " cleared successful\n";
            }
            else if (cmd == "dimension")
            {
                unsigned s;

                if (!(ss >> s))
                {
                    cerr << color::yellow << "usage: dimension <matrix_index>\n";
                    continue;
                }

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

                cout << color::yellow << "$dimension: matrix_index: " << s << " " << setMatrix[s]->sizeRow() << "x" << setMatrix[s]->sizeColunms() << "\n";
            }
            else if (cmd == "read")
            {
                unsigned s;

                if (!(ss >> s))
                {
                    cerr << color::yellow << "usage: read <matrix_index> <matrix_file>\n";
                    continue;
                }

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

                ifstream arc("data/" + arq);

                if (!arc.is_open())
                {
                    cerr << color::red << "fail: archive not opened\n";
                    continue;
                }

                setMatrix[s] = createM(arc);
                cout << color::yellow << "$read: matrix: " << arq << " as been loaded in index " << s << " successful\n";
            }
            else if (cmd == "allclear" || cmd == "clearall")
            {

                for (size_t i = 0; i < setMatrix.size(); i++)
                {
                    delete setMatrix[i];
                    setMatrix[i] = nullptr;
                }
                setMatrix = vector<SparseMatrix *>(0);

                cout << color::yellow << "$allclear: all matrices cleared successful\n";
            }
            else if (cmd == "readc")
            {
                unsigned s, r, c;

                if (!(ss >> s >> r >> c))
                {
                    cerr << color::yellow << "usage: readc <matrix_index> <rows> <cols>\n";
                    continue;
                }

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

                cout << color::yellow << " << $read: matrix in index: " << s << " successful\n";
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

    cout << color::red << "program aborted...\n";

    return 0;
}