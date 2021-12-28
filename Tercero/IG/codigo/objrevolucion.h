// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Cubo.h

//
// #############################################################################

#ifndef OBJREVOLUCION_H_INCLUDED
#define OBJREVOLUCION_H_INCLUDED

#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Cubo con centro en el origen y lado unidad por defecto
// (tiene 9 vertices y 6 caras)

class ObjRevolucion : public Malla3D
{
    public:
        ObjRevolucion();
        ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup=true, bool tapa_inf=true, bool textura=true) ;
        ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup=true, bool tapa_inf=true, bool textura=true) ;
        void draw(modoDibujado modo, int visualizado, bool tapa_sup=true, bool tapa_inf=true);
        void draw_ModoDiferido(int visualizado, bool tapa_sup=true, bool tapa_inf=true);
        void draw_ModoInmediato(int visualizado, bool tapa_sup=true, bool tapa_inf=true);
    protected:

        void calcular_normales();

        void crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, bool tapa_sup=true, bool tapa_inf=true, bool textura=true);

        std::vector<Tupla3f> perfil;

        std::vector<Tupla3i> f_tapa_sup ;
        std::vector<Tupla3i> f_tapa_inf ;
        std::vector<Tupla3i> f_ajedrez_sup_par ;
        std::vector<Tupla3i> f_ajedrez_sup_impar ;
        std::vector<Tupla3i> f_ajedrez_inf_par ;
        std::vector<Tupla3i> f_ajedrez_inf_impar ;

        GLuint  vbo_f_tapa_sup = 0 ,
                vbo_f_tapa_inf = 0 ,
                vbo_f_ajedrez_sup_par = 0 ,
                vbo_f_ajedrez_sup_impar = 0 ,
                vbo_f_ajedrez_inf_par = 0 ,
                vbo_f_ajedrez_inf_impar = 0;

        bool creada_sup = true, creada_inf = true;

        int N, M;

} ;




#endif
