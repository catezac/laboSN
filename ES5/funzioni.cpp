#include "funzioni.h"

using namespace std;


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

string SetMethod(string filename, string prop) {
    ifstream fin(filename);
    string input;
    string method;
    if(fin.is_open()){
        while(!fin.eof()){
            fin >> input;
            if( input == prop ) fin >> method;
        }
    } else cerr<<"Can't open "<< filename <<endl;
    fin.close();
    return method;
}


double ground_state(double a_0, Posizione x) {
    double r = sqrt(x.distanza2_O());
    return pow((pow(a_0,-3/2)*exp(-r/a_0)/sqrt(M_PI)),2);
};

double state_2p(double a_0, Posizione x){
    double r = sqrt(x.distanza2_O());
    return pow((pow(a_0,-5/2)*sqrt(2/M_PI)*x.getZ()*exp(-r/(2*a_0))/8), 2);
};

/* HO FATTO IL CAMPIONAMENTO CON LE COORDINATE SFERICHE
void update_x_unif(Random &rnd, Posizione &p, Posizione&p_0, double step){
    double theta, fi, a;
    fi = rnd.Rannyu() * 2 * M_PI;    // Angolo phi tra 0 e 2π
    theta = acos(1 - 2* rnd.Rannyu());  // Angolo theta tra 0 e π
    a = rnd.Rannyu(-1,1) * step; 
    p.sferichex(p_0.getX(), a, theta, fi);
    p.sferichey(p_0.getY(), a, theta, fi);
    p.sferichez(p_0.getZ(), a, theta, fi);
};

void update_x_gauss(Random &rnd, Posizione &p, Posizione&p_0, double step){
    double theta, fi, a;
    fi = rnd.Rannyu() * 2 * M_PI;    // Angolo phi tra 0 e 2π
    theta = acos(1 - 2* rnd.Rannyu());  // Angolo theta tra 0 e π
    a = rnd.Gauss(0.,1.) * step; 
    p.sferichex(p_0.getX(), a, theta, fi);
    p.sferichey(p_0.getY(), a, theta, fi);
    p.sferichez(p_0.getZ(), a, theta, fi);
};*/

void update_x_unif(Random &rnd, Posizione &p, Posizione&p_0, double step){
    p.setX(p_0.getX()+rnd.Rannyu(-1,1)*step);
    p.setY(p_0.getY()+rnd.Rannyu(-1,1)*step);
    p.setZ(p_0.getZ()+rnd.Rannyu(-1,1)*step);
}

void update_x_gauss(Random &rnd, Posizione &p, Posizione&p_0, double step){
    p.setX(p_0.getX()+rnd.Gauss(0,1)*step);
    p.setY(p_0.getY()+rnd.Gauss(0,1)*step);
    p.setZ(p_0.getZ()+rnd.Gauss(0,1)*step);
}



void WriteToFile_pos(string filename, int M, vector<Posizione> s) {
    ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < M; i++) {
            file << s[i].getX() << " " << s[i].getY() << " " << s[i].getZ() << endl;
        }
        file.close();
    } else {    cerr << "Unable to open " << filename << endl; }
};

double error(vector <double> AV, vector <double> AV2, int n) { 
    // Function for statistical uncertainty estimation
    if(n==0)
        return 0;
    else
        return sqrt((AV2[n] - pow(AV[n],2))/n);
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

void WriteToFile_r(string filename, int N, vector<double> s, vector<double> ave, vector<double> err) {
    ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < N; i++) {
            file << i+1 << " " << s[i] << " " << ave[i] << " " << err[i] << endl;
        }
        file.close();
    } else {    cerr << "Unable to open " << filename << endl; }
};