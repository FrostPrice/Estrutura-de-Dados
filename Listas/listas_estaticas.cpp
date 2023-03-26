using namespace std;

#include "iostream"

// Operações:
// 1) Inserir no final - OK
// 2) Inserir em ordem - OK
// 3) Retirar valor - OK
// 4) Buscar valor - OK
// 4) Mostrar Lista - OK
// 5) Inicializar Lista - OK

#pragma region OPERACOES_BASICAS
#define TAM 50

struct Lista
{
    char items[TAM];
    int ultimo;
};

int get_ultimo(Lista lista)
{
    return lista.ultimo;
}

char get_item(Lista lista, int index)
{
    if (index < 0 || index > lista.ultimo)
        return -1;

    return lista.items[index];
}

void inicializar_lista(Lista &lista)
{
    lista.ultimo = -1;
}

void mostrar_lista(Lista lista, char frase[])
{
    cout << frase << ": ";
    if (lista.ultimo == -1)
        cout << "Nao possui item";
    for (int i = 0; i <= lista.ultimo; i++)
    {
        cout << lista.items[i] << " ";
    }
}

int buscar_valor(Lista lista, char valor)
{
    for (int i = 0; i <= lista.ultimo; i++)
    {
        if (lista.items[i] == valor)
        {
            return i;
        }
    }

    return -1; // Para quando não encontra o valor
}

bool inserir_no_final(Lista &lista, char valor)
{
    if (lista.ultimo >= TAM) // Guard Clause
        return false;
    lista.items[++lista.ultimo] = valor; // O ++ antes da variavel e para adicionar 1 a variavel antes de realizar a operação no vetor
    return true;
}

bool inserir_em_ordem(Lista &lista, char valor)
{
    int counter = 0;

    if (lista.ultimo >= TAM) // Guard Clause
        return false;

    while (counter <= lista.ultimo && lista.items[counter] < valor)
    {
        counter++;
    }

    lista.ultimo++;

    for (int i = lista.ultimo; i > counter; i--)
    {
        lista.items[i] = lista.items[i - 1];
    }

    lista.items[counter] = valor;

    return true;
}

bool retirar_valor(Lista &lista, char valor)
{
    int posicao = buscar_valor(lista, valor);

    if (posicao == -1)
    {
        return false;
    }

    for (int i = posicao; i < lista.ultimo; i++)
    {
        lista.items[i] = lista.items[i + 1];
    }
    lista.ultimo--;
    return true;
}

#pragma endregion OPERACOES_BASICAS

// Mais Operações (Usando as operações anteriores):
// 1) Eliminar redundância/duplicidade na lista
// 2) Clonar uma lista
// 3.1) Concatenar duas listas, mantendo a ordem
// 3.2) Combinar 2 listas formando uma terceira
//      - Concatenar ou...
//      - Mesclar em ordem

#pragma region OPERACOES_AVANCADAS
Lista remover_redundancia_lista(Lista lista)
{
    for (int i = 0; i < get_ultimo(lista); i++)
    {
        int valor_atual = get_item(lista, i);

        for (int j = i + 1; j <= get_ultimo(lista); j++)
        {
            char valor_proximo = get_item(lista, j);
            if (valor_atual == valor_proximo)
            {
                retirar_valor(lista, get_item(lista, i));
                // retirar_valor(lista, j);
                // j--;
            }
        }
    }

    return lista;
}

Lista clonar_lista(Lista lista)
{
    Lista clone_lista;
    inicializar_lista(clone_lista);

    for (int i = 0; i <= get_ultimo(lista); i++)
    {
        inserir_no_final(clone_lista, get_item(lista, i));
    }

    return clone_lista;
}

Lista concatenar_listas(Lista l_1, Lista l_2)
{
    Lista l_concatenada;
    inicializar_lista(l_concatenada);

    if (get_ultimo(l_1) + get_ultimo(l_2) + 1 <= TAM)
    {
        for (int i = 0; i <= l_1.ultimo; i++)
        {
            // l_concatenada.items[i] = l_1.items[i];
            inserir_em_ordem(l_concatenada, get_item(l_1, i));
        }
        for (int i = 0; i <= l_2.ultimo; i++)
        {
            // l_concatenada.items[i] = l_2.items[i];
            inserir_em_ordem(l_concatenada, get_item(l_2, i));
        }
    }

    return l_concatenada;
}

#pragma endregion OPERACOES_AVANCADAS

int main()
{
    Lista l_1, l_2, l_duplicada, l_unica, l_clone, l_concatenada;

    inicializar_lista(l_1);
    inicializar_lista(l_2);
    inicializar_lista(l_duplicada);

    inserir_no_final(l_1, 'M');
    inserir_no_final(l_1, 'A');
    inserir_no_final(l_1, 'T');
    inserir_no_final(l_1, 'E');
    inserir_no_final(l_1, 'U');
    inserir_no_final(l_1, 'S');
    mostrar_lista(l_1, "Lista 1");

    cout << endl;

    inserir_em_ordem(l_2, 'M');
    inserir_em_ordem(l_2, 'A');
    inserir_em_ordem(l_2, 'T');
    inserir_em_ordem(l_2, 'E');
    inserir_em_ordem(l_2, 'U');
    inserir_em_ordem(l_2, 'S');

    mostrar_lista(l_2, "Lista 2");

    cout << endl;

    retirar_valor(l_2, 'T');

    mostrar_lista(l_2, "Lista 2");

    cout << endl;

    inserir_no_final(l_duplicada, 'D');
    inserir_no_final(l_duplicada, 'A');
    inserir_no_final(l_duplicada, 'B');
    inserir_no_final(l_duplicada, 'C');
    inserir_no_final(l_duplicada, 'A');
    inserir_no_final(l_duplicada, 'B');
    inserir_no_final(l_duplicada, 'A');

    l_unica = remover_redundancia_lista(l_duplicada);

    mostrar_lista(l_unica, "Lista Unica");

    cout << endl;

    l_clone = clonar_lista(l_1);

    mostrar_lista(l_clone, "Lista Clone");

    cout << endl;

    l_concatenada = concatenar_listas(l_1, l_2);

    mostrar_lista(l_concatenada, "Lista Concatenada");

    cout << endl;

    return 0;
}