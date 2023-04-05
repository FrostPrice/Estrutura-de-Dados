using namespace std;

int mdc(int a, int b)
{
    if (a == b)
        return a;

    if (a >= b)
        return mdc(a - b, b);
    else
        return mdc(a, b - a);
}

int fibonacci(int pos)
{
    if (pos == 1 || pos == 2)
        return 0;

    return fibonacci(pos - 1) + fibonacci(pos - 2);
}

int produto(int a, int b)
{
    if (b == 1)
        return a;

    return produto(a, b - 1) + a;
}

int localiza_valor(int vetor[], int tam, int valor)
{
}

int main()
{
    return 0;
}