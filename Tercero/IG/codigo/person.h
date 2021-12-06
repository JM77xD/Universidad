#include "aux.h"
#include "objply.h"
#include "brazoIzq.h"
#include "brazoDrch.h"

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

        void draw(modoDibujado modo, int visualizado);

        void setMaterial(Material mat);

        void reset();

        Person();

    private:
        
        bool change;

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