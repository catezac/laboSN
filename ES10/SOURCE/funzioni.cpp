#include "funzioni.h"
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;
using namespace arma;

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

pair<string, string> SetConfig(string filename, string prop) {
    ifstream fin(filename);
    string input;
    string config;
    string r;
    if(fin.is_open()){
        while(!fin.eof()){
            fin >> input;
            if( input == prop ) fin >> config >> r;
        }
    } else cerr<<"Can't open "<< filename <<endl;
    fin.close();
    return make_pair(config, r);
}

// Scrive la configurazione delle città su file
void WriteToFile(string filename, int N, vec L2) {
    ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < N; i++) {
            file << i << " " << L2(i) << endl;
        }
        file.close();
    } else {   cerr << "Unable to open " << filename << endl; }
}
