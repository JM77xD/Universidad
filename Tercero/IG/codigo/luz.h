// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: luz.h

//
// #############################################################################

#ifndef LUZ_H_INCLUDED
#define LUZ_H_INCLUDED

#include "aux.h"

class Luz {
    protected:
        GLenum id;
        Tupla4f posicion,
                colorAmbiente,
                colorDifuso,
                colorEspecular;
                
        bool estado;
    
    public:
        void activar();

        void desactivar();
        
};

#endif