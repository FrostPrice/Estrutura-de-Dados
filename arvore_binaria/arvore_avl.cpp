#include <iostream>
#include <stdlib.h>
using namespace std;

struct No
{
    int chave;
    int altura;
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

    cout << raiz->chave << " ";
    prefixado(raiz->esq); // Na raiz atual, vai para a esquerda
    prefixado(raiz->dir); // Na raiz atual, vai para a direita
}

void infixado(No *raiz)
{
    // In => Esq, Raiz, Dir
    if (raiz == nullptr) // Se esse no não existir sai da função
        return;

    infixado(raiz->esq); // Na raiz atual, vai para a esquerda
    cout << raiz->chave << " ";
    infixado(raiz->dir); // Na raiz atual, vai para a direita
}

void posfixado(No *raiz)
{
    // Pos => Esq, Dir, Raiz
    if (raiz == nullptr) // Se esse no não existir sai da função
        return;

    posfixado(raiz->esq); // Na raiz atual, vai para a esquerda
    posfixado(raiz->dir); // Na raiz atual, vai para a direita
    cout << raiz->chave << " ";
}
#pragma endregion CAMINHAMENTOS

void buscar_maior(No *raiz, int &chave)
{
    if (raiz == nullptr)
        return;

    if (raiz->dir != nullptr)
    {
        buscar_maior(raiz->dir, chave);
    }
    else
    {
        chave = raiz->chave;
    }
}

int buscar_altura(No *raiz)
{
    if (raiz == nullptr)
        return 0;

    return raiz->altura;
}

void inserir(No *&raiz, int chave)
{
    if (raiz == nullptr)
    {
        No *no = new No;

        no->chave = chave;
        no->altura = 1;
        no->esq = nullptr;
        no->dir = nullptr;

        raiz = no;

        return;
    }

    if (chave < raiz->chave)
        inserir(raiz->esq, chave);
    else
        inserir(raiz->dir, chave);

    // Controle de altura
    int altura_esq = buscar_altura(raiz->esq);
    int altura_dir = buscar_altura(raiz->dir);

    raiz->altura = altura_esq > altura_dir ? altura_esq + 1 : altura_dir + 1;
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
        buscar_maior(raiz->esq, aux_chave);
        raiz->chave = aux_chave;
        raiz->esq = retirar(raiz->esq, aux_chave);
        return raiz;
    }

    if (chave < raiz->chave)
        raiz->esq = retirar(raiz->esq, chave);
    else
        raiz->dir = retirar(raiz->dir, chave);

    // Controle de altura
    int altura_esq = buscar_altura(raiz->esq);
    int altura_dir = buscar_altura(raiz->dir);

    raiz->altura = altura_esq > altura_dir ? altura_esq - 1 : altura_dir - 1;

    return raiz;
}

int calc_altura(No *&raiz)
{
    int alt_esq = buscar_altura(raiz->esq);
    int alt_dir = buscar_altura(raiz->dir);

    return (alt_esq > alt_dir) ? 1 + alt_esq : 1 + alt_dir;
}

void retirar(Arvore &arvore, int chave) // Pseudo-funcao para passar uma Arvore ao inves de um No
{
    retirar(arvore.raiz, chave);
}

void inserir(Arvore &arvore, int chave) // Pseudo-funcao para passar uma Arvore ao inves de um No
{
    inserir(arvore.raiz, chave);
}

No *rotacao_simples_direita(No *k)
{
    No *x = k->esq;
    No *t2 = x->dir;

    x->dir = k;
    k->esq = t2;
    k->altura = calc_altura(k);
    x->altura = calc_altura(x);

    return x;
}

No *rotacao_dupla_direita(No *k)
{
    No *x = k->esq;
    No *w = x->dir;
    No *t2 = w->esq;
    No *t3 = w->dir;

    w->esq = x;
    w->dir = k;
    x->dir = t2;
    k->esq = t3;

    x->altura = calc_altura(x);
    k->altura = calc_altura(k);
    w->altura = calc_altura(w);

    return w;
}

No *rotacao_simples_esquerda(No *k)
{
    No *y = k->esq;
    No *t2 = y->dir;

    y->dir = k;
    k->dir = t2;
    k->altura = calc_altura(k);
    y->altura = calc_altura(y);

    return y;
}

No *rotacao_dupla_esquerda(No *k)
{
    No *y = k->dir;
    No *z = y->esq;

    No *t2 = z->esq;
    No *t3 = z->dir;

    z->esq = k;
    z->dir = y;
    k->dir = t2;
    y->esq = t3;

    y->altura = calc_altura(y);
    k->altura = calc_altura(k);
    z->altura = calc_altura(z);

    return z;
}

int main()
{
    Arvore arvore;

    inserir(arvore, 50);
    inserir(arvore, 45);
    inserir(arvore, 60);
    inserir(arvore, 47);

    // prefixado(arvore.raiz);
    // cout << endl;

    // cout << endl;

    // int chave, aux;

    // buscar_maior(arvore.raiz, chave, aux);
    // cout << "Maior valor e chave: " << aux << " (" << chave << ") " << endl;

    // retirar(arvore, 47);

    // prefixado(arvore.raiz);
    // cout << endl;

    // cout << "Altura da arvore: " << calc_altura(arvore) << endl;

    return 0;
}