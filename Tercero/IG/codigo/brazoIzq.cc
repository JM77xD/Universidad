#include "brazoIzq.h"

BrazoIzq::BrazoIzq() {
    this->brazo = new ObjPLY("Persona/brazoIzq.ply");

    this->dedoG = new ObjPLY("Persona/dedoGIzq.ply");

    this->dedos = new ObjPLY("Persona/dedosIzq.ply");

    this->giroDedoG = 0;

    this->giroDedos = 0;
}



void BrazoIzq::modificarGiroDedos(float valor) {
    this->giroDedos += valor;
}

void BrazoIzq::modificarGiroDedoG(float valor) {
    this->giroDedoG += valor;
}

void BrazoIzq::setMaterial(Material mat) {
    this->brazo->setMaterial(mat);

    this->dedoG->setMaterial(mat);

    this->dedos->setMaterial(mat);
}

void BrazoIzq::draw(modoDibujado modo, int visualizado) {
    this->brazo->draw(modo, visualizado);

    
}