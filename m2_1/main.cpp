/*
Alunos:
    - Matheus de Oliveira Rocha
    - Mateus Barbosa
*/

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
    int altura;
    No *esq = nullptr, *dir = nullptr;
};

struct Arvore
{
    No *raiz = nullptr;
};
#pragma endregion ESTRUTURAS

#pragma region HELPERS
// Interface para implementar a funcao para pegar um valor da Struct dinamicamente
template <typename T>
T get_struct_campo(Info *info, string nome_do_campo);

// Implementacao para pegar o valor de um campo da struct do tipo long int
template <>
long int get_struct_campo<long int>(Info *info, string nome_do_campo)
{
    if (nome_do_campo == "cpf")
        return info->cpf;
    else // retorna um valor padrao, caso nao tenha o campo
        return 0;
}

// Implementacao para pegar o valor de um campo da struct do tipo string
template <>
string get_struct_campo<string>(Info *info, string nome_do_campo)
{
    if (nome_do_campo == "nome")
        return info->nome;
    else // retorna um valor padrao, caso nao tenha o campo
        return "";
}
#pragma endregion HELPERS

#pragma region AVL
int get_altura(No *raiz)
{
    return (raiz == nullptr) ? 0 : raiz->altura;
}

void buscar_maior(No *raiz, Info *&info)
{
    if (raiz == nullptr)
        return;

    if (raiz->dir != nullptr)
    {
        buscar_maior(raiz->dir, info);
    }
    else
    {
        info = raiz->info;
    }
}

int calcular_altura(No *raiz)
{
    int alt_e = get_altura(raiz->esq);
    int alt_d = get_altura(raiz->dir);
    return (alt_e > alt_d) ? alt_e + 1 : alt_d + 1;
}

No *rotacao_simples_direita(No *k)
{
    No *x = k->esq;
    No *t2 = x->dir;

    x->dir = k;
    k->esq = t2;
    k->altura = calcular_altura(k);
    x->altura = calcular_altura(x);
    return x;
}

No *rotacao_dupla_direita(No *k)
{
    No *x = k->esq;
    No *w = x->dir;
    No *t2 = w->esq;
    No *t3 = w->dir;

    w->esq = x;
    w->dir = k;
    x->dir = t2;
    k->esq = t3;

    x->altura = calcular_altura(x);
    k->altura = calcular_altura(k);
    w->altura = calcular_altura(w);

    return w;
}

No *rotacao_simples_esquerda(No *k)
{
    No *y = k->dir;
    No *t2 = y->esq;

    y->esq = k;
    k->dir = t2;
    k->altura = calcular_altura(k);
    y->altura = calcular_altura(y);
    return y;
}

No *rotacao_dupla_esquerda(No *k)
{
    No *y = k->dir;
    No *z = y->esq;
    No *t2 = z->esq;
    No *t3 = z->dir;

    z->esq = k;
    z->dir = y;
    k->dir = t2;
    y->esq = t3;
    k->altura = calcular_altura(k);
    y->altura = calcular_altura(y);
    z->altura = calcular_altura(z);
    return z;
}

No *rotacao_avl(No *k)
{
    if (get_altura(k->esq) > get_altura(k->dir))
    { // Rotação a direita
        No *x = k->esq;
        if (get_altura(x->dir) > get_altura(x->esq))
            return rotacao_dupla_direita(k);
        else
            return rotacao_simples_direita(k);
    }
    else
    { // Rotação a esquerda
        No *y = k->dir;
        if (get_altura(y->esq) > get_altura(y->dir))
            return rotacao_dupla_esquerda(k);
        else
            return rotacao_simples_esquerda(k);
    }
}
#pragma endregion AVL

#pragma region TADS
template <typename T>
No *buscar(No *raiz, T chave, string nome_do_campo)
{
    if (raiz == nullptr)
        return nullptr;

    if (chave == get_struct_campo<T>(raiz->info, nome_do_campo))
        return raiz;

    if (chave < get_struct_campo<T>(raiz->info, nome_do_campo))
        return buscar<T>(raiz->esq, chave, nome_do_campo);
    else
        return buscar<T>(raiz->dir, chave, nome_do_campo);
}

template <typename T>
No *inserir(No *&raiz, T chave, string nome_do_campo, Info *info)
{
    if (raiz == nullptr)
    {
        raiz = new No;
        raiz->info = info;
        raiz->altura = 1;
        return raiz;
    }

    if (chave == get_struct_campo<T>(raiz->info, nome_do_campo))
    {
        cout << "+-------------------------+" << endl;
        cout << "| Warning: " << nome_do_campo << " Duplicado!" << endl;
        cout << "+-------------------------+" << endl;
        return nullptr;
    }
    else if (chave < get_struct_campo<T>(raiz->info, nome_do_campo))
        raiz->esq = inserir<T>(raiz->esq, chave, nome_do_campo, info);
    else
        raiz->dir = inserir<T>(raiz->dir, chave, nome_do_campo, info);

    // Controle da Altura
    int alt_e = get_altura(raiz->esq);
    int alt_d = get_altura(raiz->dir);
    if (alt_e - alt_d == 2 || alt_e - alt_d == -2)
        raiz = rotacao_avl(raiz);
    else
        raiz->altura = (alt_e > alt_d) ? alt_e + 1 : alt_d + 1;

    return raiz;
}

template <typename T>
No *retirar(No *&raiz, T chave, string nome_do_campo, Info *&info) // O info será usado para armazena o endereço da info do no retirado
{
    if (raiz == nullptr)
        return nullptr;

    if (chave == get_struct_campo<T>(raiz->info, nome_do_campo))
    {
        info = raiz->info; // Armazena a Info atual, para ser usada posterioremente
        raiz->info == nullptr;
        if (raiz->esq == nullptr && raiz->dir == nullptr)
            return nullptr;

        if (raiz->esq != nullptr && raiz->dir == nullptr)
            return raiz->esq;

        if (raiz->esq == nullptr && raiz->dir != nullptr)
            return raiz->dir;

        Info *aux_info;
        buscar_maior(raiz->esq, aux_info);
        raiz->info = aux_info;
        raiz->esq = retirar<T>(raiz->esq, get_struct_campo<T>(aux_info, nome_do_campo), nome_do_campo, aux_info); // O aux_info dessa funcao nao tem utilidade

        // Controle de altura
        int alt_e = get_altura(raiz->esq);
        int alt_d = get_altura(raiz->dir);
        if (alt_e - alt_d == 2 || alt_e - alt_d == -2)
            raiz = rotacao_avl(raiz);
        else
            raiz->altura = (alt_e > alt_d) ? alt_e + 1 : alt_d + 1;

        return raiz;
    }

    if (chave < get_struct_campo<T>(raiz->info, nome_do_campo))
        raiz->esq = retirar<T>(raiz->esq, chave, nome_do_campo, info);
    else
        raiz->dir = retirar<T>(raiz->dir, chave, nome_do_campo, info);

    // Controle de altura
    int alt_e = get_altura(raiz->esq);
    int alt_d = get_altura(raiz->dir);
    if (alt_e - alt_d == 2 || alt_e - alt_d == -2)
        raiz = rotacao_avl(raiz);
    else
        raiz->altura = (alt_e > alt_d) ? alt_e + 1 : alt_d + 1;

    return raiz;
}

// Caminhamento Infixado
void listar(No *&raiz)
{
    // In => Esq, Raiz, Dir
    if (raiz == nullptr) // Se esse no não existir sai da função
        return;

    listar(raiz->esq); // Na raiz atual, vai para a esquerda
    cout << raiz->info->cpf << "\t" << raiz->info->nome << "\t" << raiz->info->profissao << endl;
    listar(raiz->dir); // Na raiz atual, vai para a direita
}

void deletar(No *&raiz, bool deletar_info = false)
{
    if (raiz != nullptr)
    {
        deletar(raiz->esq, deletar_info);
        deletar(raiz->dir, deletar_info);
        if (deletar_info) // Se a info ainda existir na memoria, apaga ela
        {
            delete raiz->info;
        }
        raiz->info = nullptr;
        delete raiz;
        raiz = nullptr;
    }
}
#pragma endregion TADS

#pragma region PSEUDO_FUNCOES
void inserir(Arvore &arvore_cpf, Arvore &arvore_nome, Info *info) // Pseudo-funcao para passar uma Arvore ao inves de um No
{
    if (inserir<long int>(arvore_cpf.raiz, info->cpf, "cpf", info) != nullptr)
    {
        inserir<string>(arvore_nome.raiz, info->nome, "nome", info);
    };
}

void retirar(Arvore &arvore_cpf, Arvore &arvore_nome, long int chave) // Retira por CPF
{
    No *no = buscar<long int>(arvore_cpf.raiz, chave, "cpf");
    if (no != nullptr) // Verifica se o CPF informado se encontra na arvore
    {
        Info *info = nullptr;
        arvore_cpf.raiz = retirar<long int>(arvore_cpf.raiz, chave, "cpf", info);
        arvore_nome.raiz = retirar<string>(arvore_nome.raiz, info->nome, "nome", info);
        delete info; // Deleta da memoria o valor qua info aponta
        info = nullptr;
    }
    else
    {
        cout << "+-------------------------+" << endl;
        cout << "| CPF nao encontrado!\n";
        cout << "+-------------------------+" << endl;

        return;
    }
}

void retirar(Arvore &arvore_cpf, Arvore &arvore_nome, string chave) // Retira por Nome
{
    No *no = buscar<string>(arvore_nome.raiz, chave, "nome");
    if (no != nullptr) // Verifica se o Nome informado se encontra na arvore
    {
        Info *info = nullptr;
        arvore_nome.raiz = retirar<string>(arvore_nome.raiz, chave, "nome", info);
        arvore_cpf.raiz = retirar<long int>(arvore_cpf.raiz, info->cpf, "cpf", info);
        delete info; // Deleta da memoria o valor qua info aponta
        info = nullptr;
    }
    else
    {
        cout << "+-------------------------+" << endl;
        cout << "| Nome nao encontrado!\n";
        cout << "+-------------------------+" << endl;

        return;
    }
}

void listar(Arvore &arvore_cpf, Arvore &arvore_nome, int operacao)
{
    cout << "+-----------------------------------+\n"
         << "CPF\t"
         << "Nome\t"
         << "Profissao\t" << endl;

    if (operacao == 1)
    {
        listar(arvore_cpf.raiz);
    }
    else if (operacao == 2)
    {
        listar(arvore_nome.raiz);
    }
    cout << "+-----------------------------------+\n";
}

void deletar(Arvore &arvore_cpf, Arvore &arvore_nome)
{
    deletar(arvore_cpf.raiz, true);
    deletar(arvore_nome.raiz);
}
#pragma endregion PSEUDO_FUNCOES

int main()
{
    // PS: As 2 arvores sempre terao a mesma qtd de nos, mas a ordenação e altura dos nos serao diferentes
    Arvore arvore_cpf, arvore_nome;

    int input_opcao;
    long int cpf;
    string nome, profissao;

    do
    {
        system("cls || clear");
        cout
            << "+-------------------------+\n"
            << endl;
        cout << "Pleno - Sistema para RH\n"
             << endl;
        cout << "+-------------------------+"
             << endl;
        cout << "1. Inserir" << endl;
        cout << "2. Remover por CPF" << endl;
        cout << "3. Remover por Nome" << endl;
        cout << "4. Pesquisar por CPF" << endl;
        cout << "5. Pesquisar por Nome" << endl;
        cout << "6. Listar ordenado por CPF" << endl;
        cout << "7. Listar ordenado por Nome" << endl;
        cout << "8. Sair" << endl;
        cout << "+-------------------------+" << endl;
        cout << "Opcao: ";
        cin >> input_opcao;

        if (input_opcao == 1)
        {
            Info *info = new Info;
            cout << "Digite o CPF: ";
            cin >> cpf;
            cout << "Digite o nome: ";
            cin.ignore();
            getline(cin, nome);
            cout << "Digite a profissao: ";
            getline(cin, profissao);
            info->cpf = cpf;
            info->nome = nome;
            info->profissao = profissao;
            inserir(arvore_cpf, arvore_nome, info);

            cout << "Precione Enter tecla para continuar..." << endl;
            cin.get();
        }
        else if (input_opcao == 2)
        {
            cout << "Digite o CPF: ";
            cin >> cpf;
            retirar(arvore_cpf, arvore_nome, cpf);

            cout << "Precione Enter tecla para continuar..." << endl;
            cin.ignore();
            cin.get();
        }
        else if (input_opcao == 3)
        {
            cout << "Digite o nome: ";
            cin.ignore();
            getline(cin, nome);
            retirar(arvore_cpf, arvore_nome, nome);

            cout << "Precione Enter tecla para continuar..." << endl;
            cin.get();
        }
        else if (input_opcao == 4)
        {
            cout << "Digite o CPF: ";
            cin >> cpf;
            if (buscar<long int>(arvore_cpf.raiz, cpf, "cpf") != nullptr)
                cout << "CPF encontrado!\n";
            else
                cout << "CPF nao encontrado!\n";

            cout << "Precione Enter tecla para continuar..." << endl;
            cin.ignore();
            cin.get();
        }
        else if (input_opcao == 5)
        {
            cout << "Digite o nome: ";
            cin.ignore();
            getline(cin, nome);
            if (buscar<string>(arvore_nome.raiz, nome, "nome") != nullptr)
            {
                cout << "+-------------------------+" << endl;
                cout << "| Nome encontrado!\n";
                cout << "+-------------------------+" << endl;
            }
            else
            {
                cout << "+-------------------------+" << endl;
                cout << "| Nome nao encontrado!\n";
                cout << "+-------------------------+" << endl;
            }

            cout << "Precione Enter tecla para continuar..." << endl;
            cin.get();
        }
        else if (input_opcao == 6)
        {
            cout << "Valores ordenados por CPF:" << endl
                 << endl;
            listar(arvore_nome, arvore_cpf, 1);

            cout << "Precione Enter tecla para continuar..." << endl;
            cin.ignore();
            cin.get();
        }
        else if (input_opcao == 7)
        {
            cout << "Valores ordenados por Nome:" << endl
                 << endl;
            listar(arvore_nome, arvore_cpf, 2);

            cout << "Precione Enter tecla para continuar..." << endl;
            cin.ignore();
            cin.get();
        }
        else if (input_opcao == 8)
        {
            cout << "Saindo..." << endl;
            deletar(arvore_cpf, arvore_nome);
        }
        else
        {
            cout << "Opcao invalida!" << endl;
            cout << "Precione Enter tecla para continuar..." << endl;
            cin.ignore();
            cin.get();
        }

    } while (input_opcao != 8);

    return 0;
}