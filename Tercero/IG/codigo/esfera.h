// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: esfera.h

//
// #############################################################################

#ifndef ESFERA_H_INCLUDED
#define ESFERA_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"

// *****************************************************************************
//
// clases derivadas de ObjRevolucion (definen constructores específicos)
//
// *****************************************************************************


class Esfera : public ObjRevolucion
{
   public:
    Esfera(const int num_vert_perfil, const int num_instancias_perfil, const float radio);

   private:
    void crearPerfil(const int num_vert_perfil, const float radio);

} ;




#endif