using namespace std;

#include "iostream"

#define TAM 50

struct Pilha
{
    char info[TAM];
    int topo;
};

#pragma region OPERACOES
/*
Operações:
1) Inicializar - OK
2) Inserir - OK
3) Retirar - OK
*/
void inicializar(Pilha &pilha)
{
    pilha.topo = -1;
}

bool inserir(Pilha &pilha, char valor)
{
    if (pilha.topo >= TAM - 1)
        return false;

    pilha.topo++;
    pilha.info[pilha.topo] = valor;
    // pilha.info[++pilha.topo] = valor;
    return true;
}

bool retirar(Pilha &pilha, char &valor)
{
    if (pilha.topo < 0)
        return false;

    valor = pilha.info[pilha.topo];
    pilha.topo--;
    // valor = pilha.info[pilha.topo--];
    return true;
}

#pragma endregion OPERACOES

int main()
{
    Pilha pilha_1, pilha_2;
    char aux;

    inicializar(pilha_1);

    inserir(pilha_1, 'A');
    inserir(pilha_1, 'B');

    retirar(pilha_1, aux);
    cout << "Valor(aux): " << aux << endl;
    retirar(pilha_1, aux);
    cout << "Valor(aux): " << aux << endl;

    inserir(pilha_1, 'P');
    inserir(pilha_1, 'E');
    inserir(pilha_1, 'R');
    inserir(pilha_1, 'N');
    inserir(pilha_1, 'A');
    inserir(pilha_1, 'M');
    inserir(pilha_1, 'B');
    inserir(pilha_1, 'U');
    inserir(pilha_1, 'C');
    inserir(pilha_1, 'O');

    inicializar(pilha_2);
    while (retirar(pilha_1, aux))
    {
        inserir(pilha_2, aux);
    }

    cout << "Pilha 2: ";
    while (retirar(pilha_2, aux))
    {
        cout << aux << " ";
    }

    cout << endl;

    return 0;
}