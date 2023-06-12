using namespace std;

#include <iostream>
#include <math.h>
#include <iomanip>
#include <string>
#include <chrono>
#include <vector>

#pragma region ORDENACAO
void shell(int vetor[], int tam)
{
    int chave, i;
    for (int j = 1; j < tam; j++)
    {
        chave = vetor[j];
        i = j - 1;
        while (i >= 0 && vetor[i] > chave)
        {
            vetor[i + 1] = vetor[i];
            i--;
        }
        vetor[i + 1] = chave;
    }
}

void shellsort(int vetor[], int inicio, int salto, int tam)
{
    int j, k, temp;
    bool achei;

    for (int i = (inicio + salto); i < sizeof(vetor) / sizeof(int); i += salto)
    {
        j = inicio;
        achei = false;
        while (j < i && !achei)
        {
            if (vetor[i] < vetor[j])
                achei = true;
            else
                j = j + salto;
        }
        if (achei)
        {
            temp = vetor[i];
            k = i - salto;
            while (k > (j - salto))
            {
                vetor[k + salto] = vetor[k];
                k = k - salto;
            }
            vetor[j] = temp;
        }
    }
}

void shellsort(int vetor[], int np, int tam)
{
    int inc;

    for (int i = np; i >= 0; i--)
    {
        inc = pow(2, i);
        for (int j = 0; j < inc; j++)
        {
            shellsort(vetor, j, inc, tam);
        }
    }
}

void bubble(int vetor[], int tam)
{
    bool troca = true;
    int limite = tam - 1, aux, k;

    while (troca)
    {
        troca = false;

        for (int i = 0; i < limite; i++)
        {
            if (vetor[i] > vetor[i + 1])
            {
                aux = vetor[i];
                vetor[i] = vetor[i + 1];
                vetor[i + 1] = aux;
                k = i;
                troca = true;
            }
        }
        limite = k;
    }
}

void quicksort(int vetor[], int esq, int dir)
{
    int x, i, j, aux;
    i = esq;
    j = dir;
    x = vetor[(i + j) / 2];
    do
    {
        while (x > vetor[i])
            i = i + 1;

        while (x < vetor[j])
            j = j - 1;

        if (i <= j)
        {
            aux = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = aux;
            i = i + 1;
            j = j - 1;
        }
    } while (i <= j);
    if (esq < j)
        quicksort(vetor, esq, j);
    if (dir > i)
        quicksort(vetor, i, dir);
}

void selectionsort(int vetor[], int tam)
{
    int pos_menor, temp;
    for (int i = 0; i < tam; i++)
    {
        pos_menor = i;
        for (int j = i + 1; j < tam; j++)
            if (vetor[j] < vetor[pos_menor])
                pos_menor = j;
        temp = vetor[i];
        vetor[i] = vetor[pos_menor];
        vetor[pos_menor] = temp;
    }
}

void merge(int vetor[], int comeco, int meio, int fim)
{
    int com1 = comeco, com2 = meio + 1, comAux = 0, tam = fim - comeco + 1;
    int *vetAux = new int[tam];

    while (com1 <= meio && com2 <= fim)
    {
        if (vetor[com1] < vetor[com2])
        {
            vetAux[comAux] = vetor[com1];
            com1++;
        }
        else
        {
            vetAux[comAux] = vetor[com2];
            com2++;
        }
        comAux++;
    }

    while (com1 <= meio)
    {
        vetAux[comAux] = vetor[com1];
        comAux++;
        com1++;
    }

    while (com2 <= fim)
    {
        vetAux[comAux] = vetor[com2];
        comAux++;
        com2++;
    }

    for (comAux = comeco; comAux <= fim; comAux++)
    {
        vetor[comAux] = vetAux[comAux - comeco];
    }

    delete[] vetAux;
}

void mergesort(int vetor[], int inicio, int fim)
{
    if (inicio == fim)
        return;

    int meio = (inicio + fim) / 2;
    mergesort(vetor, inicio, meio);
    mergesort(vetor, meio + 1, fim);
    merge(vetor, inicio, meio, fim);
}
#pragma endregion ORDENACAO

void preencher_aleatorio(vector<int> &vetor, int tam) // Preenche somente um vetor
{
    for (int i = 0; i < tam; i++)
        vetor[i] = rand() % tam;
}

void preencher(vector<vector<int>> &matriz, int qtd_vetores, int qtd_elementos) // Preenche a matriz
{
    srand(time(NULL));

    for (int i = 0; i < qtd_elementos; i++)
    {
        matriz[0][i] = i;                       // Vetor ja ordenado
        matriz[1][i] = (qtd_elementos - 1) - i; // Vetor invertido
    }

    for (int i = 2; i < qtd_vetores; i++)
    {
        cout << "Randomizando vetor " << i << " ...\n";
        preencher_aleatorio(matriz[i], qtd_elementos);
    }
}

void mostrar(int *vetor, int tam, string rotulo) // Mostra somente um vetor
{
    if (vetor == nullptr)
    {
        cout << "Vetor nao foi criado\n";
        return;
    }

    cout << rotulo << ":\t";
    int espaco_entre_elementos = to_string(tam).length() + 1;
    for (int i = 0; i < tam; i++)
        cout << setw(espaco_entre_elementos) << vetor[i];
}

void mostrar(int **matriz, int qtd_vetores, int qtd_elementos) // Mostra a matriz
{
    if (matriz == nullptr)
    {
        cout << "Matriz nao foi criado\n";
        return;
    }

    for (int i = 0; i < qtd_vetores; i++)
    {
        mostrar(matriz[i], qtd_elementos, "Vetor " + to_string(i));
        cout << endl;
    }
    cout << endl;
}

void deletar(vector<vector<int>> matriz, int qtd_vetores)
{
    matriz.clear(); // Limpa o vetor
}

// TODO: Exportar para .csv

// TODO: Realizar ordenacoes
// TODO: Padronizar assinaturas das funcoes de ordenacao
void ordenar(double **resultados, int **matriz, int qtd_vetores, int qtd_elementos, int numero_execucoes)
{
    for (int i = 0; i < numero_execucoes; i++)
    {
        chrono::high_resolution_clock::time_point inicio = chrono::high_resolution_clock::now();

        // Algoritmo de ordenacao

        chrono::high_resolution_clock::time_point fim = chrono::high_resolution_clock::now();
        chrono::duration<double> duracao = chrono::duration_cast<std::chrono::duration<double>>(fim - inicio);
        cout << fixed << setprecision(9) << duracao.count() << endl;
    }
}

// Menu
void menu()
{
    int input_opcao, qtd_vetores, qtd_elementos, numero_execucao;
    vector<vector<int>> matriz(3); // PS: Tera no minimio 3 vetores (um ordenado, um invertido e um aleatório)
    double **resultados = nullptr;

    do
    {
        system("cls || clear"); // Limpa o terminal no windows ou linux
        cout << "+-------------------------+\n"
             << endl;
        cout << "Comparando Algoritimos de Ordenacao\n"
             << endl;
        cout << "+-------------------------+"
             << endl;
        cout << "1. Iniciar" << endl;
        cout << "2. Sair" << endl;
        cout << "+-------------------------+" << endl;
        cout << "Opcao: ";
        cin >> input_opcao;

        if (input_opcao == 1)
        {
            deletar(matriz, qtd_vetores); // Remove qualquer lixo de memória existente dessa matriz

            do
            {
                cout << "Digite a quantidade de vetores [3-" << __INT_MAX__ << "]: ";
                cin >> qtd_vetores;
            } while (qtd_vetores < 3 || qtd_elementos > __INT_MAX__);

            do
            {
                cout << "Digite a quantidade de elementos nos vetores [5-" << __INT_MAX__ << "]: ";
                cin >> qtd_elementos;
            } while (qtd_elementos < 5 || qtd_elementos > __INT_MAX__);

            do
            {
                cout << "Digite o numero de execucoes dos algoritmos [1-" << __INT_MAX__ << "]: ";
                cin >> numero_execucao;
            } while (numero_execucao < 1 || numero_execucao > __INT_MAX__);

            preencher(matriz, qtd_vetores, qtd_elementos);

            // ordenar(resultados, matriz, qtd_vetores, qtd_elementos, numero_execucao);

            cin.ignore();
            cout << "Precione Enter tecla para continuar..." << endl;
            cin.get();
        }
        else if (input_opcao == 2)
        {
            cout << "Saindo..." << endl;
            deletar(matriz, qtd_vetores);
        }
        else
        {
            cout << "Opcao invalida!" << endl;
            cout << "Precione Enter tecla para continuar..." << endl;
            cin.ignore();
            cin.get();
        }
    } while (input_opcao != 2);
}

int main()
{
    menu();

    return 0;
}
