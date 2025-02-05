#include <iostream>
#include "MatrizEsparsas.h"
#include <fstream>
#include <vector>
#include <stdexcept>
#include <sstream>

using namespace std;

void somar(MatrizEsparsas &a, MatrizEsparsas &b, vector<MatrizEsparsas> matrices)
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
        char op;
        while (op != 'N')
        {
            cout << "Do you want save this matrix? (S/N)" << endl;
            cin >> op;
            if (op == 'S')
            {
             matrices.push_back(c);
             op = 'N';   
            }
            else
            {
                cout << "Choose a valid option" << endl;
            }
        }
    }
    else
    {
        cout << "It wasn't possible sum" << endl;
    }
}

void multiplicar(MatrizEsparsas &a, MatrizEsparsas &b, vector<MatrizEsparsas> matrices)
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
        char op;
        while (op != 'N')
        {
            cout << "Do you want save this matrix? (S/N)" << endl;
            cin >> op;
            if (op == 'S')
            {
             matrices.push_back(c);
             op = 'N';   
            }
            else
            {
                cout << "Choose a valid option" << endl;
            }
        }
    }
    else
    {
        cout << "nao foi possivel multiplicar" << endl;
    }
}

void lerMatriz(MatrizEsparsas &m, string matriz)
{
    int linha, coluna;
    double valor;
    ifstream txtFile;
    txtFile.open(matriz + ".txt");

    if (txtFile.is_open())
    {
        txtFile >> linha >> coluna;
        m.criarSentinelas(linha, coluna);
        while (txtFile >> linha >> coluna >> valor)
        {
            m.insert(linha, coluna, valor);
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
    double valor;
    m.criarSentinelas(linha, coluna);
    string data;
    cout << "Insert rows, columns and values, of all ";
    cin.clear();
    getline(cin, data);
    stringstream buffer(data);
    while (buffer >> linha >> coluna >> valor)
    {
        m.insert(linha, coluna, valor);
    }
}

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
            buffer >> i >> j;
            MatrizEsparsas m;
            try
            {
                m.criarSentinelas(i, j);
            }
            catch (std::invalid_argument e)
            {
                cerr << e.what() << endl;
            }
            matrizes.push_back(m);
        }
        // createCopy i
        else if (opcao == "createCopy")
        {
            int i;
            buffer >> i;
            try
            {
                matrizes.push_back(matrizes.at(i));
            }
            catch (out_of_range e)
            {
                cerr << e.what() << endl;
            }
        }
        // read "mtrx.txt"
        else if (opcao == "read")
        {
            string nome;
            MatrizEsparsas m;
            buffer >> nome;
            try
            {
                lerMatriz(m, nome);
            }
            catch (std::invalid_argument e)
            {
                cerr << e.what() << endl;
            }
            matrizes.push_back(m);
        }
        // update m i j value
        else if (opcao == "update")
        {

            int d, i, j;
            double x;
            buffer >> d >> i >> j >> x;
            try
            {
                matrizes.at(d).insert(i, j, x);
            }
            catch (std::invalid_argument e)
            {
                cerr << e.what() << endl;
            }
        }
        // get m i j
        else if (opcao == "get")
        {

            int d, i, j;
            buffer >> d >> i >> j;
            try
            {
                cout << matrizes.at(d).get(i, j) << endl;
            }
            catch (std::invalid_argument e)
            {
                cerr << e.what() << endl;
            }
        }
        // show m
        else if (opcao == "show")
        {

            int d;
            buffer >> d;
            try
            {
                matrizes.at(d).print();
            }
            catch (std::invalid_argument e)
            {
                cerr << e.what() << endl;
            }
        }
        // showidx
        else if (opcao == "showidx")
        {
            cout << "Matrix indexes:";
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
            buffer >> m >> n;
            try
            {
                somar(matrizes.at(m), matrizes.at(n), matrizes);
            }
            catch (std::invalid_argument e)
            {
                cerr << e.what() << endl;
            }
        }
        // multiply m n
        else if (opcao == "multiply")
        {
                int m, n;
                buffer >> m >> n;
            try
            {
                multiplicar(matrizes.at(m), matrizes.at(n), matrizes);
            }
            catch (std::invalid_argument e)
            {
                cerr << e.what() << endl;
            }
        }
        // clear m
        else if (opcao == "clear")
        {
            int m;
            buffer >> m;
            try
            {
                matrizes.at(m).clear();
            }
            catch (invalid_argument e)
            {
                cerr << e.what() << endl;
            }
        }
        // erase m
        else if (opcao == "erase")
        {
            int m;
            buffer >> m;
            try
            {
                matrizes.erase(matrizes.begin()+m);
            }
            catch(invalid_argument e)
            {
                cerr << e.what() << '\n';
            }
            
        }
        // clearAll
        else if (opcao == "clearAll")
        {
            try
            {
                matrizes.clear();
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
            cout << "read 'm'........................read a sparse matrix from the file with name 'm.txt'" << endl;
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
