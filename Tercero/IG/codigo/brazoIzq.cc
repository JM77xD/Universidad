#include "brazoIzq.h"

BrazoIzq::BrazoIzq() {
    this->brazo = new ObjPLY("Persona/brazoIzq.ply");

    this->dedoG = new ObjPLY("Persona/dedoGIzq.ply");

    this->dedos = new ObjPLY("Persona/dedosIzq.ply");

    this->giroDedoG = 0;

    this->giroDedos = 0;
}

void BrazoIzq::reset() {
    this->giroDedoG = 0.0;
    this->giroDedos = 0.0;
}



void BrazoIzq::modificarGiroDedos(float valor) {
    this->giroDedos += valor;
    if (this->giroDedos > 70.0)
        this->giroDedos = 70.0;
    if (this->giroDedos < 0.0)
        this->giroDedos = 0.0;
}

void BrazoIzq::modificarGiroDedoG(float valor) {
    this->giroDedoG += valor;
    if (this->giroDedoG > 70.0)
        this->giroDedoG = 70.0;
    if (this->giroDedoG < 0.0)
        this->giroDedoG = 0.0;
}

void BrazoIzq::setMaterial(Material mat) {
    this->brazo->setMaterial(mat);

    this->dedoG->setMaterial(mat);

    this->dedos->setMaterial(mat);
}

void BrazoIzq::draw(modoDibujado modo, int visualizado) {
    this->brazo->draw(modo, visualizado);


    glPushMatrix();
    glTranslatef(5.37,-5.4,0.6);
    glRotatef(this->giroDedos, -0.5, -0.5, 0.0);
    this->dedos->draw(modo, visualizado);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5.56,-4.68,0.85);
    glRotatef(this->giroDedoG, 0.0, -1.0, 0.0);
    this->dedoG->draw(modo, visualizado);
    glPopMatrix();

    
}