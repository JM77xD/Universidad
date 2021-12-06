#include "brazoDrch.h"

BrazoDrch::BrazoDrch() {
    this->brazo = new ObjPLY("Persona/brazoDrch.ply");

    this->dedoG = new ObjPLY("Persona/dedoGDrch.ply");

    this->dedos = new ObjPLY("Persona/dedosDrch.ply");

    this->giroDedoG = 0;

    this->giroDedos = 0;
}

void BrazoDrch::reset() {
    this->giroDedoG = 0.0;
    this->giroDedos = 0.0;
}



void BrazoDrch::modificarGiroDedos(float valor) {
    this->giroDedos += valor;
    if (this->giroDedos > 70.0)
        this->giroDedos = 70.0;
    if (this->giroDedos < 0.0)
        this->giroDedos = 0.0;
}

void BrazoDrch::modificarGiroDedoG(float valor) {
    this->giroDedoG += valor;
    if (this->giroDedoG > 70.0)
        this->giroDedoG = 70.0;
    if (this->giroDedoG < 0.0)
        this->giroDedoG = 0.0;
}

void BrazoDrch::setMaterial(Material mat) {
    this->brazo->setMaterial(mat);

    this->dedoG->setMaterial(mat);

    this->dedos->setMaterial(mat);
}

void BrazoDrch::draw(modoDibujado modo, int visualizado) {
    this->brazo->draw(modo, visualizado);

    glPushMatrix();
    glTranslatef(-5.26,-5.28,0.6);
    glRotatef(this->giroDedos, -0.5, 0.5, 0.0);
    this->dedos->draw(modo, visualizado);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-5.46,-4.5,0.63);
    glRotatef(this->giroDedoG, 0.0, 1.0, 0.0);
    this->dedoG->draw(modo, visualizado);
    glPopMatrix();

}
