using namespace std;
#include <iostream>
#include "string"

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

bool eh_palindromo(Pilha pilha, Fila fila)
{
    char aux_pilha, aux_fila;

    while (retirar(pilha, aux_pilha) && retirar(fila, aux_fila))
    {
        if (aux_pilha != aux_fila)
            return false;
    }

    return true;
}

int main()
{
    // 5. Escreva um algoritmo que recebe uma fila contendo um caractere em cada posição. Estes caracteres formam uma frase com as palavras separadas por um espaço em branco, que deve ser ignorado. Este algoritmo deve verificar se a frase armazenada na fila é um palíndromo (palíndromo: frase ou palavra que pode ser lida de trás prá frente e o sentido é o mesmo. Por exemplo: "ROMA ME TEM AMOR")
    string frase;
    Fila fila;
    Pilha pilha;

    cout << "Digite uma frase: ";
    std::getline(cin, frase);

    inicializar(fila);
    inicializar(pilha);

    for (int i = 0; i < frase.length(); i++)
    {
        if (frase[i] != ' ')
        {
            inserir(pilha, frase[i]);
            inserir(fila, frase[i]);
        }
    }

    cout << endl
         << frase << " => ";
    if (eh_palindromo(pilha, fila))
        cout << "eh palindromo";
    else
        cout << "nao eh palindromo";

    cout << endl;

    return 0;
}