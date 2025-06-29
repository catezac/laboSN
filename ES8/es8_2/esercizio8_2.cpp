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
    double mu_iniz = SetParameter("../input.dat", "mu");
    double sigma_iniz = SetParameter("../input.dat", "sigma");
    int M = SetParameter("../input.dat", "M");
    int M_equil = SetParameter("../input.dat", "M_equil");
    int N = SetParameter("../input.dat", "N");
    int N_step = SetParameter("../input.dat", "N_step");

    double Hpsi;
    double p;
    double x_start =0.;
    double x = 0;
    double acceptance = 0.0;
    double L = M/N;
    vector<double> mu(N_step);
    vector<double> sigma(N_step);
    vector<double> Hmedio(N_step);
    vector<double> err_Hmedio(N_step);
 
    vector<double> T(N_step);
    equilibration(rnd, M_equil, x_start, mu_iniz, sigma_iniz, step, acceptance);
    cout << "accettanza con passo " << step << " : " << acceptance << endl;

    T[0] = 10;
    mu[0] = mu_iniz;
    sigma[0] = sigma_iniz;
    cout << mu[0] << " " << sigma[0] << endl;
    
    for(int k = 1; k < N_step; k++) { //ciclo per variare la temperatura
        print_progress_bar(float(k+1)/N_step*100);
        T[k] = T[0]/pow(k,1.5);
        mu[k] = mu[k-1] + (rnd.Rannyu(-1,1) * 0.5);
        sigma[k] = sigma[k-1] + rnd.Rannyu(-1,1) *0.5;
        while(sigma[k] < 0.2){
            sigma[k] = sigma[k-1] + rnd.Rannyu() *0.5;
        }
        vector<double> ave(N);
        vector<double> av2(N);
        vector<double> err(N);
        
        for(int i = 0; i < N; i++) {
            double sum = 0;
            x = x_start;
            for(int j = 0; j < L; j++) {
                metro(rnd, step, x, mu[k], sigma[k], acceptance);
                Hpsi = eval_Hpsi(x, mu[k], sigma[k], 1.0, 1.0);
                sum += Hpsi;
            }
            ave[i] = sum / L;
            av2[i] = pow(ave[i],2);
            err[i] = error(ave, av2, i);
        } 
        auto result = sum_prog(ave, av2, N);
        Hmedio[k] = result.first[N-1];
        err_Hmedio[k] = result.second[N-1];

        // accettazione:
        if (Hmedio[k] > Hmedio[k-1]){
            p = exp(-(1/T[k])*(Hmedio[k]-Hmedio[k-1]));
            if (rnd.Rannyu() > p) {
                //cout << "ho rifiutato il passo " << k << endl;
                Hmedio[k] = Hmedio[k-1];
                err_Hmedio[k] = err_Hmedio[k-1];
                mu[k] = mu[k-1];
                sigma[k] = sigma[k-1];
            }
        }
    }
    WriteToFile_mu_sigma("H_T.dat", N_step, T, mu, sigma, Hmedio, err_Hmedio); 

    // calcolo dell'energia con mu e sigma trovati dal simulating annealing
    double mu_best;
    double sigma_best;
    mu_best = mu[N-1];
    sigma_best = sigma[N-1];

    x_start = 0;
    equilibration(rnd, M_equil, x_start, mu_best, sigma_best, step, acceptance);

    x = x_start;
    vector<double> ave(N);
    vector<double> av2(N);
    vector<double> err(N);

    cout << "\n Valori di sigma e mu migliori: " << endl;
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
        ave[i] = sum / L;
        av2[i] = sum2 / L;
        err[i] = error(ave, av2, i);
    }
    file.close();
    auto result = sum_prog(ave, av2, N);
    WriteToFile("H_medio_best.txt", N, L, result.first, result.second);
       
    return 0;
}
