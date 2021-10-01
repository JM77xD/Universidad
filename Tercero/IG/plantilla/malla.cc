#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

// Visualización en modo inmediato con 'glDrawElements'

void Malla3D::draw_ModoInmediato(visualizacion visualizado)
{
  GLenum tipo;

  switch(visualizado) {
    case SOLIDO:
      tipo = GL_TRIANGLES;
      break;
    case AJEDREZ:
      tipo = GL_TRIANGLES;
      break;
    case PUNTOS:
      tipo = GL_POINTS;
      glPointSize(5);
      break;
    case LINEAS:
      tipo = GL_LINES;
      break;
    default:
      tipo = GL_TRIANGLES;
      break;
   }

  if (visualizado == AJEDREZ) {

    glDisableClientState(GL_COLOR_ARRAY);

    std::vector<Tupla3i> nuevosTriangulos;
    int mitad;

    for (int i = 0; i < f.size(); i+=2)
      nuevosTriangulos.push_back(f[i]);

    mitad = nuevosTriangulos.size();

    for (int i = 1; i < f.size(); i+=2)
      nuevosTriangulos.push_back(f[i]);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, v.data() );

    glShadeModel(GL_FLAT);
    
    glColor3f(0.5,1,0); //Primera mitad en verde
    glDrawElements(tipo, mitad*3, GL_UNSIGNED_INT, nuevosTriangulos.data());

    glColor3f(1,0,0.25); //Segunda mitad en rojo
    glDrawElements(tipo, (nuevosTriangulos.size()-mitad)*3, GL_UNSIGNED_INT, nuevosTriangulos.data()[mitad]);

  } else {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, v.data() );
    if (c.size() != 0) {
      glEnableClientState(GL_COLOR_ARRAY);
      glColorPointer(3, GL_FLOAT, 0, c.data() );
    }
    glShadeModel(GL_SMOOTH);
    glDrawElements( tipo, 3*f.size(), GL_UNSIGNED_INT, f.data());
  }
  glDisableClientState( GL_VERTEX_ARRAY );

}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Malla3D::draw_ModoDiferido(visualizacion visualizado)
{
   // (la primera vez, se deben crear los VBOs y guardar sus identificadores en el objeto)
   // completar (práctica 1)
   // .....
}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw(modoDibujado modo, visualizacion visualizado)
{
   if (modo == DIFERIDO)
      draw_ModoDiferido(visualizado);
   else
      draw_ModoInmediato(visualizado);
}

