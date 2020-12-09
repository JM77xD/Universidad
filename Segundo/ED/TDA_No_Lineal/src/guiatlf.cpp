#include <map>
#include <iostream>
#include <string>
#include <guiatlf.h>

using namespace std;
//------------------------------------Implementación de iterator-----------------------

typename Guia_Tlf::iterator & Guia_Tlf::iterator::operator=(const iterator &it) {
    if (*this != it)
        vit = it.vit;

    return *this;
}

typename Guia_Tlf::iterator & Guia_Tlf::iterator::operator++() {
    vit++;
    return *this;
}

typename Guia_Tlf::iterator & Guia_Tlf::iterator::operator--() {
    vit--;
    return *this;
}

pair<const string,string> & Guia_Tlf::iterator::operator*() {
    return *vit;
}

typename Guia_Tlf::iterator Guia_Tlf::begin() {
    iterator it(datos.begin());
    return it;
}

typename Guia_Tlf::iterator Guia_Tlf::end() {
    iterator it(datos.end());
    return it;
}

bool Guia_Tlf::iterator::operator!=(const iterator &it) const {
    return vit != it.vit;
}

bool Guia_Tlf::iterator::operator==(const iterator &it) const {
    return vit == it.vit;
}

//------------------------------------Implementación de const_iterator-----------------

typename Guia_Tlf::const_iterator & Guia_Tlf::const_iterator::operator=(const const_iterator &it) {
    if (*this != it)
        vit = it.vit;

    return *this;
}

typename Guia_Tlf::const_iterator & Guia_Tlf::const_iterator::operator++() {
    vit++;
    return *this;
}

typename Guia_Tlf::const_iterator & Guia_Tlf::const_iterator::operator--() {
    vit--;
    return *this;
}

const pair<const string,string> & Guia_Tlf::const_iterator::operator*() const {
    return *vit;
}

typename Guia_Tlf::const_iterator Guia_Tlf::cbegin() const {
    const_iterator it(datos.cbegin());
    return it;
}

typename Guia_Tlf::const_iterator Guia_Tlf::cend() const {
    const_iterator it(datos.cend());
    return it;
}

bool Guia_Tlf::const_iterator::operator!=(const const_iterator &it) const {
    return vit != it.vit;
}

bool Guia_Tlf::const_iterator::operator==(const const_iterator &it) const {
    return vit == it.vit;
}

//------------------------------------Implementación de métodos-----------------------

istream & operator>>(istream &is,pair<string,string> &d){
	  
	  getline(is,d.first,'\t');
	  getline(is,d.second);
	  return is;
}

Guia_Tlf::Guia_Tlf(const Guia_Tlf & gt) {
    datos.insert(gt.datos.begin(), gt.datos.end());
}

Guia_Tlf & Guia_Tlf::operator=(const Guia_Tlf & gt) {
    if (this->datos != gt.datos) {
        this->clear();
        datos.insert(gt.datos.begin(), gt.datos.end());
    }

    return *this;
}

string & Guia_Tlf::operator[](const string &nombre) {
    return datos[nombre];
}

string  Guia_Tlf::gettelefono(const string & nombre){
    map<string,string>::iterator it=datos.find(nombre);
    if (it==datos.end()) 
		return string("");
    else return it->second;
}

pair<map<string,string>::iterator,bool>  Guia_Tlf::insert(string nombre, string tlf){
    pair<string,string> p (nombre,tlf);
    pair< map<string,string> ::iterator,bool> ret;
	ret=datos.insert(p); 
	return ret;     
		
}

pair<map<string,string>::iterator,bool>  Guia_Tlf::insert(pair<string,string> p){
		      
    pair<map<string,string> ::iterator,bool> ret;
    ret=datos.insert(p); 
    return ret;     
		
}

void Guia_Tlf::borrar(const string &nombre){
	map<string,string>::iterator itlow = datos.lower_bound(nombre);//el primero que tiene dicho nombre
	map<string,string>::iterator itupper = datos.upper_bound(nombre);//el primero que ya no tiene dicho nombre
	datos.erase(itlow,itupper);//borramos todos aquellos que tiene dicho nombre
}

void Guia_Tlf::borrar(const string &nombre,const string &tlf){
    map<string,string>::iterator itlow = datos.lower_bound(nombre);//el primero que tiene dicho nombre
	map<string,string>::iterator itupper = datos.upper_bound(nombre);//el primero que ya no tiene dicho nombre
	map<string,string>::iterator it;
	bool salir =false;
	for (it=itlow; it!=itupper && !salir;++it){
	    if (it->second==tlf){
			datos.erase(it);
			salir =true;
	    }		
	}   
}

int Guia_Tlf::size() const {
    return datos.size();
}

unsigned int Guia_Tlf::contabiliza(const string &nombre){
    return datos.count(nombre);
}

void Guia_Tlf::clear(){
    datos.clear();
}

Guia_Tlf Guia_Tlf::interseccion(Guia_Tlf &G) {
    Guia_Tlf aux;
    Guia_Tlf::iterator it_b;
    Guia_Tlf::iterator it_e = end();

    for (it_b = begin();it_b != it_e; ++it_b) {

        if (G.contabiliza((*it_b).first) > 0) {

            Guia_Tlf::iterator it_low(G.datos.lower_bound((*it_b).first));
            Guia_Tlf::iterator it_up(G.datos.upper_bound((*it_b).first));
            Guia_Tlf::iterator it;
            bool salir = false;

            for (it = it_low; it != it_up && !salir; ++it) {
                if ((*it).second == (*it_b).second) {
                    aux.insert(*it_b);
                    salir = true;
                }
            }

        }
    }

    return aux;
}

void Guia_Tlf::modificar(const string &nombre, const string &tlf) {
    unsigned int aparece = contabiliza(nombre);
    if (aparece > 1) {
        Guia_Tlf::iterator itlow(datos.lower_bound(nombre));
	    Guia_Tlf::iterator itupper(datos.upper_bound(nombre));
	    Guia_Tlf::iterator it;
        unsigned int cont = 1;
        cout << "\nLos teléfonos asociados a ese nombre son:\n";
        for (it = itlow; it != itupper; cont++, ++it) {
            cout << cont << ".\t" << (*it).second << endl;
        }
        cout << "\n\nCuál desea modificar? ";
        unsigned int mod;
        cin >> mod;
        it = itlow;
        for (cont = 1; cont != mod; cont++)
            ++it;
        (*it).second = tlf;
        cout << "\nEl nuevo teléfono es: " << (*it).second << endl;
    } else if (aparece == 1) {
        Guia_Tlf::iterator it(datos.lower_bound(nombre));
        (*it).second = tlf;
        cout << "\nEl nuevo teléfono es: " << (*it).second << endl;
    } else
        cout << "\n\nNo existe ese nombre en la guía.\n\n";
}

string Guia_Tlf::gettelefonos(char &c) {
    Guia_Tlf::iterator it_b = begin();
    Guia_Tlf::iterator it_e = end();
    Guia_Tlf::iterator it;
    string telefonos;
    c = toupper(c);

    for (it = it_b; it != it_e; ++it) {
        if ((*it).first[0] == c){
            telefonos +=(*it).first + '-' + (*it).second + '\n';
        }
    }
    
    return telefonos;
}

Guia_Tlf Guia_Tlf::rango(string &nombre1, string &nombre2) {
    Guia_Tlf::iterator it_b = begin();
    Guia_Tlf::iterator it_e = end();
    Guia_Tlf::iterator it;
    Guia_Tlf result;
    if (nombre1.compare(nombre2) > 0) {
        string aux = nombre1;
        nombre1 = nombre2;
        nombre2 = nombre1;
    }

    for (it = it_b; it != it_e; ++it) {
        if ((*it).first.compare(0, nombre1.length(), nombre1) >= 0 && (*it).first.compare(0, nombre2.length(), nombre2) <= 0)
            result.insert(*it);
    }

    return result;
}


Guia_Tlf Guia_Tlf::operator+(const Guia_Tlf & g){
	Guia_Tlf aux(*this);
	map<string,string>::const_iterator it;
	for (it=g.datos.begin();it!=g.datos.end();++it){
   		aux.insert(it->first,it->second);
	}	  
	return aux;
}

Guia_Tlf Guia_Tlf::operator-(const Guia_Tlf & g){
	Guia_Tlf aux(*this);
	map<string,string>::const_iterator it;
	for (it=g.datos.begin();it!=g.datos.end();++it){
		aux.borrar(it->first,it->second);
	}	  
	return aux;
}

ostream & operator<<(ostream & os, Guia_Tlf & g){
    map<string,string>::iterator it;
    for (it=g.datos.begin(); it!=g.datos.end();++it){
		os<<it->first<<"\t"<<it->second<<endl;
    }
    return os;
}

istream & operator>>(istream & is, Guia_Tlf & g){

    pair<string,string> p;
    Guia_Tlf aux;
      
    while (is>>p) {
		aux.insert(p);
    }
    is.clear();
    g=aux;
    return is;
}