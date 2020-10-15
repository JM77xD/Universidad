#include <cassert>
#include "Pila_dinamica.hpp"

PilaDinamica::PilaDinamica(int tam = TAM) {
    assert(tam > 0);
    this->nElem = 0;
    this->reservar(tam);
}

PilaDinamica::PilaDinamica(const PilaDinamica &p) {
    assert(p.datos);
    this->nElem = p.nElem;
    this->reservados = p.reservados;
    this->datos = new base[this->reservados];
    for (int i = 0; i < this->nElem; i++) {
        *(this->datos + i) = p.datos[i];
    }
}

void PilaDinamica::copiar(const PilaDinamica &p) {
    assert(p.datos);
    if (this->reservados != p.reservados) this->reservar(p.reservados);
    this->nElem = p.nElem;
    for (int i = 0; i < this->nElem; i++) {
        *(this->datos + i) = p.datos[i];
    }
}

void PilaDinamica::reservar(int n) {
    assert(n > 0);
    this->reservados = n;
    this->datos = new base[n];
}

void PilaDinamica::liberar() {
    delete [] this->datos;
    datos = 0;
    this->reservados = 0;
    this->nElem = 0;
}

PilaDinamica::~PilaDinamica() {
    this->liberar();
}

void PilaDinamica::resize(int n) {
    assert(n > 0);
    base *aux = this->datos;
    this->reservados = n;
    this->datos = new base[n];
    for (int i = 0; i < this->nElem; i++) {
        *(this->datos + i) = *(aux + i);
    }
    delete [] aux;
}

PilaDinamica & PilaDinamica::operator=(const PilaDinamica &p) {
    if (this != &p) {
        this->liberar();
        this->copiar(p);
    }
    return *this;
}

bool PilaDinamica::vacia() const {
    return (nElem == 0);
}

void PilaDinamica::operator+=(const base &p) {
    if (nElem == reservados) this->resize(reservados*2);
    *(this->datos + this->nElem) = p;
    this->nElem++;
}

void PilaDinamica::operator--() {
    assert(this->nElem > 0);
    nElem--;
    if (nElem < reservados/4) this->resize(reservados/2);
}

base & PilaDinamica::tope() {
    assert(this->nElem > 0);
    return *(this->datos + nElem - 1);
}

const base & PilaDinamica::tope() const {
    assert(this->nElem > 0);
    return *(this->datos + nElem - 1);
}