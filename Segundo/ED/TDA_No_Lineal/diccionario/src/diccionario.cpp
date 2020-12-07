#include <iostream>
#include <string>
#include <list>
#include <diccionario.h>


//--------------------------Implementación iterator------------------------------------


template<class T, class U>
typename Diccionario<T,U>::iterator & Diccionario<T,U>::iterator::operator=(const iterator &it) {
    if (*this != it)
        vit = it.vit;

    return *this;
}

template<class T, class U>
typename Diccionario<T,U>::iterator & Diccionario<T,U>::iterator::operator++() {
    vit++;
    return *this;
}

template<class T, class U>
typename Diccionario<T,U>::iterator & Diccionario<T,U>::iterator::operator--() {
    vit--;
    return *this;
}

template<class T, class U>
data<T,U> & Diccionario<T,U>::iterator::operator*() {
    return *vit;
}

template<class T, class U>
typename Diccionario<T,U>::iterator Diccionario<T,U>::begin() {
    iterator it(datos.begin());
    return it;
}

template<class T, class U>
typename Diccionario<T,U>::iterator Diccionario<T,U>::end() {
    iterator it(datos.end());
    return it;
}

template<class T, class U>
bool Diccionario<T,U>::iterator::operator!=(const iterator &it) const {
    return vit != it.vit;
}

template<class T, class U>
bool Diccionario<T,U>::iterator::operator==(const iterator &it) const {
    return vit == it.vit;
}

//--------------------------Implementación const_iterator------------------------------------

template<class T, class U>
typename Diccionario<T,U>::const_iterator & Diccionario<T,U>::const_iterator::operator=(const const_iterator &it) {
    if (*this != it)
        vit = it.vit;

    return *this;
}

template<class T, class U>
typename Diccionario<T,U>::const_iterator & Diccionario<T,U>::const_iterator::operator++() {
    vit++;
    return *this;
}

template<class T, class U>
typename Diccionario<T,U>::const_iterator & Diccionario<T,U>::const_iterator::operator--() {
    vit--;
    return *this;
}

template<class T, class U>
const data<T,U> & Diccionario<T,U>::const_iterator::operator*() const {
    return *vit;
}

template<class T, class U>
typename Diccionario<T,U>::const_iterator Diccionario<T,U>::cbegin() const {
    const_iterator c_it(datos.cbegin());
    return c_it;
}

template<class T, class U>
typename Diccionario<T,U>::const_iterator Diccionario<T,U>::cend() const {
    const_iterator c_it(datos.cend());
    return c_it;
}

template<class T, class U>
bool Diccionario<T,U>::const_iterator::operator!=(const const_iterator &it) const {
    return vit != it.vit;
}

template<class T, class U>
bool Diccionario<T,U>::const_iterator::operator==(const const_iterator &it) const {
    return vit == it.vit;
}

//--------------------------Implementación métodos------------------------------------

template<class T, class U>
void Diccionario<T,U>::Copiar(const Diccionario<T,U>& D) {
   typename Diccionario<T,U>::const_iterator it_d;
   typename Diccionario<T,U>::iterator it=this->begin();
   
   //datos.assign(D.datos.begin(),D.datos.end());
   for (it_d=D.cbegin(); it_d!=D.cend();++it_d,++it){
	    datos.insert(it.vit,*it_d);   
   }
}

template<class T, class U>
void Diccionario<T,U>::Borrar() {  
    this->datos.erase(datos.begin(),datos.end());
}

template<class T, class U>
Diccionario<T,U> & Diccionario<T,U>::operator=(const Diccionario<T,U> &D){
	if (this!=&D){
		Borrar();
		Copiar(D);
	}
	return *this;
}

template<class T, class U>
bool Diccionario<T,U>::Esta_Clave(const T &p, typename  list<data<T,U> >::iterator &it_out){

	if (datos.size()>0) {

		typename list<data<T,U> >::iterator it;

		for (it=datos.begin(); it!=datos.end() ;++it){

			if ((*it).clave==p) {
				it_out=it;
				return true;
			} else if ((*it).clave>p) {
				it_out=it;
				return false;
			}
		}

		it_out=it;
		return false;
	} else {	
		it_out=datos.end();
		return false;
	}	    
}


template<class T, class U>
void Diccionario<T,U>::Insertar(const T& clave,const list<U> &info){

	typename list<data<T,U> >::iterator it;

	if (!Esta_Clave(clave,it)){
		data<T,U> p;
		p.clave = clave;
		p.info_asoci=info;
		datos.insert(it,p);
	}
}


template <class T, class U>
void Diccionario<T,U>::AddSignificado_Palabra(const U & s ,const T &p){
	typename list<data<T,U> >::iterator it;

	if (!Esta_Clave(p,it)){
		datos.insert(it,p);
	}	    

	    //Insertamos el siginificado al final
    (*it).info_asoci.insert((*it).info_asoci.end(),s);
}

template<class T, class U>
list<U>  Diccionario<T,U>::getInfo_Asoc(const T & p) {
	typename list<data<T,U> >::iterator it;

	if (!Esta_Clave(p,it)) {
	    return list<U>();
	} else {
	    return (*it).info_asoci;
	}
}