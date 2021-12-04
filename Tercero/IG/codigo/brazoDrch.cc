#include "brazoDrch.h"

BrazoDrch::BrazoDrch() {
    this->brazo = new ObjPLY("Persona/brazoDrch.ply");

    this->dedoG = new ObjPLY("Persona/dedoGDrch.ply");

    this->dedos = new ObjPLY("Persona/dedosDrch.ply");

    this->giroDedoG = 0;

    this->giroDedos = 0;
}



void BrazoDrch::modificarGiroDedos(float valor) {
    this->giroDedos += valor;
}

void BrazoDrch::modificarGiroDedoG(float valor) {
    this->giroDedoG += valor;
}

void BrazoDrch::setMaterial(Material mat) {
    this->brazo->setMaterial(mat);

    this->dedoG->setMaterial(mat);

    this->dedos->setMaterial(mat);
}

void BrazoDrch::draw(modoDibujado modo, int visualizado) {
    this->brazo->draw(modo, visualizado);

    glPushMatrix();
    glTranslatef(-3.35,-3.45,0.7);
    this->dedos->draw(modo, visualizado);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3.54,-2.46,0.67);
    this->dedoG->draw(modo, visualizado);
    glPopMatrix();

}
