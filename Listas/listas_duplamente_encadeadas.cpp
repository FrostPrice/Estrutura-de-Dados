using namespace std;

#include <iostream>

struct No
{
    char info;
    No *eloP;
    No *eloA;
};

struct LDE
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
void inicializar_lde(LDE &lde)
{
    lde.inicio = nullptr; // NULL
    lde.fim = nullptr;    // NULL
};

void mostrar_lista(LDE lde, char frase[])
{
    cout << frase << ": ";
    if (lde.inicio == nullptr)
        cout << "Vazia!";

    No *aux = lde.inicio;
    while (aux != nullptr)
    {
        cout << aux->info << " ";
        aux = aux->eloP;
    }
}

bool inserir_ordenado_lde(LDE &lde, char valor)
{
    No *novo = new No;

    if (novo == nullptr)
        return false;

    novo->info = valor;
    novo->eloP = nullptr;
    novo->eloA = nullptr;

    // Inserir em lista vazia
    if (lde.inicio == nullptr)
    {
        lde.inicio = novo;
        lde.fim = novo;

        return true;
    }

    // Inserir no inicio da lista
    if (valor < lde.inicio->info)
    {
        novo->eloP = lde.inicio;
        lde.inicio->eloA = novo;
        lde.inicio = novo;

        return true;
    }

    // Inserir no fim da lista
    if (valor > lde.fim->info)
    {
        novo->eloA = lde.fim;
        lde.fim->eloP = novo;
        lde.fim = novo;

        return true;
    }

    // Inserir no meio da lista
    No *aux = lde.inicio;
    while (aux->info < valor && aux->eloP->info < valor)
        aux = aux->eloP;

    novo->eloA = aux;
    novo->eloP = aux->eloP;
    aux->eloP->eloA = novo;
    aux->eloP = novo;

    return true;
}

bool inserir_final_lde(LDE &lde, char valor)
{
    No *novo = new No;

    if (novo == nullptr)
        return false;

    novo->info = valor;
    novo->eloP = nullptr;
    novo->eloA = nullptr;

    // Inserir em lista vazia
    if (lde.inicio == nullptr)
    {
        lde.inicio = novo;
        lde.fim = novo;
    }
    else
    {
        // Inserir no final
        lde.fim->eloP = novo;
        novo->eloA = lde.fim;
        lde.fim = novo;
    }
    return true;
}

No *buscar_lde(LDE &lde, char valor)
{
    No *aux = lde.inicio;

    while (aux != nullptr)
    {
        if (valor == aux->info)
            return aux;
        aux = aux->eloP;
    }

    return nullptr;
}

bool retirar_lde(LDE &lde, char valor)
{
    No *aux = buscar_lde(lde, valor);

    if (aux == nullptr)
        return false; // Lista vazia ou valor não encontrado

    // Retirada no inicio da lista
    if (aux == lde.inicio)
    {
        lde.inicio = lde.inicio->eloP;
        if (aux == lde.fim)
        {
            lde.fim = nullptr;
        }
    }
    else
    {
        aux->eloA->eloP = aux->eloP;
        if (aux == lde.fim)
            lde.fim = aux->eloA;
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

int tamanho_lista(LDE lde)
{
    if (lde.inicio == nullptr)
        return 0;

    int count = 0;
    No *aux = lde.inicio;
    while (aux != nullptr)
    {
        count++;
        aux = aux->eloP;
    }

    return count;
}

LDE duplicidade_listas(LDE lde_1, LDE lde_2)
{
    LDE repetidos;
    inicializar_lde(repetidos);

    if (lde_1.inicio == nullptr || lde_2.inicio == nullptr)
        return repetidos;

    No *aux_1 = lde_1.inicio, *aux_2;
    while (aux_1 != nullptr)
    {
        aux_2 = lde_2.inicio;
        while (aux_2 != nullptr)
        {
            if (aux_1->info == aux_2->info)
            {
                inserir_final_lde(repetidos, aux_1->info);
                break;
            }

            aux_2 = aux_2->eloP;
        }

        aux_1 = aux_1->eloP;
    }

    return repetidos;
}
#pragma endregion FUNCOES_AVANCADAS
int main()
{
    LDE lde_1, lde_2;
    inicializar_lde(lde_1);
    inicializar_lde(lde_2);

    inserir_ordenado_lde(lde_1, 'P');
    inserir_ordenado_lde(lde_1, 'E');
    inserir_ordenado_lde(lde_1, 'R');
    inserir_ordenado_lde(lde_1, 'N');
    inserir_ordenado_lde(lde_1, 'A');
    inserir_ordenado_lde(lde_1, 'M');
    inserir_ordenado_lde(lde_1, 'B');
    inserir_ordenado_lde(lde_1, 'U');
    inserir_ordenado_lde(lde_1, 'C');
    inserir_ordenado_lde(lde_1, 'O');

    mostrar_lista(lde_1, "Lista 1");

    cout << endl;

    inserir_final_lde(lde_2, 'P');
    inserir_final_lde(lde_2, 'E');
    inserir_final_lde(lde_2, 'R');
    inserir_final_lde(lde_2, 'N');
    inserir_final_lde(lde_2, 'A');
    inserir_final_lde(lde_2, 'M');
    inserir_final_lde(lde_2, 'B');
    inserir_final_lde(lde_2, 'U');
    inserir_final_lde(lde_2, 'C');
    inserir_final_lde(lde_2, 'O');

    mostrar_lista(lde_2, "Lista 2");

    cout << endl;

    cout << "(Antes) Tamanho Lista 2: " << tamanho_lista(lde_2);

    cout << endl;

    retirar_lde(lde_2, 'M');
    retirar_lde(lde_2, 'P');
    retirar_lde(lde_2, 'R');
    retirar_lde(lde_2, 'A');
    retirar_lde(lde_2, 'O');

    mostrar_lista(lde_2, "Lista 2");

    cout << endl;

    cout << "(Depois) Tamanho Lista 2: " << tamanho_lista(lde_2);

    cout << endl;

    LDE lde_3, lde_4;
    inicializar_lde(lde_3);
    inicializar_lde(lde_4);

    inserir_ordenado_lde(lde_3, 'A');
    inserir_ordenado_lde(lde_3, 'E');
    inserir_ordenado_lde(lde_3, 'I');
    inserir_ordenado_lde(lde_3, 'O');
    inserir_ordenado_lde(lde_3, 'U');

    inserir_final_lde(lde_4, 'P');
    inserir_final_lde(lde_4, 'E');
    inserir_final_lde(lde_4, 'R');
    inserir_final_lde(lde_4, 'N');
    inserir_final_lde(lde_4, 'A');
    inserir_final_lde(lde_4, 'M');
    inserir_final_lde(lde_4, 'B');
    inserir_final_lde(lde_4, 'U');
    inserir_final_lde(lde_4, 'C');
    inserir_final_lde(lde_4, 'O');

    mostrar_lista(duplicidade_listas(lde_3, lde_4), "Lista De items duplicados");

    cout << endl;

    return 0;
}