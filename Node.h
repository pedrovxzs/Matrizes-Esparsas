#ifndef NODE_H
#define NODE_H

struct Node
{
    Node *direita; // Proximo nó da linha
    Node *abaixo; // Proximo nó da coluna
    int linha;
    int coluna;
    double valor;

    // Construtor
    Node(Node* direita, Node* abaixo, int linha, int coluna, double valor) {
        this->direita = direita;
        this->abaixo = abaixo;
        this->linha = linha;
        this->coluna = coluna;
        this->valor = valor;
    }

};

#endif