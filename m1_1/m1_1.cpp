using namespace std;

#include <iostream>
#include "string"

struct No
{
    char letra;
    float coeficiente;
    int exp;
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
1) Inicializar lista - OK
2) Inserir na lista (no final da lista e ordenado por expoente do polinômio) - OK
3) Remover da lista (de acordo com o expoente do polinômio) - OK
4) Descobrir expoente: receber um expoente e determinar se o termo existe ou não no polinômio - OK
5) Imprimir lista: mostrar o polinômio na tela - NOT_OK (TODO)
*/
void inicializar(LDE &lde)
{
    lde.inicio = nullptr; // NULL
    lde.fim = nullptr;    // NULL
};

void mostrar_lista(LDE lde, string frase)
{
    // TODO: mostrar sinais de + e remover os números 1 "sozinhos"
    cout << frase << ": ";
    if (lde.inicio == nullptr)
        cout << "Vazia!";

    No *aux = lde.inicio;
    while (aux != nullptr)
    {
        cout << aux->coeficiente << aux->letra << "^" << aux->exp << " ";
        aux = aux->eloP;
    }
}

bool inserir_ordenado(LDE &lde, float coeficiente, char letra, int exp)
{
    No *novo = new No;

    if (novo == nullptr)
        return false;

    novo->coeficiente = coeficiente;
    novo->letra = letra;
    novo->exp = exp;
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
    if (exp > lde.inicio->exp)
    {
        novo->eloP = lde.inicio;
        lde.inicio->eloA = novo;
        lde.inicio = novo;

        return true;
    }

    // Inserir no fim da lista
    if (exp <= lde.fim->exp)
    {
        novo->eloA = lde.fim;
        lde.fim->eloP = novo;
        lde.fim = novo;

        return true;
    }

    // Inserir no meio da lista
    No *aux = lde.inicio;
    while (aux->exp >= exp && aux->eloP->exp >= exp)
        aux = aux->eloP;

    novo->eloA = aux;
    novo->eloP = aux->eloP;
    aux->eloP->eloA = novo;
    aux->eloP = novo;

    return true;
}

bool inserir_final(LDE &lde, float coeficiente, char letra, int exp)
{
    No *novo = new No;

    if (novo == nullptr)
        return false;

    novo->coeficiente = coeficiente;
    novo->letra = letra;
    novo->exp = exp;
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

No *buscar_por_expoente(LDE &lde, int exp)
{
    No *aux = lde.inicio;

    while (aux != nullptr)
    {
        if (exp == aux->exp)
            return aux;
        aux = aux->eloP;
    }

    return nullptr;
}

bool retirar_por_expoente(LDE &lde, int exp)
{
    No *aux = buscar_por_expoente(lde, exp);

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
1) Somar dois polinômios, resultando em um terceiro polinômio - OK
2) Subtrair dois polinômios, resultando em um terceiro polinômio - OK
3) Multiplicar um polinômio por um escalar (valor real) - OK
4) Multiplicar dois polinômios, resultando em um terceiro polinômio
5) Determinar o valor numérico de um polinômio
6) (Opicional)Fazer a divisão de polinomios (Impossível)
*/
// TODO: Somar monomios

LDE somar_polinomios(LDE polinomio_1, LDE polinomio_2)
{
    LDE polinomio_resultado;
    inicializar(polinomio_resultado);

    if (polinomio_1.inicio == nullptr || polinomio_2.inicio == nullptr)
        return polinomio_resultado;

    No *aux_polinomio_1 = polinomio_1.inicio, *aux_polinomio_2 = polinomio_2.inicio;
    while (aux_polinomio_1 != nullptr && aux_polinomio_2 != nullptr)
    {
        if (aux_polinomio_1->exp == aux_polinomio_2->exp)
        {
            int coeficiente = aux_polinomio_1->coeficiente + aux_polinomio_2->coeficiente;
            if (coeficiente != 0)
            {
                inserir_ordenado(polinomio_resultado, coeficiente, aux_polinomio_1->letra, aux_polinomio_1->exp);
            }
            aux_polinomio_1 = aux_polinomio_1->eloP;
            aux_polinomio_2 = aux_polinomio_2->eloP;
        }
        else if (aux_polinomio_1->exp > aux_polinomio_2->exp)
        {
            inserir_ordenado(polinomio_resultado, aux_polinomio_1->coeficiente, aux_polinomio_1->letra, aux_polinomio_1->exp);
            aux_polinomio_1 = aux_polinomio_1->eloP;
        }
        else
        {
            inserir_ordenado(polinomio_resultado, aux_polinomio_2->coeficiente, aux_polinomio_2->letra, aux_polinomio_2->exp);
            aux_polinomio_2 = aux_polinomio_2->eloP;
        }
    }

    // Adiciona os termos restantes do polinômio 1
    while (aux_polinomio_1 != nullptr)
    {
        inserir_ordenado(polinomio_resultado, aux_polinomio_1->coeficiente, aux_polinomio_1->letra, aux_polinomio_1->exp);
        aux_polinomio_1 = aux_polinomio_1->eloP;
    }

    // Adiciona os termos restantes do polinômio 2
    while (aux_polinomio_2 != nullptr)
    {
        inserir_ordenado(polinomio_resultado, aux_polinomio_2->coeficiente, aux_polinomio_1->letra, aux_polinomio_2->exp);
        aux_polinomio_2 = aux_polinomio_2->eloP;
    }

    return polinomio_resultado;
}

LDE subtrair_polinomios(LDE polinomio_1, LDE polinomio_2)
{
    LDE polinomio_resultado;
    inicializar(polinomio_resultado);

    if (polinomio_1.inicio == nullptr || polinomio_2.inicio == nullptr)
        return polinomio_resultado;

    No *aux_polinomio_1 = polinomio_1.inicio, *aux_polinomio_2 = polinomio_2.inicio;
    while (aux_polinomio_1 != nullptr && aux_polinomio_2 != nullptr)
    {
        if (aux_polinomio_1->exp == aux_polinomio_2->exp)
        {
            int coeficiente = aux_polinomio_1->coeficiente - aux_polinomio_2->coeficiente;
            if (coeficiente != 0)
            {
                inserir_ordenado(polinomio_resultado, coeficiente, aux_polinomio_1->letra, aux_polinomio_1->exp);
            }
            aux_polinomio_1 = aux_polinomio_1->eloP;
            aux_polinomio_2 = aux_polinomio_2->eloP;
        }
        else if (aux_polinomio_1->exp > aux_polinomio_2->exp)
        {
            inserir_ordenado(polinomio_resultado, aux_polinomio_1->coeficiente, aux_polinomio_1->letra, aux_polinomio_1->exp);
            aux_polinomio_1 = aux_polinomio_1->eloP;
        }
        else
        {
            inserir_ordenado(polinomio_resultado, aux_polinomio_2->coeficiente, aux_polinomio_2->letra, aux_polinomio_2->exp);
            aux_polinomio_2 = aux_polinomio_2->eloP;
        }
    }

    // Adiciona os termos restantes do polinômio 1
    while (aux_polinomio_1 != nullptr)
    {
        inserir_ordenado(polinomio_resultado, aux_polinomio_1->coeficiente, aux_polinomio_1->letra, aux_polinomio_1->exp);
        aux_polinomio_1 = aux_polinomio_1->eloP;
    }

    // Adiciona os termos restantes do polinômio 2
    while (aux_polinomio_2 != nullptr)
    {
        inserir_ordenado(polinomio_resultado, aux_polinomio_2->coeficiente, aux_polinomio_1->letra, aux_polinomio_2->exp);
        aux_polinomio_2 = aux_polinomio_2->eloP;
    }

    return polinomio_resultado;
}

LDE multiplicacao_escalar(LDE polinomio, float escalar_k)
{
    LDE polinomio_resultado;
    inicializar(polinomio_resultado);

    if (polinomio.inicio == nullptr)
        return polinomio_resultado;

    No *aux_polinomio = polinomio.inicio;
    while (aux_polinomio != nullptr)
    {
        float coeficiente = aux_polinomio->coeficiente * escalar_k;
        inserir_final(polinomio_resultado, coeficiente, aux_polinomio->letra, aux_polinomio->exp);

        aux_polinomio = aux_polinomio->eloP;
    }

    return polinomio_resultado;
}

LDE multiplicacao(LDE polinomio_1, LDE polinomio_2)
{
    LDE polinomio_resultado;
    inicializar(polinomio_resultado);

    if (polinomio_1.inicio == nullptr || polinomio_2.inicio == nullptr)
        return polinomio_resultado;

    No *aux_polinomio_1 = polinomio_1.inicio, *aux_polinomio_2;
    while (aux_polinomio_1 != nullptr)
    {
        aux_polinomio_2 = polinomio_2.inicio;
        while (aux_polinomio_2 != nullptr)
        {
            float coeficiente = aux_polinomio_1->coeficiente * aux_polinomio_2->coeficiente;
            int expoente = aux_polinomio_1->exp + aux_polinomio_2->exp;
            inserir_ordenado(polinomio_resultado, coeficiente, aux_polinomio_1->letra, expoente);

            aux_polinomio_2 = aux_polinomio_2->eloP;
        }

        aux_polinomio_1 = aux_polinomio_1->eloP;
    }

    // TODO: Finish this
    No *aux_polinomio_resultado = polinomio_resultado.inicio;
    while (aux_polinomio_resultado->eloP != nullptr)
    {
        if (aux_polinomio_resultado->exp == aux_polinomio_resultado->exp)
        {
            aux_polinomio_resultado->coeficiente += aux_polinomio_resultado->coeficiente;
            No *temp = aux_polinomio_resultado->eloP;
            aux_polinomio_resultado = aux_polinomio_resultado->eloP;
        }
        else
        {
            aux_polinomio_resultado = aux_polinomio_resultado;
            aux_polinomio_resultado = aux_polinomio_resultado->eloP;
        }
    }

    return polinomio_resultado;
}
#pragma endregion FUNCOES_AVANCADAS

int main()
{

    // START: Teste Soma
    // LDE polinomio_1, polinomio_2;
    // inicializar(polinomio_1);
    // inicializar(polinomio_2);
    // inserir_ordenado(polinomio_1, -7, 'x', 3);
    // inserir_ordenado(polinomio_1, 5, 'x', 2);
    // inserir_ordenado(polinomio_1, -1, 'x', 1);
    // inserir_ordenado(polinomio_1, 4, 'x', 1);
    // mostrar_lista(polinomio_1, "Polinomio 1");

    // cout << endl;

    // inserir_ordenado(polinomio_2, -2, 'x', 2);
    // inserir_ordenado(polinomio_2, 8, 'x', 1);
    // inserir_ordenado(polinomio_2, -7, 'x', 1);
    // mostrar_lista(polinomio_2, "Polinomio 2");

    // LDE polinomio_3;
    // inicializar(polinomio_3);
    // polinomio_3 = somar_polinomios(polinomio_1, polinomio_2);
    // END: Teste Soma

    // START: Teste Subtracao
    // LDE polinomio_1, polinomio_2;
    // inicializar(polinomio_1);
    // inicializar(polinomio_2);
    // inserir_ordenado(polinomio_1, 4, 'x', 2);
    // inserir_ordenado(polinomio_1, -5, 'x', 1);
    // inserir_ordenado(polinomio_1, 6, 'x', 1);
    // mostrar_lista(polinomio_1, "Polinomio 1");

    // cout << endl;

    // inserir_ordenado(polinomio_2, 3, 'x', 1);
    // inserir_ordenado(polinomio_2, -8, 'x', 1);
    // mostrar_lista(polinomio_2, "Polinomio 2");

    // cout << endl;

    // LDE polinomio_3;
    // inicializar(polinomio_3);
    // polinomio_3 = subtrair_polinomios(polinomio_1, polinomio_2);

    // mostrar_lista(polinomio_3, "Resultado Subtracao");
    // cout << endl;
    // END: Teste Subtracao

    // START: Teste Multiplicacao por Escalar
    // LDE polinomio_1;
    // int escalar = -2;
    // inicializar(polinomio_1);
    // inserir_ordenado(polinomio_1, 3, 'x', 2);
    // inserir_ordenado(polinomio_1, -5, 'x', 1);
    // inserir_ordenado(polinomio_1, 8, 'x', 0);
    // mostrar_lista(polinomio_1, "Polinomio 1");

    // cout << endl;

    // LDE polinomio_2;
    // inicializar(polinomio_2);
    // polinomio_2 = multiplicacao_escalar(polinomio_1, escalar);

    // mostrar_lista(polinomio_2, "Resultado Multiplicacao por Escalar");
    // cout << endl;
    // END: Teste Multiplicacao por Escalar

    // START: Teste Multiplicacao
    LDE polinomio_1, polinomio_2;
    inicializar(polinomio_1);
    inicializar(polinomio_2);

    inserir_ordenado(polinomio_1, 3, 'x', 2);
    inserir_ordenado(polinomio_1, -5, 'x', 1);
    inserir_ordenado(polinomio_1, 8, 'x', 0);
    mostrar_lista(polinomio_1, "Polinomio 1");

    cout << endl;

    inserir_ordenado(polinomio_2, -2, 'x', 1);
    inserir_ordenado(polinomio_2, 1, 'x', 0);
    mostrar_lista(polinomio_2, "Polinomio 2");

    cout << endl;

    LDE polinomio_3;
    inicializar(polinomio_3);
    polinomio_3 = multiplicacao(polinomio_1, polinomio_2);

    mostrar_lista(polinomio_3, "Resultado Multiplicacao");
    cout << endl;
    // END: Teste Multiplicacao

    return 0;
}