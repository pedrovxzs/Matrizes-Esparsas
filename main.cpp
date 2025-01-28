#include <iostream>
#include "MatrizEsparsas.h"
#include <fstream>
#include <vector>

using namespace std;

//Teste para ler a matriz atraves de um arquivo.
void lerMatriz(MatrizEsparsas& m, string matriz)
{
    int linha, coluna;
    double valor;

    ifstream txtFile;
    txtFile.open("matriz.txt");
    if (txtFile.is_open())
    {
        while (txtFile >> linha >> coluna >> valor)
        {
            m.insert(linha, coluna, valor);
        }
    }
    txtFile.close();
}


int main()
{
    cout << "Comecando a Matriz" << endl;
    MatrizEsparsas matriz(5, 5);
    matriz.insert(1,2, 4);
    matriz.insert(1,1, 2);
    matriz.insert(2,1, 3);
    cout << matriz.get(1,2) << endl;
    cout << matriz.get(1,1) << endl << endl;
    matriz.print();
    matriz.printSentinelas();
    cout << endl;

    // Testando a inserção de um valor na mesma coluna
    matriz.insert(1,2, 8);
    matriz.insert(1,1, 6);
    matriz.insert(2,1, 10);
    cout << matriz.get(1,2) << endl;
    cout << matriz.get(1,1) << endl << endl;
    matriz.print();
    // Sentinela Coluna sendo duplicado quando é inserido um valor na mesma coluna
    matriz.printSentinelas();

    cout<< matriz.getColunas()<< endl << matriz.getLinhas() << endl;


}