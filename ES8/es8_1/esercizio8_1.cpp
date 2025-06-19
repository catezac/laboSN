#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>
#include "../funzioni.h"
#include "/home/catezac/laboSN/PRNG/random.h"

int main() {

    Random rnd;
    double step = SetParameter("../input.dat", "step");
    double mu = SetParameter("../input.dat", "mu_iniz");
    double sigma = SetParameter("../input.dat", "sigma_iniz");
    int M = SetParameter("../input.dat", "M");
    int M_equil = SetParameter("../input.dat", "M_equil");
    int N = SetParameter("../input.dat", "N");
    double L = M/N;
    double Hpsi;
    double x = 0.;
    double acceptance = 0.0;

    vector<double> ave(N);
    vector<double> av2(N);
    vector<double> err(N);
    
    // equilibrazione del metropolis
    equilibration(rnd, M_equil, x, mu, sigma, step, acceptance);
    cout << "accettanza con passo " << step << " : " << acceptance << endl;

    for(int i = 0; i < N; i++) {
        double sum = 0;
        double sum2 = 0;
        for(int j = 0; j < L; j++) {
            metro(rnd, step, x, mu, sigma, acceptance);
            Hpsi = eval_Hpsi(x, mu, sigma, 1.0, 1.0);
            sum += Hpsi;
            sum2 += pow(Hpsi, 2);
        }
        ave[i] = sum / L;
        av2[i] = sum2 / L;
        err[i] = error(ave, av2, i);
    }

    auto result = sum_prog(ave, av2, N);
    WriteToFile("H_medio.txt", N, L, result.first, result.second);
    return 0;
}
