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
    cout << matriz.get(1,2) << endl;
    cout << matriz.get(1,1) << endl << endl;
    matriz.print();
    cout << endl << endl;
    matriz.clear();
    matriz.print();
    cout << endl;

}