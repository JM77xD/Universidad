#include "person.h"


Person::Person() {

    this->torso = new ObjPLY("Persona/torso.ply");

    this->cabeza = new ObjPLY("Persona/cabeza.ply");

    this->brazoDrch = new BrazoDrch();

    this->brazoIzq = new BrazoIzq();

    this->piernaDrch = new ObjPLY("Persona/piernaDrch.ply");

    this->piernaIzq = new ObjPLY("Persona/piernaIzq.ply");


    this->giroLCabeza = 0.0;

    this->giroVCabeza = 0.0;

    this->giroBrazoDrch = 0.0;

    this->giroBrazoIzq = 0.0;

    this->giroPiernaDrch = 0.0;

    this->giroPiernaIzq = 0.0;

    this->change = false;

}

void Person::reset() {
    this->giroLCabeza = 0.0;

    this->giroVCabeza = 0.0;

    this->giroBrazoDrch = 0.0;

    this->giroBrazoIzq = 0.0;

    this->giroPiernaDrch = 0.0;

    this->giroPiernaIzq = 0.0;

    this->change = false;

    this->brazoDrch->reset();

    this->brazoIzq->reset();
}

void Person::modificarGiroLCabeza(float valor, const bool aut) {
    if (change && aut)
        valor = -valor;
    this->giroLCabeza += valor;
    if (this->giroLCabeza > 75.0) {
        this->giroLCabeza = 75.0;
        change = !change;
    }
    else if (this->giroLCabeza < -75.0) {
        this->giroLCabeza = -75.0;
        change = !change;
    }
}

void Person::modificarGiroVCabeza(float valor, const bool aut) {
    if (change && aut)
        valor = -valor;
    this->giroVCabeza += valor;
    if (this->giroVCabeza > 30.0) {
        this->giroVCabeza = 30.0;
        change = !change;
    }
    else if (this->giroVCabeza < -30.0) {
        this->giroVCabeza = -30.0;
        change = !change;
    }
}

void Person::modificarGiroBrazoDrch(float valor, const bool aut) {
    if (change && aut)
        valor = -valor;
    this->giroBrazoDrch += valor;
    if (this->giroBrazoDrch >= 360.0 || this->giroBrazoDrch <= -360.0) {
        this->giroBrazoDrch = 0.0;
        change = !change;
    }
}

void Person::modificarGiroBrazoIzq(float valor, const bool aut) {
    if (change && aut)
        valor = -valor;
    this->giroBrazoIzq += valor;
    if (this->giroBrazoIzq >= 360.0 || this->giroBrazoIzq <= -360.0) {
        this->giroBrazoIzq = 0.0;
        change = !change;
    }
}

void Person::modificarGiroPiernaDrch(float valor, const bool aut) {
    if (change && aut)
        valor = -valor;
    this->giroPiernaDrch += valor;
    if (this->giroPiernaDrch > 45.0) {
        this->giroPiernaDrch = 45.0;
        change = !change;
    }
    else if (this->giroPiernaDrch < -45.0) {
        this->giroPiernaDrch = -45.0;
        change = !change;
    }
}

void Person::modificarGiroPiernaIzq(float valor, const bool aut) {
    if (change && aut)
        valor = -valor;
    this->giroPiernaIzq += valor;
    if (this->giroPiernaIzq > 45.0) {
        this->giroPiernaIzq = 45.0;
        change = !change;
    }
    else if (this->giroPiernaIzq < -45.0) {
        this->giroPiernaIzq = -45.0;
        change = !change;
    }
}

void Person::modificarGiroDedoGDrch(float valor, const bool aut) {
    if (change && aut)
        valor = -valor;
    this->brazoDrch->modificarGiroDedoG(valor);
}

void Person::modificarGiroDedoGIzq(float valor, const bool aut) {
    if (change && aut)
        valor = -valor;
    this->brazoIzq->modificarGiroDedoG(valor);
}

void Person::modificarGiroDedosDrch(float valor, const bool aut) {
    if (change && aut)
        valor = -valor;
    this->brazoDrch->modificarGiroDedos(valor);
}

void Person::modificarGiroDedosIzq(float valor, const bool aut) {
    if (change && aut)
        valor = -valor;
    this->brazoIzq->modificarGiroDedos(valor);
}

void Person::setMaterial(Material mat)  {
    this->torso->setMaterial(mat);

    this->cabeza->setMaterial(mat);

    this->brazoDrch->setMaterial(mat);

    this->brazoIzq->setMaterial(mat);

    this->piernaDrch->setMaterial(mat);

    this->piernaIzq->setMaterial(mat);
}

void Person::draw(modoDibujado modo, int visualizado) {
    glPushMatrix();
    glTranslatef(-0.94,11.0,0.0);
    glRotatef(this->giroPiernaDrch, -1.0, 0.0, 0.0);
    this->piernaDrch->draw(modo, visualizado);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.94,11.0,0.0);
    glRotatef(this->giroPiernaIzq, -1.0, 0.0, 0.0);
    this->piernaIzq->draw(modo, visualizado);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0,14.6,0.46);
    this->torso->draw(modo, visualizado);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0,18.5,0.35);
    glRotatef(this->giroVCabeza, -1.0, 0.0, 0.0);
    glRotatef(this->giroLCabeza, 0.0, 1.0, 0.0);
    this->cabeza->draw(modo, visualizado);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.0,17.1,0.18);
    glRotatef(this->giroBrazoDrch, -1.0, 0.0, 0.0);
    this->brazoDrch->draw(modo, visualizado);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.1,17.2,0.18);
    glRotatef(this->giroBrazoIzq, -1.0, 0.0, 0.0);
    this->brazoIzq->draw(modo, visualizado);
    glPopMatrix();
}