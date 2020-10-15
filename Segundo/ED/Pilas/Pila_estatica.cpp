#include <cassert>
#include "Pila_estatica.hpp"

PilaEstatica::PilaEstatica() {
    this->nElem = 0;
}

PilaEstatica::PilaEstatica(const PilaEstatica &p) {
    this->nElem = p.nElem;
    for (int i = 0; i < this->nElem; i++) {
        *(this->datos + i) = p.datos[i];
    }
}

PilaEstatica & PilaEstatica::operator=(const PilaEstatica &p) {
    PilaEstatica nueva;
    nueva.copiar(p);
    return nueva;
}

bool PilaEstatica::vacia() const {
    return (this->nElem == 0);
}

void PilaEstatica::operator+=(const base &p) {
    assert(this->nElem < TAM);
    *(this->datos + nElem) = p;
    nElem++;
}

void PilaEstatica::operator--() {
    assert(this->nElem > 0);
    nElem--;
}

base & PilaEstatica::tope() {
    assert(this->nElem > 0);
    return *(this->datos + nElem - 1);
}

const base & PilaEstatica::tope() const {
    assert(this->nElem > 0);
    return *(this->datos + nElem - 1);
}

void PilaEstatica::copiar(const PilaEstatica &p) {
    this->nElem = p.nElem;
    for (int i = 0; i < this->nElem; i++) {
        *(this->datos + i) = p.datos[i];
    }
}