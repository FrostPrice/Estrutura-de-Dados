#include <iostream>
#include <stdlib.h>
using namespace std;

struct No
{
    int chave;
    int info;
    No *esq, *dir;
};

struct Arvore
{
    No *raiz = nullptr;
};

#pragma region CAMINHAMENTOS
void prefixado(No *raiz)
{
    // Pre => Raiz, Esq, Dir
    if (raiz == nullptr) // Se esse no não existir sai da função
        return;

    cout << raiz->info << " ";
    prefixado(raiz->esq); // Na raiz atual, vai para a esquerda
    prefixado(raiz->dir); // Na raiz atual, vai para a direita
}

void infixado(No *raiz)
{
    // In => Esq, Raiz, Dir
    if (raiz == nullptr) // Se esse no não existir sai da função
        return;

    infixado(raiz->esq); // Na raiz atual, vai para a esquerda
    cout << raiz->info << " ";
    infixado(raiz->dir); // Na raiz atual, vai para a direita
}

void posfixado(No *raiz)
{
    // Pos => Esq, Dir, Raiz
    if (raiz == nullptr) // Se esse no não existir sai da função
        return;

    posfixado(raiz->esq); // Na raiz atual, vai para a esquerda
    posfixado(raiz->dir); // Na raiz atual, vai para a direita
    cout << raiz->info << " ";
}
#pragma endregion CAMINHAMENTOS

No *buscar(No *raiz, int chave)
{
    if (raiz == nullptr)
        return nullptr;

    if (raiz->chave == chave)
        return raiz;

    if (chave < raiz->chave)
        buscar(raiz->esq, chave);
    else
        buscar(raiz->dir, chave);
}

No *busca_valor(No *raiz, int info)
{
    if (raiz == nullptr)
        return nullptr;

    if (raiz->info == info)
        return raiz;

    busca_valor(raiz->esq, info);
    busca_valor(raiz->dir, info);
}

void buscar_maior(No *raiz, int &chave, int &info)
{
    if (raiz == nullptr)
        return;

    if (raiz->dir != nullptr)
    {
        buscar_maior(raiz->dir, chave, info);
    }
    else
    {
        chave = raiz->chave;
        info = raiz->info;
    }
}

void buscar_menor(No *raiz, int &chave, int &info)
{
    if (raiz == nullptr)
        return;

    if (raiz->esq != nullptr)
    {
        buscar_menor(raiz->esq, chave, info);
    }
    else
    {
        chave = raiz->chave;
        info = raiz->info;
    }
}

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

No *retirar(No *&raiz, int chave)
{
    if (raiz == nullptr)
        return nullptr;

    if (raiz->chave == chave)
    {
        if (raiz->esq == nullptr && raiz->dir == nullptr)
            return nullptr;

        if (raiz->esq != nullptr && raiz->dir == nullptr)
            return raiz->esq;

        if (raiz->esq == nullptr && raiz->dir != nullptr)
            return raiz->dir;

        int aux_chave, aux_info;
        buscar_maior(raiz->esq, aux_chave, aux_info);
        raiz->chave = aux_chave;
        raiz->info = aux_info;
        raiz->esq = retirar(raiz->esq, aux_chave);
        return raiz;
    }

    if (chave < raiz->chave)
        raiz->esq = retirar(raiz->esq, chave);
    else
        raiz->dir = retirar(raiz->dir, chave);

    return raiz;
}

int calc_altura(No *&raiz)
{
    // Recursivo: Contar a qtq de nos separando a esquerda e direita
    if (raiz == nullptr)
        return 0;

    int esq = calc_altura(raiz->esq);
    int dir = calc_altura(raiz->dir);

    int maior_altura;
    esq > dir ? maior_altura = esq : maior_altura = dir; // Define o lado maior

    return 1 + maior_altura;
}

int calc_qtd_nos(No *&raiz)
{
    if (raiz == nullptr)
        return 0;

    return 1 + calc_qtd_nos(raiz->esq) + calc_qtd_nos(raiz->dir);
}

int calc_altura(Arvore &arvore) // Pseudo-funcao para passar uma Arvore ao inves de um No
{
    return calc_altura(arvore.raiz);
}

int calc_qtd_nos(Arvore &arvore) // Pseudo-funcao para passar uma Arvore ao inves de um No
{
    return calc_qtd_nos(arvore.raiz);
}

void retirar(Arvore &arvore, int chave) // Pseudo-funcao para passar uma Arvore ao inves de um No
{
    retirar(arvore.raiz, chave);
}

void inserir(Arvore &arvore, int chave, int info) // Pseudo-funcao para passar uma Arvore ao inves de um No
{
    inserir(arvore.raiz, chave, info);
}

int main()
{
    Arvore arvore;

    inserir(arvore, 50, 50);
    inserir(arvore, 45, 45);
    inserir(arvore, 60, 60);
    inserir(arvore, 47, 47);
    prefixado(arvore.raiz);
    cout << endl;

    retirar(arvore, 50);

    prefixado(arvore.raiz);
    cout << endl;

    // cout << buscar(arvore.raiz, 45);
    // cout << endl;

    // int chave, aux;
    // buscar_menor(arvore.raiz, chave, aux);
    // cout << "Menor valor e chave: " << aux << " (" << chave << ") " << endl;

    // buscar_maior(arvore.raiz, chave, aux);
    // cout << "Maior valor e chave: " << aux << " (" << chave << ") " << endl;

    // cout << buscar(arvore.raiz, 47);
    // cout << endl;

    // retirar(arvore, 47);

    // prefixado(arvore.raiz);
    // cout << endl;

    // cout << "Altura da arvore: " << calc_altura(arvore) << endl;
    // cout << "Qtd. de Nos na arvore: " << calc_qtd_nos(arvore) << endl;

    return 0;
}