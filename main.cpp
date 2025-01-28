#include <iostream>
#include "MatrizEsparsas.h"
#include <fstream>
#include <vector>
#include <stdexcept>
#include <sstream>

using namespace std;

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
    MatrizEsparsas matriz;
    lerMatriz(matriz);
    matrizes.push_back(matriz);
    matrizes.at(0).print();

}