#include <iostream>
#include "MatrizEsparsas.h"

using namespace std;

int main()
{
    cout << "Comecando a Matriz" << endl;
    MatrizEsparsas matriz(5, 5);
    matriz.print();
    matriz.insert(1,2, 4);
    cout << matriz.get(1,2) << endl;
    cout << matriz.get(2,2) << endl;
    cout << matriz.get(1,1) << endl;
    matriz.print();
    return 0;
}