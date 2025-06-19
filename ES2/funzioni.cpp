#include "funzioni.h"

using namespace std;


double error(vector <double> AV, vector <double> AV2, int n) { 
    // Function for statistical uncertainty estimation
    if(n==0)
        return 0;
    else
        return sqrt((AV2[n] - pow(AV[n],2))/n);
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

void WriteToFile_RW(string filename, int N_step, vector<double> s, vector<double> err) {
    ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < N_step; i++) {
            file << s[i] << " " << err[i] << endl;
        }
        file.close();
    } else {    cerr << "Unable to open " << filename << endl; }
};

void Write_config(string filename, int N, vector<Posizione> p){
    ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < N; i++) {
            file << p[i].getX() << " " << p[i].getY() << " " << p[i].getZ() << endl;
        }
        file.close();
    } else {    cerr << "Unable to open " << filename << endl; }
}

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

double fcos(double a, double b, double x){
    return a*cos(b*x);
};

double gcos(double a, double b, double x){
    return a*cos(b*x)/(2*(1-x));
};

void RW3D_discrete(Posizione &p, double r, int a) {
    
    if(r==0) {  p.setX(p.getX()+a);  };
    if(r==1) {  p.setX(p.getX()-a);  };
    if(r==2) {  p.setY(p.getY()+a);  };
    if(r==3) {  p.setY(p.getY()-a);  };
    if(r==4) {  p.setZ(p.getZ()+a);  };
    if(r==5) {  p.setZ(p.getZ()-a);  };
};


void RW3D_continuum(Posizione &p, double r_theta, double r_fi, int a){
    double theta;
    double fi;
    fi = r_fi * 2 * M_PI;    // Angolo phi tra 0 e 2π
    theta = acos(1 - 2*r_theta);  // Angolo theta tra 0 e π
    
    p.sferichex(p.getX(), a, theta, fi);
    p.sferichey(p.getY(), a, theta, fi);
    p.sferichez(p.getZ(), a, theta, fi);
};

