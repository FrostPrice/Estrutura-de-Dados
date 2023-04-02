/*
Alunos:
    - Mateus Barbosa
    - Matheus de Oliveira Rocha
*/

using namespace std;

#include <iostream>
#include <string>
#include <regex>

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
            if (aux->coeficiente != 0 && aux->coeficiente != 1)
            {
                cout << aux->coeficiente;
            }
        }
        else
        {
            if (aux->coeficiente != 0 && aux->coeficiente != 1)
            {
                if (aux->coeficiente > 1)
                    cout << "+ " << aux->coeficiente;
                else
                    cout << "- " << -aux->coeficiente;
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
6) (Opicional)Fazer a divisão de polinomios (Impossível)
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

// TODO: A funcao somar_polinomios e subtrair_polinomios podem se tornar apenas uma funcao com um if determinando a inversao dos sinais
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
            int expoente = aux_polinomio_1->exp + aux_polinomio_2->exp;
            inserir_ordenado(polinomio_resultado, coeficiente, aux_polinomio_1->letra, expoente);

            aux_polinomio_2 = aux_polinomio_2->eloP;
        }

        aux_polinomio_1 = aux_polinomio_1->eloP;
    }

    polinomio_resultado = somar_monomios(polinomio_resultado);

    return polinomio_resultado;
}

float valor_numerico(LDE polinomio, float valor_real)
{
    LDE polinomio_resultado;
    inicializar(polinomio_resultado);

    float resultado_final = 0;
    No *aux_polinomio = polinomio.inicio;
    while (aux_polinomio != nullptr)
    {
        float resultado_exponencial = 1;
        for (int i = 1; i <= aux_polinomio->exp; i++)
        {
            resultado_exponencial *= valor_real;
        }

        resultado_final += resultado_exponencial * aux_polinomio->coeficiente;
        aux_polinomio = aux_polinomio->eloP;
    };

    return resultado_final;
}
#pragma endregion FUNCOES_AVANCADAS

string remove_espacos(string str)
{
    string sem_espacos;
    for (char letra : str)
    {
        if (!isspace(letra))
        {
            sem_espacos += letra;
        }
    }

    return sem_espacos;
}

void solicita_input_polinomio(LDE &polinomio)
{
    /*
    Digite um polinomio: 4x^2 + x^1 - 5
    */
    // Pegar string inteira
    // Separar os monomios (4x^2) (+ x^1) (- 5)
    // Inserir cada monomio em um no da LDE informada por parametro

    string input_polinomio;

    cout << "Digite um polinomio (Ex: 4x^2 + x^1 - 5): ";
    getline(cin, input_polinomio);

    cout << remove_espacos(input_polinomio) << endl;

    string letra;
    string coeficiente;
    string expoente;

    // Extrai float coeficiente

    // Extrai char letra

    // Extrai int Expoente
}

/*
Funcao determina a operacao
*/

// void determina_operacao()
// {
// }

int main()
{
#pragma region TESTES
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
    // cout << endl;

    // LDE polinomio_3;
    // inicializar(polinomio_3);
    // polinomio_3 = somar_polinomios(polinomio_1, polinomio_2);
    // mostrar_lista(polinomio_3, "Polinomio Resultado");

    // cout << endl;
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

// START: Teste Multiplicacao de Polinomios
// LDE polinomio_1, polinomio_2;
// inicializar(polinomio_1);
// inicializar(polinomio_2);

// inserir_ordenado(polinomio_1, 3, 'x', 2);
// inserir_ordenado(polinomio_1, -5, 'x', 1);
// inserir_ordenado(polinomio_1, 8, 'x', 0);
// mostrar_lista(polinomio_1, "Polinomio 1");

// cout << endl;

// inserir_ordenado(polinomio_2, -2, 'x', 1);
// inserir_ordenado(polinomio_2, 1, 'x', 0);
// mostrar_lista(polinomio_2, "Polinomio 2");

// cout << endl;

// LDE polinomio_3;
// inicializar(polinomio_3);
// polinomio_3 = multiplicacao_polinomios(polinomio_1, polinomio_2);

// mostrar_lista(polinomio_3, "Resultado Multiplicacao");
// cout << endl;
// END: Teste Multiplicacao

// START: Teste Valor Numerico
// LDE polinomio_1;
// inicializar(polinomio_1);

// inserir_ordenado(polinomio_1, 1, 'x', 3);
// inserir_ordenado(polinomio_1, -2, 'x', 2);
// inserir_ordenado(polinomio_1, 4, 'x', 1);
// mostrar_lista(polinomio_1, "Polinomio 1");

// cout << endl;

// float valor;
// valor = valor_numerico(polinomio_1, 2);

// cout << "Resultado Valor Numerico: " << valor;

// cout << endl;
// END: Teste Valor Numerico
#pragma endregion TESTES

    LDE polinomio_teste;
    inicializar(polinomio_teste);
    solicita_input_polinomio(polinomio_teste);

    bool test = false;
    if (test == true)
    {
        string menu = "//////////////////////////////////////////////////////////\n"
                      "//\t\t\tHP12C-no-rpn\t\t\t//\n"
                      "//\t\t\t\t\t\t\t//\n"
                      "//\t\t\t\t\t\t\t//\n"
                      "// Escolha a operação [1-6]\t\t\t\t//\n"
                      "// 1) Valor Numerico\t\t\t\t\t//\n"
                      "// 2) Somar Polinomios\t\t\t\t\t//\n"
                      "// 3) Subtrait Polonomios\t\t\t\t//\n"
                      "// 4) Multiplicacao Escalar\t\t\t\t//\n"
                      "// 5) Multiplicacao de Polinomios\t\t\t//\n"
                      "// 6) Sair\t\t\t\t\t\t//\n"
                      "//\t\t\t\t\t\t\t//\n"
                      "//////////////////////////////////////////////////////////\n";

        cout << menu;
        int input_usuario;
        do
        {
            cout << "Qual operacao deseja fazer? ";
            cin >> input_usuario;
        } while (input_usuario < 1 || input_usuario > 6);

        switch (input_usuario)
        {
            LDE polinomio_1, polinomio_2;
        case 1:
            float valor_real;

            // FUNCAO PARA SOLICITAR POLINOMIO

            cout << "Digite o valor de X: ";
            cin >> valor_real;
            cout << endl;
            valor_numerico(polinomio_1, valor_real);
            break;
        case 2:

            // FUNCAO PARA SOLICITAR POLINOMIO_1
            // FUNCAO PARA SOLICITAR POLINOMIO_2

            somar_polinomios(polinomio_1, polinomio_2);
            break;
        case 3:

            // FUNCAO PARA SOLICITAR POLINOMIO_1
            // FUNCAO PARA SOLICITAR POLINOMIO_2

            subtrair_polinomios(polinomio_1, polinomio_2);
            break;
        case 4:
            float escalar_k;

            // FUNCAO PARA SOLICITAR POLINOMIO

            cout << "Digite o valor para multiplicar os coeficientes: ";
            cin >> escalar_k;
            cout << endl;
            multiplicacao_escalar(polinomio_1, escalar_k);
            break;
        case 5:

            // FUNCAO PARA SOLICITAR POLINOMIO_1
            // FUNCAO PARA SOLICITAR POLINOMIO_2

            multiplicacao_polinomios(polinomio_1, polinomio_2);
            break;
        case 6:
            cout << "Saindo da aplicação...\n";
            return 0;
            break;
        default:
            cout << "Error: Isso nao devia ter acontecido :(\n";
            return 0;
            break;
        }
    }
    return 0;
}