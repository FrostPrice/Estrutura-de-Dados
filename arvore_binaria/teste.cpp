#include <iostream>
#include <string>
using namespace std;

struct Info
{
    long int CPF;
    string Nome;
    string Profissao;
};

struct No
{
    Info *info;
    No *esq;
    No *dir;
};

No *arvoreCPF = NULL;
No *arvoreNome = NULL;

// função para inserir um novo funcionário
void inserir(No *&raizCPF, No *&raizNome, Info *info)
{
    // se a árvore está vazia, criamos o nó com a informação
    if (raizCPF == NULL && raizNome == NULL)
    {
        No *novo = new No;
        novo->info = info;
        novo->esq = NULL;
        novo->dir = NULL;
        raizCPF = novo;
        raizNome = novo;
    }
    // se o CPF já está cadastrado, não fazemos a inserção
    else if (raizCPF->info->CPF == info->CPF)
    {
        cout << "CPF ja cadastrado!" << endl;
    }
    // se o CPF é menor que o da raiz, inserimos na subárvore esquerda
    else if (info->CPF < raizCPF->info->CPF)
    {
        inserir(raizCPF->esq, raizNome, info);
    }
    // se o CPF é maior que o da raiz, inserimos na subárvore direita
    else if (info->CPF > raizCPF->info->CPF)
    {
        inserir(raizCPF->dir, raizNome, info);
    }

    // inserção na árvore ordenada por nome
    // se o nome já está cadastrado, não fazemos a inserção
    else if (raizNome->info->Nome == info->Nome)
    {
        cout << "Nome ja cadastrado!" << endl;
    }
    // se o nome é menor que o da raiz, inserimos na subárvore esquerda
    else if (info->Nome < raizNome->info->Nome)
    {
        inserir(raizCPF, raizNome->esq, info);
    }
    // se o nome é maior que o da raiz, inserimos na subárvore direita
    else if (info->Nome > raizNome->info->Nome)
    {
        inserir(raizCPF, raizNome->dir, info);
    }
}

// função para remover um funcionário pelo CPF ou pelo nome
void remover(No *&raizCPF, No *&raizNome, long int CPF, string Nome)
{
    if (raizCPF == NULL || raizNome == NULL)
    {
        cout << "Funcionario nao encontrado!" << endl;
    }
    else if (CPF < raizCPF->info->CPF)
    {
        remover(raizCPF->esq, raizNome, CPF, Nome);
    }
    else if (CPF > raizCPF->info->CPF)
    {
        remover(raizCPF->dir, raizNome, CPF, Nome);
    }
    else if (CPF == raizCPF->info->CPF && Nome == raizNome->info->Nome)
    {
        // encontramos o funcionário
        // removemos o nó e liberamos a memória da estrutura Info
        No *aux = raizCPF;
        if (raizCPF->esq == NULL)
        {
            raizCPF = raizCPF->dir;
            raizNome = raizNome->dir;
        }
        else if (raizCPF->dir == NULL)
        {
            raizCPF = raizCPF->esq;
            raizNome = raizNome->esq;
        }
        else
        {
            No *sucessorCPF = raizCPF->dir;
            No *sucessorNome = raizNome->dir;
            while (sucessorCPF->esq != NULL && sucessorNome->esq != NULL)
            {
                sucessorCPF = sucessorCPF->esq;
                sucessorNome = sucessorNome->esq;
            }
            raizCPF->info = sucessorCPF->info;
            raizNome->info = sucessorNome->info;
            remover(raizCPF->dir, raizNome->dir, sucessorCPF->info->CPF, sucessorNome->info->Nome);
        }
        delete aux->info;
        delete aux;
    }
    else if (Nome < raizNome->info->Nome)
    {
        remover(raizCPF, raizNome->esq, CPF, Nome);
    }
    else if (Nome > raizNome->info->Nome)
    {
        remover(raizCPF, raizNome->dir, CPF, Nome);
    }
}

// função para pesquisar um funcionário pelo CPF ou pelo nome
void pesquisar(No *&raizCPF, No *&raizNome, long int CPF, string Nome)
{
    if (raizCPF == NULL || raizNome == NULL)
    {
        cout << "Funcionario nao encontrado!" << endl;
    }
    else if (CPF < raizCPF->info->CPF)
    {
        pesquisar(raizCPF->esq, raizNome, CPF, Nome);
    }
    else if (CPF > raizCPF->info->CPF)
    {
        pesquisar(raizCPF->dir, raizNome, CPF, Nome);
    }
    else if (CPF == raizCPF->info->CPF && Nome == raizNome->info->Nome)
    {
        // encontramos o funcionário
        cout << "CPF: " << raizCPF->info->CPF << endl;
        cout << "Nome: " << raizNome->info->Nome << endl;
        cout << "Profissao: " << raizCPF->info->Profissao << endl;
    }
    else if (Nome < raizNome->info->Nome)
    {
        pesquisar(raizCPF, raizNome->esq, CPF, Nome);
    }
    else if (Nome > raizNome->info->Nome)
    {
        pesquisar(raizCPF, raizNome->dir, CPF, Nome);
    }
}

// função para listar todos os funcionários
void listar(No *raiz, int opcao)
{
    if (raiz != NULL)
    {
        listar(raiz->esq, opcao);
        cout << "CPF: " << raiz->info->CPF << endl;
        cout << "Nome: " << raiz->info->Nome << endl;
        cout << "Profissao: " << raiz->info->Profissao << endl
             << endl;
        listar(raiz->dir, opcao);
    }
}

// função para liberar a memória alocada pelas estruturas
void liberarMemoria(No *&raizCPF, No *&raizNome)
{
    if (raizCPF != NULL && raizNome != NULL)
    {
        liberarMemoria(raizCPF->esq, raizNome->esq);
        liberarMemoria(raizCPF->dir, raizNome->dir);
        delete raizCPF->info;
        delete raizCPF;
        delete raizNome;
        raizCPF = NULL;
        raizNome = NULL;
    }
}

// função principal
int main()
{
    No *arvoreCPF = NULL;
    No *arvoreNome = NULL;

    int opcao;
    long int CPF;
    string Nome, Profissao;

    do
    {
        cout << "-------------------------" << endl;
        cout << "SISTEMA DE RH" << endl;
        cout << "-------------------------" << endl;
        cout << "1. Inserir novo funcionario" << endl;
        cout << "2. Remover funcionario" << endl;
        cout << "3. Pesquisar funcionario" << endl;
        cout << "4. Listar funcionarios ordenados por CPF" << endl;
        cout << "5. Listar funcionarios ordenados por nome" << endl;
        cout << "6. Encerrar o programa" << endl;
        cout << "-------------------------" << endl;
        cout << "Digite uma opcao: ";
        cin >> opcao;
        Info *info = new Info;

        switch (opcao)
        {
        case 1:
            cout << "Digite o CPF: ";
            cin >> CPF;
            cout << "Digite o nome: ";
            cin.ignore();
            getline(cin, Nome);
            cout << "Digite a profissao: ";
            getline(cin, Profissao);
            info->CPF = CPF;
            info->Nome = Nome;
            info->Profissao = Profissao;
            inserir(arvoreCPF, arvoreNome, info);
            break;
        case 2:
            cout << "Digite o CPF: ";
            cin >> CPF;
            cout << "Digite o nome: ";
            cin.ignore();
            getline(cin, Nome);
            remover(arvoreCPF, arvoreNome, CPF, Nome);
            break;
        case 3:
            cout << "Digite o CPF: ";
            cin >> CPF;
            cout << "Digite o nome: ";
            cin.ignore();
            getline(cin, Nome);
            pesquisar(arvoreCPF, arvoreNome, CPF, Nome);
            break;
        case 4:
            cout << "Funcionarios ordenados por CPF:" << endl
                 << endl;
            listar(arvoreCPF, 1);
            break;
        case 5:
            cout << "Funcionarios ordenados por nome:" << endl
                 << endl;
            listar(arvoreNome, 2);
            break;
        case 6:
            cout << "Encerrando o programa..." << endl;
            liberarMemoria(arvoreCPF, arvoreNome);
            break;
        default:
            cout << "Opcao invalida!" << endl;
            break;
        }
    } while (opcao != 6);

    return 0;
}