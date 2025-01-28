#include <iostream>
#include "MatrizEsparsas.h"
#include <fstream>
#include <vector>
#include <stdexcept>
#include <sstream>

using namespace std;

void soma(MatrizEsparsas& a, MatrizEsparsas& b) {
	if(a.getLinhas() == b.getLinhas() && a.getColunas() == b.getColunas()){
        // a.print();
        // cout << endl;
        // b.print();
        // cout << endl;

	    MatrizEsparsas c;
        c.criarSentinelas(a.getLinhas(), a.getColunas());
	    for(int i = 1; i <= c.getLinhas(); i++)
	        for(int j = 1; j <= c.getColunas(); j++)
	            c.insert(i, j, a.get(i, j) + b.get(i, j));
        c.print();
	}
	else {
	    cout << "nao foi possivel somar" << endl;
	}
}

//Teste para ler a matriz atraves de um arquivo.
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
    a.print();
    cout << endl;
    lerMatriz(b, "matriz");
    b.print();
    cout << endl;
    matrizes.push_back(a);
    matrizes.push_back(b);
    soma(a, b);

}