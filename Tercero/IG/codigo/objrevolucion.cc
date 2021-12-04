#include "aux.h"
#include "objrevolucion.h"
#include "ply_reader.h"
#include "algorithm"




// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************

void ObjRevolucion::calcular_normales() {
  Tupla3i actual;
  Tupla3f p, q, r, vA, vB, normalCaraActual, normalActual;
  std::vector<Tupla3f> normalesCaras;

  normalesVertices.reserve(v.size());

  for (int i = 0; i < f.size(); i++) {
    actual = f[i];
    p = v[actual(0)];
    q = v[actual(1)];
    r = v[actual(2)];
    
    vA = q-p;
    vB = r-p;
    //Calculamos el producto vectorial
    normalCaraActual(X) = vA(Y)*vB(Z) - vA(Z)*vB(Y);
    normalCaraActual(Y) = vA(Z)*vB(X) - vA(X)*vB(Z);
    normalCaraActual(Z) = vA(X)*vB(Y) - vA(Y)*vB(X);

    //Normalizamos el vector
    double result = sqrt(normalCaraActual(X)*normalCaraActual(X) + normalCaraActual(Y)*normalCaraActual(Y) + normalCaraActual(Z)*normalCaraActual(Z));
    normalCaraActual(X) /= result;
    normalCaraActual(Y) /= result;
    normalCaraActual(Z) /= result;

    normalesVertices[actual(0)] = normalesVertices[actual(0)] + normalCaraActual;
    normalesVertices[actual(1)] = normalesVertices[actual(1)] + normalCaraActual;
    normalesVertices[actual(2)] = normalesVertices[actual(2)] + normalCaraActual;
  }

  for (int i = 0; i < f_tapa_inf.size() && creada_inf; i++) {
    actual = f_tapa_inf[i];
    p = v[actual(0)];
    q = v[actual(1)];
    r = v[actual(2)];
    
    vA = q-p;
    vB = r-p;
    //Calculamos el producto vectorial
    normalCaraActual(X) = vA(Y)*vB(Z) - vA(Z)*vB(Y);
    normalCaraActual(Y) = vA(Z)*vB(X) - vA(X)*vB(Z);
    normalCaraActual(Z) = vA(X)*vB(Y) - vA(Y)*vB(X);

    //Normalizamos el vector
    double result = sqrt(normalCaraActual(X)*normalCaraActual(X) + normalCaraActual(Y)*normalCaraActual(Y) + normalCaraActual(Z)*normalCaraActual(Z));
    normalCaraActual(X) /= result;
    normalCaraActual(Y) /= result;
    normalCaraActual(Z) /= result;

    normalesVertices[actual(0)] = normalesVertices[actual(0)] + normalCaraActual;
    normalesVertices[actual(1)] = normalesVertices[actual(1)] + normalCaraActual;
    normalesVertices[actual(2)] = normalesVertices[actual(2)] + normalCaraActual;
  }

  for (int i = 0; i < f_tapa_sup.size() && creada_sup; i++) {
    actual = f_tapa_sup[i];
    p = v[actual(0)];
    q = v[actual(1)];
    r = v[actual(2)];
    
    vA = q-p;
    vB = r-p;
    //Calculamos el producto vectorial
    normalCaraActual(X) = vA(Y)*vB(Z) - vA(Z)*vB(Y);
    normalCaraActual(Y) = vA(Z)*vB(X) - vA(X)*vB(Z);
    normalCaraActual(Z) = vA(X)*vB(Y) - vA(Y)*vB(X);

    //Normalizamos el vector
    double result = sqrt(normalCaraActual(X)*normalCaraActual(X) + normalCaraActual(Y)*normalCaraActual(Y) + normalCaraActual(Z)*normalCaraActual(Z));
    normalCaraActual(X) /= result;
    normalCaraActual(Y) /= result;
    normalCaraActual(Z) /= result;

    normalesVertices[actual(0)] = normalesVertices[actual(0)] + normalCaraActual;
    normalesVertices[actual(1)] = normalesVertices[actual(1)] + normalCaraActual;
    normalesVertices[actual(2)] = normalesVertices[actual(2)] + normalCaraActual;
  }

  for (int i = 0; i < normalesVertices.size(); i++) {
    normalActual = normalesVertices[i];
    double result = sqrt(normalActual(X)*normalActual(X) + normalActual(Y)*normalActual(Y) + normalActual(Z)*normalActual(Z));

    normalesVertices[i](X) /= result;
    normalesVertices[i](Y) /= result;
    normalesVertices[i](Z) /= result;
  }
}

// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion() {}

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
   ply::read_vertices(archivo,perfil);
   crearMalla(perfil, num_instancias, tapa_sup, tapa_inf);

   creada_sup = tapa_sup;
   creada_inf = tapa_inf;

   for (int i = 0; i < v.size(); i++) {
      c_solido.push_back(Tupla3f(0,0,1));
      c_lineas.push_back(Tupla3f(1,0,0));
      c_puntos.push_back(Tupla3f(0,1,0));
      c_ajedrez_par.push_back(Tupla3f(0.5,1,0));
      c_ajedrez_impar.push_back(Tupla3f(1,0,0.25));
   }

   for (int i = 0; i < f.size(); i++)
      if (i % 2 == 0)
         f_ajedrez_par.push_back(f[i]);
      else
         f_ajedrez_impar.push_back(f[i]);

    for (int i = 0; i < f_tapa_inf.size(); i++)
      if (i % 2 == 0)
         f_ajedrez_inf_par.push_back(f_tapa_inf[i]);
      else
         f_ajedrez_inf_impar.push_back(f_tapa_inf[i]);
   
   for (int i = 0; i < f_tapa_sup.size(); i++)
      if (i % 2 == 0)
         f_ajedrez_sup_par.push_back(f_tapa_sup[i]);
      else
         f_ajedrez_sup_impar.push_back(f_tapa_sup[i]);

   calcular_normales();
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

 
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {

   crearMalla(archivo, num_instancias, tapa_sup, tapa_inf);

   creada_sup = tapa_sup;
   creada_inf = tapa_inf;

   for (int i = 0; i < v.size(); i++) {
      c_solido.push_back(Tupla3f(0,0,1));
      c_lineas.push_back(Tupla3f(1,0,0));
      c_puntos.push_back(Tupla3f(0,1,0));
      c_ajedrez_par.push_back(Tupla3f(0.5,1,0));
      c_ajedrez_impar.push_back(Tupla3f(1,0,0.25));
   }

   for (int i = 0; i < f.size(); i++)
      if (i % 2 == 0)
         f_ajedrez_par.push_back(f[i]);
      else
         f_ajedrez_impar.push_back(f[i]);
   
   for (int i = 0; i < f_tapa_inf.size(); i++)
      if (i % 2 == 0)
         f_ajedrez_inf_par.push_back(f_tapa_inf[i]);
      else
         f_ajedrez_inf_impar.push_back(f_tapa_inf[i]);
   
   for (int i = 0; i < f_tapa_sup.size(); i++)
      if (i % 2 == 0)
         f_ajedrez_sup_par.push_back(f_tapa_sup[i]);
      else
         f_ajedrez_sup_impar.push_back(f_tapa_sup[i]);

   
   calcular_normales();
    
}

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, bool tapa_sup, bool tapa_inf) {

   v.clear();
   f.clear();

   N = num_instancias;
   M = perfil_original.size();

   if (perfil_original[0](Y) > perfil_original[perfil_original.size()-1](Y)) {
       std::reverse(perfil_original.begin(), perfil_original.end());
   }

   Tupla3f verticeSur(0,perfil_original[0](Y),0),
           verticeNorte(0,perfil_original[M-1](Y),0);

   if (perfil_original[0](X) == 0) {
      verticeSur = perfil_original[0];
      perfil_original.erase(perfil_original.begin());
      M--;
   }

   if (perfil_original[M-1](X) == 0) {
      std::cout << "Vertice norte detectado\n";
      verticeNorte = perfil_original[M-1];
      perfil_original.erase(--perfil_original.end());
      M--;
   }

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

   //Tapa inferior
   if (tapa_inf) {
      v.push_back(verticeSur);

      for (int j = 0; j < N; j++) {
         int a = M*j;
         int b = M*((j+1)%N);

         Tupla3i tri(a,N*M,b);
         f_tapa_inf.push_back(tri);
      }
   }

   //Tapa superior
   if (tapa_sup) {
      v.push_back(verticeNorte);
      
      for (int j = 0; j < N; j++) {
         int a = M*(j+1) - 1;
         int b = M*(((j+1)%N) + 1) - 1;

         Tupla3i tri(a,b,N*M+1);
         f_tapa_sup.push_back(tri);
      }
   }
   
}

// Visualización en modo inmediato con 'glDrawElements'

void ObjRevolucion::draw_ModoInmediato(int visualizado, bool tapa_sup, bool tapa_inf)
{

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, v.data() );
  glEnable(GL_CULL_FACE);
  glEnableClientState(GL_COLOR_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glNormalPointer(GL_FLOAT, 0, normalesVertices.data());

  glPointSize(6); //Indicamos el tamaño de los puntos

  if ((visualizado & AJEDREZ) == AJEDREZ) {
    glPolygonMode(GL_FRONT, GL_FILL);

   glColorPointer(3, GL_FLOAT, 0, c_ajedrez_par.data() );

    glDrawElements(GL_TRIANGLES, f_ajedrez_par.size()*3, GL_UNSIGNED_INT, f_ajedrez_par.data());
    if (creada_sup && tapa_sup) {
        glDrawElements(GL_TRIANGLES, f_ajedrez_sup_par.size()*3, GL_UNSIGNED_INT, f_ajedrez_sup_par.data());
    }
    if (creada_inf && tapa_inf) {
        glDrawElements(GL_TRIANGLES, f_ajedrez_inf_par.size()*3, GL_UNSIGNED_INT, f_ajedrez_inf_par.data());
    }

   glColorPointer(3, GL_FLOAT, 0, c_ajedrez_impar.data() );

    glDrawElements(GL_TRIANGLES, f_ajedrez_impar.size()*3, GL_UNSIGNED_INT, f_ajedrez_impar.data());
    if (creada_sup && tapa_sup) {
        glDrawElements(GL_TRIANGLES, f_ajedrez_sup_impar.size()*3, GL_UNSIGNED_INT, f_ajedrez_sup_impar.data());
    }
    if (creada_inf && tapa_inf) {
        glDrawElements(GL_TRIANGLES, f_ajedrez_inf_impar.size()*3, GL_UNSIGNED_INT, f_ajedrez_inf_impar.data());
    }

    } else if ((visualizado & SOLIDO) == SOLIDO) {             //Habilitamos CULL_FACE para no pintar la cara interior del sólido
        glPolygonMode(GL_FRONT, GL_FILL);   //Indicamos de pintar solo el frente y el modo a pintar


         glColorPointer(3, GL_FLOAT, 0, c_solido.data() );

        glDrawElements( GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, f.data());

        if (creada_inf && tapa_inf)
            glDrawElements( GL_TRIANGLES, 3*f_tapa_inf.size(), GL_UNSIGNED_INT, f_tapa_inf.data());
        
        if (creada_sup && tapa_sup)
            glDrawElements( GL_TRIANGLES, 3*f_tapa_sup.size(), GL_UNSIGNED_INT, f_tapa_sup.data());
    }

    if ((visualizado & LINEAS) == LINEAS) {   //Pintamos líneas

        glPolygonMode(GL_FRONT, GL_LINE);  //Indicamos el modo a pintar
        

        glColorPointer(3, GL_FLOAT, 0, c_lineas.data() );

        glDrawElements( GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, f.data());

        if (creada_inf && tapa_inf)
            glDrawElements( GL_TRIANGLES, 3*f_tapa_inf.size(), GL_UNSIGNED_INT, f_tapa_inf.data());
        
        if (creada_sup && tapa_sup)
            glDrawElements( GL_TRIANGLES, 3*f_tapa_sup.size(), GL_UNSIGNED_INT, f_tapa_sup.data());

    }

    if ((visualizado & PUNTOS) == PUNTOS) {

        glPolygonMode(GL_FRONT, GL_POINT); //Indicamos modo a pintar
        

        glColorPointer(3, GL_FLOAT, 0, c_puntos.data() );

        glDrawElements( GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, f.data());

        if (creada_inf && tapa_inf)
            glDrawElements( GL_TRIANGLES, 3*f_tapa_inf.size(), GL_UNSIGNED_INT, f_tapa_inf.data());
        
        if (creada_sup && tapa_sup)
            glDrawElements( GL_TRIANGLES, 3*f_tapa_sup.size(), GL_UNSIGNED_INT, f_tapa_sup.data());

    }

    glDisableClientState( GL_VERTEX_ARRAY );
    glDisableClientState( GL_NORMAL_ARRAY );

}   
//   -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void ObjRevolucion::draw_ModoDiferido(int visualizado, bool tapa_sup, bool tapa_inf)
{

  if (vbo_normalesVertices == 0) {
    vbo_normalesVertices = crearVBO(GL_ARRAY_BUFFER, normalesVertices.size()*3*sizeof(float), normalesVertices.data());
  }

  if (vbo_triangulos == 0 || vbo_vertices == 0 || vbo_triangulos_aje_impar == 0 || vbo_triangulos_aje_par == 0) {
    vbo_vertices = crearVBO(GL_ARRAY_BUFFER, v.size()*3*sizeof(float), v.data());
    vbo_triangulos = crearVBO(GL_ELEMENT_ARRAY_BUFFER, f.size()*3*sizeof(int), f.data());
    vbo_triangulos_aje_par = crearVBO(GL_ELEMENT_ARRAY_BUFFER, f_ajedrez_par.size()*3*sizeof(int), f_ajedrez_par.data());
    vbo_triangulos_aje_impar = crearVBO(GL_ELEMENT_ARRAY_BUFFER, f_ajedrez_impar.size()*3*sizeof(int), f_ajedrez_impar.data());
    vbo_f_tapa_inf = crearVBO(GL_ELEMENT_ARRAY_BUFFER, f_tapa_inf.size()*3*sizeof(int), f_tapa_inf.data());
    vbo_f_ajedrez_inf_par = crearVBO(GL_ELEMENT_ARRAY_BUFFER, f_ajedrez_inf_par.size()*3*sizeof(int), f_ajedrez_inf_par.data());
    vbo_f_ajedrez_inf_impar = crearVBO(GL_ELEMENT_ARRAY_BUFFER, f_ajedrez_inf_impar.size()*3*sizeof(int), f_ajedrez_inf_impar.data());
    vbo_f_tapa_sup = crearVBO(GL_ELEMENT_ARRAY_BUFFER, f_tapa_sup.size()*3*sizeof(int), f_tapa_sup.data());
    vbo_f_ajedrez_sup_par = crearVBO(GL_ELEMENT_ARRAY_BUFFER, f_ajedrez_sup_par.size()*3*sizeof(int), f_ajedrez_sup_par.data());
    vbo_f_ajedrez_sup_impar = crearVBO(GL_ELEMENT_ARRAY_BUFFER, f_ajedrez_sup_impar.size()*3*sizeof(int), f_ajedrez_sup_impar.data());
  }
  
  glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);  //Cargamos el buffer de vértices
  glVertexPointer(3,GL_FLOAT,0,0);
  glBindBuffer(GL_NORMAL_ARRAY_BUFFER_BINDING, vbo_normalesVertices);
  glNormalPointer(GL_FLOAT, 0, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_NORMAL_ARRAY_BUFFER_BINDING, 0);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glEnable(GL_CULL_FACE);

  //Comprobar si hay colores. Si los hay, cargarlos.

  if ((vbo_colores_ajedrez_par == 0 || vbo_colores_ajedrez_impar) && c_ajedrez_par.size() != 0 && c_ajedrez_impar.size() != 0) {  //Comprobamos si están creados los vbo, si no los creamos
    vbo_colores_ajedrez_par = crearVBO(GL_ELEMENT_ARRAY_BUFFER, c_ajedrez_par.size()*3*sizeof(float), c_ajedrez_par.data());
    vbo_colores_ajedrez_impar = crearVBO(GL_ELEMENT_ARRAY_BUFFER, c_ajedrez_impar.size()*3*sizeof(float), c_ajedrez_impar.data());
  }
  
  if(c_solido.size() != 0 && vbo_colores_solido == 0)
    vbo_colores_solido = crearVBO(GL_ARRAY_BUFFER, c_solido.size()*3*sizeof(float), c_solido.data());

  if(c_lineas.size() != 0 && vbo_colores_lineas == 0)
    vbo_colores_lineas = crearVBO(GL_ARRAY_BUFFER, c_lineas.size()*3*sizeof(float), c_lineas.data());

  if(c_puntos.size() != 0 && vbo_colores_puntos == 0)
    vbo_colores_puntos = crearVBO(GL_ARRAY_BUFFER, c_puntos.size()*3*sizeof(float), c_puntos.data());
  

  if ((visualizado & AJEDREZ) == AJEDREZ) { //Mostramos en modo ajedrez
    glPolygonMode(GL_FRONT, GL_FILL);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_triangulos_aje_par);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_colores_ajedrez_par);
    glColorPointer(3, GL_FLOAT, 0, 0);
    glDrawElements(GL_TRIANGLES, 3*f_ajedrez_par.size(), GL_UNSIGNED_INT, 0);
    if (creada_sup && tapa_sup) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_f_ajedrez_sup_par);
        glDrawElements(GL_TRIANGLES, f_ajedrez_sup_par.size()*3, GL_UNSIGNED_INT, 0);
    }
    if (creada_inf && tapa_inf) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_f_ajedrez_inf_par);
        glDrawElements(GL_TRIANGLES, f_ajedrez_inf_par.size()*3, GL_UNSIGNED_INT, 0);
    }
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_triangulos_aje_impar);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_colores_ajedrez_impar);
    glColorPointer(3, GL_FLOAT, 0, 0);
    glDrawElements(GL_TRIANGLES, 3*f_ajedrez_impar.size(), GL_UNSIGNED_INT, 0);
    if (creada_sup && tapa_sup) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_f_ajedrez_sup_impar);
        glDrawElements(GL_TRIANGLES, f_ajedrez_sup_impar.size()*3, GL_UNSIGNED_INT, 0);
    }
    if (creada_inf && tapa_inf) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_f_ajedrez_inf_impar);
        glDrawElements(GL_TRIANGLES, f_ajedrez_inf_impar.size()*3, GL_UNSIGNED_INT, 0);
    }
  }

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_triangulos);  //Cambiamos el buffer

  if ((visualizado & SOLIDO) == SOLIDO && (visualizado & AJEDREZ) != AJEDREZ) { //Mostramos en sólido
    glPolygonMode(GL_FRONT, GL_FILL);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_colores_solido);
    glColorPointer(3, GL_FLOAT, 0, 0);
    glDrawElements(GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, 0);
    if (creada_sup && tapa_sup) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_f_tapa_sup);
        glDrawElements(GL_TRIANGLES, f_tapa_sup.size()*3, GL_UNSIGNED_INT, 0);
    }
    if (creada_inf && tapa_inf) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_f_tapa_inf);
        glDrawElements(GL_TRIANGLES, f_tapa_inf.size()*3, GL_UNSIGNED_INT, 0);
    }
  }

  if ((visualizado & LINEAS) == LINEAS) { //Mostramos como líneas
    glPolygonMode(GL_FRONT, GL_LINE);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_colores_lineas);
    glColorPointer(3, GL_FLOAT, 0, 0);
    glDrawElements(GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, 0);
    if (creada_sup && tapa_sup) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_f_tapa_sup);
        glDrawElements(GL_TRIANGLES, f_tapa_sup.size()*3, GL_UNSIGNED_INT, 0);
    }
    if (creada_inf && tapa_inf) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_f_tapa_inf);
        glDrawElements(GL_TRIANGLES, f_tapa_inf.size()*3, GL_UNSIGNED_INT, 0);
    }
  }

  if ((visualizado & PUNTOS) == PUNTOS) { //Mostramos como puntos
    glPointSize(6); //Indicamos el tamaño de los puntos
    glPolygonMode(GL_FRONT, GL_POINT);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_colores_puntos);
    glColorPointer(3, GL_FLOAT, 0, 0);
    glDrawElements(GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, 0);
    if (creada_sup && tapa_sup) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_f_tapa_sup);
        glDrawElements(GL_TRIANGLES, f_tapa_sup.size()*3, GL_UNSIGNED_INT, 0);
    }
    if (creada_inf && tapa_inf) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_f_tapa_inf);
        glDrawElements(GL_TRIANGLES, f_tapa_inf.size()*3, GL_UNSIGNED_INT, 0);
    }
  }

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);  //Quitamos el buffer de triangulos

  glDisableClientState(GL_VERTEX_ARRAY);  //Desactivamos el array de vértices
  glDisableClientState(GL_NORMAL_ARRAY);

}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void ObjRevolucion::draw(modoDibujado modo, int visualizado, bool tapa_sup, bool tapa_inf)
{
   if (this->tieneMaterial)
    this->m.aplicar();

   if (modo == DIFERIDO)
      draw_ModoDiferido(visualizado, tapa_sup, tapa_inf);
   else
      draw_ModoInmediato(visualizado, tapa_sup, tapa_inf);
}