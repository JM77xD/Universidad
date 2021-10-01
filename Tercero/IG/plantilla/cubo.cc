#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{
   float pos = lado/2;

   v.push_back(Tupla3f(-pos, -pos, -pos));
   v.push_back(Tupla3f(-pos, -pos, pos));
   v.push_back(Tupla3f(-pos, pos, -pos));
   v.push_back(Tupla3f(-pos, pos, pos));
   v.push_back(Tupla3f(pos, -pos, -pos));
   v.push_back(Tupla3f(pos, -pos, pos));
   v.push_back(Tupla3f(pos, pos, -pos));
   v.push_back(Tupla3f(pos, pos, pos));

   f.push_back(Tupla3i(0,2,4));
   f.push_back(Tupla3i(4,2,6));
   f.push_back(Tupla3i(1,5,3));
   f.push_back(Tupla3i(3,5,7));
   f.push_back(Tupla3i(1,3,0));
   f.push_back(Tupla3i(0,3,2));
   f.push_back(Tupla3i(5,4,7));
   f.push_back(Tupla3i(7,4,6));
   f.push_back(Tupla3i(1,0,5));
   f.push_back(Tupla3i(5,0,4));
   f.push_back(Tupla3i(3,7,2));
   f.push_back(Tupla3i(2,7,6));
   
   c.push_back(Tupla3f(1,0,0));
   c.push_back(Tupla3f(0,1,0));
   c.push_back(Tupla3f(1,0,0));
   c.push_back(Tupla3f(0,1,0));
   c.push_back(Tupla3f(1,0,0));
   c.push_back(Tupla3f(0,1,0));
   c.push_back(Tupla3f(1,0,0));
   c.push_back(Tupla3f(0,1,0));

}

