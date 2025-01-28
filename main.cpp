#include <iostream>
#include "MatrizEsparsas.h"
#include <fstream>
#include <vector>
#include <stdexcept>
using namespace std;

//Teste para ler a matriz atraves de um arquivo.
void lerMatriz(MatrizEsparsas& m)
{
    int linha, coluna;
    double valor;
    ifstream txtFile;
    txtFile.open("matriz.txt");

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


int main()
{
    

}