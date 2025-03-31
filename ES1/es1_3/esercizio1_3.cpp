#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include "/home/catezac/laboSN/PRNG/random.h"
#include "../funzioni.h"
using namespace std;



int main() {
    Random rnd;

    int M=100000;         // Total number of throws
    int N = 100;       // Number of blocks
    double L = 0.8; // lenght of the needle
    double d = 1.5; // distance between the lines
    vector <double> p(N,0); // prograssive sum of pi
    vector <double> p_ave(N,0); // comulatve average of pi
    vector <double> p_av2(N,0); //comulative av2 of pi

    vector <double> er_pi(N,0); 
    int N_hit = 0; // Number of needles that hit a line
    double N_throw = M/N; // number of throws for each block
    vector <int> n;
    for(int i=0; i<N; i++) {
        n.push_back(i);           // [0,1,2,...,N-1]
    }

    for(int j = 0; j< N; j++) {
        N_hit = 0;
        //sum_p = 0;
        for(int k = 0; k < N_throw ; k++) {
            double x = rnd.Rannyu(0,d/2); // x coordinate of the center of the needle
            double theta = rnd.Rannyu(0,M_PI/2); // angle of the needle
            if(x <= L/2*sin(theta)) {
                N_hit += 1;
            }
            
        }
        p[j] = 2*L*N_throw/(N_hit*d); // pi estimation di un blocco
        p_av2[j] = pow(p[j],2);
    }

    auto result = sum_prog(p, p_av2, N);

    WriteToFile("pi_estimation.dat", N, n, N_throw, result.first, result.second);

    return 0;
}