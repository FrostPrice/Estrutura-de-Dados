using namespace std;

#include <iostream>
#include <math.h>
#include <iomanip>
#include <string>
#include <chrono>
#include <vector>
#include <functional>
#include <iostream>
#include <fstream>

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

    for (int i = (inicio + salto); i < tam; i += salto)
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

#pragma region PSEUDO_ORDENACAO // Funcoes usadas para padronizar as assinaturas das funcoes
void shell(vector<int> vetor)
{
    shell(vetor.data(), vetor.size());
}

void shellsort(vector<int> vetor)
{
    shellsort(vetor.data(), 3, vetor.size());
}

void bubble(vector<int> vetor)
{
    bubble(vetor.data(), vetor.size());
}

void quicksort(vector<int> vetor)
{
    quicksort(vetor.data(), 0, vetor.size());
}

void selectionsort(vector<int> vetor)
{
    selectionsort(vetor.data(), vetor.size());
}

void mergesort(vector<int> vetor)
{
    mergesort(vetor.data(), 0, vetor.size() - 1);
}
#pragma endregion PSEUDO_ORDENACAO

void preencher_aleatorio(vector<int> &vetor, int tam) // Preenche somente um vetor
{
    for (int i = 0; i < tam; i++)
        vetor[i] = rand() % tam;
}

void preencher(vector<vector<int>> &matriz, int qtd_vetores, int qtd_elementos) // Preenche a matriz
{
    matriz.resize(qtd_vetores, vector<int>(qtd_elementos));

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

void mostrar(vector<int> vetor, string rotulo) // Mostra somente um vetor
{
    if (vetor.empty())
    {
        cout << "Vetor nao foi criado\n";
        return;
    }

    cout << rotulo << ":\t";
    int espaco_entre_elementos = to_string(vetor.size()).length() + 1;
    for (int i = 0; i < vetor.size(); i++)
        cout << setw(espaco_entre_elementos) << vetor[i];
}

void mostrar(vector<vector<int>> matriz) // Mostra a matriz
{
    if (matriz.empty())
    {
        cout << "Matriz nao foi criado\n";
        return;
    }

    for (int i = 0; i < matriz.size(); i++)
    {
        mostrar(matriz[i], "Vetor " + to_string(i));
        cout << endl;
    }
    cout << endl;
}

void deletar(vector<vector<int>> matriz, int qtd_vetores)
{
    matriz.clear(); // Limpa o vetor
}

void exportar_para_csv(string nome_do_arquivo, string cabecalho, vector<vector<double>> matriz)
{
    cout << "Exportando resultados para o arquivo: " << nome_do_arquivo << ".csv\n";

    ofstream arquivo("./resultados.csv");

    if (arquivo.is_open())
    {
        vector<string> nome_funcoes = {"Shell", "ShellSort", "Bubble", "QuickSort", "SelectionSort", "MergeSort"};

        arquivo << cabecalho << "\n";
        for (int i = 0; i < matriz.size(); i++)
        {
            arquivo << nome_funcoes[i] << ",";
            for (int j = 0; j < matriz[i].size(); j++)
            {
                arquivo << fixed << setprecision(15) << matriz[i][j]; // Escreve informacao no arquivo

                // Escreve separacao por virgula
                if (j < matriz[i].size() - 1)
                    arquivo << ",";
            }
            arquivo << "\n"; // Termina linha
        }
        arquivo.close();
    }
    else
    {
        cout << "Error: Nao foi possivel abrir o arquivo!\n";
    }
}

void ordenar(vector<vector<double>> &resultados, vector<vector<int>> matriz, int qtd_vetores, int qtd_elementos, int numero_execucoes)
{
    vector<string> nome_funcoes = {"Shell", "ShellSort", "Bubble", "QuickSort", "SelectionSort", "MergeSort"}; // Vetor usado somente para mostrar output para o usuario
    // Vetor contendo todas as funcoes de ordenacao usadas
    vector<function<void(vector<int>)>> funcoes = {
        [](vector<int> vetor)
        { shell(vetor); },
        [](vector<int> vetor)
        { shellsort(vetor); },
        [](vector<int> vetor)
        { bubble(vetor); },
        [](vector<int> vetor)
        { quicksort(vetor); },
        [](vector<int> vetor)
        { selectionsort(vetor); },
        [](vector<int> vetor)
        { mergesort(vetor); }};

    for (int f = 0; f < funcoes.size(); f++)
    {
        vector<double> resultado_funcao; // Tempo de execucao de todas as iteracoes da funcao atual
        for (int i = 0; i < numero_execucoes; i++)
        {
            for (int j = 0; j < matriz.size(); j++)
            {
                chrono::high_resolution_clock::time_point inicio = chrono::high_resolution_clock::now();

                // Algoritmo de ordenacao
                funcoes[f](matriz[j]);

                chrono::high_resolution_clock::time_point fim = chrono::high_resolution_clock::now();
                chrono::duration<double> duracao = chrono::duration_cast<std::chrono::duration<double>>(fim - inicio);
                resultado_funcao.push_back(duracao.count());
            }
        }

        double soma = 0;
        double melhor_caso = resultado_funcao[0];
        double pior_caso = resultado_funcao[0];
        for (int i = 0; i < resultado_funcao.size(); i++)
        {
            soma += resultado_funcao[i];

            if (resultado_funcao[i] < melhor_caso)
                melhor_caso = resultado_funcao[i];

            if (resultado_funcao[i] > pior_caso)
                pior_caso = resultado_funcao[i];
        }

        resultados[f][0] = melhor_caso;                             // Melhor caso
        resultados[f][1] = soma / numero_execucoes * matriz.size(); // Media dos casos
        resultados[f][2] = pior_caso;                               // Pior caso

        cout << nome_funcoes[f] << " - OK" << endl;
    }
}

// Menu
void menu()
{
    srand(time(NULL));

    int input_opcao, qtd_vetores, qtd_elementos, numero_execucao;
    vector<vector<int>> matriz; // PS: Tera no minimio 3 vetores (um ordenado, um invertido e um aleatório)
    vector<vector<double>> resultados(6, vector<double>(3));

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
            } while (qtd_vetores < 3 || qtd_vetores > __INT_MAX__);

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

            ordenar(resultados, matriz, qtd_vetores, qtd_elementos, numero_execucao);

            exportar_para_csv("resultados", "funcao,melhor_caso,media_dos_casos,pior_caso", resultados);

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
