#include "Posizione.h"
#include <iostream>
#include <cmath> 

using namespace std;

// Costruttore di default
Posizione::Posizione() 
{
  x = 0;
  y = 0;
  z = 0;
}

// Specific costructor, in coordiante cartesiane
Posizione::Posizione(double x, double y, double z) 
{
  x = x;
  y = y;
  z = z;
}


// Destructor
//Posizione::~Posizione() {}

// modifica il valore di una coordinata
void Posizione::setX(double x_val) { x = x_val; }
void Posizione::setY(double y_val) { y = y_val; }
void Posizione::setZ(double z_val) { z = z_val; }


// modifica posizione in coordinate sferiche
void Posizione::sferichex(double a, double r, double theta, double fi) { x = a + r * (sin(theta)* cos(fi));  }
void Posizione::sferichey(double a, double r, double theta, double fi) { y = a + r * (sin(theta)* sin(fi));  }
void Posizione::sferichez(double a, double r, double theta, double fi) { z = a + r * (cos(theta));           }

// Metodi per ottenere le singole coordinate
double Posizione::getX() const { return x; }
double Posizione::getY() const { return y; }
double Posizione::getZ() const { return z; }

// Metodo per ottenere la distanza dall'origine
double Posizione::distanza2_O() const {
    return (pow(x,2) + pow(y,2) + pow(z,2));
}

// Metodo per stampare la posizione
void Posizione::stampa() const {
    cout << "Posizione: (" << x << ", " << y << ", " << z << ")\n";
}


