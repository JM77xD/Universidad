#include "Pais.h"

ostream & operator<<(ostream & os, const Pais &P) {
    os<<P.p<<" "<<P.pais<<" "<<P.bandera<<endl;
    return os;
}

istream & operator>>(istream & is, Pais & P){
    double lat,lng;

    is>>lat>>lng>>P.pais>>P.bandera;

	P.p=Punto(lat,lng,' ');
	return is;
}