#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <filesystem> 
#include "/home/catezac/laboSN/PRNG/random.h"
#include "../funzioni.h"
using namespace std;
namespace fs = std::filesystem;

int main(){

    Random rnd;

    int M=100000;          // Total number of throws
    int N=100;             // Number of blocks
    int L=int(M/N);        // Number of throws in each block
    
    vector <double> ave(N, 0);
    vector <double> av2(N, 0);
    
    vector <double> ave_s(N, 0);
    vector <double> av2_s(N, 0);    
    
    for(int i=0; i < N; i++) {
        double sum1 = 0;
        double sum = 0;
        double r;
        for(int j=0; j<L; j++){
            r = rnd.Rannyu(); // Generate random number
            sum1 += r;
            sum += pow((r-0.5),2); // Accumulate measures
        }
        ave[i] = sum1/L;     // r_i 
        av2[i] = pow((ave[i]),2); // (r_i)^2 
        ave_s[i] = sum/L;           // Estimate in each block 
        av2_s[i] = pow((ave_s[i]),2);
    }

    auto result = sum_prog(ave, av2, N);
    auto result_s = sum_prog(ave_s, av2_s, N);

    WriteToFile("data.dat", N, result.first, result.second);
    
    WriteToFile("data_sigma.dat", N, result_s.first, result_s.second);

    //Chi test
    double m = 100;     // Number of sub-intervals
    int n = 100000;     // Number of random numbers
    int rep = 10000;    // Number of repetitions
    vector <double> chi(rep,0);
    double r;
    ofstream chi_test;
    chi_test.open("chi_test_1000000.dat");
    if(chi_test.is_open()) {

        for(int j=0; j<rep; j++) {
            vector <double> n_i(m,0);
            for (int k = 0; k < n; k++) {
                r = rnd.Rannyu();
                n_i[int(r*m)] += 1;
            }
            for(int i=0; i<m; i++) {
                chi[j] += pow((n_i[i]- n/m),2)/(n/m);
            }
            chi_test << j+1 << " " << chi[j] << endl;
            r = 0;
        }
    } else cerr << "Unable to open chi_test.dat" << endl;
    chi_test.close();    

    
   
    return 0;
}