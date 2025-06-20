#ifndef FUNZIONI_H
#define FUNZIONI_H

#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>


using namespace std;

double error(vector <double> AV, vector <double> AV2, int n);
void WriteToFile(string filename, int N, vector<double> s, vector<double> err);
pair<vector<double>, vector<double>> sum_prog(vector<double> ave, vector <double> av2, int N);
double gcos(double a, double b, double x);
double fcos(double a, double b, double x);


#endif