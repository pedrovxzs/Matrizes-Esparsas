#include <iostream>
#include "MatrizEsparsas.h"

using namespace std;

int main()
{
    cout << "Começando a Matriz" << endl;
    MatrizEsparsas matriz(5, 5);
    matriz.print();
    cout << "Pegando o valor 1,1" << matriz.get(1,1) << endl;
    return 0;
}