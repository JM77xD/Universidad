#include "person.h"


Person::Person() {

    this->parteSuperior = new ParteSuperior();

    this->parteInferior = new ParteInferior();

    this->giroTorso = 0.0;

    this->change = false;

}

void Person::reset() {
    this->giroTorso = 0.0;

    this->change = false;

    this->parteSuperior->reset();

    this->parteInferior->reset();
}

void Person::modificarGiroLCabeza(float valor, const bool aut) {
    this->parteSuperior->modificarGiroLCabeza(valor, aut);
}

void Person::modificarGiroVCabeza(float valor, const bool aut) {
    this->parteSuperior->modificarGiroVCabeza(valor, aut);
}

void Person::modificarGiroBrazoDrch(float valor, const bool aut) {
    this->parteSuperior->modificarGiroBrazoDrch(valor, aut);
}

void Person::modificarGiroBrazoIzq(float valor, const bool aut) {
    this->parteSuperior->modificarGiroBrazoIzq(valor, aut);
}

void Person::modificarGiroPiernaDrch(float valor, const bool aut) {
    this->parteInferior->modificarGiroPiernaDrch(valor, aut);
}

void Person::modificarGiroPiernaIzq(float valor, const bool aut) {
    this->parteInferior->modificarGiroPiernaIzq(valor, aut);
}

void Person::modificarGiroDedoGDrch(float valor, const bool aut) {
    this->parteSuperior->modificarGiroDedoGDrch(valor, aut);
}

void Person::modificarGiroDedoGIzq(float valor, const bool aut) {
    this->parteSuperior->modificarGiroDedoGIzq(valor, aut);
}

void Person::modificarGiroDedosDrch(float valor, const bool aut) {
    this->parteSuperior->modificarGiroDedosDrch(valor, aut);
}

void Person::modificarGiroDedosIzq(float valor, const bool aut) {
    this->parteSuperior->modificarGiroDedosIzq(valor, aut);
}

void Person::modificarGiroTronco(float valor, const bool aut) {
    if (change && aut)
        valor = -valor;
    this->giroTorso += valor;
    if (this->giroTorso > 10.0) {
        this->giroTorso = 10.0;
        change = !change;
    }
    else if (this->giroTorso < -10.0) {
        this->giroTorso = -10.0;
        change = !change;
    }
}

void Person::modificarPosBrazoDrch(float valor, const bool aut) {
    this->parteSuperior->modificarPosBrazoDrch(valor, aut);
}

void Person::setMaterial(Material mat)  {

    this->parteSuperior->setMaterial(mat);

    this->parteInferior->setMaterial(mat);
    
}

void Person::draw(modoDibujado modo, int visualizado) {

    glPushMatrix();
    glTranslatef(0.0,11.0,0.0);
    this->parteInferior->draw(modo, visualizado);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0,14.6,0.46);
    glRotatef(this->giroTorso, 0.0, 1.0, 0.0);
    this->parteSuperior->draw(modo, visualizado);
    glPopMatrix();
    
}