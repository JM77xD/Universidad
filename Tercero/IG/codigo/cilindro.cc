#include "cilindro.h"


void Cilindro::crearPerfil(const int vert_perfil, const float altura, const float radio) {
    float num_partes = altura/(vert_perfil - 1);

    for (int i = 0; i < vert_perfil; i++) {
        Tupla3f tri(radio, num_partes*i,0.0);
        perfil.push_back(tri);
    }
}

Cilindro::Cilindro(const int vert_perfil, const int instancias_perfil, const float altura, const float radio, bool textura) {
    crearPerfil(vert_perfil, altura, radio);
    crearMalla(perfil, instancias_perfil, textura);

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
    
    for (int i = 0; i < f_tapa_inf.size(); i++)
      if (i % 2 == 0)
         f_ajedrez_inf_par.push_back(f_tapa_inf[i]);
      else
         f_ajedrez_inf_impar.push_back(f_tapa_inf[i]);
   
   for (int i = 0; i < f_tapa_sup.size(); i++)
      if (i % 2 == 0)
         f_ajedrez_sup_par.push_back(f_tapa_sup[i]);
      else
         f_ajedrez_sup_impar.push_back(f_tapa_sup[i]);

    calcular_normales();
}