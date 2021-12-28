#include "parteSuperior.h"

ParteSuperior::ParteSuperior() {

    this->torso = new ObjPLY("Persona/torso.ply");

    this->cabeza = new ObjPLY("Persona/cabeza.ply");

    this->brazoDrch = new BrazoDrch();

    this->brazoIzq = new BrazoIzq();

    this->change = false;

    this->giroLCabeza = 0.0;

    this->giroVCabeza = 0.0;

    this->giroBrazoDrch = 0.0;

    this->giroBrazoIzq = 0.0;

    this->posBrazoDrch = 0.0;
}


void ParteSuperior::reset() {
    this->giroLCabeza = 0.0;

    this->giroVCabeza = 0.0;

    this->giroBrazoDrch = 0.0;

    this->giroBrazoIzq = 0.0;
    
    this->posBrazoDrch = 0.0;

    this->change = false;
}

void ParteSuperior::modificarGiroLCabeza(float valor, const bool aut) {
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

void ParteSuperior::modificarGiroVCabeza(float valor, const bool aut) {
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

void ParteSuperior::modificarGiroBrazoDrch(float valor, const bool aut) {
    if (change && aut)
        valor = -valor;
    this->giroBrazoDrch += valor;
    if (this->giroBrazoDrch >= 360.0 || this->giroBrazoDrch <= -360.0) {
        this->giroBrazoDrch = 0.0;
        change = !change;
    }
}

void ParteSuperior::modificarGiroBrazoIzq(float valor, const bool aut) {
    if (change && aut)
        valor = -valor;
    this->giroBrazoIzq += valor;
    if (this->giroBrazoIzq >= 360.0 || this->giroBrazoIzq <= -360.0) {
        this->giroBrazoIzq = 0.0;
        change = !change;
    }
}

void ParteSuperior::modificarGiroDedoGDrch(float valor, const bool aut) {
    if (change && aut)
        valor = -valor;
    this->brazoDrch->modificarGiroDedoG(valor);
}

void ParteSuperior::modificarGiroDedoGIzq(float valor, const bool aut) {
    if (change && aut)
        valor = -valor;
    this->brazoIzq->modificarGiroDedoG(valor);
}

void ParteSuperior::modificarGiroDedosDrch(float valor, const bool aut) {
    if (change && aut)
        valor = -valor;
    this->brazoDrch->modificarGiroDedos(valor);
}

void ParteSuperior::modificarGiroDedosIzq(float valor, const bool aut) {
    if (change && aut)
        valor = -valor;
    this->brazoIzq->modificarGiroDedos(valor);
}

void ParteSuperior::modificarPosBrazoDrch(float valor, const bool aut) {
    if (change && aut)
        valor = -valor;
    this->posBrazoDrch += valor;
    if (this->posBrazoDrch > 10.0) {
        this->posBrazoDrch = 10.0;
        change = !change;
    }
    else if (this->posBrazoDrch < -10.0) {
        this->posBrazoDrch = -10.0;
        change = !change;
    }
}


void ParteSuperior::setMaterial(Material mat)  {
    this->torso->setMaterial(mat);

    this->cabeza->setMaterial(mat);

    this->brazoDrch->setMaterial(mat);

    this->brazoIzq->setMaterial(mat);
}

void ParteSuperior::draw(modoDibujado modo, int visualizado) {
    this->torso->draw(modo, visualizado);

    glPushMatrix();
    glTranslatef(0.0,3.9,-0.11);
    glRotatef(this->giroVCabeza, -1.0, 0.0, 0.0);
    glRotatef(this->giroLCabeza, 0.0, 1.0, 0.0);
    this->cabeza->draw(modo, visualizado);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.1,2.5,-0.28);
    glRotatef(this->giroBrazoDrch, -1.0, 0.0, 0.0);
    glTranslatef(0.0,this->posBrazoDrch,0.0);
    this->brazoDrch->draw(modo, visualizado);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.1,2.5,-0.28);
    glRotatef(this->giroBrazoIzq, -1.0, 0.0, 0.0);
    this->brazoIzq->draw(modo, visualizado);
    glPopMatrix();
}