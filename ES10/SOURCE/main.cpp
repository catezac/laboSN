#include <iostream>
#include "population.h"

using namespace std;

int main() {
    Population pop;
    pop.initialize();

    Population new_pop;
    new_pop.initialize();

    int n_generations = SetParameter("input.dat", "NGENERATIONS");
    double p_crossover = SetParameter("input.dat", "P_CROSSOVER");

    pop.first_popul(); //genero la prima popolazione
    vec L1_medio(n_generations);
    vec L1(n_generations);
    pop.sorting();
    pop._chromosome(pop._nchrom-1).Write_Config("../OUTPUT/best_config_iniziale.dat");
    for(int i = 0; i < n_generations; i++) {
        pop.sorting();
        L1(i) = pop._chromosome(pop._nchrom - 1).loss();
        L1_medio(i) = pop.L1_ave();
        //copio i due migliori
        new_pop._chromosome(0) = pop._chromosome(pop._nchrom-1);
        new_pop._chromosome(1) = pop._chromosome(pop._nchrom-2);
        // faccio crossover scegliendo tra i migliori, muto i figli 
        int j = 2;
        while(j < pop._nchrom){
            Chromosome mother(pop._chromosome(0)._ncity); // selection
            Chromosome father(pop._chromosome(0)._ncity); // selection
            pop.crossover(mother, father);
            new_pop._chromosome(j) = mother;
            new_pop._chromosome(j+1) = father;
            j+=2;
        }
        pop = new_pop;
        pop.Mutation();
        //pop.sorting();
        //L1(i) = pop._chromosome(pop._nchrom - 1).loss();
    }
    //pop.sorting();
    pop._chromosome(pop._nchrom-1).Write_Config("../OUTPUT/best_config.dat");
    WriteToFile("../OUTPUT/L1_medio.dat", n_generations, L1_medio);
    WriteToFile("../OUTPUT/L1_best.dat", n_generations, L1);

    return 0;
}