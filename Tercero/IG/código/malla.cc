#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

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

    glColor3f(1,0,0); //Asignamos color a los vértices
    glDrawElements( GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, f.data());

  }

  if ((visualizado & PUNTOS) == PUNTOS) {

    glPolygonMode(GL_FRONT, GL_POINT); //Indicamos modo a pintar

    glColorPointer(3, GL_FLOAT, 0, c_puntos.data() );

    glColor3f(0,1,0);                           //Asignamos color a los vértices
    glDrawElements( GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, f.data());

  }

  glDisableClientState( GL_VERTEX_ARRAY );

}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Malla3D::draw_ModoDiferido(int visualizado)
{
  if (vbo_triangulos == 0 || vbo_vertices == 0 || vbo_triangulos_aje_impar == 0 || vbo_triangulos_aje_par == 0) {
    vbo_vertices = crearVBO(GL_ARRAY_BUFFER, v.size()*3*sizeof(float), v.data());
    vbo_triangulos = crearVBO(GL_ELEMENT_ARRAY_BUFFER, f.size()*3*sizeof(int), f.data());
  }
  
  glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);  //Cargamos el buffer de vértices
  glVertexPointer(3,GL_FLOAT,0,0);
  glBindBuffer(GL_ARRAY_BUFFER, 0); //Descargamos
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glEnable(GL_CULL_FACE);

  //Comprobar si hay colores. Si los hay, cargarlos.

  if ((vbo_colores_ajedrez_par == 0 || vbo_colores_ajedrez_impar) && c_ajedrez_par.size() != 0 && c_ajedrez_impar.size() != 0) {  //Comprobamos si están creados los vbo, si no los creamos
    vbo_colores_ajedrez_par = crearVBO(GL_ELEMENT_ARRAY_BUFFER, c_ajedrez_par.size()*3*sizeof(float), c_ajedrez_par.data());
    vbo_colores_ajedrez_impar = crearVBO(GL_ELEMENT_ARRAY_BUFFER, c_ajedrez_impar.size()*3*sizeof(float), c_ajedrez_impar.data());
  }

  if(c_solido.size() != 0 && vbo_colores_solido == 0) {
    vbo_colores_solido = crearVBO(GL_ARRAY_BUFFER, c_solido.size()*3*sizeof(float), c_solido.data());
  }

  if(c_lineas.size() != 0 && vbo_colores_lineas == 0) {
    vbo_colores_lineas = crearVBO(GL_ARRAY_BUFFER, c_lineas.size()*3*sizeof(float), c_lineas.data());
  }

  if(c_puntos.size() != 0 && vbo_colores_puntos == 0) {
    vbo_colores_puntos = crearVBO(GL_ARRAY_BUFFER, c_puntos.size()*3*sizeof(float), c_puntos.data());
  }

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_triangulos);  //Cambiamos el buffer

  if ((visualizado & AJEDREZ) == AJEDREZ) { //Mostramos en modo ajedrez
    glPolygonMode(GL_FRONT, GL_FILL);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_colores_ajedrez_par);
    glColorPointer(3, GL_FLOAT, 0, 0);
    glDrawElements(GL_TRIANGLES, 3*v.size(), GL_UNSIGNED_INT, 0);
  }

  if ((visualizado & SOLIDO) == SOLIDO && (visualizado & AJEDREZ) != AJEDREZ) { //Mostramos en sólido
    glShadeModel(GL_SMOOTH);
    glPolygonMode(GL_FRONT, GL_FILL);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_colores_solido);
    glColorPointer(3, GL_FLOAT, 0, 0);
    glDrawElements(GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  if ((visualizado & LINEAS) == LINEAS) { //Mostramos como líneas
    glShadeModel(GL_FLAT);
    glPolygonMode(GL_FRONT, GL_LINE);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_colores_lineas);
    glColorPointer(3, GL_FLOAT, 0, 0);
    glDrawElements(GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, 0);
  }

  if ((visualizado & PUNTOS) == PUNTOS) { //Mostramos como puntos
    glShadeModel(GL_FLAT);
    glPointSize(6); //Indicamos el tamaño de los puntos
    glPolygonMode(GL_FRONT, GL_POINT);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_colores_puntos);
    glColorPointer(3, GL_FLOAT, 0, 0);
    glDrawElements(GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, 0);
  }

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);  //Quitamos el buffer de triangulos

  glDisableClientState(GL_VERTEX_ARRAY);  //Desactivamos el array de vértices

}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw(modoDibujado modo, int visualizado)
{
   if (modo == DIFERIDO)
      draw_ModoDiferido(visualizado);
   else
      draw_ModoInmediato(visualizado);
}

