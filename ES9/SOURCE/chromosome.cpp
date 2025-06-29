#include <cmath>
#include <cstdlib>
#include <string>
#include <fstream>
#include "chromosome.h"

using namespace std;
using namespace arma;

void Chromosome::Circle() { // creazione delle città sul cerchio
    for(int i = 0; i < _ncity ;i++){
        _cities(i)._pos(0) = i;
        double r = _rnd.Rannyu(0, 2*M_PI);  // la città è collocata in base all'angolo sulla circonferenza
        _cities(i)._pos(1) = _radius * cos(r);
        _cities(i)._pos(2) = _radius * sin(r);
    }
}

void Chromosome::Square(){ // creazione delle città nel quadrato
    for(int i = 0; i < _ncity ;i++){
        _cities(i)._pos(0) = i;
        _cities(i)._pos(1) = _rnd.Rannyu(0,_length);
        _cities(i)._pos(2) = _rnd.Rannyu(0,_length);
    }
}

void Chromosome::File(string filename){
    ifstream read(filename);
    
    if (!read.is_open()) {
        cerr << "Errore nell'apertura del file!" << std::endl;
    }
    int N=0;
    string riga;
    while(getline(read, riga)){
        N++;
    }
    // Torna all'inizio del file
    read.clear();           // resetta EOF
    read.seekg(0, ios::beg); // torna all'inizio
    _ncity = N;
    _cities.set_size(int(_ncity));
    double x = 0;
    double y = 0;
    for(int i = 0; i<N;i++){
        read >> x >> y;
        _cities(i)._pos(0) = i;
        _cities(i)._pos(1) = x;
        _cities(i)._pos(2) = y;
    }

    read.close();
}

void Chromosome::configuration() { 
    // inizializzazione della config del sistema e settaggio delle posizioni delle città
    _ncity = SetParameter("input.dat", "NCITY");
    auto c = SetConfig("input.dat", "CONFIGURATION");
    _config = c.first;
    _cities.set_size(int(_ncity));
    if(_config == "circle"){
        _radius = stod(c.second);
        Circle();
    } else if(_config == "square"){
        _length = stod(c.second);
        Square();   
    } else if(_config == "file"){
        File(c.second);
    } else {
        cerr << "PROBLEM: unknown configuration" << endl;
        exit(EXIT_FAILURE);
    } 
    return;
}

void Chromosome :: check(){
    if(_cities(0).getpos(0)!=0) {
        _check = "no"; 
    } else if (_cities(0).getpos(0) == 0){
        _check = "yes";
    } // la prima città deve essere sempre la 0
    for(int i = 0; i< _ncity; i++) {
        for(int j = 0; j < _ncity; j++){
            if (i==j){
                continue;
            } else{
                if (_cities(i) == _cities(j)) {
                    _check = "no";
                }
            }
        }
    }
} /*funzione che controlla che il cromosoma rispetti i constraint:  
                        1. all the cities has to be visited once and only once
                        2. the first city has to be always at position 1 in each chromosome 
                        (3. at the end the saleman has to return to the first city --> questo lo metterò nella loss) */
double Chromosome::distance(City citta1, City citta2){
    double x2 = pow((citta1.getpos(1)-citta2.getpos(1)),2);
    double y2 = pow((citta1.getpos(2)-citta2.getpos(2)),2);
    return sqrt(x2+y2);
}
                        
double Chromosome::loss() {
    double sum = 0;
    for(int i = 0; i<_ncity-1; i++){
        sum += distance(_cities(i),_cities(i+1));
    }
    sum += distance(_cities(_ncity-1),_cities(0));
    return sum;
}

void Chromosome::permutation(){  //scambia la posizione di due città casuali
    int i = rint(_rnd.Rannyu(1, _ncity-1));
    int j = rint(_rnd.Rannyu(1, _ncity-1));
    if (i !=0 && i!= j) {
        City city_appo;
        city_appo = _cities(i);
        _cities(i).setpos(_cities(j).getpos());
        _cities(j).setpos(city_appo.getpos());
    }
}

void Chromosome::permutation_m(){  //scambia la posizione di m città casuali
    int m = rint(_rnd.Rannyu(0, _ncity-1));
    for(int k = 0; k<m; k++) {
        int i = rint(_rnd.Rannyu(0, _ncity-1));
        int j = rint(_rnd.Rannyu(0, _ncity-1));
        if (i !=0 && i!= j) {
            City city_appo;
            city_appo = _cities(i);
            _cities(i).setpos(_cities(j).getpos());
            _cities(j).setpos(city_appo.getpos());
        }
    } 
}

// Funzione per eseguire uno shift circolare a destra su un arma::field<City>
field<City> shift_field(const field<City>& input, int n) {
    
    // Ottengo la dimensione del field (numero di città)
    int len = input.n_elem;

    // Creo un nuovo field con la stessa dimensione per memorizzare l'output
    field<City> output(len);

    // Calcolo lo shift effettivo (positivo e compreso tra 0 e len-1)
    // Questo gestisce anche valori negativi di n
    int k = ((n % (len)) + len) % len;

    // Scorro ogni elemento dell'input
    for (int i = 0; i < len; ++i) {
        // Inserisco l'elemento nella nuova posizione ruotata nel field di output
        output((i + k) % len) = input(i);
    }

    // Ritorno il field ruotato
    return output;
}

void Chromosome::shift_n(){
    // Estrai sottovettore
    int m = rint(_rnd.Rannyu(1,_ncity-1));
    int n = rint(_rnd.Rannyu(1,_ncity-1));
    int start = rint(_rnd.Rannyu(1,_ncity-m-1));
    int end = start+2*m;
    int len = 2 * m;
    if(start+2*m < _ncity) {
        // Crea field temporaneo e copia a mano
        field<City> sub(len);
        for (int i = 0; i < len; ++i) {
            sub(i) = _cities(start + i);
        }
        // Shift circolare
        field<City> shifted_sub = shift_field(sub, n);
        // Riassegna al vettore originale
        for (int i = 0; i < len; ++i) {
            _cities(start + i) = shifted_sub(i);
        }
    }
}

void Chromosome::inversion() {
    // Estrai sottovettore
    int m = rint(_rnd.Rannyu(1,_ncity-1));
    int start = rint(_rnd.Rannyu(1,_ncity-m-1));
    int end = start+m;
    int len = m;
    if(start+m < _ncity) {
        // Crea field temporaneo e copia a mano
        field<City> sub(len);
        for (int i = 0; i < len; i++) {
            sub(i) = _cities(start + i);
        }
        // inversione
        field<City> inverted(len);
        for(int i = 0; i<len;i++){
            inverted(i) = sub(len-1-i);
        }
        // Riassegna al vettore originale
        for (int i = 0; i < len; i++) {
            _cities(start + i) = inverted(i);
        }
    }
}

void Chromosome::Write_Config(string filename){
    ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < _ncity; i++) {
            file << _cities(i)._pos[0] << " " << _cities(i)._pos[1] << " " << _cities(i)._pos[2] << endl;
        }
        file.close();
    } else {   cerr << "Unable to open " << filename << endl; }
}