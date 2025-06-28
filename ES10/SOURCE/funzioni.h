#ifndef __funzioni_h
#define __funzioni_h

#include <vector>
#include <string>
#include <utility>
#include <armadillo>

using namespace std;
using namespace arma;

// Legge un parametro numerico da file
double SetParameter(string filename, string prop);

// Legge una configurazione (stringa + valore) da file
pair<string, string> SetConfig(string filename, string prop);

void WriteToFile(string filename, int N, vec L2);

#endif // __funzioni_h