#include <iostream>
#include <stdlib.h>
using namespace std;

template <typename T>
struct No
{
    T info;
    No *esq, *dir;
};

template <typename T>
void prefixado(No<T> *raiz)
{
    // Pre => Raiz, Esq, Dir
    if (raiz == NULL) // Se esse no não existir sai da função
        return;

    cout << raiz->info << " ";
    prefixado(raiz->esq); // Na raiz atual, vai para a esquerda
    prefixado(raiz->dir); // Na raiz atual, vai para a direita
}

template <typename T>
void infixado(No<T> *raiz)
{
    // In => Esq, Raiz, Dir
    if (raiz == NULL) // Se esse no não existir sai da função
        return;

    infixado(raiz->esq); // Na raiz atual, vai para a esquerda
    cout << raiz->info << " ";
    infixado(raiz->dir); // Na raiz atual, vai para a direita
}

template <typename T>
void posfixado(No<T> *raiz)
{
    // Pos => Esq, Dir, Raiz
    if (raiz == NULL) // Se esse no não existir sai da função
        return;

    posfixado(raiz->esq); // Na raiz atual, vai para a esquerda
    posfixado(raiz->dir); // Na raiz atual, vai para a direita
    cout << raiz->info << " ";
}

int main()
{
    No<char> *raiz, *n1, *n2, *n3, *n4, *n5, *n6;

    n1 = new No<char>;
    n1->info = 'B';
    n1->esq = NULL;
    n1->dir = NULL;

    n2 = new No<char>;
    n2->info = 'D';
    n2->esq = NULL;
    n2->dir = NULL;

    n3 = new No<char>;
    n3->info = 'E';
    n3->esq = NULL;
    n3->dir = NULL;

    n4 = new No<char>;
    n4->info = 'G';
    n4->esq = NULL;
    n4->dir = NULL;

    n5 = new No<char>;
    n5->info = 'F';
    n5->esq = n1;
    n5->dir = n2;

    n6 = new No<char>;
    n6->info = 'C';
    n6->esq = n3;
    n6->dir = n4;

    raiz = new No<char>;
    raiz->info = 'A';
    raiz->esq = n5;
    raiz->dir = n6;

    cout << "Pre-fixado: ";
    prefixado(raiz);
    cout << endl;

    cout << "Infixado: ";
    infixado(raiz);
    cout << endl;

    cout << "Pos-fixado: ";
    posfixado(raiz);
    cout << endl;

    return 0;
}
