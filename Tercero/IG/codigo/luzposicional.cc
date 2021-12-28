#include "luzposicional.h"

LuzPosicional::LuzPosicional(Tupla3f posicion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso) {
    this->id = idLuzOpenGL;
    this->colorAmbiente = colorAmbiente;
    this->colorDifuso = colorDifuso;
    this->colorEspecular = colorEspecular;

    this->estado = false;

    Tupla4f pos(posicion(X), posicion(Y), posicion(Z), 1.0);

    this->posicion = pos;

    glLightfv(id, GL_AMBIENT, this->colorAmbiente);
    glLightfv(id, GL_DIFFUSE, this->colorDifuso);
    glLightfv(id, GL_SPECULAR, this->colorEspecular);
}

void LuzPosicional::rotar(float valor){
    this->posicion = Tupla4f(this->posicion(X)*cos(valor)-this->posicion(Z)*sin(valor), this->posicion(Y), this->posicion(Z)*cos(valor)+this->posicion(X)*sin(valor), 1.0);
}