#include <iostream>
#include <random>
#include <thread>
#include "HoareMonitor.h"

using namespace std;
using namespace HM;

const int tam = 33;
const int num_hebras = 3;

int memoria_compartida[tam];

class Lec_Esc : public HoareMonitor {
    private:
        bool escrib;
        unsigned int n_lec;
        unsigned int dato;
        unsigned int valor;
        int n_datos;
        CondVar lectura;
        CondVar escritura;

    public:
        Lec_Esc();
        void ini_lec();
        void fin_lec();
        void ini_esc();
        void fin_esc();
        void leer();
        void escribir();
        int get_datos() const;
        int get_valor() const;
};

int Lec_Esc::get_datos() const {
    return dato;
}

int Lec_Esc::get_valor() const {
    return valor;
}

Lec_Esc::Lec_Esc() {
    escrib = false;
    n_lec = 0;
    dato = 0;
    valor = 0;
    n_datos = 0;
    lectura = newCondVar();
    escritura = newCondVar();
}

void Lec_Esc::ini_lec() {
    if (escrib || n_datos <= 0)
        lectura.wait();
    
    n_lec++;
    n_datos--;
    if (n_datos > 1)
        lectura.signal();
}

void Lec_Esc::leer() {
    if (n_datos >= 0) {
        int result = memoria_compartida[dato];
        cout << "\tLeido el valor " << result << ".\n";
        dato++;
    }
}

void Lec_Esc::fin_lec() {
    n_lec--;
    if (n_lec == 0)
        escritura.signal();
}

void Lec_Esc::ini_esc() {
    if (n_lec > 0 || escrib)
        escritura.wait();
    escrib = true;
}


void Lec_Esc::escribir() {
    memoria_compartida[valor] = valor;
    n_datos++;
    cout << "Escrito el valor " << memoria_compartida[valor] << ".\n";
    valor++;
}


void Lec_Esc::fin_esc() {
    escrib = false;

    if (!lectura.empty())
        lectura.signal();
    else
        escritura.signal();
}


void funcion_escritor(MRef<Lec_Esc> monitor) {
    while (monitor->get_valor() < tam) {
        monitor->ini_esc();
        monitor->escribir();
        monitor->fin_esc();
    }
}

void funcion_lector(MRef<Lec_Esc> monitor) {
    while (monitor->get_datos() < tam) {
        monitor->ini_lec();
        monitor->leer();
        monitor->fin_lec();
    }
}

int main() {
    MRef<Lec_Esc> monitor = Create<Lec_Esc>();
    thread escritores[num_hebras];
    thread lectores[num_hebras];

    for (int i = 0; i < num_hebras; i++)
        escritores[i] = thread(funcion_escritor, monitor);
    
    for (int i = 0; i < num_hebras; i++)
        lectores[i] = thread(funcion_lector, monitor);

    for (int i = 0; i < num_hebras; i++) {
        escritores[i].join();
        lectores[i].join();
    }
}