/*
Alunos:
    - Mateus Barbosa
    - Matheus de Oliveira Rocha
*/

using namespace std;

#include <iostream>
#include <string>
#include <regex>
#include "lde_polinomios.h"

string remove_espacos(string str)
{
    string sem_espacos;
    for (char letra : str)
    {
        if (!isspace(letra))
        {
            sem_espacos += letra;
        }
    }

    return sem_espacos;
}

void solicita_input_polinomio(LDE &polinomio, string frase)
{
    string input_polinomio;

    do
    {
        cout << frase;
        getline(cin, input_polinomio, '\n');
    } while (input_polinomio.empty());
    input_polinomio = remove_espacos(input_polinomio);

    regex padrao_regex("(-?\\d*(\\.\\d+)?)?([a-zA-Z])\\^?(-?\\d+)?|(-?\\d+(\\.\\d+)?)");
    smatch valor_encontrado;

    while (regex_search(input_polinomio, valor_encontrado, padrao_regex))
    {
        string coeficiente = valor_encontrado[1].str();
        string letra = valor_encontrado[3].str();
        string expoente = valor_encontrado[4].str();
        string constante = valor_encontrado[5].str();

        if (!constante.empty())
            inserir_ordenado(polinomio, stof(constante), '\0', 0);
        else
        {
            if (coeficiente.empty())
                coeficiente = "1";
            else if (coeficiente == "-")
                coeficiente = "-1";

            if (expoente.empty())
                expoente = "1";

            inserir_ordenado(polinomio, stof(coeficiente), letra[0], stoi(expoente));
        }

        input_polinomio = valor_encontrado.suffix().str(); // Tenta encontrar a proxima string que entra no padrão regex
    }
}

int main()
{
    string menu = "//////////////////////////////////////////////////////////\n"
                  "//\t\t\tHP12C-no-rpn\t\t\t//\n"
                  "//\t\t\t\t\t\t\t//\n"
                  "//\t\t\t\t\t\t\t//\n"
                  "// Escolha a operação [1-6]\t\t\t\t//\n"
                  "// 1) Valor Numerico\t\t\t\t\t//\n"
                  "// 2) Somar Polinomios\t\t\t\t\t//\n"
                  "// 3) Subtrair Polonomios\t\t\t\t//\n"
                  "// 4) Multiplicacao Escalar\t\t\t\t//\n"
                  "// 5) Multiplicacao de Polinomios\t\t\t//\n"
                  "// 6) Sair\t\t\t\t\t\t//\n"
                  "//\t\t\t\t\t\t\t//\n"
                  "//////////////////////////////////////////////////////////\n";

    bool executando_aplicacao = true;
    while (executando_aplicacao)
    {
        system("cls || clear"); // LImpa o terminal no Windows ou Linux
        cout << menu;
        int input_usuario;
        do
        {
            cout << "Qual operacao deseja fazer? ";
            cin >> input_usuario;
        } while (input_usuario < 1 || input_usuario > 6);
        cin.ignore();

        if (input_usuario == 1)
        {
            LDE polinomio_1;
            float valor_real;

            inicializar(polinomio_1);

            solicita_input_polinomio(polinomio_1, "Digite um polinomio (Ex: 4x^2 + x^1 - 5): ");

            cout << "Digite o valor do coeficiente: ";
            cin >> valor_real;
            cin.ignore();
            cout << endl;
            cout << "Resultado: " << valor_numerico(polinomio_1, valor_real) << endl;
            cout << "Precione Enter tecla para continuar..." << endl;
            cin.get();
        }
        else if (input_usuario == 2)
        {
            LDE polinomio_1, polinomio_2;
            inicializar(polinomio_1);
            inicializar(polinomio_2);

            solicita_input_polinomio(polinomio_1, "Digite um polinomio (Ex: 4x^2 + x^1 - 5): ");
            solicita_input_polinomio(polinomio_2, "Digite outro polinomio (Ex: 4x^2 + x^1 - 5): ");

            mostrar_lista(somar_polinomios(polinomio_1, polinomio_2), "Resultado");
            cout << "Precione Enter tecla para continuar..." << endl;
            cin.get();
        }
        else if (input_usuario == 3)
        {
            LDE polinomio_1, polinomio_2;
            inicializar(polinomio_1);
            inicializar(polinomio_2);

            solicita_input_polinomio(polinomio_1, "Digite um polinomio (Ex: 4x^2 + x^1 - 5): ");
            solicita_input_polinomio(polinomio_2, "Digite outro polinomio (Ex: 4x^2 + x^1 - 5): ");

            mostrar_lista(subtrair_polinomios(polinomio_1, polinomio_2), "Resultado");
            cout << "Precione Enter tecla para continuar..." << endl;
            cin.get();
        }
        else if (input_usuario == 4)
        {
            LDE polinomio_1;
            inicializar(polinomio_1);
            float escalar_k;

            solicita_input_polinomio(polinomio_1, "Digite um polinomio (Ex: 4x^2 + x^1 - 5): ");

            cout << "Digite o valor para multiplicar os coeficientes: ";
            cin >> escalar_k;
            cin.ignore();
            cout << endl;
            mostrar_lista(multiplicacao_escalar(polinomio_1, escalar_k), "Resultado");
            cout << "Precione Enter tecla para continuar..." << endl;
            cin.get();
        }
        else if (input_usuario == 5)
        {
            LDE polinomio_1, polinomio_2;
            inicializar(polinomio_1);
            inicializar(polinomio_2);

            solicita_input_polinomio(polinomio_1, "Digite um polinomio (Ex: 4x^2 + x^1 - 5): ");
            solicita_input_polinomio(polinomio_2, "Digite outro polinomio (Ex: 4x^2 + x^1 - 5): ");

            mostrar_lista(multiplicacao_polinomios(polinomio_1, polinomio_2), "Resultado");
            cout << "Precione Enter tecla para continuar..." << endl;
            cin.get();
        }
        else if (input_usuario == 6)
        {
            executando_aplicacao = false;
            cout << "Saindo da aplicação...\n";
            return 0;
        }
    }
    return 0;
}