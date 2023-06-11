using namespace std;

#include "iostream"

void preencher(int vetor[], int tam)
{
    srand(time(NULL));
    for (int i = 0; i < tam; i++)
    {
        vetor[i] = rand() % tam;
    }
}

void mostrar(int vetor[], int tam)
{
    cout << "Vetor: ";
    for (int i = 0; i < tam; i++)
    {
        cout << vetor[i] << " ";
    }
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

int main()
{
    int TAM = 10;
    int vetor[TAM];

    preencher(vetor, TAM);

    mostrar(vetor, TAM);

    cout << endl;

    selectionsort(vetor, TAM);

    mostrar(vetor, TAM);

    return 0;
}
