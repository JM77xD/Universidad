#include "textura.h"

Textura::Textura(std::string archivo) {

    jpg::Imagen *pimg = NULL;

    pimg = new jpg::Imagen(archivo);

    this->width = pimg->tamX();
    this->height = pimg->tamY();

    unsigned char * texels = pimg->leerPixels();

    for(int i = 0; i < 3*this->width*this->height; i++)
        this->data.push_back(texels[i]);

    glGenTextures(1, &this->textura_id);

    glBindTexture(GL_TEXTURE_2D, this->textura_id);

    gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB, this->width, this->height, GL_RGB, GL_UNSIGNED_BYTE, this->data.data());

    glBindTexture(GL_TEXTURE_2D, 0);

}

GLuint Textura::getID() {
    return this->textura_id;
}

void Textura::activar() {
    glBindTexture(GL_TEXTURE_2D, this->textura_id);
}