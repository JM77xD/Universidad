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
   
   typename list<data<T,U>>::const_iterator it_d = D.datos.cbegin();
   typename list<data<T,U>>::iterator it=datos.begin();
   
   
   //datos.assign(D.datos.begin(),D.datos.end());
   
   for (it_d; it_d!=D.datos.cend();++it_d,++it){
	    datos.insert(it,*it_d);
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

	Diccionario<T,U>::iterator it;

	if (!Esta_Clave(clave,it.vit)){
		data<T,U> p;
		p.clave = clave;
		p.info_asoci=info;
		datos.insert(it.vit,p);
	}
}

template<class T, class U>
void Diccionario<T,U>::del(const T& clave) {
	Diccionario<T,U>::iterator it;

	if (Esta_Clave(clave, it.vit))
			this->datos.erase(it.vit);
}

template<class T, class U>
Diccionario<T,U> Diccionario<T,U>::unir(Diccionario<T,U> &D) {
	Diccionario<T,U> result(D);
	Diccionario<T,U>::iterator it;
	Diccionario<T,U>::iterator it_e = this->end();
	Diccionario<T,U>::iterator check;

	for (it = this->begin(); it != it_e; ++it) {
		if (result.Esta_Clave((*it).clave, check.vit)) {
				(*check).info_asoci.merge((*it).info_asoci);
				(*check).info_asoci.sort();
				(*check).info_asoci.unique();
		} else {
			data<T,U> p;
			p.clave = (*it).clave;
			p.info_asoci = (*it).info_asoci;
			result.datos.insert(check.vit,p);
		}
	}

	return result;
}

template<class T, class U>
list<data<T,U>> Diccionario<T,U>::rango(T &clave1, T &clave2) {
	if (clave2 < clave1) {
		T aux = clave2;
		clave2 = clave1;
		clave1 = aux;
	}

	list<data<T,U>> result;

	Diccionario<T,U>::iterator it;
	Diccionario<T,U>::iterator it_e = datos.end();
	Diccionario<T,U>::iterator in;

	for (it = begin(); it != it_e; ++it) {
		if ((*it).clave >= clave1 && (*it).clave <= clave2) {
			in.vit = result.end();
			result.insert(in.vit, *it);
		}
	}

	return result;
}

template<class T, class U>
Diccionario<T,U> Diccionario<T,U>::diferencia(const Diccionario<T,U> &D) {
	Diccionario<T,U> result(*this);

	Diccionario<T,U>::const_iterator it;
	Diccionario<T,U>::const_iterator it_e = D.cend();
	Diccionario<T,U>::iterator check;

	for (it = D.cbegin(); it != it_e; ++it) {
		if (result.Esta_Clave((*it).clave, check.vit))
			result.datos.erase(check.vit);
	}

	return result;
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