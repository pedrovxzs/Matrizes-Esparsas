#include "MatrizEsparsas.h"
#include <iostream>

MatrizEsparsas::MatrizEsparsas(int linhas, int colunas)
{
    if (linhas > 0 && colunas > 0 && linhas <= 30000 && colunas <= 30000)
    {
        this->colunas = colunas;
        this->linhas = linhas;

        // Primeiro nó
        head = new Node(head, head, 0, 0, 0);

        Node *auxLinha = head;
        for (int i = 1; i <= linhas; i++)
        {
            Node *novo = new Node(head, auxLinha, i, 0, 0);
            auxLinha->abaixo = novo;
            auxLinha = novo;
        }
        auxLinha->abaixo = head;

        Node *auxColuna = head;
        for (int j = 1; j <= colunas; j++)
        {
            Node *novo = new Node(auxColuna, head, 0, j, 0);
            auxColuna->direita = novo;
            auxColuna = novo;
        }
        auxColuna->direita = head;
    }
    else
    {
        throw std::out_of_range("Fora do Intervalo");
    }
}

void MatrizEsparsas::print()
{
    Node *linhaAtual = head->abaixo;
    for (int i = 1; i <= linhas; i++)
    {
        Node *colunaAtual = linhaAtual->direita;
        for (int j = 1; j <= colunas; j++)
        {
            if (colunaAtual->valor != 0)
            {
                std::cout << colunaAtual->valor << " ";
            }
            else
            {
                std::cout << "0 ";
            }
            colunaAtual = colunaAtual->direita;
        }
        std::cout << std::endl;
        linhaAtual = linhaAtual->abaixo;
    }
}

double MatrizEsparsas::get(int coluna, int linha)
{
    if (coluna <= this->colunas && linha <= this->linhas)
    {
        Node *linhaAtual = head->abaixo;
        Node *colunaAtual = linhaAtual->direita;
        while (linhaAtual->linha > 0)
        {
            while (colunaAtual->coluna > 0)
            {
                if (colunaAtual->coluna == coluna && colunaAtual->linha == linha)
                {
                    return colunaAtual->valor;
                }
                colunaAtual = colunaAtual->direita;
            }
            linhaAtual = linhaAtual->abaixo;
            colunaAtual = linhaAtual->direita;
        }
        delete linhaAtual;
        delete colunaAtual;
        return 0;
    }
    else throw std::out_of_range("Fora do Intervalo");
}