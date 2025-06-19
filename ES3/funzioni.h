#ifndef FUNZIONI_H
#define FUNZIONI_H

#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

double error(vector <double> AV, vector <double> AV2, int n); // error

double GBM(double S_0, double t, double r, double sigma, double Wt); // geometric brownian motion

double GBM_discrete(double S_t1, double dt, double r, double sigma, double Z); // discrete geometric brownian motion
 
void WriteToFile(string filename, int N, vector<double> s, vector<double> err);

pair<vector<double>, vector<double>> sum_prog(vector<double> ave, vector <double> av2, int N);
#endif