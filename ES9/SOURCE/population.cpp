#include <cmath>
#include <cstdlib>
#include <string>
#include "population.h"

using namespace std;
using namespace arma;

void Population :: initialize() {
    _nchrom = SetParameter("input.dat", "NCHROMOSOME");
    _p_permutation = SetParameter("input.dat", "P_PERMUTATION");
    _p_permutation_m = SetParameter("input.dat", "P_PERMUTATION_M");
    _p_shift = SetParameter("input.dat", "P_SHIFT");
    _p_inversion = SetParameter("input.dat", "P_INVERSION");
    _p_crossover = SetParameter("input.dat", "P_CROSSOVER");
    _chromosome.set_size(_nchrom);
    _first.configuration(); // il primo cromosoma ha le città nell'ordine in cui sono state create (0, 1, 2,..., 33)
    return;
}

void Population::first_popul(){  //creo la prima popolazione permutando in ogni cromosoma due città casuali, tenendo conto che la prima città deve rimanere ferma
    for(int j = 0; j<_nchrom; j++){
        _chromosome(j) = _first;
        for(int i = 0; i< 2*34; i++){
            _chromosome(j).permutation();
        }
        _chromosome(j).check();
            if(_chromosome(j)._check == "no") {
                cout << "Problem in the " << j << "chromosome in the creation of the first population" << endl;
            }
    }
}

void Population::sorting() { //metto in ordine i cromosomi da quello con loss più alta a quello con loss più bassa
    vec loss(_nchrom);
    for(int i = 0; i < _nchrom; i++) {
        loss(i)=(_chromosome(i).loss()); 
    }
    field<Chromosome> new_chromosome(_nchrom);
    //new_chromosome.set_size(_nchrom);
    uvec sorting = sort_index(loss, "descend");
    for(int i = 0; i < _nchrom; i++) {
        new_chromosome(i) = _chromosome(sorting(i));
    } 
    _chromosome = new_chromosome;
}

double Population::L1_ave(){
    double sum = 0;
    for(int i = _nchrom/2 ; i < _nchrom; i++) {
        sum += _chromosome(i).loss();
    }
    return sum/(_nchrom/2);
}

int Population::selection(){
    double r = _rnd.Rannyu();
    double index = int(_nchrom*pow(r,0.4));
    return index;
}

void Population::Mutation(){ 
    Chromosome chrom_init;
    for(int i = 0; i <_nchrom; i++){
        chrom_init = _chromosome(i);
        double p = 0;
        p = _rnd.Rannyu();
        //cout << "Probabilità di permutazione " << p << endl;
        if(p < _p_permutation){
            _chromosome(i).permutation();
            //cout << "Permutazione" << endl;
        }
        _chromosome(i).check();
        if(_chromosome(i)._check=="no"){
            _chromosome(i) = chrom_init;
            //cout << "Ho scartato la permutazione " << endl;
        }
        chrom_init = _chromosome(i);
        p = _rnd.Rannyu();
        if(p< _p_permutation_m){
            _chromosome(i).permutation_m();
            //cout << "Permutazione M" << endl;
        }
        _chromosome(i).check();
        if(_chromosome(i)._check=="no"){
            _chromosome(i) = chrom_init;
            //cout << "Ho scartato la permutazione M " << endl;
        }
        chrom_init = _chromosome(i);
        p = _rnd.Rannyu();
        if(p < _p_shift) {
            _chromosome(i).shift_n();
            //cout << "Shift" << endl;
        }
        _chromosome(i).check();
        if(_chromosome(i)._check=="no"){
            _chromosome(i) = chrom_init;
            //cout << "Ho scartato lo shift " << endl;
        }
        chrom_init = _chromosome(i);
        p = _rnd.Rannyu();
        if(p < _p_inversion){
            _chromosome(i).inversion();
            //cout << "Inversione" << endl;
        }
        _chromosome(i).check();
        if(_chromosome(i)._check=="no"){
            _chromosome(i) = chrom_init;
            //cout << "Ho scartato l'inversione " << endl;
        }
    }
}

void Population::crossover(Chromosome& mother, Chromosome& father) {
    double r = _rnd.Rannyu();
     // Selezione dei genitori
        int index1 = selection();
        int index2 = selection();
        //cout << "sto facendo crossover tra cromosomi " << index1 << " e " << index2 << endl;
        mother = _chromosome(index1);
        father = _chromosome(index2);
    if (r < _p_crossover) {
        int N = mother._ncity;
        int cut = rint(_rnd.Rannyu(1.5, N - 1));
        bool condition = true;

        // CROSSOVER SULLA MADRE
        for (int i = cut; i < N; i++) {
            for (int k = 1; k < N; k++) {
                condition = true;
                City candidate = father._cities(k);
                    for (int j = 1; j < i; j++) {
                        if (candidate == mother._cities(j)) {
                            condition = false;
                            break;
                        }
                    }
                    if (condition) {
                        mother._cities(i) = candidate;
                        break;
                    }
                }
            }

            mother.check();
            if (mother._check == "no") {
                //cout << "Madre non valida, ripristino" << endl;
                mother = _chromosome(index1);
            }

        // CROSSOVER SUL PADRE
        for (int i = cut; i < N; i++) {
            for (int k = 1; k < N; k++) {
                condition = true;
                City candidate = mother._cities(k);
                    for (int j = 1; j < i; j++) {
                        if (candidate == father._cities(j)) {
                            condition = false;
                            break;
                        }
                    }
                    if (condition) {
                        father._cities(i) = candidate;
                        break;
                    }
                }
            }

        father.check();
        if (father._check == "no") {
            //cout << "Padre non valido, ripristino" << endl;
            father = _chromosome(index2);
        }
    }
}
