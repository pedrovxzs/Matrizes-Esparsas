#include <iostream>
#include "MatrizEsparsas.h"
#include <fstream>
#include <vector>
#include <stdexcept>
#include <sstream>

using namespace std;

void somar(MatrizEsparsas& a, MatrizEsparsas& b) {
	if(a.getLinhas() == b.getLinhas() && a.getColunas() == b.getColunas()){
	    MatrizEsparsas c;
        c.criarSentinelas(a.getLinhas(), a.getColunas());
	    for(int i = 1; i <= c.getLinhas(); i++)
	        for(int j = 1; j <= c.getColunas(); j++)
	            c.insert(i, j, a.get(i, j) + b.get(i, j));
        c.print();
	}
	else {
	    cout << "Nao foi possivel somar" << endl;
	}
}

void multiplicar(MatrizEsparsas& a, MatrizEsparsas& b) {
	if(a.getColunas() == b.getLinhas()){
	    MatrizEsparsas c;
        c.criarSentinelas(a.getLinhas(), b.getColunas());
	    double resultado_mult;
	    for(int i = 1; i <= c.getLinhas(); i++){
	        for(int v = 1; v <= c.getColunas(); v++){
                resultado_mult = 0;
	            for(int j = 1; j <= b.getLinhas(); j++){
	                resultado_mult += a.get(i, j)*b.get(j, v);
	            }
	            c.insert(i, v, resultado_mult);
	        }
	    }
	    c.print();
    }
    else {
        cout << "nao foi possivel multiplicar" << endl;
    }
}

void lerMatriz(MatrizEsparsas& m, string matriz)
{
    int linha, coluna;
    double valor;
    ifstream txtFile;
    txtFile.open(matriz+".txt");

    if (txtFile.is_open())
    {
    txtFile >> linha >> coluna;
    m.criarSentinelas(linha, coluna);
        while (txtFile >> linha >> coluna >> valor)
        {
            m.insert(linha, coluna, valor);
        }
    }
    txtFile.close();
}

void lerMatriz(MatrizEsparsas& m, int linha, int coluna)
{
    double valor;
    m.criarSentinelas(linha, coluna);
    string data;
    cout << "Insert rows, columns and values, of all ";
    cin.clear();
    getline(cin, data);
    stringstream buffer(data);
    while(buffer >> linha >> coluna >> valor)
    {
        m.insert(linha, coluna, valor);
    }
}

int main()
{
    vector<MatrizEsparsas> matrizes;
    cout << "Welcome to matrix system!" << endl;
    cout << "type 'help' to see the list of commands" << endl;
    while(true){
        string comando, opcao;
        getline(cin, comando);
        stringstream buffer {comando};
        buffer >> opcao;
        cout << "$" << buffer.str() << endl;

        //exit
        if(opcao == "exit")
        {
            matrizes.clear();
            break;
        }
        //create i j
        else if(opcao == "create")
        {
            try{
            int i, j;
            buffer >> i >> j;
            MatrizEsparsas m;
            m.criarSentinelas(i, j);
            matrizes.push_back(m);
            }
            catch(std::invalid_argument e){
                cout << e.what() << endl;
            }
        }
        //createCopy i
        else if(opcao == "createCopy")
        {
            try{
            int i;
            buffer >> i;
            try{
            matrizes.push_back(matrizes.at(i));
            } 
            catch(out_of_range e)
            {
                cout << e.what() << endl;
                break;
            }
            }
            catch(std::invalid_argument e){
                cout << e.what() << endl;
            }
        }
        //read "mtrx.txt"
        else if(opcao == "read")
        {
            try{
            string nome;
            MatrizEsparsas m;
            buffer >> nome;
            lerMatriz(m, nome);
            matrizes.push_back(m);
            }
            catch(std::invalid_argument e){
                cout << e.what() << endl;
            }
        }
        //update m i j value
        else if(opcao == "update")
        {
            try{
            int d, i, j;
            double x;
            buffer >> d >> i >> j >> x;
            matrizes.at(d).insert(i, j, x);
            }
            catch(std::invalid_argument e){
                cout << e.what() << endl;
            }
        }
        //get m i j
        else if(opcao == "get")
        {
            try{
            int d, i, j;
            buffer >> d >> i >> j;
            cout << matrizes.at(d).get(i, j) << endl;
            }
            catch(std::invalid_argument e){
                cout << e.what() << endl;
            }
        }
        //show m
        else if(opcao == "show")
        {
            try{
            int d;
            buffer >> d;
            matrizes.at(d).print();
            }
            catch(std::invalid_argument e){
                cout << e.what() << endl;
            }
        }
        //showidx
        else if(opcao == "showidx")
        {
            for(int i = 0; i < matrizes.size(); i++)
                cout << i << endl;
        }
        //sum m n
        else if(opcao == "sum")
        {
            try{
            int m, n;
            buffer >> m >> n;
            somar(matrizes.at(m), matrizes.at(n));
            }
            catch(std::invalid_argument e){
                cout << e.what() << endl;
            }
        }
        //multiply m n
        else if(opcao == "multiply")
        {
            try{
            int m, n;
            buffer >> m >> n;
            multiplicar(matrizes.at(m), matrizes.at(n));
            }
            catch(std::invalid_argument e){
                cout << e.what() << endl;
            }
        }
        //help
        else if(opcao == "help")
        {
            cout << "HELP --------------------------------------------------------------------------------------" << endl;
            cout << "exit............................close the program" << endl;
            cout << "create i j......................create a new matrix with m rows and n columns" << endl;
            cout << "createCopy i....................create copy of a matrix i of the vector of matrices" << endl;
            cout << "read 'm.txt'....................read a sparse matrix from the file with name 'm.txt'" << endl;
            cout << "show i..........................print the matrix i in the terminal" << endl;
            cout << "showidx.........................show all the indexes of the matrices" << endl;
            cout << "get m i j.......................show the value of cell(c,j) in the matrix m" << endl;
            cout << "sum m n.........................sum the matrices m and n of the vector of matrices" << endl;
            cout << "multiply m n....................multiply the matrices m and n of the vector of matrices" << endl;
            cout << "update m i j value..............update the value of the cell(i,j) in the matrix m" << endl;
            cout << "-------------------------------------------------------------------------------------------" << endl;
        }   
        else
        {
            cout << "wrong arguments" << endl;
        }
    }
    return 0;
}
