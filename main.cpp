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

void lerMatriz(MatrizEsparsas& m)
{
    int linha, coluna;
    double valor;
    cout << "Insira o tamanho da linha e coluna, e depois as coordenadas dos valores, com o valores, e pressione enter quando terminar: " << endl;
    cin >> linha >> coluna;
    m.criarSentinelas(linha, coluna);
    string data;
    
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
    MatrizEsparsas a, b;
    lerMatriz(a, "matriz");
    lerMatriz(b, "matrizb");
    matrizes.emplace_back(a);
    matrizes.emplace_back(b);
    cout << endl << "Matriz A: " << endl;
    matrizes.at(0).print();

    cout << endl << "Matriz B:" << endl;
    matrizes.at(1).print();

    cout << endl << "Soma A e B:" << endl;
    somar(matrizes.at(0), matrizes.at(1));

    cout << endl << "Multiplicacao de A e B:" << endl;
    multiplicar(matrizes.at(0),matrizes.at(1));
}
