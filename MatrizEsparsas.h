#ifndef MATRIZESPARSAS_H
#define MATRIZESPARSAS_H
#include "Node.h"

class MatrizEsparsas
{
private:
    Node *head;
    int linhas;
    int colunas;

public:
    MatrizEsparsas(int linhas, int colunas);

    void print();
};

#endif // MATRIZES_ESPARSAS_H