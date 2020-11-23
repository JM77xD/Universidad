#include <iostream>
#include <cassert>
#include <climits>
#include "pila_max_VD.h"

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
  return elementos.empty();
}

elemento& Pila_max:: tope(){
  assert(!elementos.empty());
  return elementos.back();
}

const elemento& Pila_max:: tope() const{
  return elementos.back();
}

void Pila_max:: poner(const int &n){

  int mayor = n > maximo()?n:maximo();

  elemento p;
  p.valor = n;
  p.max = mayor;

  elementos.push_back(p);
}

void Pila_max:: quitar(){

  assert(!elementos.empty());
  elementos.pop_back();
}

int Pila_max:: getNelementos() const{
  return elementos.size();
}

int Pila_max:: maximo() const{

  if(elementos.empty()) return INT_MIN;
    return tope().max;
}

