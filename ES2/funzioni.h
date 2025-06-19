#ifndef FUNZIONI_H
#define FUNZIONI_H

#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>
#include "es2_2/Posizione.h"

using namespace std;

double error(vector <double> AV, vector <double> AV2, int n); // error

void Write_config(string filename, int N, vector<Posizione> p);
void WriteToFile(string filename, int N, vector<double> s, vector<double> err);
void WriteToFile_RW(string filename, int N_step, vector<double> s, vector<double> err);

pair<vector<double>, vector<double>> sum_prog(vector<double> ave, vector <double> av2, int N);

double gcos(double a, double b, double x);

double fcos(double a, double b, double x);

void RW3D_continuum(Posizione &p, double r_theta, double r_fi, int a);

void RW3D_discrete(Posizione &p, double r, int a);


#endif