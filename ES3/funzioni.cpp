#include "funzioni.h"

using namespace std;


double error(vector <double> AV, vector <double> AV2, int n) { 
    // Function for statistical uncertainty estimation
    if(n==0)
        return 0;
    else
        return sqrt((AV2[n] - pow(AV[n],2))/n);
};

double GBM(double S_0, double t, double r, double sigma, double Wt) {
    return S_0 * exp((r- (0.5*pow(sigma,2)))*t + (sigma*Wt));
};

double GBM_discrete(double S_t1, double dt, double r, double sigma, double Z) {
    return S_t1 * exp((r - (0.5*pow(sigma,2)))*dt+ (sigma*Z*sqrt(dt)));
};

void WriteToFile(string filename, int N, vector<double> s, vector<double> err) {
    ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < N; i++) {
            file << i+1 << " " << s[i] << " " << err[i] << endl;
        }
        file.close();
    } else {    cerr << "Unable to open " << filename << endl; }
};

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