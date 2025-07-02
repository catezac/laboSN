#include <iostream>
#include <iomanip>
#include "population.h"
#include "mpi.h"

using namespace std;


void print_progress_bar(float progress) {
  int bar_width = 50;
  int pos = bar_width * progress / 100.0;

  cout << "\rProgress: [";
  for (int j = 0; j < bar_width; ++j) {
      if (j < pos) cout << "=";
      else if (j == pos) cout << ">";
      else cout << " ";
  }
  cout << "] " << fixed << setprecision(1) << progress << "%";
  cout.flush();
}


int main(int argc, char* argv[]) {

    int size, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    Population pop;
    pop.initialize(rank);

    Population new_pop;
    new_pop.initialize(rank);
    cout << "Inizializzazione completata" << endl;
    int n_generations = SetParameter("input.dat", "NGENERATIONS");
    double p_crossover = SetParameter("input.dat", "P_CROSSOVER");
    int migration = SetParameter("input.dat", "MIGRATION");

    pop.first_popul(); //genero la prima popolazione
    vec L1_medio(n_generations);
    vec L1(n_generations);
    pop.sorting();
    if(rank == 0) pop._chromosome(pop._nchrom-1).Write_Config("../OUTPUT/best_config_iniziale.dat");
    for(int i = 0; i < n_generations; i++) {
        if(rank == 0) print_progress_bar(float(i+1)/n_generations*100);
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
        if(i%migration == 0 & i !=0) {
            //cout << "Migrazione " << i/migration << endl;
            pop.sorting();
            pop.Migration(size, rank);
        }
    }
    pop.sorting();
    double loss; 
    loss = pop._chromosome(pop._nchrom-1).loss();
    
    double send[2] = {loss, static_cast<double>(rank)};
    double rec[2];
    MPI_Reduce(send, rec, 1, MPI_2DOUBLE_PRECISION, MPI_MINLOC, 0, MPI_COMM_WORLD);
    MPI_Bcast(rec, 2, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    int best_rank = rec[1];
    //cout << best_rank << endl;

    if (rank == best_rank) {
        pop._chromosome(pop._nchrom-1).Write_Config("../OUTPUT/best_config.dat");
        WriteToFile("../OUTPUT/L1_medio.dat", n_generations, L1_medio);
        WriteToFile("../OUTPUT/L1_best.dat", n_generations, L1);
    }

    MPI_Finalize();
    return 0;
}