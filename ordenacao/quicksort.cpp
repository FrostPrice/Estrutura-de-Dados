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

int main()
{
    int TAM = 10;
    int vetor[TAM];

    preencher(vetor, TAM);

    mostrar(vetor, TAM);

    cout << endl;

    quicksort(vetor, 0, TAM);

    mostrar(vetor, TAM);

    return 0;
}
