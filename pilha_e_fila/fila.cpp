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
// Criar uma Fila circular

int main()
{
    Fila fila_1, fila_2;
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

    inicializar(fila_2);
    while (retirar(fila_1, aux))
    {
        inserir(fila_2, aux);
    }

    cout << "Fila 2: ";
    while (retirar(fila_2, aux))
    {
        cout << aux << " ";
    }

    cout << endl;

    return 0;
}