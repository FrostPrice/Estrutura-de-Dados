#include <iostream>
#include <stdlib.h>
using namespace std;

// template <typename T>
struct No
{
    int chave;
    // T info;
    int info;
    No *esq, *dir;
};

// template <typename T>
struct Arvore
{
    // No<T> *raiz;
    No *raiz;
};

// START: Caminhamentos
// template <typename T>
// void prefixado(No<T> *raiz)
// {
//     // Pre => Raiz, Esq, Dir
//     if (raiz == nullptr) // Se esse no não existir sai da função
//         return;

//     cout << raiz->info << " ";
//     prefixado(raiz->esq); // Na raiz atual, vai para a esquerda
//     prefixado(raiz->dir); // Na raiz atual, vai para a direita
// }

// template <typename T>
// void infixado(No<T> *raiz)
// {
//     // In => Esq, Raiz, Dir
//     if (raiz == nullptr) // Se esse no não existir sai da função
//         return;

//     infixado(raiz->esq); // Na raiz atual, vai para a esquerda
//     cout << raiz->info << " ";
//     infixado(raiz->dir); // Na raiz atual, vai para a direita
// }

// template <typename T>
// void posfixado(No<T> *raiz)
// {
//     // Pos => Esq, Dir, Raiz
//     if (raiz == nullptr) // Se esse no não existir sai da função
//         return;

//     posfixado(raiz->esq); // Na raiz atual, vai para a esquerda
//     posfixado(raiz->dir); // Na raiz atual, vai para a direita
//     cout << raiz->info << " ";
// }
// END: Caminhamentos

// template <typename T>
void inicializar(Arvore &arvore)
{
    arvore.raiz = nullptr;
}

// template <typename T>
void inserir(No *&raiz, int chave, int info)
{
    if (raiz == nullptr)
    {
        No *no = new No;

        no->chave = chave;
        no->info = info;
        no->esq = nullptr;
        no->dir = nullptr;

        raiz = no;

        return;
    }

    if (chave < raiz->chave)
        inserir(raiz->esq, chave, info);
    else

        inserir(raiz->dir, chave, info);
}

void inserir(Arvore &arvore, int chave, int info) // Pseudo-funcao para passar uma Arvore ao inves de um No
{
    inserir(arvore.raiz, chave, info);
}

int main()
{
    Arvore arvore;

    inicializar(arvore);

    // inserir(arvore.raiz, 50, 50);
    // inserir(arvore.raiz, 45, 45);
    // inserir(arvore.raiz, 60, 60);
    // inserir(arvore.raiz, 47, 47);

    inserir(arvore, 50, 50);
    inserir(arvore, 45, 45);
    inserir(arvore, 60, 60);
    inserir(arvore, 47, 47);

    return 0;
}