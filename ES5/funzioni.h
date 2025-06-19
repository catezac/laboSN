#ifndef FUNZIONI_H
#define FUNZIONI_H

#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>
#include "Posizione.h"
#include "/home/catezac/laboSN/PRNG/random.h"

using namespace std;

double SetParameter(string file,string prop);
string SetMethod(string filename, string prop);

double ground_state(double a_0, Posizione x);
double state_2p(double a_0, Posizione x);
void update_x_unif(Random &rnd, Posizione &p, Posizione&p_0, double step);
void update_x_gauss(Random &rnd, Posizione &p, Posizione&p_0, double step);
void update_x(double r, Posizione &p, Posizione&p_0, double step);

template <typename probability>
void metro(Random &rnd, double step, Posizione &p, Posizione &p_0, double a_0, double &acceptance, probability psi, string method){ // Metropolis algorithm
    double alpha;
    if (method == "unif") {
        update_x_unif(rnd, p, p_0, step); //propose a new position
    } else if (method == "gauss") {
        update_x_gauss(rnd, p, p_0, step);
    } else{
        cout << "metodo non riconosciuto" << endl;
    }
    alpha = psi(a_0, p) / psi(a_0, p_0);
    if(rnd.Rannyu() < alpha) {
        acceptance ++; // increase the acceptance counter
    } else {
        p = p_0; // rigetto la mossa
    }
}

template <typename probability>
void equilibration(Random &rnd, int M_equil, vector <Posizione> &p, double a_0, probability psi, string method, double &step, double &acceptance) {
    while(acceptance < 0.45 || acceptance > 0.55) {
        step += 0.1;
        for(int i = 0; i<M_equil; i++) {
            metro(rnd, step, p[i+1], p[i], a_0, acceptance, psi, method);
        }
        acceptance/=M_equil;
    }
}

void WriteToFile_pos(string filename, int M, vector<Posizione> s);
void WriteToFile_r(string filename, int N, vector<double> s, vector<double> ave, vector<double> err);
double error(vector <double> AV, vector <double> AV2, int n);
pair<vector<double>, vector<double>> sum_prog(vector<double> ave, vector <double> av2, int N);


#endif