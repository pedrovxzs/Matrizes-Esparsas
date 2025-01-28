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
    MatrizEsparsas(); // construtor vazio
    void criarSentinelas(int linhas, int colunas);
    void clear();
    void print();
    double get(int linha, int coluna);
    void printSentinelas();
    void insert(int linha, int coluna, double valor);
    int getLinhas();
    int getColunas();
    MatrizEsparsas operator=(const MatrizEsparsas& matriz);
    ~MatrizEsparsas();
};

#endif // MATRIZES_ESPARSAS_H