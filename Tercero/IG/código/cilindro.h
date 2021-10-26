// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: cilindro.h

//
// #############################################################################

#ifndef CILINDRO_H_INCLUDED
#define CILINDRO_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"

// *****************************************************************************
//
// clases derivadas de ObjRevolucion (definen constructores específicos)
//
// *****************************************************************************


class Cilindro : public ObjRevolucion
{
   public:
    Cilindro(const int vert_perfil, const int instancias_perfil, const float altura, const float radio);

   private:
    void crearPerfil(const int vert_perfil, const float altura, const float radio);

} ;




#endif
