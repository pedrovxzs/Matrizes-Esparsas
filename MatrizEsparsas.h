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
    ~MatrizEsparsas();
    void clear();
    void print();
    double get(int linha, int coluna);
    void printSentinelas();
    void insert(int linha, int coluna, double valor);
};

#endif // MATRIZES_ESPARSAS_H