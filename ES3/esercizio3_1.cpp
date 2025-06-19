#include "/home/catezac/laboSN/PRNG/random.h"
#include "funzioni.h"

using namespace std;

int main() {

    Random rnd;

    // parametri del problema
    double S_0 = 100;    // asset price
    double sigma = 0.25; // volatility
    double mu = 0;       // centro dell'estrazione gaussiana
    double r = 0.1;      // risk-free interest rate
    double K = 100;      // strike price
    double T = 1;        // delivery time

    // variabili per il calcolo
    double Wt = 0;
    double St = 0;
    double C = 0;
    double P = 0;

    //parametri per la media a blocchi
    int M = 10000;
    int N = 100;
    int L = M/N;
    
    vector<double> ave_P(M);
    vector<double> av2_P(M);
    vector<double> ave_C(M);
    vector<double> av2_C(M);

    double sum_C = 0;
    double sum_P = 0;

    vector <int> n;
    for(int i=0; i<N; i++) {
        n.push_back(i);           // [0,1,2,...,N-1]
    }
    
    for(int i = 0; i<N; i++) {
        sum_C = 0;
        sum_P = 0;
        for (int j = 0; j < L; j++) {
            Wt = rnd.Gauss(mu, T);
            St = GBM(S_0, T, r, sigma, Wt);
            C = exp(-r*T)*max(St-K, 0.);
            P = exp(-r*T)*max(K-St, 0.);
            sum_C += C;
            sum_P += P;
        }
        ave_C[i] = sum_C/L;
        av2_C[i] = pow(ave_C[i],2);
        ave_P[i] = sum_P/L;
        av2_P[i] = pow(ave_P[i],2);
    }

    auto result_C = sum_prog(ave_C, av2_C, N);
    auto result_P = sum_prog(ave_P, av2_P, N);

    WriteToFile("Call.dat", N, result_C.first, result_C.second);
    WriteToFile("Put.dat", N, result_P.first, result_P.second);
    
    // sampling with discrete GBM
        //parametri per discretizzare il tempo
    double dt = T/100;
    double Z = 0;
    
    vector<double> ave_P_d(M);
    vector<double> av2_P_d(M);
    vector<double> ave_C_d(M);
    vector<double> av2_C_d(M);

    double C_d = 0;
    double P_d = 0;

    for(int i = 0; i<N; i++) {
        double sum_C_d = 0;
        double sum_P_d = 0;
        for (int j = 0; j < L; j++) {
            vector <double> St_discrete(100);
            St_discrete[0] = 100;
            for (int k = 1; k < 100; k++) {
                Z = rnd.Gauss(0,1);
                St_discrete[k] = GBM_discrete(St_discrete[k-1], dt, r, sigma, Z);
            }
            C_d = exp(-r*T)*max(0., St_discrete[99]-K);
            P_d = exp(-r*T)*max(K-St_discrete[99], 0.);
            sum_C_d += C_d;
            sum_P_d += P_d;
        }
        ave_C_d[i] = sum_C_d/L;
        av2_C_d[i] = pow(ave_C_d[i],2);
        ave_P_d[i] = sum_P_d/L;
        av2_P_d[i] = pow(ave_P_d[i],2);
    }

    auto result_C_d = sum_prog(ave_C_d, av2_C_d, N);
    auto result_P_d = sum_prog(ave_P_d, av2_P_d, N);

    WriteToFile("Call_d.dat", N, result_C_d.first, result_C_d.second);
    WriteToFile("Put_d.dat", N, result_P_d.first, result_P_d.second);

    return 0;
}