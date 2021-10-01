#include "aux.h"
#include "malla.h"
#include "tetraedro.h"

Tetraedro::Tetraedro(float lado)
{

   v.push_back(Tupla3f(lado/sqrt(3),0,0));
   v.push_back(Tupla3f(-((lado/2)*0.577),0,-lado/2));
   v.push_back(Tupla3f(-((lado/2)*0.577),0,lado/2));
   v.push_back(Tupla3f(0,lado*(sqrt(6)/3),0));

   f.push_back(Tupla3i(0,1,2));
   f.push_back(Tupla3i(1,2,3));
   f.push_back(Tupla3i(2,0,3));
   f.push_back(Tupla3i(1,3,0));

   c.push_back(Tupla3f(0,1,0));
   c.push_back(Tupla3f(0,0,1));
   c.push_back(Tupla3f(0,0,1));
   c.push_back(Tupla3f(0,0,1));

}

