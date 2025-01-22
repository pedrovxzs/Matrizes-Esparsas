#include <iostream>
#include "MatrizEsparsas.h"

using namespace std;

int main()
{
    cout << "Comecando a Matriz" << endl;
    MatrizEsparsas matriz(5, 5);
    matriz.insert(1,2, 4);
    matriz.insert(1,1, 2);
    cout << matriz.get(1,2) << endl;
    cout << matriz.get(1,1) << endl << endl;
    matriz.print();
    cout << endl;

    // Testando a inserção de um valor na mesma coluna
    matriz.insert(1,2, 8);
    matriz.insert(1,1, 6);
    cout << matriz.get(1,2) << endl;
    cout << matriz.get(1,1) << endl << endl;
    matriz.print();
    // Sentinela Coluna sendo duplicado quando é inserido um valor na mesma coluna
    matriz.printSentinelas();

}