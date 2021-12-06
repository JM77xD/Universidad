#include "aux.h"
#include "objply.h"


class BrazoDrch : Malla3D {
    public:

        void modificarGiroDedos(float valor);

        void modificarGiroDedoG(float valor);

        void draw(modoDibujado modo, int visualizado);

        void setMaterial(Material mat);

        void reset();

        BrazoDrch();

    private:

        float   giroDedoG,
                giroDedos;

        ObjPLY  *brazo = nullptr,
                *dedos = nullptr,
                *dedoG = nullptr;

};