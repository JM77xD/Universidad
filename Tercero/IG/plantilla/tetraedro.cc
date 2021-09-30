#include "aux.h"
#include "malla.h"
#include "tetraedro.h"

Tetraedro::Tetraedro(float lado)
{

   v.emplace_back(Tupla3f(0,lado,0));
   v.emplace_back(Tupla3f(lado/sqrt(3),0,0));
   v.emplace_back(Tupla3f(-((lado/2)*0.577),0,lado/2));
   v.emplace_back(Tupla3f(-((lado/2)*0.577),0,-lado/2));

   f.emplace_back(Tupla3i(0,1,2));
   f.emplace_back(Tupla3i(0,2,3));
   f.emplace_back(Tupla3i(0,3,1));
   f.emplace_back(Tupla3i(1,3,2));

   c.emplace_back(Tupla3f(0,1,0));
   c.emplace_back(Tupla3f(0,0,1));
   c.emplace_back(Tupla3f(0,0,1));
   c.emplace_back(Tupla3f(0,0,1));
   
   cAje.emplace_back(Tupla3f(0.5,1,0));
   cAje.emplace_back(Tupla3f(1,0,0.25));
   cAje.emplace_back(Tupla3f(0.5,1,0));
   cAje.emplace_back(Tupla3f(1,0,0.25));

}

