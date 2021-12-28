#include "luz.h"

void Luz::activar() {
    if (!estado) {
        glEnable(this->id);
        estado = true;
    }
    glLightfv(this->id, GL_POSITION, this->posicion);
}

void Luz::desactivar() {
    if (estado) {
        glDisable(this->id);
        estado = false;
    }
}