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

typename Guia_Tlf::const_iterator Guia_Tlf::begin() const {
    const_iterator it(datos.begin());
    return it;
}

typename Guia_Tlf::const_iterator Guia_Tlf::end() const {
    const_iterator it(datos.end());
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