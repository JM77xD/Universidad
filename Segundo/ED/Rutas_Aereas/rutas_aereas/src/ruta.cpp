#include "ruta.h"

Ruta::Ruta(string nombre, list<Punto> p) {
    nombreRuta = nombre;
    puntos = p;
    nPuntos = p.size();
}

Ruta::Ruta(const Ruta &r) {
    nombreRuta = r.nombreRuta;
    nPuntos = r.nPuntos;
    puntos = r.puntos;
}

Punto Ruta::getPunto(int pos) {
    assert(pos < puntos.size());
    list<Punto>::iterator it = puntos.begin();
    for (int i = 0; i < pos; i++)
        ++it;
    return *it;
}

ostream &operator<<(ostream &os, const Ruta &r) {
    os << r.nombreRuta << "\t" << r.nPuntos << "\t";

    list<Punto>::const_iterator it;

    for (it = r.puntos.cbegin(); it != r.puntos.cend(); ++it)
        os << *it;
    
    return os;
}

istream & operator>>(istream &is , Ruta & r) {
    is >> r.nombreRuta >> r.nPuntos;

    for (int i = 0; i < r.nPuntos; i++) {
        Punto p;
        is >> p;
        r.puntos.push_back(p);
    }

    return is;
}

Ruta::iterator Ruta::begin(){
	iterator it;
	it.p = puntos.begin();
	return it;
} 


Ruta::const_iterator Ruta::begin()const{
	const_iterator it;
	it.p = puntos.begin();
	return it;
}

Ruta::iterator Ruta::end(){
	iterator it;
	it.p = puntos.end();
	return it;
}

Ruta::const_iterator Ruta::end()const{
	const_iterator it;
	it.p = puntos.end();
	return it;
}

Ruta::iterator Ruta::find(const Punto &p){
    iterator it;
    list<Punto>::iterator i;
    for (i=puntos.begin(); i!=puntos.end() && !((*i)==p);++i);
    it.p=i;
    return it;
}