#include "funzioni.h"
#include "/home/catezac/laboSN/PRNG/random.h"
#include <cmath>

using namespace std;

double SetParameter(string file,string prop) {
    ifstream fin(file);
    string input;
    double r = 0.;
    
    if(fin.is_open()){
        while(!fin.eof()){
            fin >> input;
            if( input == prop ) fin >> r;
        }
    } else cerr<<"Can't open "<<file<<endl;
    fin.close();
    return r;
};

double eval_psi(double x, double mu, double sigma) {
    return exp(-pow((x-mu),2)/(2*pow(sigma,2))) + exp(-pow((x+mu),2)/(2*pow(sigma,2)));
}
/*
double eval_Hpsi(double x, double mu, double sigma, double hbar, double m) {
    // coefficienti utili
    double sigma2 = sigma * sigma;
    double sigma4 = sigma2 * sigma2;
    //double a = 1.0 / (2.0 * sigma2);
    double b = mu / sigma2;

    // rapporto Psi''(x) / Psi(x)
    double term1 = x * x / sigma4;
    double term2 = (2.0 * mu * x / sigma4) * tanh(b * x);
    double term3 = 1.0 / sigma2;
    double term4 = (mu * mu) / sigma4;
    double psi2_over_psi = term1 - term2 - term3 + term4;

    // parte cinetica: -(ħ^2 / 2m) * (Psi''/Psi)
    double kinetic = - (hbar * hbar / (2.0 * m)) * psi2_over_psi;

    // parte potenziale: V(x)
    double potential = pow(x, 4) - 5*pow(x, 2) /2;

    return kinetic + potential;
}*/


double eval_Hpsi(double x, double mu, double sigma, double hbar = 1.0, double m = 1.0) {
    double sigma2 = sigma * sigma;
    double sigma4 = sigma2 * sigma2;

    double exp1 = exp(- (x - mu) * (x - mu) / (2.0 * sigma2));
    double exp2 = exp(- (x + mu) * (x + mu) / (2.0 * sigma2));
    double psi = exp1 + exp2;

    double d2_exp1 = ((x - mu)*(x - mu) - sigma2) / sigma4 * exp1;
    double d2_exp2 = ((x + mu)*(x + mu) - sigma2) / sigma4 * exp2;
    double psi_dd = d2_exp1 + d2_exp2;

    double kinetic = - (hbar * hbar) / (2.0 * m) * (psi_dd / psi);
    double potential = pow(x, 4) - 2.5 * x * x;

    return kinetic + potential;
}



void metro(Random &rnd, double step, double &x, double mu, double sigma, double &acceptance){ // Metropolis algorithm
    double r, x_new, alpha;
    r = rnd.Rannyu(-1,1);
    x_new = x + r * step; // propose a new position
    //cout << x_new << endl;
    alpha = pow(eval_psi(x_new, mu, sigma),2) / pow(eval_psi(x, mu, sigma),2);
    //cout << alpha << endl;
    if(rnd.Rannyu() < alpha) {
        x = x_new; // accept the new position
        acceptance ++; // increase the acceptance counter
    }
}

void equilibration(Random &rnd, int M_equil, double &x, double mu, double sigma, double &step, double &acceptance) {
    while(acceptance < 0.45 || acceptance > 0.55) {
        step += 0.1;
        //cout << "Sto equilibrando il sistema con passo: " << step << endl;
        for(int i = 0; i<M_equil; i++) {
            metro(rnd, step, x, mu, sigma, acceptance);
        }
        acceptance/=M_equil;
    }
}

double error(vector <double> AV, vector <double> AV2, int n) { 
    // Function for statistical uncertainty estimation
    if(n==0)
        return 0;
    else
        return sqrt((AV2[n] - pow(AV[n],2))/n);
};

void WriteToFile(string filename, int N, double L, vector<double> s, vector<double> err) {
    ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < N; i++) {
            file << (i+1) << " " << s[i] << " " << err[i] << endl;
        }
        file.close();
    } else {    cerr << "Unable to open " << filename << endl; }
}

void WriteToFile_mu_sigma(string filename, double N_step, vector<double> T, vector<double> mu, vector<double> sigma, vector<double> Hmedio, vector<double> err_Hmedio) {
    ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < N_step; i++) {
            file << i << " " << T[i] << " " << mu[i] << " " << sigma[i] << " " << Hmedio[i] << " " << err_Hmedio[i] << endl;
        }
        file.close();
    } else { cerr << "Unable to open " << filename << endl; }
}

pair<vector<double>, vector<double>> sum_prog(vector<double> ave, vector <double> av2, int N) {
    vector<double> sum_prog(N);
    vector<double> su2_prog(N);
    vector<double> err_prog(N);
    for(int i=0; i<N; i++){
        for(int j=0; j<i+1; j++){
            sum_prog[i] += ave[j];
            su2_prog[i] += av2[j];

        }
        sum_prog[i] /= (i+1);
        su2_prog[i] /= (i+1);
        err_prog[i] = error(sum_prog, su2_prog, i);
    }

    return make_pair(sum_prog, err_prog);
}