#include "aux.h"
#include "malla.h"
#include "tetraedro.h"

Tetraedro::Tetraedro(float lado)
{
    float alt2 = lado*(sqrt(6)/3)/2;

    v.push_back(Tupla3f(lado/sqrt(3),-alt2,0));
    v.push_back(Tupla3f(-((lado/2)*0.577),-alt2,-lado/2));
    v.push_back(Tupla3f(-((lado/2)*0.577),-alt2,lado/2));
    v.push_back(Tupla3f(0,alt2,0));

    f.push_back(Tupla3i(1,0,2));
    f.push_back(Tupla3i(1,2,3));
    f.push_back(Tupla3i(2,0,3));
    f.push_back(Tupla3i(1,3,0));

    for (int i = 0; i < v.size(); i++) {
        c_solido.push_back(Tupla3f(0,0,1));
        c_lineas.push_back(Tupla3f(1,0,0));
        c_puntos.push_back(Tupla3f(0,1,0));
        c_ajedrez_par.push_back(Tupla3f(0.5,1,0));
        c_ajedrez_impar.push_back(Tupla3f(1,0,0.25));
    }

   for (int i = 0; i < f.size(); i++)
      if (i % 2 == 0)
        f_ajedrez_par.push_back(f[i]);
      else
        f_ajedrez_impar.push_back(f[i]);

}

