// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: material.h

//
// #############################################################################

#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#include "aux.h"

class Material {
    private:
        Tupla4f difuso,
                especular,
                ambiente;
        float   brillo;
    
    public:

        Material();
        
        Material(Tupla4f difuso, Tupla4f especular, Tupla4f ambiente, float brillo);

        Material(Tupla3f difuso, Tupla3f especular, Tupla3f ambiente, float brillo);

        void aplicar();
        
};

#endif