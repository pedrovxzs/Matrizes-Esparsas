#include <iostream>
#include "MatrizEsparsas.h"

using namespace std;

int main()
{
    cout << "Começando a Matriz" << endl;
    MatrizEsparsas matriz(5, 5);
    matriz.print();

    return 0;
}