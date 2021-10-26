#include "cono.h"


void Cono::crearPerfil(const int vert_perfil, const float altura, const float radio) {
    float divAltura = altura/(vert_perfil - 1), divRadio = radio/(vert_perfil-1); 

    for (int i = 0, j = vert_perfil-1; i < vert_perfil, j >= 0; i++, j--) {
        Tupla3f tri(divRadio*j, divAltura*i,0.0);
        perfil.push_back(tri);
    }
}

Cono::Cono(const int vert_perfil, const int instancias_perfil, const float altura, const float radio) {
    crearPerfil(vert_perfil, altura, radio);
    crearMalla(perfil, instancias_perfil);

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