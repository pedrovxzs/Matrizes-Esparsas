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
    //void insert(int linha, int coluna, double valor);
    double get(int linha, int coluna);
    void print();
    void printSentinelas();
};

#endif // MATRIZES_ESPARSAS_H