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
}