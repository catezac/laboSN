#include <iostream>
#include "population.h"

using namespace std;

int main() {
    Random rnd;
    int n_generations = SetParameter("input.dat", "NGENERATIONS");
    double p_crossover = SetParameter("input.dat", "P_CROSSOVER");
    double r;
    Population pop;
    pop.initialize();
    pop.first_popul(); //genero la prima popolazione
    vec L2_medio(n_generations);
    vec L2(n_generations);
    pop.sorting();
    pop._chromosome(pop._chromosome.n_elem-1).Write_Config("best_config_iniziale.dat");
    for(int i = 0; i < n_generations; i++) {
        L2_medio(i) = pop.L2_ave();     // salvo il valor medio di L2, mediato sulla metà migliore della popolazione
        // faccio evolvere l'algoritmo genertico facendo:
        // - le mutazioni, ciascuna con una certa probabilità
        // - crossover con una certa probabilità
        //int index = pop.selection();
        pop.Mutation();
        pop.sorting();                  //metto in ordine la popolazione in base alla L2
        r = rnd.Rannyu();
        if (r < p_crossover){
            int index1 = pop.selection();
            int index2 = pop.selection();
            //cout << "Sto facendo crossover su cromosoma "<< index1 << " e " << index2 << endl;
            pop.crossover(index1, index2);
            pop.sorting(); 
            L2(i) = pop._chromosome(pop._chromosome.n_elem-1).loss();
        }
        //pop._chromosome(pop._chromosome.n_elem-1).Write_Config("config_" + to_string(i) + ".dat");
    }
    //pop.sorting();
    pop._chromosome(pop._chromosome.n_elem-1).Write_Config("best_config.dat");
    WriteToFile("L2_medio.dat", n_generations, L2_medio);
    WriteToFile("L2_best.dat", n_generations, L2);

    return 0;
}