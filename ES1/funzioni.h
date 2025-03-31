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

void WriteToFile(string filename, int N, vector<int> n, double L, vector<double> s, vector<double> err);

pair<vector<double>, vector<double>> sum_prog(vector<double> ave, vector <double> av2, int N);


#endif