using namespace std;
#include <iostream>

#define TAM 10

#pragma region FUNCOES_BASICAS_LUE
struct LUE
{
    No *inicio, *fim;
};

struct No
{
    int info;
    No *elo;
};

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

void mostrar_lista(LUE lue)
{
    if (lue.inicio == nullptr)
        cout << "Vazia!";

    No *aux = lue.inicio;
    while (aux != nullptr)
    {
        cout << aux->info << " ";
        aux = aux->elo;
    }
}

bool inserir_ordenado_lue(LUE &lue, int valor)
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

bool inserir_final_lue(LUE &lue, int valor)
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

No *buscar_lue(LUE &lue, int valor)
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

bool retirar_lue(LUE &lue, int valor)
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
#pragma endregion FUNCOES_BASICAS_LUE

int funcao_hash(int chave)
{
    return chave % TAM;
}

void inserir(LUE tabela_hash[], int valor)
{
    int hash = funcao_hash(valor);

    inserir_ordenado_lue(tabela_hash[hash], valor);
}

bool buscar(LUE tabela_hash[], int valor)
{
    int hash = funcao_hash(valor);

    return ((buscar_lue(tabela_hash[hash], valor)) == nullptr) ? false : true;
}

void mostrar(LUE tabela_hash[])
{
    cout << endl
         << "Tabela Hash: " << endl;
    for (int i = 0; i < TAM; i++)
    {
        cout << endl
             << "Posicao " << i << " => ";
        mostrar_lista(tabela_hash[i]);
    }
}

int main()
{
    // Implementar um programa que receba numeros inteiros fornecidos pelo usuario (enquanto ele desejar) e os armazene em um vetor ou tabela hashing
    // Caracteristicas
    //  - Calculo de endereços pelo resto da divisao
    //  - Tratar colisoes por enderecamento fechado com LUE
    //  - Permitir inserir, pesquisar e mostrar todas as posicoes
    //  - Tamanho do vetor ou tabela usando define
    LUE tabela_hash[TAM];
    int num, op;

    for (int i = 0; i < TAM; i++)
    {
        inicializar_lue(tabela_hash[i]);
    };

    do
    {
        cout << "Digite sua opcao: " << endl;
        cout << "\t1. Inserir na Tabela";
        cout << "\t2. Pesquisar na Tabela";
        cout << "\t3. Mostrar toda a Tabela";
        cout << "\t4. Fim";

        switch (op)
        {
        case 1: // insercao
            cout << endl
                 << "Digite um numero inteiro: ";
            cin >> num;
            inserir(tabela_hash, num);
            break;
        case 2: // Pesquisa
            if (buscar)
                cout << endl
                     << num << " foi encontrado na tabela";
            else
                cout << endl
                     << num << " nao foi encontrado na tabela";
            break;
        case 3: // Mostrar
            mostrar(tabela_hash);
            break;
        case 4: // Fim
            break;
        default:
            cout << "Opcao invalida" << endl;
        }

    } while (op != 4);
    cout << endl;

    return 0;
}