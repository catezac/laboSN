#ifndef CITY_H
#define CITY_H

#include <cmath>
#include <cstdlib>
#include <string>
#include <armadillo>
#include "/home/catezac/laboSN/PRNG/random.h"

using namespace std;
using namespace arma;

class City {
    private:
    int _ndim = 2;
    int _id; // numero assegnato alla città che la fissa in una posizione
    
    public:
    vec _pos;
        
    City(){
        _pos.set_size(3);};
    vec getpos();
    double getpos(int i);
    bool operator==(City a);
    bool operator!=(City a);
    void setpos(int i, double val);
    void setpos(vec x);


};
#endif /* city.h */