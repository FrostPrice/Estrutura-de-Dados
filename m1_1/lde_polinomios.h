/*
Alunos:
    - Mateus Barbosa
    - Matheus de Oliveira Rocha
*/

#ifndef LDE_POLINOMIOS_H
#define LDE_POLINOMIOS_H

using namespace std;
#include <iostream>
#include <string>

struct No
{
    float coeficiente;
    char letra;
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
5) Imprimir lista: mostrar o polinômio na tela - OK
*/
void inicializar(LDE &lde)
{
    lde.inicio = nullptr; // NULL
    lde.fim = nullptr;    // NULL
};

void mostrar_lista(LDE lde, string frase)
{
    cout << frase << ": ";
    if (lde.inicio == nullptr)
        cout << "Vazia!";

    No *aux = lde.inicio;
    while (aux != nullptr)
    {
        // Formata os monomios
        if (aux == lde.inicio)
        {
            if (aux->coeficiente != 0 && aux->coeficiente != 1 || aux->letra == '\0')
            {
                cout << aux->coeficiente;
            }
        }
        else
        {
            if (aux->coeficiente != 0 && aux->coeficiente != 1 && aux->coeficiente != -1 || aux->letra == '\0')
            {
                if (aux->coeficiente > 1)
                    cout << "+ " << aux->coeficiente;
                else
                    cout << "- " << -aux->coeficiente;
            }
            else
            {
                if (aux->coeficiente > 0)
                    cout << "+ ";
                else
                    cout << "- ";
            }
        }

        if (aux->exp != 0)
        {
            if (aux->exp != 1)
            {
                cout << aux->letra;
                cout << "^";
                cout << aux->exp;
            }
            else
                cout << aux->letra;
        }

        cout << " ";

        aux = aux->eloP;
    }
    cout << endl;
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
4) Multiplicar dois polinômios, resultando em um terceiro polinômio - OK
5) Determinar o valor numérico de um polinômio - OK
6) (Opicional)Fazer a divisão de polinomios (Impossível) - NOK
*/
LDE somar_monomios(LDE polinomio)
{
    LDE polinomio_soma;
    inicializar(polinomio_soma);

    No *aux_monomio_1 = polinomio.inicio;
    while (aux_monomio_1 != nullptr)
    {
        float coeficiente = aux_monomio_1->coeficiente;
        int expoente = aux_monomio_1->exp;
        char letra = aux_monomio_1->letra;

        No *aux_monomio_2 = aux_monomio_1->eloP;
        while (aux_monomio_2 != nullptr && aux_monomio_2->exp == expoente)
        {
            coeficiente += aux_monomio_2->coeficiente;
            aux_monomio_2 = aux_monomio_2->eloP;
        }

        inserir_ordenado(polinomio_soma, coeficiente, letra, expoente);
        aux_monomio_1 = aux_monomio_2;
    }

    return polinomio_soma;
}

LDE somar_polinomios(LDE polinomio_1, LDE polinomio_2)
{
    LDE polinomio_resultado;
    inicializar(polinomio_resultado);

    No *aux_polinomio_1 = polinomio_1.inicio;
    while (aux_polinomio_1 != nullptr)
    {
        inserir_ordenado(polinomio_resultado, aux_polinomio_1->coeficiente, aux_polinomio_1->letra, aux_polinomio_1->exp);
        aux_polinomio_1 = aux_polinomio_1->eloP;
    }

    No *aux_polinomio_2 = polinomio_2.inicio;
    while (aux_polinomio_2 != nullptr)
    {
        inserir_ordenado(polinomio_resultado, aux_polinomio_2->coeficiente, aux_polinomio_2->letra, aux_polinomio_2->exp);
        aux_polinomio_2 = aux_polinomio_2->eloP;
    }

    polinomio_resultado = somar_monomios(polinomio_resultado);
    return polinomio_resultado;
}

LDE subtrair_polinomios(LDE polinomio_1, LDE polinomio_2)
{
    LDE polinomio_resultado;
    inicializar(polinomio_resultado);

    No *aux_polinomio_1 = polinomio_1.inicio;
    while (aux_polinomio_1 != nullptr)
    {
        inserir_ordenado(polinomio_resultado, aux_polinomio_1->coeficiente, aux_polinomio_1->letra, aux_polinomio_1->exp);
        aux_polinomio_1 = aux_polinomio_1->eloP;
    }

    No *aux_polinomio_2 = polinomio_2.inicio;
    while (aux_polinomio_2 != nullptr)
    {
        inserir_ordenado(polinomio_resultado, -aux_polinomio_2->coeficiente, aux_polinomio_2->letra, aux_polinomio_2->exp); // O -aux_polinomio_2->coeficiente já faz o trabalho de inverter o sinal do coeficiente
        aux_polinomio_2 = aux_polinomio_2->eloP;
    }

    polinomio_resultado = somar_monomios(polinomio_resultado);
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

    polinomio_resultado = somar_monomios(polinomio_resultado);

    return polinomio_resultado;
}

LDE multiplicacao_polinomios(LDE polinomio_1, LDE polinomio_2)
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
            char letra;
            if (aux_polinomio_1->letra == '\0')
                letra = aux_polinomio_2->letra;
            else if (aux_polinomio_2->letra == '\0')
                letra = aux_polinomio_1->letra;
            else
                letra = aux_polinomio_1->letra;

            int expoente = aux_polinomio_1->exp + aux_polinomio_2->exp;
            inserir_ordenado(polinomio_resultado, coeficiente, letra, expoente);

            aux_polinomio_2 = aux_polinomio_2->eloP;
        }

        aux_polinomio_1 = aux_polinomio_1->eloP;
    }

    polinomio_resultado = somar_monomios(polinomio_resultado);

    return polinomio_resultado;
}

float valor_numerico(LDE polinomio, float valor_real)
{
    float resultado_final = 0;
    No *aux_polinomio = polinomio.inicio;

    while (aux_polinomio != nullptr)
    {
        float resultado_exponencial = 1;
        if (aux_polinomio->letra != '\0')
            for (int i = 0; i < aux_polinomio->exp; i++)
                resultado_exponencial *= valor_real;

        resultado_final += resultado_exponencial * aux_polinomio->coeficiente;
        aux_polinomio = aux_polinomio->eloP;
    };

    return resultado_final;
}
#pragma endregion FUNCOES_AVANCADAS
#endif // LDE_POLINOMIOS_H
