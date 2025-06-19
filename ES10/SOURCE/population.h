#ifndef POPULATION_H
#define POPULATION_H

#include <cmath>
#include <cstdlib>
#include <string>
#include "/home/catezac/laboSN/PRNG/random.h"
#include "funzioni.h"
#include "city.h"
#include "chromosome.h"


using namespace std;
using namespace arma;

class Population {
    private:
    Random _rnd;
    
    double _p_permutation, _p_permutation_m, _p_shift, _p_inversion, _p_crossover;
        
    public:
    field <Chromosome> _chromosome;
    int _nchrom;
    Population(){;};
    Population(int N ){
        _nchrom = N;
        _chromosome.set_size(N);};
    void initialize();  // inizializzo il sistema 
    void first_popul(); /*creo la prima popolazione: primo cromosoma che rispetta i vincoli banale è [1,2,3,..., 34]
                           per creare gli altri si permutano città in individui gia presenti, infatti la permutazione non rompe i vincoli */
    void sorting();     //riordina la popolazione da quello con funzione loss più alta a funzione loss piu bassa
    double L1_ave(); // calcola il valor medio della L2 sulla metà migliore della popolazione
    
    int selection();   // selection operator with the algorithm: j = int(M*r^p)+1
    void Mutation();

    //void crossing(Chromosome& mother, Chromosome& father);
    void crossover(Chromosome& mother, Chromosome& father);   //  taglia i due cammini nella stessa posizione, conserva la prima parte di entrambi e completa la seconda parte con le citta mancanti nell'ordine in cui appaiono nell'altro cammino        
    
};

#endif