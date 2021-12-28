// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: cono.h

//
// #############################################################################

#ifndef CONO_H_INCLUDED
#define CONO_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"

// *****************************************************************************
//
// clases derivadas de ObjRevolucion (definen constructores específicos)
//
// *****************************************************************************


class Cono : public ObjRevolucion
{
   public:
    Cono(const int num_vert_perfil, const int num_instancias_perfil, const float altura, const float radio, bool textura=true);

   private:
    void crearPerfil(const int num_vert_perfil, const float altura, const float radio);

} ;




#endif