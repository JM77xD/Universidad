#include<iostream>
#include "Racional.h"

using namespace std;

//Constructor por defecto
Racional::Racional(){
  num = 0;
  den = 1;
}

//Constructor
Racional::Racional(int n, int d ){
  num = n;
  den = d;
} 

//Constructor de copia
Racional::Racional (const Racional& c){
  num = c.num;
  den = c.den;
}

//Devuelve el valor del numerador
int Racional::numerador() {
  return this->num;
}

//Devuelve el valor del denominador
int Racional::denominador() {
  return this->den;
}

//Asignación
void Racional::asignar(int n, int d){
  num = n;
  den = d;
}

//Comparación
bool Racional::comparar(Racional r){
  return ((num*r.den == den*r.num)?1:0);
}

//Impresión en cout
void Racional::print(){
  cout << '(' << this->num << '/' << this->den << ')';
}

//Operador +
Racional Racional::operator+(const Racional &r){
  return Racional(num*r.den+den*r.num, den*r.den);
}

//Operador *
Racional Racional::operator*(const Racional &r){
  return Racional(num*r.num, den*r.den);
}

//Operador +=
void Racional::operator+=(const Racional &r){
  num = num*r.den+den*r.num;
  den = den*r.den;
}

//Operador ==
bool Racional::operator==(const Racional & l){
  return ((num*l.den == den*l.num)?1:0); 
}

//Operador <<
ostream& operator<< (ostream & os, const Racional & r){
  return os << '(' << r.num << ',' << r.den << ')';
}

//Operador >>
istream& operator>> (istream& is, Racional& r){
  char caracter;
  int numerador, denominador;
  is >> caracter >> numerador >> caracter >> denominador >> caracter;
  r= Racional(numerador,denominador);
  return is;
}

//Operador -
Racional Racional::operator-(Racional r) {
  return Racional(this->num - r.num, this->den - r.den);
}

//Operador /
Racional Racional::operator/(Racional r) {
  return Racional(this->num * r.den, this->den * r.num);
}

//Simplificación a forma irreducible
Racional Racional::simplifica(){
   int a, b;

   /* Casos base */
   if (num == 0)
       return Racional(0,den);
   else if (num == den)
       return Racional(num,den);
   else if (num > den){
       a = num;
       b = den;
   }
   else{
       a = den;
       b = num;
   };

   /* Algoritmo de Euclides */
   int r;
   do{
     r = a % b;
     a = b;
     b = r;
   } while (r > 0);

   return Racional(num/=a, den/=a);
}

//Devuelve el valor real asociado a un racional
double valorReal(Racional r) {
  double i;
  i = r.numerador() / r.denominador();
  return i;
}

//Convierte un racional en irreducible
void irreducible(Racional r) {
  int a = r.numerador();
  int b = r.denominador();

  if (a==0) {
    r.asignar(0, b);
    return;
  } else if (a==b) {
    r.asignar(1,1);
    return;
  } else if (a<b) {
    int aux = a;
    a = b;
    b = aux;
  }

  /* Algoritmo de Euclides */
  int aux;

  do{
    aux = a % b;
    a = b;
    b = aux;
  } while (aux > 0);
  
  r.asignar(r.numerador()/a, r.denominador()/a);

}
