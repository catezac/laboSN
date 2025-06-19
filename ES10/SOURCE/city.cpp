#include <cmath>
#include <cstdlib>
#include <string>
#include "city.h"

using namespace std;
using namespace arma;



vec City::getpos(){
    return _pos;
}

double City::getpos(int i){
    return _pos(i);
}

bool City::operator==(City a){
    return all(_pos==a.getpos());
}
bool City::operator!=(City a){
    return all(_pos!=a.getpos());
}

void City::setpos(int i, double val){
    _pos(i) = val;
}

void City::setpos(vec x){
    _pos = x;
}
