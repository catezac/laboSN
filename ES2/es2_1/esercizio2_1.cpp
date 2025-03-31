#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include "/home/catezac/laboSN/PRNG/random.h"
#include "../funzioni.h"

using namespace std;

int main(){
    Random rnd;

    // estraggo numeri casuali, valuto la funzione nei numeri estratti e calcolo l'area dei rettangoli che si formano, poi faccio la media dell'area dei rettangoli
    int M = 100000;
    int N = 100;
    double L = M/N;
    vector <int> n;
    for(int i=0; i<N; i++) {
        n.push_back(i);           // [0,1,2,...,N-1]
    }
    
    vector<double> x(M);
    vector<double> y(M);
    vector<double> ave(M);
    vector<double> av2(M);
    double sum = 0;
  
    for(int j = 0; j<N; j++){
        sum = 0;
        for(int i=0; i <L; i++){
            x[i] = rnd.Rannyu();
            y[i] = fcos(M_PI/2., M_PI/2., x[i]);
            sum += y[i];
        }     
        ave[j] = sum/L;
        av2[j] = pow(ave[j],2);      
    }

    auto result = sum_prog(ave, av2, N);
    WriteToFile("integral1.dat", N, n, L, result.first, result.second);
    
    // importance sampling, uso come probabilità p(x) = 2(1-x) e come funzione g(x) = pi/2 * cos(pi/2 * x) / 2(1-x)
    vector<double> x_is(M);
    vector<double> y_is(M);
    vector<double> ave_is(M);
    vector<double> av2_is(M);
    double sum_is = 0;

    for(int j = 0; j<N; j++){
        sum_is = 0;
        for(int i=0; i <L; i++){
            x_is[i] = rnd.Imp_sampling();
            y_is[i] = gcos(M_PI/2., M_PI/2., x_is[i]);
            sum_is += y_is[i];
    
        }     
        ave_is[j] = sum_is/L;
        av2_is[j] = pow(ave_is[j],2);      
    }

    auto result_is = sum_prog(ave_is, av2_is, N);
    WriteToFile("integral2.dat", N, n, L, result_is.first, result_is.second);

    return 0;
}