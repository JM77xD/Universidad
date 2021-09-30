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
      break;
    case LINEAS:
      tipo = GL_LINE_STRIP;
      break;
    default:
      tipo = GL_TRIANGLES;
      break;
   }

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, v.data() );
  glEnableClientState(GL_COLOR_ARRAY);
  glColorPointer(3, GL_FLOAT, 0, c.data() );
  if (visualizado == AJEDREZ) {
    glColorPointer(3, GL_FLOAT, 0, cAje.data());
    glShadeModel(GL_FLAT);
  } else {
    glShadeModel(GL_SMOOTH);
  }
  glDrawElements( tipo, 3*f.size(), GL_UNSIGNED_INT, f.data());
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

