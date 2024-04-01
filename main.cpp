#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <ctime>
using namespace std;

const int maxIndividuos = 1000;

void gerarIndividuos(int individuos[maxIndividuos], int &a, int &b, int &c, int &d, int &e, int &f, int &quantidadeIndividuos, int &numeroDeGeracoes, int &taxaDeMutacao)
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

        cout << "Insira a taxa de mutação (0 a 100): " << endl;
        cin >> taxaDeMutacao;
        if (taxaDeMutacao > 100 || taxaDeMutacao < 0)
        {
            cout << "Por favor, insira um valor entre 0 e 100" << endl;
            continue;
        }

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

        // Gera os individuos aletóriamente dentro do range de -1000 a 1000
        for (int i = 0; i < quantidadeIndividuos; i++)
        {
            individuos[i] = rand() % 2001 - 1000;
        }
        break;
    }
}

void mutarIndividuo(int &individuo, int taxaDeMutacao)
{
    // Se eu mutar uma posicao muito significativa, demora pra encontrar o resultado
    int posicao = round(taxaDeMutacao * 16 / 100.0);
    int possibilidadeDeMutacao = (rand() % 2) == 0;

    int mascaraDeBits = possibilidadeDeMutacao << posicao;

    // Limpa o valor do bit na posição sorteada
    individuo = individuo & ~(1 << posicao);

    // Realiza a mutação
    individuo = individuo | mascaraDeBits;
}

void crossOver(int individuos[maxIndividuos], int quantidadeIndividuos, int taxaDeSeparacao, int taxaDeMutacao)
{
    for (int i = 0; i < quantidadeIndividuos; i++)
    {
        int taxaDeCrossOver = 0.5 * 32;
        int mascaraPrimeiroIndividuo[2] = {individuos[i], individuos[i]};
        int mascaraSegundoIndividuo[2] = {individuos[i + 1], individuos[i + 1]};

        int novoFilhoPrimeiroIndividuo;
        int novoFilhoSegundoIndividuo;

        // Bits da esquerda
        for (int i = 0; i < taxaDeCrossOver; i++)
        {
            mascaraPrimeiroIndividuo[0] = mascaraPrimeiroIndividuo[0] & ~(1 << i);
            mascaraSegundoIndividuo[0] = mascaraSegundoIndividuo[0] & ~(1 << i);
        }

        // Bits da direita
        for (int i = 16; i < 32; i++)
        {
            mascaraPrimeiroIndividuo[1] = mascaraPrimeiroIndividuo[1] & ~(1 << i);
            mascaraSegundoIndividuo[1] = mascaraSegundoIndividuo[1] & ~(1 << i);
        }

        // Realiza o Cross Over
        novoFilhoPrimeiroIndividuo = mascaraPrimeiroIndividuo[0] | mascaraSegundoIndividuo[1];
        novoFilhoSegundoIndividuo = mascaraSegundoIndividuo[0] | mascaraPrimeiroIndividuo[1];

        // Adiciona os novos filhos
        individuos[i + taxaDeSeparacao] = novoFilhoPrimeiroIndividuo;
        individuos[i + taxaDeSeparacao + 1] = novoFilhoSegundoIndividuo;
        if (i != 0)
            mutarIndividuo(individuos[i], taxaDeMutacao);
    }
}

void separacao(int individuos[maxIndividuos], int quantidadeIndividuos, int taxaDeMutacao)
{
    // esse + 1 é pro individuo[0] que se mantem através das gerações
    int taxaDeSeparacao = quantidadeIndividuos * 0.5 + 1;

    // Limpeza para novos individuos
    for (int i = taxaDeSeparacao; i < quantidadeIndividuos; i++)
    {
        individuos[i] = 0;
    }
    crossOver(individuos, quantidadeIndividuos, taxaDeSeparacao, taxaDeMutacao);
}

long long int validar(int a, int b, int c, int d, int e, int f, int x)
{
    return (a * pow(x, 5)) + (b * pow(x, 4)) + (c * pow(x, 3)) + (d * pow(x, 2)) + (e * x) + f;
}

void validaSolucaoBoa(int individuos[maxIndividuos], int a, int b, int c, int d, int e, int f, int quantidadeIndividuos, int numeroDeGeracoes, int taxaDeMutacao)
{
    long long int resultado;
    long long int resultadoMaisProximo = LLONG_MAX;
    int geracaoMaisProxima = 0;

    for (int geracaoAtual = 0; geracaoAtual < numeroDeGeracoes; geracaoAtual++)
    {
        for (int individuoAtual = 0; individuoAtual < quantidadeIndividuos; individuoAtual++)
        {
            resultado = abs(validar(a, b, c, d, e, f, individuos[individuoAtual]));
            if (resultado == 0)
            {
                cout << "\nO resultado foi encontrado!" << endl
                     << "Valor do indivíduo: " << individuos[individuoAtual] << endl
                     << "Com o indivíduo: " << individuoAtual << endl
                     << "Na geração: " << geracaoAtual + 1 << endl;
                exit(EXIT_SUCCESS);
            }

            // Garanto que o melhor resultado de cada geração seja sempre o primeiro individuo
            if (resultado < resultadoMaisProximo)
            {
                individuos[0] = individuos[individuoAtual];
                resultadoMaisProximo = resultado;
                geracaoMaisProxima = geracaoAtual + 1;
            }
        }

        if (geracaoAtual == numeroDeGeracoes - 1)
        {
            cout << "\nValor do indivíduo: " << individuos[0] << endl
                 << "Proximidade do resultado: " << resultadoMaisProximo << endl
                 << "Foi encontrado na geração: " << geracaoMaisProxima << endl;
            exit(EXIT_SUCCESS);
        }
        else
        {
            separacao(individuos, quantidadeIndividuos, taxaDeMutacao);
        }
    }
}

int main()
{
    srand(time(0));
    int a, b, c, d, e, f;
    int quantidadeIndividuos = 1000, numeroDeGeracoes = 0, taxaDeMutacao = 0;
    int individuos[maxIndividuos];

    gerarIndividuos(individuos, a, b, c, d, e, f, quantidadeIndividuos, numeroDeGeracoes, taxaDeMutacao);

    validaSolucaoBoa(individuos, a, b, c, d, e, f, quantidadeIndividuos, numeroDeGeracoes, taxaDeMutacao);

    return 0;
}

/*
CASOS DE USO:






*/