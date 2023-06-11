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

int main()
{

    const int TAM = 10;
    int vetor[TAM];

    preencher(vetor, TAM);

    mostrar(vetor, TAM);

    cout << endl;

    bubble(vetor, TAM);

    mostrar(vetor, TAM);

    return 0;
}
