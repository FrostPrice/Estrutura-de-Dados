using namespace std;
#include <iostream>

#define TAM 10

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

bool vazia(Fila fila)
{
    return (fila.inicio > fila.fim) ? true : false;
}

void inverter(Fila &fila)
{
    Pilha pilha;
    char aux;

    inicializar(pilha);
    while (retirar(fila, aux))
    {
        inserir(pilha, aux);
    }
    inicializar(fila);
    while (retirar(pilha, aux))
    {
        inserir(fila, aux);
    }
}

int main()
{
    // 4. Escreva um algoritmo ou pequeno programa que inverte o conteúdo previamente armazenado em uma fila. Use uma pilha para a tarefa da inversão e pode pressupor que a fila já está preenchida.
    Fila fila_1;
    char aux;

    inicializar(fila_1);
    inserir(fila_1, 'P');
    inserir(fila_1, 'E');
    inserir(fila_1, 'R');
    inserir(fila_1, 'N');
    inserir(fila_1, 'A');
    inserir(fila_1, 'M');
    inserir(fila_1, 'B');
    inserir(fila_1, 'U');
    inserir(fila_1, 'C');
    inserir(fila_1, 'O');

    inverter(fila_1);

    cout << "Fila Invertida: ";
    while (retirar(fila_1, aux))
    {
        cout << aux << " ";
    }

    cout << endl;

    return 0;
}