#include "aux.h"
#include "objply.h"
#include "brazoIzq.h"
#include "brazoDrch.h"

class Person : public Malla3D {
    public:
        void modificarGiroLCabeza(float valor);

        void modificarGiroVCabeza(float valor);

        void modificarGiroBrazoDrch(float valor);

        void modificarGiroBrazoIzq(float valor);

        void modificarGiroPiernaDrch(float valor);

        void modificarGiroPiernaIzq(float valor);

        void modificarGiroDedoGDrch(float valor);

        void modificarGiroDedoGIzq(float valor);

        void modificarGiroDedosDrch(float valor);

        void modificarGiroDedosIzq(float valor);

        void draw(modoDibujado modo, int visualizado);

        void setMaterial(Material mat);

        Person();

    private:

        float   giroLCabeza,
                giroVCabeza,
                giroBrazoDrch,
                giroBrazoIzq,
                giroPiernaDrch,
                giroPiernaIzq;

        ObjPLY  *torso = nullptr,
                *cabeza = nullptr,
                *piernaDrch = nullptr,
                *piernaIzq = nullptr;
        BrazoDrch *brazoDrch = nullptr;
        BrazoIzq  *brazoIzq = nullptr;

};