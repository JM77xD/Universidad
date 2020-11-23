#include <iostream>
#include <climits>
#include "pila_max_cola.h"

using namespace std;

ostream& operator <<(ostream &flujo, const elemento &p){
  flujo << "(" << p.valor << " | " << p.max << ")" << "\n";
  return flujo;
}


Pila_max::Pila_max(const Pila_max &otra):elementos(otra.elementos){}

Pila_max& Pila_max::operator= (const Pila_max& otra){
  if(&otra != this)
    elementos=otra.elementos;
  return *this;
}

bool Pila_max::vacia() const{
  return elementos.vacia();
}

elemento& Pila_max:: tope(){
  return elementos.frente();
}

const elemento& Pila_max:: tope() const{
  return elementos.frente();
}

void Pila_max:: poner(const int &n){

  int mayor = n > maximo()?n:maximo();

  elemento p;
  p.valor = n;
  p.max = mayor;

  Pila_max aux(*this);
  elementos.poner(p);

  int num=elementos.num_elementos()-1;

  for(int i=0; i<num; i++){
    elementos.quitar();
  }

  for(int i=0; i<num; i++){
    elementos.poner(aux.tope());
    aux.quitar();
  }
}

void Pila_max:: quitar(){
  elementos.quitar();
}

int Pila_max:: getNelementos() const{
  return elementos.num_elementos();
}

int Pila_max:: maximo() const{

  if(elementos.vacia()) return INT_MIN;
    return tope().max;
}