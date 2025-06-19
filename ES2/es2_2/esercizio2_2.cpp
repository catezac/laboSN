#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include "/home/catezac/laboSN/PRNG/random.h"
#include "Posizione.h"
#include "../funzioni.h"

using namespace std;

int main(){
    Random rnd;
    Random rnd_angolo;

    // random walk on a cubic lattice with step length a = 1
    int M = 10000; //number of steps
    int N = 100; //number of blocks
    int L = M/N; //number of steps in each block

    vector <double> ave_r2(N);
    vector <double> av2_r2(N);
    vector <double> ave_r2_c(N);
    vector <double> av2_r2_c(N);

    int N_step = 100; // passi del RW
    int a = 1; // passo del reticolo

    vector <Posizione> p(M); //vettore di posizioni per M random walks, ogni volta cancello la posizione precedente e salvo la successiva
    vector <Posizione> p_c(M); // vettore di posizioni per il random walk continuo
    vector <Posizione> pos(L); //vettore di posizioni per 1 RW_discreto, per disegnarlo
    vector <Posizione> pos_c(L); // vettore di posizioni per 1 RW_continuo, per disegnarlo

    vector <double> sqrt_r2_medio_d(N_step); // per ogni passo salvo sqrt(r^2) finale dopo aver farro la media a blocchi, _discreto
    vector <double> sqrt_r2_err_d(N_step);     // salvo errore del valore finale, valutato con la media a blocchi, _continuo

    vector <double> sqrt_r2_medio_c(N_step); // per ogni passo salvo sqrt(r^2) finale dopo aver farro la media a blocchi, _continuo
    vector <double> sqrt_r2_err_c(N_step);  // salvo errore del valore finale, valutato con la media a blocchi, _continuo

    double sum_r2 = 0; // per salvare la somma che mi serve per calcolare la media dentro a un blocco
    double sum_r2_c = 0; // per salvare la somma che mi serve per calcolare la media dentro a un blocco

    double r; // random number for the discrete random walk
    double r_theta; // random number for theta angle for the continuous random walk
    double r_fi; // random number for fi angle for the continuous random walk
    for(int i = 0; i < N_step; i++) {                // ciclo sui passi
        
        for(int j = 0; j < N; j++) {                 // ciclo sui blocchi
            sum_r2 = 0;   
            sum_r2_c = 0;                           // azzero la somma per ogni blocco 
            for(int k = 0; k < L; k++) {            // ciclo all'interno di un blocco che è fatto da L esperimenti
                r = rnd.Rannyu(0,6);
                r = floor(r);                       // passo discreto
                r_theta = rnd_angolo.Rannyu();             // angolo theta continuo
                r_fi = rnd_angolo.Rannyu();                // angolo fi continuo
                if(j*N+k == 0){                      // salvo le posizioni dell'ultimo RW per poterle disegnare
                    pos[i] = p[j*N+k];
                    pos_c[i] = p_c[j*N+k];
                }
                RW3D_discrete(p[j*N+k], r, a);       // per fare ogni esperimento genero il passo successivo del RW aggiornando il precedente
                RW3D_continuum(p_c[j*N+k], r_theta, r_fi, a);
                sum_r2 += p[j*N+k].distanza2_O();    // dopo aver aggiornato il passo calcolo la distanza dall'origine al qudrato e la sommo dentro a sum_r2
                sum_r2_c += p_c[j*N+k].distanza2_O();
                
            }
            
            ave_r2[j] = sqrt(sum_r2/L);              // in ogni blocco faccio la media, quindi alla fine ave_r2 contiene N valori medi
            av2_r2[j] = pow(ave_r2[j],2);            // calcolo anche il valor medio al quadrato che mi serve poi per calcolare l'errore
            ave_r2_c[j] = sqrt(sum_r2_c/L);
            av2_r2_c[j] = pow(ave_r2_c[j],2);

        }

        auto result_d = sum_prog(ave_r2, av2_r2, N);
        auto result_c = sum_prog(ave_r2_c, av2_r2_c, N);

        sqrt_r2_medio_d[i] = result_d.first[N-1];     // il valore di r^2 che considero è l'ultimo valor medio della media a blocchi
        sqrt_r2_err_d[i] = result_c.second[N-1] ;

        sqrt_r2_medio_c[i] = result_c.first[N-1];     // il valore di r^2 che considero è l'ultimo valor medio della media a blocchi
        sqrt_r2_err_c[i] = result_d.second[N-1];
    }   

    Write_config("config_discreto.dat", L, pos);
    Write_config("config_continuo.dat", L, pos_c);
    WriteToFile_RW("sqrt_r2_medio.dat", N_step, sqrt_r2_medio_d, sqrt_r2_err_d);
    WriteToFile_RW("sqrt_r2_medio_continuum.dat", N_step, sqrt_r2_medio_c, sqrt_r2_err_c);
    
    return 0;
}