using namespace std;

#include "iostream"

#define TAM 50

struct Pilha
{
    int info[TAM];
    int topo;
};

#pragma region OPERACOES
/*
Operações:
1) Inicializar - OK
2) Inserir - OK
3) Retirar - OK
*/
void inicializar(Pilha &pilha)
{
    pilha.topo = -1;
}

bool inserir(Pilha &pilha, int valor)
{
    if (pilha.topo >= TAM - 1)
        return false;

    pilha.topo++;
    pilha.info[pilha.topo] = valor;
    // pilha.info[++pilha.topo] = valor;
    return true;
}

bool retirar(Pilha &pilha, int &valor)
{
    if (pilha.topo < 0)
        return false;

    valor = pilha.info[pilha.topo];
    pilha.topo--;
    // valor = pilha.info[pilha.topo--];
    return true;
}

#pragma endregion OPERACOES

void juntar_pilhas(Pilha pilha_1, Pilha pilha_2, Pilha &pilha_3)
{
    bool flag_pilha_1, flag_pilha_2;
    int num_1, num_2;

    inicializar(pilha_3);
    flag_pilha_1 = retirar(pilha_1, num_1);
    flag_pilha_2 = retirar(pilha_2, num_2);

    while (flag_pilha_1 || flag_pilha_2)
    {
        if (flag_pilha_1 && !flag_pilha_2)
        { // Conseguiu da pilha_1 e não da pilha_2
            inserir(pilha_3, num_1);
            flag_pilha_1 = retirar(pilha_1, num_1);
        }
        else
        {
            if (!flag_pilha_1 && flag_pilha_2)
            { // Não conseguiu da pilha_1 e conseguiu da pilha_2
                inserir(pilha_3, num_2);
                flag_pilha_2 = retirar(pilha_2, num_2);
            }
            else
            { // Conseguiu das duas
                if (num_1 < num_2)
                {
                    inserir(pilha_3, num_1);
                    flag_pilha_1 = retirar(pilha_1, num_1);
                }
                else
                {
                    inserir(pilha_3, num_2);
                    flag_pilha_2 = retirar(pilha_2, num_2);
                }
            }
        }
    }
}
int main()
{
    // 1. Duas pilhas sequenciais numéricas estão ordenadas crescentemente a partir do topo.Transferir os elementos dessas pilhas para uma terceira pilha, inicialmente vazia, de modo que ela fique ordenada decrescentemente com o maior valor no topo

    Pilha pilha_1, pilha_2, pilha_3;
    int aux;
    inicializar(pilha_1);

    inserir(pilha_1, 10);
    inserir(pilha_1, 7);
    inserir(pilha_1, 5);
    inserir(pilha_1, 3);
    inserir(pilha_1, 2);
    inserir(pilha_1, 1);
    inserir(pilha_1, 0);

    inicializar(pilha_2);
    inserir(pilha_2, 8);
    inserir(pilha_2, 6);
    inserir(pilha_2, 5);
    inserir(pilha_2, 4);
    inserir(pilha_2, 3);
    inserir(pilha_2, 2);

    juntar_pilhas(pilha_1, pilha_2, pilha_3);

    while (retirar(pilha_3, aux))
    {
        cout << aux << " ";
    };

    cout << endl;

    return 0;
}