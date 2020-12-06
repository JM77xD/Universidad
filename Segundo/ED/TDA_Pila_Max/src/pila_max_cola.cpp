#include <iostream>
#include <climits>
#include "pila_max_cola.h"

using namespace std;


Pila_max_cola::Pila_max_cola(const Pila_max_cola &otra):elementos(otra.elementos){}

Pila_max_cola& Pila_max_cola::operator= (const Pila_max_cola& otra){
  if(&otra != this)
    elementos=otra.elementos;
  return *this;
}

bool Pila_max_cola::vacia() const{
  return elementos.vacia();
}

elemento& Pila_max_cola:: tope(){
  return elementos.frente();
}

const elemento& Pila_max_cola:: tope() const{
  return elementos.frente();
}

void Pila_max_cola:: poner(const int &n){

  int mayor = n > maximo()?n:maximo();

  elemento p;
  p.valor = n;
  p.max = mayor;

  Pila_max_cola aux(*this);
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

void Pila_max_cola:: quitar(){
  elementos.quitar();
}

int Pila_max_cola:: getNelementos() const{
  return elementos.num_elementos();
}

int Pila_max_cola:: maximo() const{

  if(elementos.vacia()) return INT_MIN;
    return tope().max;
}