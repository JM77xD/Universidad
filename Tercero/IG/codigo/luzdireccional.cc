#include "luzdireccional.h"

LuzDireccional::LuzDireccional(Tupla2f direccion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso) {
    this->alpha = direccion(X);
    this->beta = direccion(Y);

    this->estado = false;
    
    this->id = idLuzOpenGL;
    this->colorAmbiente = colorAmbiente;
    this->colorDifuso = colorDifuso;
    this->colorEspecular = colorEspecular;

    Tupla4f pos(sin(alpha)*cos(beta), sin(beta)*sin(alpha), cos(alpha) , 0.0);

    this->posicion = pos;

    glLightfv(id, GL_AMBIENT, colorAmbiente);
    glLightfv(id, GL_DIFFUSE, colorDifuso);
    glLightfv(id, GL_SPECULAR, colorEspecular);
    glLightfv(id, GL_POSITION, posicion);
}

void LuzDireccional::variarAnguloAlpha(float incremento) {
    alpha += incremento;
    float resto = alpha/180;
    if (resto >= 1.0)
        alpha -= 180;
    
    Tupla4f pos(sin(alpha)*cos(beta), sin(beta)*sin(alpha), cos(alpha) , 0.0);

    this->posicion = pos;

    glLightfv(this->id, GL_POSITION, posicion);
}

void LuzDireccional::variarAnguloBeta(float incremento) {
    beta += incremento;
    float resto = beta/360;
    if (resto >= 1.0)
        beta -= 360;
    
    Tupla4f pos(sin(alpha)*cos(beta), sin(beta)*sin(alpha), cos(alpha) , 0.0);

    this->posicion = pos;

    glLightfv(this->id, GL_POSITION, posicion);
}