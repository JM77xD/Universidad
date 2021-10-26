#include "aux.h"
#include "objrevolucion.h"
#include "ply_reader.h"




// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion() {}

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
   ply::read_vertices(archivo,perfil);
   crearMalla(perfil, num_instancias);
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

 
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {

   crearMalla(archivo, num_instancias);
    
}

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias) {

   v.clear();
   f.clear();

   int N = num_instancias;
   int M = perfil_original.size();

   double incremento_ang = 2*M_PI/N;

   //Crear tabla de vértices

   for (int i = 0; i < N; i++) {

      double angulo = i * incremento_ang;

      for (int j = 0; j < M; j++) {
         Tupla3f actual = perfil_original[j];
         float x = actual(X),z = actual(Z);

         actual(X) = (cos(angulo) * x) + (sin(angulo) * z);
         actual(Z) = (-sin(angulo) * x) + (cos(angulo) * z);

         v.push_back(actual);

      }

   }

   //Crear tabla de triángulos

   for (int i = 0; i < N; i++) {
      for (int j = 0; j < M-1; j++) {
         int a = M*i+j;
         int b = M*((i+1)%N)+j;
         Tupla3i tri(a, b, b+1);
         f.push_back(tri);
         Tupla3i tri2(a, b+1, a+1);
         f.push_back(tri2);
      }
   }

   //Tapas

   Tupla3f verticeSur(0,perfil[0](Y),0),
           verticeNorte(0,perfil[M-1](Y),0);

   v.push_back(verticeSur);
   v.push_back(verticeNorte);

   
   //Tapa inferior
   for (int j = 0; j < N; j++) {
      int a = M*j;
      int b = M*((j+1)%N);

      Tupla3i tri(a,N*M,b);
      f.push_back(tri);
   }
   
   
   //Tapa superior
   for (int j = 0; j < N; j++) {
      int a = M*(j+1) - 1;
      int b = M*(((j+1)%N) + 1) - 1;

      Tupla3i tri(a,b,N*M+1);
      f.push_back(tri);
   }
   
}
