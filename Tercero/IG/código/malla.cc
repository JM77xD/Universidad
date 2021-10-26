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

  glPointSize(6); //Indicamos el tamaño de los puntos

  if ((visualizado & AJEDREZ) == AJEDREZ) {
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT, GL_FILL);
    glDisableClientState(GL_COLOR_ARRAY);

    //Separamos los triángulos en 2 mitades, primero todos los pares y luego los impares
    for (int i = 0; i < f.size(); i+=2)
      nuevosTriangulos1.push_back(f[i]);

    for (int i = 1; i < f.size(); i+=2)
      nuevosTriangulos2.push_back(f[i]);

    glShadeModel(GL_FLAT);  //Indicamos que no queremos degradado en las caras
                            //pintamos primero las caras pares y luego las impares, asignando colores distintos

    glColor3f(0.5,1,0); //Primera mitad en verde
    glDrawElements(GL_TRIANGLES, nuevosTriangulos1.size()*3, GL_UNSIGNED_INT, nuevosTriangulos1.data());

    glColor3f(1,0,0.25); //Segunda mitad en rojo
    glDrawElements(GL_TRIANGLES, nuevosTriangulos2.size()*3, GL_UNSIGNED_INT, nuevosTriangulos2.data());

  } else if ((visualizado & SOLIDO) == SOLIDO) {
    glEnable(GL_CULL_FACE);             //Habilitamos CULL_FACE para no pintar la cara interior del sólido
    glPolygonMode(GL_FRONT, GL_FILL);   //Indicamos de pintar solo el frente y el modo a pintar

    if (c.size() != 0) {                //Comprobamos que exista algún ColorArray y si no pintamos azul por defecto
      glEnableClientState(GL_COLOR_ARRAY);
      glColorPointer(3, GL_FLOAT, 0, c.data() );
    } else {
      glDisableClientState(GL_COLOR_ARRAY);
      glColor3f(0,0,1);
    }

    glShadeModel(GL_SMOOTH);            //Habilitamos la transición suave de colores para producir degradados en las caras
    glDrawElements( GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, f.data());
  }

  if ((visualizado & LINEAS) == LINEAS) {   //Pintamos líneas

    glDisable(GL_CULL_FACE);            //Deshabilitamos CULL_FACE, ya que queremos ver las líneas y puntos por ambas caras
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  //Indicamos el modo a pintar

    glDisableClientState(GL_COLOR_ARRAY); //Deshabilitamos el color array (para asegurar por si estaba habilitado)
    glShadeModel(GL_FLAT);                //Evitamos degradados en el dibujado

    glColor3f(1,0,0); //Asignamos color a los vértices
    glDrawElements( GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, f.data());

  }

  if ((visualizado & PUNTOS) == PUNTOS) {

    glDisable(GL_CULL_FACE);            //Deshabilitamos CULL_FACE, ya que queremos ver las líneas y puntos por ambas caras
    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); //Indicamos modo a pintar

    glDisableClientState(GL_COLOR_ARRAY); //Deshabilitamos el color array (para asegurar por si estaba habilitado)
    glShadeModel(GL_FLAT);                //Evitamos degradados en el dibujado

    glColor3f(0,1,0);                           //Asignamos color a los vértices
    glDrawElements( GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, f.data());

  }

  glDisableClientState( GL_VERTEX_ARRAY );

}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Malla3D::draw_ModoDiferido(int visualizado)
{
  
  if ((vbo_triangulos_aje1 == 0 || vbo_vertices == 0 || vbo_triangulos_aje2 == 0) && (visualizado & AJEDREZ) == AJEDREZ) {  //Comprobamos si están creados los vbo, si no los creamos
  
    vbo_vertices = crearVBO(GL_ARRAY_BUFFER, v.size()*3*sizeof(float), v.data());

    //Separamos los triángulos en 2 mitades, primero todos los pares y luego los impares
    for (int i = 0; i < f.size(); i+=2)
      nuevosTriangulos1.push_back(f[i]);
    
    vbo_triangulos_aje1 = crearVBO(GL_ELEMENT_ARRAY_BUFFER, nuevosTriangulos1.size()*3*sizeof(int), nuevosTriangulos1.data());

    for (int i = 1; i < f.size(); i+=2)
      nuevosTriangulos2.push_back(f[i]);

    vbo_triangulos_aje2 = crearVBO(GL_ELEMENT_ARRAY_BUFFER, nuevosTriangulos2.size()*3*sizeof(int), nuevosTriangulos2.data());


  } else if (vbo_triangulos == 0 || vbo_vertices == 0) {
    vbo_vertices = crearVBO(GL_ARRAY_BUFFER, v.size()*3*sizeof(float), v.data());
    vbo_triangulos = crearVBO(GL_ELEMENT_ARRAY_BUFFER, f.size()*3*sizeof(int), f.data());
  }
  
  glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);  //Cargamos el buffer de vértices
  glVertexPointer(3,GL_FLOAT,0,0);
  glBindBuffer(GL_ARRAY_BUFFER, 0); //Descargamos
  glEnableClientState(GL_VERTEX_ARRAY);

  if ((visualizado & AJEDREZ) == AJEDREZ) { //Mostramos en modo ajedrez
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_FLAT);
    glPolygonMode(GL_FRONT, GL_FILL);
    glDisableClientState(GL_COLOR_ARRAY);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_triangulos_aje1);
    glColor3f(0.5,1,0); //Primera mitad en verde
    glDrawElements(GL_TRIANGLES, 3*nuevosTriangulos1.size(), GL_UNSIGNED_INT, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_triangulos_aje2);
    glColor3f(1,0,0.25); //Segunda mitad en rojo
    glDrawElements(GL_TRIANGLES, 3*nuevosTriangulos2.size(), GL_UNSIGNED_INT, 0);
  }

  //Comprobar si hay colores. Si los hay, cargarlos.
  if(c.size() != 0 && vbo_colores == 0) {
    vbo_colores = crearVBO(GL_ARRAY_BUFFER, c.size()*3*sizeof(float), c.data());
  }

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_triangulos);  //Cambiamos el buffer

  if ((visualizado & SOLIDO) == SOLIDO && (visualizado & AJEDREZ) != AJEDREZ) { //Mostramos en sólido
    glShadeModel(GL_SMOOTH);
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT, GL_FILL);
    if (c.size() != 0) {
      glEnableClientState(GL_COLOR_ARRAY);
      glBindBuffer(GL_ARRAY_BUFFER, vbo_colores);
      glColorPointer(3, GL_FLOAT, 0, 0);
    } else {
      glDisableClientState(GL_COLOR_ARRAY);
      glColor3f(0,0,1);
    }
    glDrawElements(GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  if ((visualizado & LINEAS) == LINEAS) { //Mostramos como líneas
    glDisableClientState(GL_COLOR_ARRAY);
    glDisable(GL_CULL_FACE);
    glShadeModel(GL_FLAT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(1,0,0);
    glDrawElements(GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, 0);
  }

  if ((visualizado & PUNTOS) == PUNTOS) { //Mostramos como puntos
    glDisableClientState(GL_COLOR_ARRAY);
    glDisable(GL_CULL_FACE);
    glShadeModel(GL_FLAT);
    glPointSize(6); //Indicamos el tamaño de los puntos
    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    glColor3f(0,1,0);
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

