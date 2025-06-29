#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>
#include "/home/catezac/laboSN/PRNG/random.h"
#include "Posizione.h"
#include "funzioni.h"

using namespace std;

int main() {
    
    Random rnd;
    int M = SetParameter("input.dat", "M");
    int M_equil = SetParameter("input.dat", "M_equil"); // numero di step per l'equilibrazione
    int N = SetParameter("input.dat", "N"); // numero di blocchi
    string method = SetMethod("input.dat", "method");
    double passo_gs = SetParameter("input.dat", "passo_gs");
    double passo_2p = SetParameter("input.dat", "passo_2p");
    double a_0 = 1;
    double L = M/N;

    // funzione d'onda GS

    vector <Posizione> x_GS(M);
    x_GS[0].setX(0);
    x_GS[0].setY(0);
    x_GS[0].setZ(0);
    double acceptance_gs = 0;
    double r_gs = 0;
    
    // equilibrazione del sistema 
    equilibration(rnd, M_equil, x_GS, a_0, ground_state, method, passo_gs, acceptance_gs);
    cout << "Accettanza GS con passo " << passo_gs << " : " << acceptance_gs << endl;

    // ora faccio il ciclo di Metropolis e la media a blocchi
    vector<double> ave_GS(M); 
    vector<double> av2_GS(M);

    //x_GS[0] = x_GS[M_equil]; // setto la posizione iniziale della catena di Metropolis alla posizione finale della catena di equilibrio   
    for(int i = 0; i < N; i++) {
        double sum = 0;
        for(int j = 0; j < L; j++) {
            metro(rnd, passo_gs, x_GS[i+j+1], x_GS[i+j], a_0, acceptance_gs, ground_state, method);
            r_gs = sqrt(x_GS[i+j].distanza2_O());
            sum += r_gs;
            //sum2 += pow(r_gs, 2);
        }
        ave_GS[i] = sum / L;
        av2_GS[i] = pow(ave_GS[i],2);
    }

    cout << "Accettanza GS, con probabilità di transizione " << method << ": " << acceptance_gs/M << endl;
    WriteToFile_pos("OUTPUT/prob_GS.dat", M, x_GS);
    auto result_gs_unif = sum_prog(ave_GS, av2_GS, N);
    WriteToFile_r("OUTPUT/r_medio_GS_" + method + ".dat", N, result_gs_unif.first, ave_GS, result_gs_unif.second);

    // funzione d'onda 2p

    vector <Posizione> x_2p(M);
    x_2p[0].setX(0);
    x_2p[0].setY(0);
    x_2p[0].setZ(0);
    double acceptance_2p = 0;
    double r_2p = 0;

    equilibration(rnd, M_equil, x_2p, a_0, state_2p, method, passo_2p, acceptance_2p);
    cout << "Accettanza 2p con passo " << passo_2p << " : " << acceptance_2p << endl;
    vector<double> ave_2p(M); 
    vector<double> av2_2p(M);

    //x_2p[0] = x_2p[M_equil]; // setto la posizione iniziale della catena di Metropolis alla posizione finale della catena di equilibrio   
    for(int i = 0; i < N; i++) {
        double sum = 0;
        double sum2 = 0;
        for(int j = 0; j < L; j++) {
            metro(rnd, passo_2p, x_2p[i+j+1], x_2p[i+j], a_0, acceptance_2p, state_2p, method);
            r_2p = sqrt(x_2p[i+j].distanza2_O());
            sum += r_2p;
            sum2 += pow(r_2p, 2);
        }
        ave_2p[i] = sum / L;
        av2_2p[i] = pow(ave_2p[i],2);
    }

    cout << "Accettanza 2p, con probabilità di transizione " << method <<  ": " << acceptance_2p/M << endl;
    WriteToFile_pos("OUTPUT/prob_2p.dat", M, x_2p);     
    auto result_2p = sum_prog(ave_2p, av2_2p, N);
    WriteToFile_r("OUTPUT/r_medio_2p_" + method + ".dat", N, result_2p.first, ave_2p, result_2p.second);

    return 0;
}