#include "luz.h"

void Luz::activar() {
    if (!estado) {
        glEnable(this->id);
        estado = true;
    }

    glLightfv(id, GL_AMBIENT, this->colorAmbiente);
    glLightfv(id, GL_DIFFUSE, this->colorDifuso);
    glLightfv(id, GL_SPECULAR, this->colorEspecular);
    glLightfv(id, GL_POSITION, this->posicion);
}

void Luz::desactivar() {
    if (estado) {
        glDisable(this->id);
        estado = false;
    }
}