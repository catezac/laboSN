#include "funzioni.h"

using namespace std;


double error(vector <double> AV, vector <double> AV2, int n) { 
    // Function for statistical uncertainty estimation
    if(n==0)
        return 0;
    else
        return sqrt((AV2[n] - pow(AV[n],2))/n);
};

void WriteToFile(string filename, int N, vector<int> n, double L, vector<double> s, vector<double> err) {
    ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < N; i++) {
            file << n[i] * L << " " << s[i] << " " << err[i] << endl;
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
