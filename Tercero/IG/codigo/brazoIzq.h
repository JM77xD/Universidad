#include "aux.h"
#include "objply.h"


class BrazoIzq : Malla3D {
    public:

        void modificarGiroDedos(float valor);

        void modificarGiroDedoG(float valor);

        void draw(modoDibujado modo, int visualizado);

        void setMaterial(Material mat);

        BrazoIzq();

    private:

        float   giroDedoG,
                giroDedos;

        ObjPLY  *brazo = nullptr,
                *dedos = nullptr,
                *dedoG = nullptr;

};