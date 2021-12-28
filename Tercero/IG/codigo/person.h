#ifndef PERSON_H_INCLUDED
#define PERSON_H_INCLUDED
#include "aux.h"
#include "parteSuperior.h"
#include "parteInferior.h"

class Person : public Malla3D {
    public:
        void modificarGiroLCabeza(float valor, const bool aut = false);

        void modificarGiroVCabeza(float valor, const bool aut = false);

        void modificarGiroBrazoDrch(float valor, const bool aut = false);

        void modificarGiroBrazoIzq(float valor, const bool aut = false);

        void modificarGiroPiernaDrch(float valor, const bool aut = false);

        void modificarGiroPiernaIzq(float valor, const bool aut = false);

        void modificarGiroDedoGDrch(float valor, const bool aut = false);

        void modificarGiroDedoGIzq(float valor, const bool aut = false);

        void modificarGiroDedosDrch(float valor, const bool aut = false);

        void modificarGiroDedosIzq(float valor, const bool aut = false);

        void modificarGiroTronco(float valor, const bool aut = false);

        void modificarPosBrazoDrch(float valor, const bool aut = false);

        void draw(modoDibujado modo, int visualizado);

        void setMaterial(Material mat);

        void reset();

        Person();

    private:
        
        bool            change;

        float           giroTorso;

        ParteSuperior   *parteSuperior = nullptr;
        ParteInferior   *parteInferior = nullptr;

};

#endif