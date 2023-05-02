using namespace std;

#include "string"
#include "iostream"

#pragma region ESTRUTURAS
struct Info
{
    long int cpf;
    string nome;
    string profissao;
};

struct No
{
    Info *info;
    No *esq = nullptr, *dir = nullptr;
};

struct Arvore
{
    No *raiz = nullptr;
};
#pragma endregion ESTRUTURAS

#pragma region AVL
#pragma endregion AVL

#pragma region FUNCOES
// TODO:
// Inserir uma nova informação; - OK
// Remover um registro pesquisando por CPF ou por nome;
// Pesquisar um registro por CPF ou por nome; - OK
// Listar todos as informações cadastradas (como se fosse um relatório, mas em tela) de forma ordenada por nome ou cpf; - OK
// Ao encerrar a aplicação, todas as posições/espaços de memória alocados devem ser liberados;

void buscar_maior_cpf(No *raiz, Info *info)
{
    if (raiz == nullptr)
        return;

    if (raiz->dir != nullptr)
    {
        buscar_maior_cpf(raiz->dir, info);
    }
    else
    {
        info = raiz->info;
    }
}

void buscar_maior_nome(No *raiz, string &chave, Info *info)
{
    if (raiz == nullptr)
        return;

    if (raiz->dir != nullptr)
    {
        buscar_maior_nome(raiz->dir, chave, info);
    }
    else
    {
        chave = raiz->info->nome;
        info = raiz->info;
    }
}

// Pesquisa por cpf
No *buscar(No *raiz_cpf, long int cpf)
{
    if (raiz_cpf == nullptr)
    {
        cout << "CPF nao encontrado!" << endl;
        return nullptr;
    }

    if (cpf == raiz_cpf->info->cpf)
    {
        cout << "CPF encontrado!" << endl;
        return raiz_cpf;
    }
    else if (cpf < raiz_cpf->info->cpf)
        buscar(raiz_cpf->esq, cpf);
    else
        buscar(raiz_cpf->dir, cpf);
}

// Pesquisa por nome
No *buscar(No *raiz_nome, string nome)
{
    if (raiz_nome == nullptr)
    {
        cout << "Nome nao encontrado!" << endl;
        return nullptr;
    }

    if (nome == raiz_nome->info->nome)
    {
        cout << "Nome encontrado!" << endl;
        return raiz_nome;
    }
    else if (nome < raiz_nome->info->nome)
        buscar(raiz_nome->esq, nome);
    else
        buscar(raiz_nome->dir, nome);
}

// Insere em uma unica arvore
No *inserir_cpf(No *&raiz_cpf, Info *info)
{
    if (raiz_cpf == nullptr)
    {
        No *no = new No;
        no->info = info;
        no->esq = nullptr;
        no->dir = nullptr;

        raiz_cpf = no;

        return no;
    }

    if (raiz_cpf->info->cpf == info->cpf)
    {
        cout << "CPF duplicado!" << endl;
        return nullptr;
    }
    else if (info->cpf < raiz_cpf->info->cpf)
    {
        inserir_cpf(raiz_cpf->esq, info);
    }
    else
    {
        inserir_cpf(raiz_cpf->dir, info);
    }
}

// Insere em uma unica arvore
No *inserir_nome(No *&raiz_nome, Info *info)
{
    if (raiz_nome == nullptr)
    {

        No *no = new No;
        no->info = info;
        no->esq = nullptr;
        no->dir = nullptr;

        raiz_nome = no;

        return no;
    }

    if (raiz_nome->info->nome == info->nome)
    {
        cout << "Nome duplicado!" << endl;
        return nullptr;
    }
    else if (info->nome < raiz_nome->info->nome)
    {
        inserir_nome(raiz_nome->esq, info);
    }
    else
    {
        inserir_nome(raiz_nome->dir, info);
    }
}

// Retirar de uma unica arvore
No *retirar_cpf(No *&raiz_cpf, long int cpf)
{
    if (raiz_cpf == nullptr)
        return nullptr;

    if (raiz_cpf->info->cpf == cpf)
    {
        delete raiz_cpf->info;
        raiz_cpf->info = nullptr;
        if (raiz_cpf->esq == nullptr && raiz_cpf->dir == nullptr)
        {
            cout << "A";
            return nullptr;
        }
        if (raiz_cpf->esq != nullptr && raiz_cpf->dir == nullptr)
        {
            cout << "B";
            return raiz_cpf->esq;
        }
        if (raiz_cpf->esq == nullptr && raiz_cpf->dir != nullptr)
        {
            cout << "C";
            return raiz_cpf->dir;
        }
        long int aux_cpf;
        Info *aux_info;
        cout << "A" << aux_cpf;
        cout << "V" << aux_info;
        buscar_maior_cpf(raiz_cpf->esq, aux_info);
        cout << "A" << aux_cpf;
        cout << "V" << aux_info;

        raiz_cpf->info = aux_info;
        raiz_cpf->esq = retirar_cpf(raiz_cpf->esq, aux_cpf);
        return raiz_cpf;
    }

    if (cpf < raiz_cpf->info->cpf)
        raiz_cpf->esq = retirar_cpf(raiz_cpf->esq, cpf);
    else
        raiz_cpf->dir = retirar_cpf(raiz_cpf->dir, cpf);
    return raiz_cpf;
}

// Caminhamento Infixado
void listar_cpf(No *&raiz_cpf)
{
    // In => Esq, Raiz, Dir
    if (raiz_cpf == nullptr) // Se esse no não existir sai da função
        return;

    listar_cpf(raiz_cpf->esq); // Na raiz atual, vai para a esquerda
    cout << raiz_cpf->info->cpf << "\t" << raiz_cpf->info->nome << "\t" << raiz_cpf->info->profissao << endl;
    listar_cpf(raiz_cpf->dir); // Na raiz atual, vai para a direita
}

// Caminhamento Infixado
void listar_nome(No *&raiz_nome)
{
    // In => Esq, Raiz, Dir
    if (raiz_nome == nullptr) // Se esse no não existir sai da função
        return;

    cout << raiz_nome->info->cpf << "\t" << raiz_nome->info->nome << "\t" << raiz_nome->info->profissao << endl;
    listar_nome(raiz_nome->esq); // Na raiz atual, vai para a esquerda
    listar_nome(raiz_nome->dir); // Na raiz atual, vai para a direita
}

#pragma endregion FUNCOES

#pragma region PSEUDO_FUNCOES
void inserir(Arvore &arvore_cpf, Arvore &arvore_nome, Info *info) // Pseudo-funcao para passar uma Arvore ao inves de um No
{
    No *no_cpf = inserir_cpf(arvore_cpf.raiz, info);
    if (no_cpf != nullptr)
        inserir_nome(arvore_nome.raiz, info);
}

void retirar(Arvore &arvore, int chave) // Pseudo-funcao para passar uma Arvore ao inves de um No
{
    retirar_cpf(arvore.raiz, chave);
}

void listar_info(Arvore &arvore_cpf, Arvore &arvore_nome, int operacao)
{
    cout << "CPF\t"
         << "Nome\t"
         << "Profissao\t" << endl;

    if (operacao == 1)
    {
        listar_cpf(arvore_cpf.raiz);
    }
    else if (operacao == 2)
    {
        listar_nome(arvore_nome.raiz);
    }
}
#pragma endregion PSEUDO_FUNCOES

int main()
{
    // PS: As 2 arvores sempre terao a mesma qtd de nos, mas a ordenação e altura dos nos serao diferentes
    Arvore arvore_cpf, arvore_nome;

    Info *info = new Info;
    info->cpf = 4;
    info->nome = "a";
    info->profissao = "a";

    inserir(arvore_cpf, arvore_nome, info);

    Info *info_2 = new Info;
    info_2->cpf = 3;
    info_2->nome = "B";
    info_2->profissao = "a";

    inserir(arvore_cpf, arvore_nome, info_2);

    Info *info_3 = new Info;
    info_3->cpf = 2;
    info_3->nome = "c";
    info_3->profissao = "a";

    inserir(arvore_cpf, arvore_nome, info_3);

    Info *info_4 = new Info;
    info_4->cpf = 1;
    info_4->nome = "d";
    info_4->profissao = "a";

    inserir(arvore_cpf, arvore_nome, info_4);

    retirar(arvore_cpf, 4);

    buscar(arvore_cpf.raiz, 4);
    // buscar(arvore_cpf.raiz, 2);
    // buscar(arvore_cpf.raiz, 3);
    // buscar(arvore_cpf.raiz, 4);
    // buscar(arvore_cpf.raiz, 5);

    // buscar(arvore_nome.raiz, "a");
    // buscar(arvore_nome.raiz, "B");
    // buscar(arvore_nome.raiz, "c");
    // buscar(arvore_nome.raiz, "d");
    // buscar(arvore_nome.raiz, "z");

    // listar_info(arvore_cpf, arvore_nome, 1);
    // listar_info(arvore_cpf, arvore_nome, 2);

    delete info;
    delete info_2;
    delete info_3;
    delete info_4;

    return 0;
}