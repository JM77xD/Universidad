#include "esfera.h"


void Esfera::crearPerfil(const int vert_perfil, const float radio) {
    float angulo = M_PI/(vert_perfil - 1); 

    for (int i = 0; i < vert_perfil; i++) {
        Tupla3f tri(radio*cos(angulo*i-(M_PI/2)), radio*sin(angulo*i-(M_PI/2)),0.0);
        perfil.push_back(tri);
    }
}

Esfera::Esfera(const int vert_perfil, const int instancias_perfil, const float radio) {
    crearPerfil(vert_perfil, radio);
    crearMalla(perfil, instancias_perfil);
}