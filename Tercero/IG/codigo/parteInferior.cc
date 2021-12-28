#include "parteInferior.h"


ParteInferior::ParteInferior() {
    
    this->piernaDrch = new ObjPLY("Persona/piernaDrch.ply");

    this->piernaIzq = new ObjPLY("Persona/piernaIzq.ply");

    this->giroPiernaDrch = 0.0;

    this->giroPiernaIzq = 0.0;

    this->change = false;

}


void ParteInferior::reset() {
    
    this->giroPiernaDrch = 0.0;

    this->giroPiernaIzq = 0.0;

    this->change = false;

}

void ParteInferior::setMaterial(Material mat) {

    this->piernaDrch->setMaterial(mat);

    this->piernaDrch->setMaterial(mat);

}

void ParteInferior::modificarGiroPiernaDrch(float valor, const bool aut) {

    if (change && aut)
        valor = -valor;

    this->giroPiernaDrch += valor;

    if (this->giroPiernaDrch > 45.0) {
        this->giroPiernaDrch = 45.0;
        change = !change;
    } else if (this->giroPiernaDrch < -45.0) {
        this->giroPiernaDrch = -45.0;
        change = !change;
    }

}

void ParteInferior::modificarGiroPiernaIzq(float valor, const bool aut) {
    if (change && aut)
        valor = -valor;

    this->giroPiernaIzq += valor;

    if (this->giroPiernaIzq > 45.0) {
        this->giroPiernaIzq = 45.0;
        change = !change;
    } else if (this->giroPiernaIzq < -45.0) {
        this->giroPiernaIzq = -45.0;
        change = !change;
    }

}


void ParteInferior::draw(modoDibujado modo, int visualizado) {

    glPushMatrix();
    glTranslatef(-0.94,0.0,0.0);
    glRotatef(this->giroPiernaDrch, -1.0, 0.0, 0.0);
    this->piernaDrch->draw(modo, visualizado);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.94,0.0,0.0);
    glRotatef(this->giroPiernaIzq, -1.0, 0.0, 0.0);
    this->piernaIzq->draw(modo, visualizado);
    glPopMatrix();

}