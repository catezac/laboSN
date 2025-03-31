#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include "/home/catezac/laboSN/PRNG/random.h"
using namespace std;

int main() {
    Random rnd;
    
    int M=100000;         // Total number of realizations
    vector <int> N = {1,2,10,100}; // Number of throws in each block
    vector <double> S_uniform(M,0); // Average of uniform random numbers
    vector <double> S_exp(M,0);     // Average of exponential random numbers 
    vector <double> S_lorentz(M,0); // Average of Lorentzian random numbers

    ofstream histo1;
    ofstream histo2;
    ofstream histo10;
    ofstream histo100;
    histo1.open("histo1.dat");
    histo2.open("histo2.dat");
    histo10.open("histo10.dat");
    histo100.open("histo100.dat");
    
    if(histo1.is_open()&& histo2.is_open() && histo10.is_open()&& histo100.is_open()) {
        for(int i = 0; i<4; i++) {
            for(int k=0; k<M; k++){
                S_uniform[k] = 0;
                S_exp[k] = 0;
                S_lorentz[k] = 0;  
                for(int j=0; j<N[i]; j++) {
                    S_uniform[k] += rnd.Rannyu();
                    S_exp[k] += rnd.Exponential(1);
                    S_lorentz[k] += rnd.Lorentz(0,1);
                }
                S_uniform[k] /= N[i];   
                S_exp[k] /= N[i];
                S_lorentz[k] /= N[i];
                if(N[i] == 1) {histo1 <<  S_uniform[k] << " " << S_exp[k] << " " << S_lorentz[k] << endl;  }
                if(N[i] == 2) {histo2 <<  S_uniform[k] << " " << S_exp[k] << " " << S_lorentz[k] << endl;  }
                if(N[i] == 10) {histo10 <<  S_uniform[k] << " " << S_exp[k] << " " << S_lorentz[k] << endl;  } 
                if(N[i] == 100) {histo100 <<  S_uniform[k] << " " << S_exp[k] << " " << S_lorentz[k] << endl;}
            } 
        }
    }else cerr << "Unable to open files" << endl;
    
    histo1.close();
    histo2.close();
    histo10.close();
    histo100.close();


    return 0;
}