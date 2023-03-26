using namespace std;
#include <iostream>

#define TAM 50

struct Pilha
{
    int info[TAM];
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

bool retirar(Pilha &pilha, int &valor)
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
    // 2. Para um dado número inteiro n > 1, o menor inteiro d > 1 que divide n é chamado de fator primo.É possível determinar a fatoração prima de n achando - se o fator primo d e substituindo n pelo quociente n / d, repetindo essa operação até que n seja igual a 1. Utilizando uma das estruturas vistas em sala(Pilha ou Fila) para auxiliá - lo na manipulação de dados, implemente um programa que compute a fatoração prima de um número imprimindo os seus fatores em ordem decrescente.Por exemplo, para n = 3960, deverá ser impresso 11 * 5 * 3 * 3 * 2 * 2 * 2.

    Pilha pilha_1;
    int num, aux, divisor = 2;

    do
    {
        cout << "Digite um número: ";
        cin >> num;
    } while (num <= 1);

    inicializar(pilha_1);

    aux = num;
    while (aux > 1)
    {
        if (aux % divisor == 0)
        {
            inserir(pilha_1, divisor);
            aux = aux / divisor;
        }
        else
            divisor++;
    }

    cout << num << " = ";
    while (retirar(pilha_1, aux))
    {
        cout << aux << " ";
    };

    cout << endl;

    return 0;
}