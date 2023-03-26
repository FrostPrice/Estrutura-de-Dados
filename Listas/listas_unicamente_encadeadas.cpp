using namespace std;

#include <iostream>

struct No
{
    char info;
    No *elo;
};

struct LUE
{
    No *inicio;
    No *fim;
};

#pragma region FUNCOES_BASICAS
/*
Operações:
1) Inicializar Lista - OK
2) Inserir no final - OK
3) Inserir em ordem - OK
4) Retirar valor - OK
5) Buscar valor - OK
6) Mostrar Lista - OK
*/
void inicializar_lue(LUE &lue)
{
    lue.inicio = nullptr; // NULL
    lue.fim = nullptr;    // NULL
};

void mostrar_lista(LUE lue, char frase[])
{
    cout << frase << ": ";
    if (lue.inicio == nullptr)
        cout << "Vazia!";

    No *aux = lue.inicio;
    while (aux != nullptr)
    {
        cout << aux->info << " ";
        aux = aux->elo;
    }
}

bool inserir_ordenado_lue(LUE &lue, char valor)
{
    No *novo = new No;

    if (novo == nullptr)
        return false;

    novo->info = valor;
    novo->elo = nullptr;

    // Inserir em lista vazia
    if (lue.inicio == nullptr)
    {
        lue.inicio = novo;
        lue.fim = novo;

        return true;
    }

    // Inserir no inicio da lista
    if (valor < lue.inicio->info)
    {
        novo->elo = lue.inicio;
        lue.inicio = novo;

        return true;
    }

    // Inserir no inicio da lista
    if (valor > lue.fim->info)
    {
        lue.fim->elo = novo;
        lue.fim = novo;

        return true;
    }

    // Inserir no meio da lista
    No *aux = lue.inicio;
    while (aux->info < valor && aux->elo->info < valor)
        aux = aux->elo;
    novo->elo = aux->elo;
    aux->elo = novo;

    return true;
}

bool inserir_final_lue(LUE &lue, char valor)
{
    No *novo = new No;

    if (novo == nullptr)
        return false;

    novo->info = valor;
    novo->elo = nullptr;

    // Inserir em lista vazia
    if (lue.inicio == nullptr)
    {
        lue.inicio = novo;
        lue.fim = novo;
    }
    else
    {
        // Inserir no final

        lue.fim->elo = novo;
        lue.fim = novo;
    }
    return true;
}

No *buscar_lue(LUE &lue, char valor)
{
    No *aux = lue.inicio;

    while (aux != nullptr)
    {
        if (valor = aux->info)
            return aux;
        aux = aux->elo;
    }

    return nullptr;
}

bool retirar_lue(LUE &lue, char valor)
{
    No *aux = lue.inicio, *anterior = nullptr;

    while (aux != nullptr && aux->info != valor)
    {
        anterior = aux;
        aux = aux->elo;
    }

    if (aux == nullptr)
        return false; // Lista vazia ou valor não encontrado

    // Retirada no inicio da lista
    if (aux == lue.inicio)
    {
        lue.inicio = lue.inicio->elo;
        if (aux == lue.fim)
            lue.fim = nullptr;
    }
    else
    {
        anterior->elo = aux->elo;
        if (aux == lue.fim)
            lue.fim = anterior;
    }

    delete aux;
    return true;
};
#pragma endregion FUNCOES_BASICAS

#pragma region FUNCOES_AVANCADAS
/*
1) Escrever funcao que recebe uma lista e retorna a quantidade de nos da lista - OK
2) Escrever uma funcao que recebe duas listas e retorna uma terceira lista formada com os valores repetidos nas duas primeiras listas - OK
*/
int tamanho_lista(LUE &lue)
{
    if (lue.inicio == nullptr)
        return 0;

    int count = 0;
    No *aux = lue.inicio;
    while (aux != nullptr)
    {
        count++;
        aux = aux->elo;
    }

    return count;
}

LUE duplicidade_listas(LUE lue_1, LUE lue_2)
{
    LUE repetidos;
    inicializar_lue(repetidos);

    if (lue_1.inicio == nullptr || lue_2.inicio == nullptr)
        return repetidos;

    No *aux_1 = lue_1.inicio, *aux_2;
    while (aux_1 != nullptr)
    {
        aux_2 = lue_2.inicio;
        while (aux_2 != nullptr)
        {
            if (aux_1->info == aux_2->info)
            {
                inserir_final_lue(repetidos, aux_1->info);
                break;
            }

            aux_2 = aux_2->elo;
        }
        aux_1 = aux_1->elo;
    }

    return repetidos;
}
#pragma endregion FUNCOES_AVANCADAS
int main()
{
    LUE lue_1, lue_2;
    inicializar_lue(lue_1);
    inicializar_lue(lue_2);

    inserir_ordenado_lue(lue_1, 'P');
    inserir_ordenado_lue(lue_1, 'E');
    inserir_ordenado_lue(lue_1, 'R');
    inserir_ordenado_lue(lue_1, 'N');
    inserir_ordenado_lue(lue_1, 'A');
    inserir_ordenado_lue(lue_1, 'M');
    inserir_ordenado_lue(lue_1, 'B');
    inserir_ordenado_lue(lue_1, 'U');
    inserir_ordenado_lue(lue_1, 'C');
    inserir_ordenado_lue(lue_1, 'O');

    mostrar_lista(lue_1, "Lista 1");

    cout << endl;

    inserir_final_lue(lue_2, 'P');
    inserir_final_lue(lue_2, 'E');
    inserir_final_lue(lue_2, 'R');
    inserir_final_lue(lue_2, 'N');
    inserir_final_lue(lue_2, 'A');
    inserir_final_lue(lue_2, 'M');
    inserir_final_lue(lue_2, 'B');
    inserir_final_lue(lue_2, 'U');
    inserir_final_lue(lue_2, 'C');
    inserir_final_lue(lue_2, 'O');

    mostrar_lista(lue_2, "Lista 2");

    cout << endl;

    cout << "(Antes) Tamanho Lista 2: " << tamanho_lista(lue_2);

    cout << endl;

    retirar_lue(lue_2, 'M');
    retirar_lue(lue_2, 'P');
    retirar_lue(lue_2, 'R');
    retirar_lue(lue_2, 'A');

    mostrar_lista(lue_2, "Lista 2");

    cout << endl;

    cout << "(Depois) Tamanho Lista 2: " << tamanho_lista(lue_2);

    cout << endl;

    LUE lue_3, lue_4;
    inicializar_lue(lue_3);
    inicializar_lue(lue_4);

    inserir_ordenado_lue(lue_3, 'A');
    inserir_ordenado_lue(lue_3, 'E');
    inserir_ordenado_lue(lue_3, 'I');
    inserir_ordenado_lue(lue_3, 'O');
    inserir_ordenado_lue(lue_3, 'U');

    inserir_final_lue(lue_4, 'P');
    inserir_final_lue(lue_4, 'E');
    inserir_final_lue(lue_4, 'R');
    inserir_final_lue(lue_4, 'N');
    inserir_final_lue(lue_4, 'A');
    inserir_final_lue(lue_4, 'M');
    inserir_final_lue(lue_4, 'B');
    inserir_final_lue(lue_4, 'U');
    inserir_final_lue(lue_4, 'C');
    inserir_final_lue(lue_4, 'O');

    mostrar_lista(duplicidade_listas(lue_3, lue_4), "Lista De items duplicados");

    cout << endl;

    return 0;
}