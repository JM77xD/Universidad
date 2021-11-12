#include "material.h"

Material::Material() {}

Material::Material(Tupla4f difuso, Tupla4f especular, Tupla4f ambiente, float brillo) {
this->ambiente = ambiente;
this->especular = especular;
this->difuso = difuso;
this->brillo = brillo;
}

Material::Material(Tupla3f difuso, Tupla3f especular, Tupla3f ambiente, float brillo) {
this->ambiente = Tupla4f(ambiente(X), ambiente(Y), ambiente(Z), 1.0);
this->especular = Tupla4f(especular(X), especular(Y), especular(Z), 1.0);
this->difuso = Tupla4f(difuso(X), difuso(Y), difuso(Z), 1.0);

this->brillo = brillo;
}

void Material::aplicar() {
    glMaterialfv(GL_FRONT, GL_AMBIENT, this->ambiente);
    glMaterialfv(GL_FRONT, GL_SPECULAR, this->especular);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, this->difuso);
    glMaterialf(GL_FRONT, GL_SHININESS, this->brillo);
}