#include <iostream>
#include <bitset>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <ctime>
using namespace std;

const int maxIndividuos = 1000;

void gerarIndividuos(int individuos[maxIndividuos], int &a, int &b, int &c, int &d, int &e, int &f, int &quantidadeIndividuos, int &numeroDeGeracoes)
{
    while (true)
    {
        cout << "Seja bem vindo ao sistema de genética" << endl
             << "Por favor, digite quantas populações gostaria de gerar (10, 100 ou 1000): " << endl;
        cin >> quantidadeIndividuos;

        if ((quantidadeIndividuos != 1000) &&
            (quantidadeIndividuos != 100) &&
            (quantidadeIndividuos != 10))
        {
            cout << "Por favor, escolha uma das opções válidas" << endl;
            continue;
        }
        cout << "Quantas gerações vc deseja?" << endl;
        cin >> numeroDeGeracoes;

        cout << "Insira o valor de a: " << endl;
        cin >> a;
        if (a == 0)
        {
            cout << "O valor de a não pode ser 0" << endl;
            continue;
        }
        cout << "Insira o valor de b: " << endl;
        cin >> b;
        cout << "Insira o valor de c: " << endl;
        cin >> c;
        cout << "Insira o valor de d: " << endl;
        cin >> d;
        cout << "Insira o valor de e: " << endl;
        cin >> e;
        cout << "Insira o valor de f: " << endl;
        cin >> f;

        switch (quantidadeIndividuos)
        {
        case 10:
            cout << "Você escolheu a população de 10" << endl;
            break;
        case 100:
            cout << "Você escolheu a população de 100" << endl;
            break;
        case 1000:
            cout << "Você escolheu a população de 1000" << endl;
            break;
        }

        // Gera os individuos aletóriamente dentro do range de -2000 a 2000
        for (int i = 0; i < quantidadeIndividuos; i++)
        {
            individuos[i] = rand() % 2000;
        }
        break;
    }
}

void crossOver(int individuos[maxIndividuos])
{
    // individuos
}

long long int validar(int a, int b, int c, int d, int e, int f, int x)
{
    return (a * pow(x, 5)) + (b * pow(x, 4)) + (c * pow(x, 3)) + (d * pow(x, 2)) + (e * x) + f;
}

bitset<32> passibilidadeDeMutacao(bitset<32> conteudoBit)
{
    srand(time(0));

    int posicao = rand() % 32;

    // Lembrar de pular a mutação do último bit da posição 31 pq ele controla o sinal do número
    if (posicao != 31)
        conteudoBit.set(posicao, (rand() % 2) == 0);

    return conteudoBit;
}

void separacao(int individuos[maxIndividuos], int quantidadeIndividuos, int numeroDeGeracoes)
{
    int taxaDeSeparação = quantidadeIndividuos * 0.5 + 1;

    // Indivíduos antigos serão substituídos por novos
    for (int i = taxaDeSeparação; i < quantidadeIndividuos; i++)
    {
        individuos[i] = rand() % 2000;
    }
    cout << endl;
}

void validaSolucaoBoa(int individuos[maxIndividuos], int a, int b, int c, int d, int e, int f, int quantidadeIndividuos, int numeroDeGeracoes)
{
    long long int resultado;

    for (int geracaoAtual = 0; geracaoAtual < numeroDeGeracoes; geracaoAtual++)
    {
        for (int individuoAtual = 0; individuoAtual < quantidadeIndividuos; individuoAtual++)
        {
            resultado = validar(a, b, c, d, e, f, individuos[individuoAtual]);
            if (resultado == 0 || resultado == 1 || resultado == -1)
            {
                cout << "Valor do indivíduo: " << individuos[individuoAtual] << endl
                     << "Com o indivíduo: " << individuoAtual << endl
                     << "Na geração" << geracaoAtual + 1 << endl;
                exit(EXIT_SUCCESS);
            }
            else
            {
                separacao(individuos, quantidadeIndividuos, numeroDeGeracoes);
            }
        }
    }
}

int main()
{
    srand(time(0));
    int a, b, c, d, e, f;
    int quantidadeIndividuos = 1000, numeroDeGeracoes = 0;
    int individuos[maxIndividuos]; // Perguntar pro professor se tem problema colocar esse vetor num contexto global.

    gerarIndividuos(individuos, a, b, c, d, e, f, quantidadeIndividuos, numeroDeGeracoes);
    sort(individuos, individuos + quantidadeIndividuos); // Ordena os individuos em ordem crescente

    validaSolucaoBoa(individuos, a, b, c, d, e, f, quantidadeIndividuos, numeroDeGeracoes);

    return 0;
}