#include <iostream>
#include "MatrizEsparsas.h"
#include <fstream>
#include <vector>
#include <stdexcept>
#include <sstream>

using namespace std;
// Author: Willgner S. Ferreira, 567152
void somar(MatrizEsparsas &a, MatrizEsparsas &b, vector<MatrizEsparsas> &matrices)
{
    if (a.getLinhas() == b.getLinhas() && a.getColunas() == b.getColunas())
    {
        MatrizEsparsas c;
        c.criarSentinelas(a.getLinhas(), a.getColunas());
        for (int i = 1; i <= c.getLinhas(); i++)
            for (int j = 1; j <= c.getColunas(); j++)
                c.insert(i, j, a.get(i, j) + b.get(i, j));

        cout << "This is the sum of the matrices:" << endl;
        c.print();
        string op = "x";
        while (op != "N")
        {
            cout << "Do you want save this matrix? (S/N)" << endl;
            cin >> op;
            if (op == "S")
            {
                cout << "Matrix saved successfully, his index is: " << matrices.size() << endl;
                matrices.push_back(c);
                op = "N";
            }
            else
            {
                cout << "Choose a valid option" << endl;
            }
        }
        cin.ignore(10000, '\n');
    }
    else
    {
        cout << "It wasn't possible sum" << endl;
    }
}
// Author: Willgner S. Ferreira, 567152
void multiplicar(MatrizEsparsas &a, MatrizEsparsas &b, vector<MatrizEsparsas> &matrices)
{
    if (a.getColunas() == b.getLinhas())
    {
        MatrizEsparsas c;
        c.criarSentinelas(a.getLinhas(), b.getColunas());
        double resultado_mult;
        for (int i = 1; i <= c.getLinhas(); i++)
        {
            for (int v = 1; v <= c.getColunas(); v++)
            {
                resultado_mult = 0;
                for (int j = 1; j <= b.getLinhas(); j++)
                {
                    resultado_mult += a.get(i, j) * b.get(j, v);
                }
                c.insert(i, v, resultado_mult);
            }
        }
        cout << "This is the multiplication of the matrices:" << endl;
        c.print();
        string op;
        while (op != "N")
        {
            cout << "Do you want save this matrix? (S/N)" << endl;
            cin >> op;
            if (op == "S")
            {
                cout << "Matrix saved successfully, his index is: " << matrices.size() << endl;
                matrices.push_back(c);
                op = "N";
            }
            else
            {
                cout << "Choose a valid option" << endl;
            }
        }
        cin.ignore(10000, '\n');
    }
    else
    {
        cout << "nao foi possivel multiplicar" << endl;
    }
}

void lerMatriz(MatrizEsparsas &m, string matriz)
{
    int linha, coluna;
    string temp;
    ifstream txtFile;
    txtFile.open(matriz + ".txt");

    if (txtFile.is_open())
    {
        txtFile >> linha >> coluna;
        m.criarSentinelas(linha, coluna);
        while (txtFile >> linha >> coluna >> temp)
        {
            m.insert(linha, coluna, stod(temp));
        }
    }
    else
    {
        throw runtime_error("Invalid file");
    }
    txtFile.close();
}

void lerMatriz(MatrizEsparsas &m, int linha, int coluna)
{
    m.criarSentinelas(linha, coluna);
    string data;
    cout << "Insert rows, columns and values, of all ";
    cin.clear();
    getline(cin, data);
    stringstream buffer(data);
    while (buffer >> linha >> coluna >> data)
    {
        m.insert(linha, coluna, stod(data));
    }
}
// Author: Willgner S. Ferreira, 567152
int main()
{
    vector<MatrizEsparsas> matrizes;
    cout << "Welcome to matrix system!" << endl;
    cout << "type 'help' to see the list of commands" << endl;
    while (true)
    {
        string comando, opcao;
        getline(cin, comando);
        stringstream buffer{comando};
        buffer >> opcao;
        cout << "$" << buffer.str() << endl;

        // exit
        if (opcao == "exit")
        {
            matrizes.clear();
            break;
        }
        // create i j
        else if (opcao == "create")
        {
            int i, j;
            if (buffer >> i >> j && i > 0 && j > 0 && i <= 30000 && j <= 30000)
            {
                MatrizEsparsas m;
                try
                {
                    m.criarSentinelas(i, j);
                    matrizes.push_back(m);
                    cout << "The matrix was created successfully, his index is: " << matrizes.size() - 1 << endl;
                }
                catch (std::invalid_argument e)
                {
                    cerr << e.what() << endl;
                }
            }
            else
            {
                cout << "Please enter valid numbers" << endl;
            }
        }
        // createCopy i
        else if (opcao == "createCopy")
        {
            int i;
            if (buffer >> i && i < matrizes.size())
            {
                try
                {
                    matrizes.push_back(matrizes.at(i));
                    cout << "The matrix was copied successfully, his index is: " << matrizes.size() - 1 << endl;
                }
                catch (out_of_range e)
                {
                    cerr << e.what() << endl;
                }
            }
            else
            {
                cout << "Please enter a valid index" << endl;
            }
        }
        // read mtrx
        else if (opcao == "read")
        {
            string nome;
            ifstream arquivo;
            MatrizEsparsas m;
            buffer >> nome;
            arquivo.open(nome+".txt");
            if (arquivo.is_open())
            {
                try
                {
                    lerMatriz(m, nome);
                    matrizes.push_back(m);
                    cout << "The matrix was created successfully, his index is: " << matrizes.size() - 1 << endl;
                }
                catch (std::invalid_argument e)
                {
                    cerr << e.what() << endl;
                }
            }
            else
            {
                cout << "Please enter a file name" << endl;
            }
        }
        // readC i j
        else if (opcao == "readC")
        {
            int i, j;
            MatrizEsparsas m;
            if (buffer >> i >> j && i > 0 && j > 0 && i <= 30000 && j <= 30000)
            {

                try
                {
                    lerMatriz(m, i, j);
                    matrizes.push_back(m);
                    cout << "The matrix was created successfully, his index is: " << matrizes.size() - 1 << endl;
                }
                catch (const std::invalid_argument e)
                {
                    cerr << e.what() << '\n';
                }
            }
            else
            {
                cout << "Please enter valid numbers" << endl;
            }
        }
        // update m i j value
        else if (opcao == "update")
        {
            int d, i, j;
            double x;
            if (buffer >> d >> i >> j >> x && i > 0 && j > 0 && i <= 30000 && j <= 30000 && d < matrizes.size())
            {
                try
                {
                    matrizes.at(d).insert(i, j, x);
                    cout << "The value was updated successfully" << endl;
                }
                catch (std::invalid_argument e)
                {
                    cerr << e.what() << endl;
                }
            }
            else
            {
                cout << "Please enter valid numbers" << endl;
            }
        }
        // get m i j
        else if (opcao == "get")
        {
            int d, i, j;
            if (buffer >> d >> i >> j && i > 0 && j > 0 && i <= 30000 && j <= 30000 && d < matrizes.size())
            {

                try
                {
                    cout << "The value is: " << matrizes.at(d).get(i, j) << endl;
                }
                catch (std::invalid_argument e)
                {
                    cerr << e.what() << endl;
                }
            }
            else
            {
                cout << "Please enter valid numbers" << endl;
            }
        }
        // show m
        else if (opcao == "show")
        {
            int d;
            if (buffer >> d && d < matrizes.size())
            {
                try
                {
                    cout << "Showing the matrix[" << d << "]" << endl;
                    matrizes.at(d).print();
                }
                catch (std::invalid_argument e)
                {
                    cerr << e.what() << endl;
                }
            }
            else
            {
                cout << "Please enter a valid index" << endl;
            }
        }
        // showidx
        else if (opcao == "showidx")
        {
            if (matrizes.size() > 0)
                cout << "Matrices indexes:";
            else
                cout << "No matrix has been created yet" << endl;
            for (int i = 0; i < matrizes.size(); i++)
            {
                if (i > 0)
                    cout << ",";
                cout << " " << i;
            }
            cout << endl;
        }
        // sum m n
        else if (opcao == "sum")
        {
            int m, n;
            if (buffer >> m >> n && m < matrizes.size() && n < matrizes.size())
            {
                try
                {
                    somar(matrizes.at(m), matrizes.at(n), matrizes);
                }
                catch (std::invalid_argument e)
                {
                    cerr << e.what() << endl;
                }
            }
            else
            {
                cout << "Please enter valid indexes" << endl;
            }
        }
        // multiply m n
        else if (opcao == "multiply")
        {
            int m, n;
            if (buffer >> m >> n && m < matrizes.size() && n < matrizes.size())
            {
                try
                {
                    multiplicar(matrizes.at(m), matrizes.at(n), matrizes);
                }
                catch (std::invalid_argument e)
                {
                    cerr << e.what() << endl;
                }
            }
            else
            {
                cout << "Please enter valid indexes" << endl;
            }
        }
        // clear m
        else if (opcao == "clear")
        {
            int m;
            if (buffer >> m && m < matrizes.size())
            {
                try
                {
                    matrizes.at(m).clear();
                    cout << "The matrix [" << m << "] has been cleared" << endl;
                }
                catch (invalid_argument e)
                {
                    cerr << e.what() << endl;
                }
            }
            else
            {
                cout << "Please enter a valid index" << endl;
            }
        }
        // erase m
        else if (opcao == "erase")
        {
            int m;
            if (buffer >> m && m < matrizes.size())
            {
                try
                {
                    matrizes.erase(matrizes.begin() + m);
                    cout << "he matrix [" << m << "] has been erased" << endl;
                }
                catch (invalid_argument e)
                {
                    cerr << e.what() << '\n';
                }
            }
            else
            {
                cout << "Please enter a valid index" << endl;
            }
        }
        // eraseAll
        else if (opcao == "eraseAll")
        {
            try
            {
                matrizes.clear();
                cout << "The vector of matrices has been erased" << endl;
            }
            catch (invalid_argument e)
            {
                cerr << e.what() << endl;
            }
        }
        // help
        else if (opcao == "help")
        {
            cout << "HELP --------------------------------------------------------------------------------------" << endl;
            cout << "exit............................close the program" << endl;
            cout << "create i j......................create a new matrix with m rows and n columns" << endl;
            cout << "createCopy i....................create copy of a matrix i of the vector of matrices" << endl;
            cout << "read m..........................read a sparse matrix from the file with name m.txt" << endl;
            cout << "readC i j.......................create a sparse matrix with i rows and j columns" << endl;
            cout << "show i..........................print the matrix i in the terminal" << endl;
            cout << "showidx.........................show all the indexes of the matrices" << endl;
            cout << "get m i j.......................show the value of cell(c,j) in the matrix m" << endl;
            cout << "sum m n.........................sum the matrices m and n of the vector of matrices" << endl;
            cout << "multiply m n....................multiply the matrices m and n of the vector of matrices" << endl;
            cout << "update m i j value..............update the value of the cell(i,j) in the matrix m" << endl;
            cout << "clear m.........................clear the matrix m" << endl;
            cout << "erase m.........................erase the matrix m" << endl;
            cout << "eraseAll........................erase all the matrices currently in the program" << endl;
            cout << "-------------------------------------------------------------------------------------------" << endl;
        }
        else
        {
            cout << "wrong arguments" << endl;
        }
    }
    return 0;
}
