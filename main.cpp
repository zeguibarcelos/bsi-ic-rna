#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Neuronio
{
public:
    vector<double> w;
    double gamma;

    Neuronio(vector<double> pesos, double g)
    {
        w = pesos;
        gamma = g;
    }

    int funcAtivacao(double v)
    {
        return (v > 0) ? 1 : -1;
    }

    double potencial(const vector<int> &x)
    {
        double v = 0.0;
        for (int i = 0; i < x.size(); i++)
        {
            v += w[i] * x[i];
        }
        return v;
    }

    int saida(const vector<int> &x)
    {
        return funcAtivacao(potencial(x));
    }

    double treinar(const vector<int> &x, int yd)
    {
        int y = saida(x);
        int e = yd - y;

        for (int i = 0; i < w.size(); i++)
        {
            w[i] = w[i] + gamma * e * x[i];
        }

        return pow(e, 2);
    }

    void imprimir()
    {
        for (double peso : w)
        {
            cout << peso << " ";
        }
        cout << endl;
    }
};

int main()
{
    double GAMMA = 0.05;
    Neuronio N1({1, 1, 1, 1, 1, 1, 1, 1}, GAMMA);
    Neuronio N2({-1, -1, -1, -1, -1, -1, -1, -1}, GAMMA);
    Neuronio N3({1, -1, 1, -1, 1, -1, 1, -1}, GAMMA);

    // Grupo de amostras Xi
    vector<vector<int>> X = {
        {1, 1, 1, 1, 1, -1, -1, -1},   // X1 => paciente com febre, coriza, dor de cabeça, dor de garganta
        {1, 1, -1, -1, -1, 1, 1, -1},  // X2 => paciente com febre, manchas no corpo e dor no corpo
        {1, 1, -1, -1, -1, -1, 1, 1},  // X3 => paciente com febre, dor no corpo e bolhas no corpo
        {1, -1, 1, 1, 1, -1, -1, -1},  // X4 => paciente com coriza, dor de cabeça e dor de garganta
        {1, -1, -1, -1, -1, 1, 1, -1}, // X5 => paciente com manchas no corpo e dor no corpo
        {1, -1, -1, -1, -1, -1, 1, 1}  // X6 => paciente com dor no corpo e bolhas no corpo
    };

    // Grupo de valores esperados para as amostras Xi
    vector<vector<int>> Yd = {
        {1, -1, -1}, // X1 => febre
        {-1, 1, -1}, // X2 => dengue
        {-1, -1, 1}, // X3 => catapora
        {1, -1, -1}, // X4 => febre
        {-1, 1, -1}, // X5 => dengue
        {-1, -1, 1}  // X6 => catapora
    };

    double erroEpoca = 10.0;
    int epoca = 0;

    while (erroEpoca > 0.001)
    {
        epoca++;

        double E1 = 0, E2 = 0, E3 = 0;

        for (int i = 0; i < 6; i++)
        {
            E1 += N1.treinar(X[i], Yd[i][0]);
            E2 += N2.treinar(X[i], Yd[i][1]);
            E3 += N3.treinar(X[i], Yd[i][2]);
        }

        erroEpoca = (E1 + E2 + E3) / 3.0;

        cout << "Epoca: " << epoca << " | Erro: " << erroEpoca << endl;
    }

    cout << "\nPesos finais:\n";
    cout << "W1: ";
    N1.imprimir();
    cout << "W2: ";
    N2.imprimir();
    cout << "W3: ";
    N3.imprimir();

    vector<int> Xteste = {1, 1, 1, -1, -1, -1, 1, -1}; // xTeste => paciente com febre, coriza e dor no corpo

    cout << "\nTeste com entrada nao utilizada no treinamento:\n";

    int y1 = N1.saida(Xteste);
    int y2 = N2.saida(Xteste);
    int y3 = N3.saida(Xteste);

    cout << "\nEntrada teste: ";
    for (int v : Xteste)
        cout << v << " ";

    cout << "\nSaida obtida:   ";
    cout << y1 << " " << y2 << " " << y3 << endl;

    return 0;
}
