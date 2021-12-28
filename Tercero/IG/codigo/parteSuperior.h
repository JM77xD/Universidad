#ifndef PARTESUPERIOR_H_INCLUDED
#define PARTESUPERIOR_H_INCLUDED
#include "aux.h"
#include "objply.h"
#include "brazoIzq.h"
#include "brazoDrch.h"

class ParteSuperior : public Malla3D {
    public:
        void modificarGiroLCabeza(float valor, const bool aut = false);

        void modificarGiroVCabeza(float valor, const bool aut = false);

        void modificarGiroBrazoDrch(float valor, const bool aut = false);

        void modificarGiroBrazoIzq(float valor, const bool aut = false);

        void modificarGiroDedoGDrch(float valor, const bool aut = false);

        void modificarGiroDedoGIzq(float valor, const bool aut = false);

        void modificarGiroDedosDrch(float valor, const bool aut = false);

        void modificarGiroDedosIzq(float valor, const bool aut = false);

        void modificarGiroTronco(float valor, const bool aut = false);

        void modificarPosBrazoDrch(float valor, const bool aut = false);

        void draw(modoDibujado modo, int visualizado);

        void setMaterial(Material mat);

        void reset();

        ParteSuperior();
    
    private:

        float   giroLCabeza,
                giroVCabeza,
                giroBrazoDrch,
                giroBrazoIzq,
                posBrazoDrch;

        ObjPLY  *torso = nullptr,
                *cabeza = nullptr;
        BrazoDrch *brazoDrch = nullptr;
        BrazoIzq  *brazoIzq = nullptr;

        bool change;

};

#endif