#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

//Constructor por defecto para que el compilador no chille
Malla3D::Malla3D() {}

//Asignar material a la malla
void Malla3D::setMaterial(Material mat) {
  this->m = mat;
  this->tieneMaterial = true;
}

//Cambiar el color sólido de un objeto
void Malla3D::setColor(Tupla3f nuevoColor) {
  c_solido.clear();
  
  for (int i = 0; i < v.size(); i++)
    c_solido.push_back(nuevoColor);

}


//Calculo de normales
void Malla3D::calcular_normales() {
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

  for (int i = 0; i < normalesVertices.size(); i++) {
    normalActual = normalesVertices[i];
    double result = sqrt(normalActual(X)*normalActual(X) + normalActual(Y)*normalActual(Y) + normalActual(Z)*normalActual(Z));

    normalesVertices[i](X) /= result;
    normalesVertices[i](Y) /= result;
    normalesVertices[i](Z) /= result;
  }
}

// Creación de VBO
GLuint Malla3D::crearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid *puntero_ram) {
  GLuint id_vbo ;                     // resultado: identificador de VBO
  
  glGenBuffers ( 1 , & id_vbo );      // crear nuevo VBO, obtener identificador (nunca 0)
  
  glBindBuffer ( tipo_vbo , id_vbo ); // activar el VBO usando su identificador

  glBufferData ( tipo_vbo , tamanio_bytes , puntero_ram , GL_STATIC_DRAW ); // esta instrucción hace la transferencia de datos desde RAM hacia GPU
 
  glBindBuffer ( tipo_vbo , 0 );      // desactivación del VBO (activar 0)
  
  return id_vbo ;                     // devolver el identificador resultado
}

// Visualización en modo inmediato con 'glDrawElements'

void Malla3D::draw_ModoInmediato(int visualizado)
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

    glColorPointer(3, GL_FLOAT, 0, c_ajedrez_impar.data() );
    glDrawElements(GL_TRIANGLES, f_ajedrez_impar.size()*3, GL_UNSIGNED_INT, f_ajedrez_impar.data());

  } else if ((visualizado & SOLIDO) == SOLIDO) {             //Habilitamos CULL_FACE para no pintar la cara interior del sólido
    glPolygonMode(GL_FRONT, GL_FILL);   //Indicamos de pintar solo el frente y el modo a pintar

    glColorPointer(3, GL_FLOAT, 0, c_solido.data() );

    glDrawElements( GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, f.data());
  }

  if ((visualizado & LINEAS) == LINEAS) {   //Pintamos líneas

    glPolygonMode(GL_FRONT, GL_LINE);  //Indicamos el modo a pintar

    glColorPointer(3, GL_FLOAT, 0, c_lineas.data() );

    glDrawElements( GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, f.data());

  }

  if ((visualizado & PUNTOS) == PUNTOS) {

    glPolygonMode(GL_FRONT, GL_POINT); //Indicamos modo a pintar

    glColorPointer(3, GL_FLOAT, 0, c_puntos.data() );

    glDrawElements( GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, f.data());

  }

  glDisableClientState( GL_VERTEX_ARRAY );
  glDisableClientState( GL_NORMAL_ARRAY );

}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Malla3D::draw_ModoDiferido(int visualizado)
{

  if (vbo_normalesVertices == 0) {
    vbo_normalesVertices = crearVBO(GL_ARRAY_BUFFER, normalesVertices.size()*3*sizeof(float), normalesVertices.data());
  }

  if (vbo_triangulos == 0 || vbo_vertices == 0 || vbo_triangulos_aje_impar == 0 || vbo_triangulos_aje_par == 0) {
    vbo_vertices = crearVBO(GL_ARRAY_BUFFER, v.size()*3*sizeof(float), v.data());
    vbo_triangulos = crearVBO(GL_ELEMENT_ARRAY_BUFFER, f.size()*3*sizeof(int), f.data());
    vbo_triangulos_aje_par = crearVBO(GL_ELEMENT_ARRAY_BUFFER, f_ajedrez_par.size()*3*sizeof(int), f_ajedrez_par.data());
    vbo_triangulos_aje_impar = crearVBO(GL_ELEMENT_ARRAY_BUFFER, f_ajedrez_impar.size()*3*sizeof(int), f_ajedrez_impar.data());
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
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_triangulos_aje_impar);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_colores_ajedrez_impar);
    glColorPointer(3, GL_FLOAT, 0, 0);
    glDrawElements(GL_TRIANGLES, 3*f_ajedrez_impar.size(), GL_UNSIGNED_INT, 0);
  }

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_triangulos);  //Cambiamos el buffer

  if ((visualizado & SOLIDO) == SOLIDO && (visualizado & AJEDREZ) != AJEDREZ) { //Mostramos en sólido
    glPolygonMode(GL_FRONT, GL_FILL);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_colores_solido);
    glColorPointer(3, GL_FLOAT, 0, 0);
    glDrawElements(GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, 0);
  }

  if ((visualizado & LINEAS) == LINEAS) { //Mostramos como líneas
    glPolygonMode(GL_FRONT, GL_LINE);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_colores_lineas);
    glColorPointer(3, GL_FLOAT, 0, 0);
    glDrawElements(GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, 0);
  }

  if ((visualizado & PUNTOS) == PUNTOS) { //Mostramos como puntos
    glPointSize(6); //Indicamos el tamaño de los puntos
    glPolygonMode(GL_FRONT, GL_POINT);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_colores_puntos);
    glColorPointer(3, GL_FLOAT, 0, 0);
    glDrawElements(GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, 0);
  }

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);  //Quitamos el buffer de triangulos

  glDisableClientState(GL_VERTEX_ARRAY);  //Desactivamos el array de vértices
  glDisableClientState(GL_NORMAL_ARRAY);

}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw(modoDibujado modo, int visualizado)
{

   if (this->tieneMaterial)
    this->m.aplicar();

   if (modo == DIFERIDO)
      draw_ModoDiferido(visualizado);
   else
      draw_ModoInmediato(visualizado);
}

