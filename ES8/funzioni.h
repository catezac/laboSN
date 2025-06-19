#ifndef FUNZIONI_H
#define FUNZIONI_H

#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>
#include "/home/catezac/laboSN/PRNG/random.h"

using namespace std;

double SetParameter(string file,string prop);
void initialize_parameters(int &M, int &M_equil, int &N, int &N_step, double &step, double &mu, double &sigma);
double eval_psi(double x, double mu, double sigma);
double eval_Hpsi( double x, double sigma, double mu, double hbar, double m);
void metro(Random &rnd, double step, double &x, double mu, double sigma, double &acceptance); // Metropolis algorithm
void equilibration(Random &rnd, int M_equil, double &x, double mu, double sigma, double &step, double &acceptance);
double error(vector <double> AV, vector <double> AV2, int n); // error

pair<vector<double>, vector<double>> sum_prog(vector<double> ave, vector <double> av2, int N);

void WriteToFile(string filename, int N, double L, vector<double> s, vector<double> err);
void WriteToFile_mu_sigma(string filename, double N_step, vector<double> T, vector<double> mu, vector<double> sigma, vector<double> Hmedio, vector<double> err_Hmedio);



#endif