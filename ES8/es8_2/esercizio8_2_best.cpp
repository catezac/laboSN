#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include "../funzioni.h"
#include "/home/catezac/laboSN/PRNG/random.h"


void print_progress_bar(float progress) {
  int bar_width = 50;
  int pos = bar_width * progress / 100.0;

  cout << "\rProgress: [";
  for (int j = 0; j < bar_width; ++j) {
      if (j < pos) cout << "=";
      else if (j == pos) cout << ">";
      else cout << " ";
  }
  cout << "] " << fixed << setprecision(1) << progress << "%";
  cout.flush();
}

int main(){
    
    Random rnd;
    double step = SetParameter("../input.dat", "step");
    //double mu_iniz = SetParameter("../input.dat", "mu");
    //double sigma_iniz = SetParameter("../input.dat", "sigma");
    int M = SetParameter("../input.dat", "M");
    int M_equil = SetParameter("../input.dat", "M_equil");
    int N = SetParameter("../input.dat", "N");
    int N_step = SetParameter("../input.dat", "N_step");

    double Hpsi;
    double x_start =0.;
    double x = 0;
    double acceptance = 0.0;
    double L = M/N;
    vector<double> mu(N_step);
    vector<double> sigma(N_step);
    vector<double> Hmedio(N_step);
    vector<double> err_Hmedio(N_step);

    // calcolo dell'energia con mu e sigma trovati dal simulating annealing
    double mu_best;
    double sigma_best;
    mu_best = 0.807;
    sigma_best = 0.63;
    
    equilibration(rnd, M_equil, x_start, mu_best, sigma_best, step, acceptance);
    cout << step << "           " << acceptance << endl;
    x = x_start;

    vector<double> ave(N);
    vector<double> av2(N);
    vector<double> err(N);

    cout << "Valori di sigma e mu migliori: " << endl;
    cout << setprecision(5) << "       sigma = " << sigma_best << endl;
    cout << setprecision(5) << "       mu = " << mu_best << endl;
    ofstream file("probability.dat");

    for(int i = 0; i < N; i++) {
        double sum = 0;
        double sum2 = 0;
        for(int j = 0; j < L; j++) {
            metro(rnd, step, x, mu_best, sigma_best, acceptance);
            file << setw(12) << x << endl;
            Hpsi = eval_Hpsi(x, mu_best, sigma_best, 1.0, 1.0);
            sum += Hpsi;
            sum2 += pow(Hpsi, 2);
        }
        //cout << acceptance/(L*(i+1)) << endl;
        ave[i] = sum / L;
        av2[i] = sum2 / L;
        err[i] = error(ave, av2, i);
    }
    file.close();
    auto result = sum_prog(ave, av2, N);
    WriteToFile("H_medio_best.txt", N, L, result.first, result.second);
       
    return 0;
}
