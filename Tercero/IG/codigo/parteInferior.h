#ifndef PARTEINFERIOR_H_INCLUDED
#define PARTEINFERIOR_H_INCLUDED

#include "aux.h"
#include "objply.h"

class ParteInferior : public Malla3D {
    public:

        void modificarGiroPiernaDrch(float valor, const bool aut = false);

        void modificarGiroPiernaIzq(float valor, const bool aut = false);

        void draw(modoDibujado modo, int visualizado);

        void setMaterial(Material mat);

        void reset();

        ParteInferior();
    
    private:

        float   giroPiernaDrch,
                giroPiernaIzq;

        ObjPLY  *piernaDrch = nullptr,
                *piernaIzq = nullptr;
        
        bool change;
};

#endif