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
    MatrizEsparsas(); // Construtor vazio
    MatrizEsparsas(const MatrizEsparsas& matriz); // Construtor de cópia
    void criarSentinelas(int linhas, int colunas); // Função que promete criar os nós sentinelas
    void clear(); // Função que apaga todos os nós de uma Matriz Esparsa
    void clearAll(); // Função que apaga todos os nós, incluindo os sentinelas de uma Matriz Esparsa
    void print();// Função que printa a Matriz Esparsa
    double get(int linha, int coluna); // Função que retorna o valor de um nó (linha, coluna), da Matrz Esparsa
    void printSentinelas(); // Função que printa os nós sentinelas
    void insert(int linha, int coluna, double valor); // Função que insere um valor no nó (linha, coluna)
    int getLinhas();// Função que retorna a quantidade de linhas
    int getColunas();// Função que retorna a quantidade de colunas
    MatrizEsparsas& operator=(const MatrizEsparsas& matriz);// Função do operador de atribuição, atribui um valor de uma matriz a outra
    ~MatrizEsparsas(); // Destrutor da Matriz Esparsa
};

#endif // MATRIZES_ESPARSAS_H