// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Malla3D.h
// -- declaraciones de clase Malla3D (mallas indexadas) y derivados
//
// #############################################################################

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "aux.h"

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************
typedef enum {DIFERIDO, INMEDIATO} modoDibujado;
typedef enum {AJEDREZ = 1, SOLIDO = 2, PUNTOS = 4, LINEAS = 8} visualizacion;
class Malla3D
{
   public:

   // dibuja el objeto en modo inmediato
   void draw_ModoInmediato(int visualizado);

   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido(int visualizado);

   // función que redibuja el objeto
   // está función llama a 'draw_ModoInmediato' (modo inmediato)
   // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
   void draw(modoDibujado modo, int visualizado) ;

   protected:

   GLuint crearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid *puntero_ram);

   void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)

   std::vector<Tupla3f> v ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> f ;   // una terna de 3 enteros por cada cara o triángulo
   std::vector<Tupla3i> f_ajedrez_par ;   // una terna de 3 enteros por cada cara o triángulo par
   std::vector<Tupla3i> f_ajedrez_impar ;   // una terna de 3 enteros por cada cara o triángulo impar
   std::vector<Tupla3f> c_solido ;    // Una terna de 3 floats para el color de cada cara solida
   std::vector<Tupla3f> c_lineas ;    // Una terna de 3 floats para el color de cada lineas
   std::vector<Tupla3f> c_puntos ;    // Una terna de 3 floats para el color de cada punto
   std::vector<Tupla3f> c_ajedrez_par ;    // Una terna de 3 floats para el color de cada cara ajedrez par
   std::vector<Tupla3f> c_ajedrez_impar ;    // Una terna de 3 floats para el color de cada cara ajedrez par
   

   GLuint   vbo_vertices = 0,
            vbo_triangulos = 0,
            vbo_triangulos_aje_par = 0,
            vbo_triangulos_aje_impar = 0,
            vbo_colores_solido = 0,
            vbo_colores_lineas = 0,
            vbo_colores_puntos = 0,
            vbo_colores_ajedrez_par = 0,
            vbo_colores_ajedrez_impar = 0;

   // completar: tabla de normales de vértices
} ;


#endif
