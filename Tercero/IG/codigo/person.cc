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

}

void Person::modificarGiroLCabeza(float valor) {
    this->giroLCabeza += valor;
}

void Person::modificarGiroVCabeza(float valor) {
    this->giroVCabeza += valor;
}

void Person::modificarGiroBrazoDrch(float valor) {
    this->giroBrazoDrch += valor;
}

void Person::modificarGiroBrazoIzq(float valor) {
    this->giroBrazoIzq += valor;
}

void Person::modificarGiroPiernaDrch(float valor) {
    this->giroPiernaDrch += valor;
}

void Person::modificarGiroPiernaIzq(float valor) {
    this->giroPiernaIzq += valor;
}

void Person::modificarGiroDedoGDrch(float valor) {
    brazoDrch->modificarGiroDedoG(valor);
}

void Person::modificarGiroDedoGIzq(float valor) {
    brazoIzq->modificarGiroDedoG(valor);
}

void Person::modificarGiroDedosDrch(float valor) {
    brazoDrch->modificarGiroDedos(valor);
}

void Person::modificarGiroDedosIzq(float valor) {
    brazoIzq->modificarGiroDedos(valor);
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
    glTranslatef(-0.87,6.0,0.0);
    piernaDrch->draw(modo, visualizado);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.87,6.0,0.0);
    piernaIzq->draw(modo, visualizado);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0,14.6,0.53);
    torso->draw(modo, visualizado);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0,20.05,0.85);
    cabeza->draw(modo, visualizado);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.1,14.9,0.25);
    brazoDrch->draw(modo, visualizado);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.1,15.0,0.25);
    brazoIzq->draw(modo, visualizado);
    glPopMatrix();
}