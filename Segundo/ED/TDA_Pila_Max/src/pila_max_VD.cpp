#include <iostream>
#include <cassert>
#include <climits>
#include "pila_max_VD.h"

using namespace std;

ostream& operator <<(ostream &flujo, const elemento &p){
  flujo << "(" << p.valor << " | " << p.max << ")" << "\n";
  return flujo;
}

Pila_max_VD::Pila_max_VD(const Pila_max_VD &otra):elementos(otra.elementos){}

Pila_max_VD& Pila_max_VD::operator= (const Pila_max_VD& otra){
  if(&otra != this)
    elementos=otra.elementos;
  return *this;
}

bool Pila_max_VD::vacia() const{
  return elementos.empty();
}

elemento& Pila_max_VD:: tope(){
  assert(!elementos.empty());
  return elementos.back();
}

const elemento& Pila_max_VD:: tope() const{
  return elementos.back();
}

void Pila_max_VD:: poner(const int &n){

  int mayor = n > maximo()?n:maximo();

  elemento p;
  p.valor = n;
  p.max = mayor;

  elementos.push_back(p);
}

void Pila_max_VD:: quitar(){

  assert(!elementos.empty());
  elementos.pop_back();
}

int Pila_max_VD:: getNelementos() const{
  return elementos.size();
}

int Pila_max_VD:: maximo() const{

  if(elementos.empty()) return INT_MIN;
    return tope().max;
}

