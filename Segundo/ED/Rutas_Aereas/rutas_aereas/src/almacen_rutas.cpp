#include "almacen_rutas.h"

Ruta Almacen_Rutas::GetRuta(const string a) {
    iterator it;
    for (it = begin(); it != end() && !((*it)==a); ++it);
    return *it;
}

void Almacen_Rutas::Insertar(const Ruta &R){
	datos.insert(R);
}

void Almacen_Rutas::Borrar(const Ruta &R){
	datos.erase(R);
}

Almacen_Rutas::iterator Almacen_Rutas::begin(){
	iterator it;
	it.r = datos.begin();
	return it;
} 

Almacen_Rutas::const_iterator Almacen_Rutas::begin()const{
	const_iterator it;
	it.r = datos.begin();
	return it;
}

Almacen_Rutas::iterator Almacen_Rutas::end(){
	iterator it;
	it.r = datos.end();
	return it;
}

Almacen_Rutas::const_iterator Almacen_Rutas::end()const{
	const_iterator it;
	it.r = datos.end();
	return it;
}

Almacen_Rutas::iterator Almacen_Rutas::find(const Ruta &r){
    iterator it;
    set<Ruta>::iterator i;
    for (i=datos.begin(); i!=datos.end() && !((*i)==r);++i);
    it.r=i;
    return it;
}

istream & operator>>(istream & is, Almacen_Rutas & R){
    Almacen_Rutas rlocal;
    //leemos el comentario
    if (is.peek()=='#'){
		string a;
		getline(is,a);
    }

    Ruta P;

    while (is.peek() != '#' && !is.eof()){
		is >> P;
		rlocal.Insertar(P);
		is.ignore(100, '\n');
    }

	if (is.peek() == '#') {
		string a;
		getline (is,a);
		while (!is.eof()) {
			rlocal.nInteres++;
			pair<Punto, string> p;
			is >> p.first;
			getline(is, p.second);
			rlocal.puntosInteres.insert(p);
		}
	}
    
    R=rlocal;
    return is;
}

ostream & operator<<(ostream & os, const Almacen_Rutas &R){	
    Almacen_Rutas::const_iterator it;
    for (it=R.begin(); it!=R.end(); ++it){
	os<<*it<<"\n";
    }
	if (R.nInteres > 0) {
		os << "\nLos puntos de interés:\n";
		map<Punto,string>::const_iterator i;
		for (i = R.puntosInteres.begin(); i != R.puntosInteres.end(); ++i) {
			os << (*i).first << (*i).second << endl;
		}
	}
    return os;
}