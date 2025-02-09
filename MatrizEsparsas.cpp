#include "MatrizEsparsas.h"
#include <iostream>
#include <stdexcept>
#include <iomanip>

// Author: Pedro Vittor M. S, 570598
// Promete criar uma Matriz Esparsa vazia
MatrizEsparsas::MatrizEsparsas()
{
    // Primeiro nó
    head = new Node(nullptr, nullptr, 0, 0, 0);
    head->abaixo = head;
    head->direita = head;
    linhas = 0;
    colunas = 0;
}

// Author: Pedro Vittor M. S, 570598
// Recebe uma matriz constante por referência, e promete criar uma cópia dela
MatrizEsparsas::MatrizEsparsas(const MatrizEsparsas &matriz)
    : MatrizEsparsas()
{
    this->criarSentinelas(matriz.linhas, matriz.colunas);
    Node *linhaAtual = matriz.head->abaixo;
    Node *colunaAtual = linhaAtual->direita;
    while (linhaAtual->linha > 0)
    {
        while (colunaAtual->coluna > 0)
        {
            if (colunaAtual->valor)
            {
                this->insert(linhaAtual->linha, colunaAtual->coluna, colunaAtual->valor);
            }
            colunaAtual = colunaAtual->direita;
        }
        linhaAtual = linhaAtual->abaixo;
        colunaAtual = linhaAtual->direita;
    }
}

// Author: Pedro Vittor M. S, 570598
// Promete criar linhas+colunas nó sentinelas

void MatrizEsparsas::criarSentinelas(int linhas, int colunas)
{
    if (linhas > 0 && colunas > 0 && linhas <= 30000 && colunas <= 30000)
    {
        this->colunas = colunas;
        this->linhas = linhas;

        Node *auxLinha = head;

        for (int i = 1; i <= linhas; i++) // O(a)
        {
            Node *novo = new Node(nullptr, auxLinha, i, 0, 0);
            novo->direita = novo;
            auxLinha->abaixo = novo;
            auxLinha = novo;
        }
        auxLinha->abaixo = head;

        Node *auxColuna = head;
        for (int j = 1; j <= colunas; j++) // O(b)
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
        throw std::out_of_range("Invalid number of columns or rows");
    }
}

// Author: Pedro Vittor M. S, 570598
// Promete apagar todos os nós da matriz
void MatrizEsparsas::clear()
{
    Node *linhaAtual = head->abaixo;
    Node *colunaAtual = linhaAtual->direita;
    while (linhaAtual->linha > 0)
    {
        while (colunaAtual->coluna > 0)
        {
            Node *temp = colunaAtual;
            colunaAtual = colunaAtual->direita;
            delete temp;
        }

        linhaAtual->direita = linhaAtual;
        linhaAtual = linhaAtual->abaixo;
    }
}

// Author: Pedro Vittor M. S, 570598
// Promete apagar todos os nós incluindo os sentinelas da matriz
void MatrizEsparsas::clearAll()
{
    Node *linhaAtual = head->abaixo;
    Node *colunaAtual = linhaAtual->direita;
    while (linhaAtual->linha > 0)
    {
        while (colunaAtual->coluna > 0)
        {
            Node *temp = colunaAtual;
            colunaAtual = colunaAtual->direita;
            delete temp;
        }
        Node *temp = linhaAtual;
        linhaAtual = linhaAtual->abaixo;
        delete temp;
    }

    head->abaixo = head;
    head->direita = head;
}

// Author: Pedro Vittor M. S, 570598
// Promete printar a matriz
void MatrizEsparsas::print()
{
    Node *linhaAtual = head->abaixo;
    for (int i = 1; i <= linhas; i++)
    {
        Node *colunaAtual = linhaAtual->direita;
        for (int j = 1; j <= colunas; j++)
        {
            if (colunaAtual->coluna == j)
            {
                std::cout << std::setw(8) << colunaAtual->valor;
                colunaAtual = colunaAtual->direita;
            }
            else
            {
                std::cout << std::setw(8) << "0";
            }
        }
        std::cout << std::endl;
        linhaAtual = linhaAtual->abaixo;
    }
}
// Author: Willgner S. Ferreira, 567152
// Recebe a linha e a coluna, e promete retornar o valor do nó nessas coordenadas
// No pior caso, o algoritmo percorre todas as linha e todas as coluna da matriz até encontrar o nó desejado dentro de um loop aninhado,
// logo a complexidade é O(n^2)
double MatrizEsparsas::get(int linha, int coluna)
{
    // Confere se os valores de linha e coluna são válidos
    if (coluna <= colunas && linha <= linhas && linha > 0 && coluna > 0)
    {
        Node *linhaAtual = head->abaixo;
        Node *colunaAtual = linhaAtual->direita;
        // Navega pela a matriz indo sempre para a linha abaixo até chegar no ponto inicial // O(n)
        while (linhaAtual->linha > 0)
        {
            // Navega pela a matriz indo sempre para a coluna a direita até chegar no ponto inicial // O(n)
            while (colunaAtual->coluna > 0)
            {
                // Confere se já chegou ao nó desejado
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
    }
    else
        throw std::out_of_range("Invalid coordinates");
}
// Author: Willgner S. Ferreira, 567152
// Promete printar todos os nós sentinelas de uma matriz;
void MatrizEsparsas::printSentinelas()
{
    Node *linhaSentinela = head->abaixo;
    Node *colunaSentinela = head->direita;
    // Navega por todos os sentinelas de linha
    while (linhaSentinela->linha > 0)
    {
        std::cout << "Linha Sentinela Atual: " << linhaSentinela->linha << std::endl;
        linhaSentinela = linhaSentinela->abaixo;
    }
    // Navega por todos os sentinelas de coluna
    while (colunaSentinela->coluna > 0)
    {
        std::cout << "Coluna Sentinela Atual: " << colunaSentinela->coluna << std::endl;
        colunaSentinela = colunaSentinela->direita;
    }
}

// Author: Willgner S. Ferreira, 567152
// Recebe um int linha, int coluna e double valor,
// Promete inserir um valor, no nó das coordenadas(linha, coluna)
// No pior caso, o algoritmo percorre
// todas as linha e todas as coluna da matriz até encontrar
// o nó a ser inserido, logo a complexidade é O(a+b)
// Analise de Complexidade: O(a+b)

void MatrizEsparsas::insert(int linha, int coluna, double valor)
{
    // Confere se o valor de linha e coluna são válidos
    if (coluna <= colunas && linha <= linhas && linha > 0 && coluna > 0)
    {

        // Cria-se um ponteiro auxiliar para navegar pelas linhas da matriz
        Node *linhaAtual = head->abaixo;

        // Navega até a linha do nó a ser inserido // O(a)
        while (linhaAtual->linha > 0 && linhaAtual->linha != linha) 
            linhaAtual = linhaAtual->abaixo;

        // Navega até o nó a esquerda do nó há ser inserido; // O(a)
        while (linhaAtual->direita->coluna > 0 && linhaAtual->direita->coluna < coluna)
            linhaAtual = linhaAtual->direita;

        // Confere se o nó a direita existe, Se sim subistitui o valor dele
        if (linhaAtual->direita->valor != 0 && linhaAtual->direita->coluna == coluna)
        {
            linhaAtual->direita->valor = valor;
        }
        else
        {
            // Cria-se o sentinela auxiliar para navegar pelas colunas e o nó a ser inserido
            Node *colunaAtual = head->direita;
            Node *aux = new Node(nullptr, nullptr, linha, coluna, valor);

            // Navega até a coluna do nó a ser inserido // O(b)
            while (colunaAtual->coluna > 0 && colunaAtual->coluna != coluna)
                colunaAtual = colunaAtual->direita;

            // Nageva até o nó acima do nó há ser inserido // O(b)
            while (colunaAtual->abaixo->linha > 0 && colunaAtual->abaixo->linha < linha)
                colunaAtual = colunaAtual->abaixo;
            // Modifica os valores dos ponteiros
            aux->direita = linhaAtual->direita;
            aux->abaixo = colunaAtual->abaixo;
            linhaAtual->direita = aux;
            colunaAtual->abaixo = aux;
        }
    }
    else
        throw std::out_of_range("Invalid coordinates");
}

// Author: Pedro Vittor M. S, 570598
// Retorna a quantidade de linhas
int MatrizEsparsas::getLinhas()
{
    return linhas;
}

// Author: Pedro Vittor M. S, 570598
// Retorna a quantidade de colunas
int MatrizEsparsas::getColunas()
{
    return colunas;
}

// Author: Pedro Vittor M. S, 570598
// Operador de atribuição, cópia todos os valores da matriz constante passada por referência
MatrizEsparsas &MatrizEsparsas::operator=(const MatrizEsparsas &matriz)
{
    if (this == &matriz)
    {
        return *this;
    }
    this->clearAll();
    this->criarSentinelas(matriz.linhas, matriz.colunas);
    Node *linhaAtual = matriz.head->abaixo;
    Node *colunaAtual = linhaAtual->direita;
    while (linhaAtual->linha > 0)
    {
        while (colunaAtual->coluna > 0)
        {
            if (colunaAtual->valor)
            {
                this->insert(linhaAtual->linha, colunaAtual->coluna, colunaAtual->valor);
            }
            colunaAtual = colunaAtual->direita;
        }
        linhaAtual = linhaAtual->abaixo;
        colunaAtual = linhaAtual->direita;
    }
    return *this;
}

// Author: Pedro Vittor M. S, 570598
// Destrutor da matriz
MatrizEsparsas::~MatrizEsparsas()
{
    // Apagar os nós e sentinelas da matriz
    clear();

    Node *linhaAtual = head->abaixo;
    while (linhaAtual != head)
    {
        Node *temp = linhaAtual;
        linhaAtual = linhaAtual->abaixo;
        delete temp;
    }

    // Apagar os sentinelas colunas
    Node *colunaAtual = head->direita;
    while (colunaAtual != head)
    {
        Node *temp = colunaAtual;
        colunaAtual = colunaAtual->direita;
        delete temp;
    }
    // Apagar o nó head
    delete head;

    // std::cout << "Matriz Apagada" << std::endl;
}