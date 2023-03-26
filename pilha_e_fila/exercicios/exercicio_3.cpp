using namespace std;
#include <iostream>

#define TAM 10

struct Fila
{
    char info[TAM];
    int inicio, fim, contador;
};

#pragma region OPERACOES
/*
Operações:
1) Inicializar
2) Inserir
3) Retirar
*/
void inicializar(Fila &fila)
{
    fila.inicio = 0;   // Ondem os valores saem
    fila.fim = -1;     // Onde os valores entram
    fila.contador = 0; // Para determinar a quantidade de campos com valores
}

bool inserir(Fila &fila, char valor)
{
    if (fila.fim >= TAM - 1)
        return false;

    fila.fim++;
    fila.info[fila.fim] = valor;
    // fila.info[++fila.fim] = valor;
    return true;
}

bool retirar(Fila &fila, char &valor)
{
    if (fila.inicio > fila.fim)
        return false;

    valor = fila.info[fila.inicio];
    fila.inicio++;
    return true;
}

#pragma endregion OPERACOES

struct Pilha
{
    char info[TAM];
    char topo;
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

bool vazia(Fila fila)
{
    return (fila.inicio > fila.fim) ? true : false;
}

int main()
{
    // 3. Considere a existência de uma fila contendo um valor numérico de até 12 dígitos (um dígito em cada posição da fila). Escreva um algoritmo que apresenta este valor formatado. Observe que os dois últimos dígitos sempre compõem a parte decimal do valor e quando existirem apenas dois dígitos na fila, deve ser acrescentado um digito 0 (zero) com parte inteira na apresentação. Por exemplo, o valor {12427383642} deve ser escrito como 124.273.836,42 ou o valor {56} deve ser apresentado como 0,56.
    Fila fila_1;
    Pilha pilha_1, pilha_2;
    char num[] = "12427383642", aux;
    int contador = 0;

    inicializar(fila_1);
    inicializar(pilha_1);
    inicializar(pilha_2);

    for (int i = 0; i < strlen(num); i++)
    {
        inserir(fila_1, num[i]);
    }

    while (retirar(fila_1, aux))
    {
        inserir(pilha_1, aux);
    }
    inicializar(fila_1);

    if (retirar(pilha_1, aux))
        inserir(fila_1, aux);
    if (retirar(pilha_1, aux))
        inserir(fila_1, aux);
    else
    {
        inserir(fila_1, '0');
        inserir(fila_1, ',');
        inserir(fila_1, '0');
    }

    if (!vazia(fila_1))
    {
        inserir(fila_1, ',');
        while (retirar(pilha_1, aux))
        {
            if (contador == 3)
            {
                inserir(fila_1, '.');
                contador = 0;
            }
            inserir(fila_1, aux);
            contador++;
        }
    }
    else
    {
        inserir(fila_1, ',');
        inserir(fila_1, '0');
    }

    while (retirar(pilha_1, aux))
    {
        inserir(pilha_2, aux);
    };

    while (retirar(pilha_2, aux))
    {
        cout << aux << " ";
    };

    cout << endl;

    return 0;
}