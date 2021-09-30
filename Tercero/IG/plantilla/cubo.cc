#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{

   v.emplace_back(Tupla3f(0, 0, 0));
   v.emplace_back(Tupla3f(0, 0, lado));
   v.emplace_back(Tupla3f(0, lado, 0));
   v.emplace_back(Tupla3f(0, lado, lado));
   v.emplace_back(Tupla3f(lado, 0, 0));
   v.emplace_back(Tupla3f(lado, 0, lado));
   v.emplace_back(Tupla3f(lado, lado, 0));
   v.emplace_back(Tupla3f(lado, lado, lado));

   f.emplace_back(Tupla3i(0,5,1));
   f.emplace_back(Tupla3i(1,5,3));
   f.emplace_back(Tupla3i(3,5,7));
   f.emplace_back(Tupla3i(7,5,4));
   f.emplace_back(Tupla3i(5,0,4));
   f.emplace_back(Tupla3i(6,4,0));
   f.emplace_back(Tupla3i(2,6,0));
   f.emplace_back(Tupla3i(1,2,0));
   f.emplace_back(Tupla3i(1,3,2));
   f.emplace_back(Tupla3i(3,7,2));
   f.emplace_back(Tupla3i(2,7,6));
   f.emplace_back(Tupla3i(6,7,4));
   
   c.emplace_back(Tupla3f(1,0,0));
   c.emplace_back(Tupla3f(0,1,0));
   c.emplace_back(Tupla3f(1,0,0));
   c.emplace_back(Tupla3f(0,1,0));
   c.emplace_back(Tupla3f(0,0,1));
   c.emplace_back(Tupla3f(0,1,0));
   c.emplace_back(Tupla3f(1,0,0));
   c.emplace_back(Tupla3f(0,1,0));

   cAje.emplace_back(Tupla3f(0.5,1,0));
   cAje.emplace_back(Tupla3f(1,0,0.25));
   cAje.emplace_back(Tupla3f(1,0,0.25));
   cAje.emplace_back(Tupla3f(0.5,1,0));
   cAje.emplace_back(Tupla3f(1,0,0.25));
   cAje.emplace_back(Tupla3f(0.5,1,0));
   cAje.emplace_back(Tupla3f(0.5,1,0));
   cAje.emplace_back(Tupla3f(1,0,0.25));

}

