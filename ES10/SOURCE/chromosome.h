#ifndef __chromosome_h
#define __chromosome_h

#include <cmath>
#include <cstdlib>
#include <string>
#include "/home/catezac/laboSN/PRNG/random.h"
#include "funzioni.h"
#include "city.h"
#include "mpi.h"

using namespace std;
using namespace arma;

class Chromosome {
    private:
    
    string _config; // tipo di configurazione delle città
    vector<int> _x; // è un gene, cioè ogni elemento del cromosoma, salvo l'indice assegnato alla città
    
    double _radius;
    double _length;

    public:
    field <City> _cities; //dove sono collocate le città
    int _ncity; //numero di città prensenti
    string _check;
    Random _rnd;
    
    Chromosome(){
        _ncity = SetParameter("input.dat", "NCITY");
        _cities.set_size(_ncity);};
    Chromosome(int N ){
        _ncity = N;
        _cities.set_size(N);};
    void Circle();
    void Square();
    int get_ncity();
    void configuration(); // leggo file input per settare alcuni valori e creo il primo cromosoma che è fatto da le 34 città in ordine
    void check(); /*funzione che controlla che il cromosoma rispetti i constraint:  
                        1. all the cities has to be visited once and only once
                        2. at the end the saleman has to return to the first city
                        3. the first city has to be always at position 1 in each chromosome */
    
    double distance(City citta1, City citta2);
    double loss(); // funzione che calcola la loss come distanza L(2) tra le varie città in un cromosoma
    // genetic mutations:
    void permutation();     // permutazione delle città (già implementato per creare la prima popolazione)
    void shift_n();           //shift di +n di m citta contigue 
    void permutation_m();    // permutazione di m citta contigue con altre m citta contigue 
    void inversion();       // inversione dell'ordine in cui appaiono di m città contigue
    void Write_Config(string filename);
};

#endif /* chromosome.h */