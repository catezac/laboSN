#ifndef __Posizione_h__
#define __Posizione_h__

//#include <iostream>
//#include <cmath>  // Per sqrt()

class Posizione {
private:
    double x, y, z;  // Coordinate della posizione

public:
    // Costruttori
    Posizione();
    Posizione(double x_val, double y_val, double z_val);

    // Metodi setter
    void setX(double x_val);
    void setY(double y_val);
    void setZ(double z_val);

    void sferichex(double a, double r, double theta, double fi);
    void sferichey(double a, double r, double theta, double fi);
    void sferichez(double a, double r, double theta, double fi);

    // Metodi getter
    double getX() const;
    double getY() const;
    double getZ() const;

    // Metodo per calcolare la distanza dall'origine
    double distanza2_O() const;

    // Metodo per stampare la posizione
    void stampa() const;
};

#endif // POSIZIONE_H
