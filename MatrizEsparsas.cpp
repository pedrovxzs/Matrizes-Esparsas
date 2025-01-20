#include "MatrizEsparsas.h"
#include <iostream>

MatrizEsparsas::MatrizEsparsas(int linhas, int colunas)
{
    if (linhas > 0 && colunas > 0 && linhas <= 30000 && colunas <= 30000)
    {
        this->colunas = colunas;
        this->linhas = linhas;

        // Primeiro nó
        head = new Node(nullptr, nullptr, 0, 0, 0);
        head->abaixo = head;
        head->direita = head;
        Node *auxLinha = head;
        for (int i = 1; i <= linhas; i++)
        {
            Node *novo = new Node(nullptr, auxLinha, i, 0, 0);
            novo->direita = novo;
            auxLinha->abaixo = novo;
            auxLinha = novo;
        }
        auxLinha->abaixo = head;

        Node *auxColuna = head;
        for (int j = 1; j <= colunas; j++)
        {
            Node *novo = new Node(auxColuna, nullptr, 0, j, 0);
            novo->abaixo = novo;
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

double MatrizEsparsas::get(int linha, int coluna)
{
    if (coluna <= colunas && linha <= linhas && linha > 0 && coluna > 0)
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
        return 0;
        delete linhaAtual;
        delete colunaAtual;
    }
    else
        throw std::out_of_range("Fora do Intervalo");
}

void MatrizEsparsas::printSentinelas()
{
    Node *linhaSentinela = head->abaixo;
    Node *colunaSentinela = head->direita;
    while (linhaSentinela->linha > 0)
    {
        std::cout << "Linha Sentinela Atual: " << linhaSentinela->linha << std::endl;
        linhaSentinela = linhaSentinela->abaixo;
    }
    while (colunaSentinela->coluna > 0)
    {
        std::cout << "Coluna Sentinela Atual: " << colunaSentinela->coluna << std::endl;
        colunaSentinela = colunaSentinela->abaixo;
        colunaSentinela = colunaSentinela->direita;
    }
}
// Fazendo ...
void MatrizEsparsas::insert(int linha, int coluna, double valor)
{
    if (coluna <= colunas && linha <= linhas && linha > 0 && coluna > 0)
    {

        // Cria-se sentinelas auxiliares e nó auxiliar a ser inserido
        Node *linhaAtual = head->abaixo;
        Node *colunaAtual = head->direita;
        Node *aux = new Node(nullptr, nullptr, linha, coluna, valor);
        // Navega até a linha do nó a ser inserido
        while (linhaAtual->linha > 0 && linhaAtual->linha != linha)
            linhaAtual = linhaAtual->abaixo;

        // Navega até o nó anterior do nó há ser inserido;
        while (linhaAtual->direita->coluna > 0 && linhaAtual->direita->coluna < coluna)
            linhaAtual = linhaAtual->direita;

        // Navega até a coluna do nó a ser inserido
        while (colunaAtual->coluna > 0 && colunaAtual->coluna != coluna)
            colunaAtual = colunaAtual->direita;

        // Nageva até o nó anterior do nó há ser inserido
        while (colunaAtual->abaixo->linha > 0 && colunaAtual->abaixo->linha < linha)
            colunaAtual = colunaAtual->abaixo;

        aux->direita = linhaAtual->direita;
        aux->abaixo = colunaAtual->abaixo;
        linhaAtual->direita = aux;
        colunaAtual->abaixo = aux;

        delete aux;
        delete linhaAtual;
        delete colunaAtual;
    }
    else
        throw std::out_of_range("Fora do Intervalo");
}