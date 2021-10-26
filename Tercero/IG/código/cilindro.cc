#include "cilindro.h"


void Cilindro::crearPerfil(const int vert_perfil, const float altura, const float radio) {
    float num_partes = altura/(vert_perfil - 1);

    for (int i = 0; i < vert_perfil; i++) {
        Tupla3f tri(radio, num_partes*i,0.0);
        perfil.push_back(tri);
    }
}

Cilindro::Cilindro(const int vert_perfil, const int instancias_perfil, const float altura, const float radio) {
    crearPerfil(vert_perfil, altura, radio);
    crearMalla(perfil, instancias_perfil);
}