#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

// Visualización en modo inmediato con 'glDrawElements'

void Malla3D::draw_ModoInmediato(int visualizado)
{

  std::vector<Tupla3i> nuevosTriangulos;

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, v.data() );

  glPointSize(6); //Indicamos el tamaño de los puntos

  switch(visualizado) {       //Alternamos por los distintos modos de visualización disponibles ( y combinaciones de sólido, líneas y puntos)
    case (SOLIDO | LINEAS | PUNTOS):

      //Pintamos sólido

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

      //Pintamos líneas

      glDisable(GL_CULL_FACE);            //Deshabilitamos CULL_FACE, ya que queremos ver las líneas y puntos por ambas caras
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  //Indicamos el modo a pintar

      glDisableClientState(GL_COLOR_ARRAY); //Deshabilitamos el color array (para asegurar por si estaba habilitado)
      glShadeModel(GL_FLAT);                //Evitamos degradados en el dibujado

      glColor3f(1,0,0); //Asignamos color a los vértices
      glDrawElements( GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, f.data());

      //Pintamos puntos

      glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); //Indicamos modo a pintar
      glColor3f(0,1,0);                           //Asignamos color a los vértices
      glDrawElements( GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, f.data());

      break;

    case (SOLIDO | LINEAS):

      //Pintamos sólido

      glEnable(GL_CULL_FACE);
      glPolygonMode(GL_FRONT, GL_FILL);

      if (c.size() != 0) {
        glEnableClientState(GL_COLOR_ARRAY);
        glColorPointer(3, GL_FLOAT, 0, c.data() );
      } else {
        glDisableClientState(GL_COLOR_ARRAY);
        glColor3f(0,0,1);
      }

      glShadeModel(GL_SMOOTH);
      glDrawElements( GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, f.data());

      //Pintamos líneas
      glDisable(GL_CULL_FACE);
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

      glDisableClientState(GL_COLOR_ARRAY);

      glColor3f(1,0,0);

      glShadeModel(GL_FLAT);
      glDrawElements( GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, f.data());

      break;
    
    case (SOLIDO | PUNTOS):

      //Pintamos sólido

      glEnable(GL_CULL_FACE);
      glPolygonMode(GL_FRONT, GL_FILL);

      if (c.size() != 0) {
        glEnableClientState(GL_COLOR_ARRAY);
        glColorPointer(3, GL_FLOAT, 0, c.data() );
      } else {
        glDisableClientState(GL_COLOR_ARRAY);
        glColor3f(0,0,1);
      }

      glShadeModel(GL_SMOOTH);
      glDrawElements( GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, f.data());

      // Pintamos puntos

      glDisable(GL_CULL_FACE);
      glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

      glDisableClientState(GL_COLOR_ARRAY);

      glColor3f(0,1,0);

      glShadeModel(GL_FLAT);
      glDrawElements( GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, f.data());

      break;

    case (LINEAS | PUNTOS):

      //Pintamos líneas
      
      glDisable(GL_CULL_FACE);
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

      glDisableClientState(GL_COLOR_ARRAY);
      glShadeModel(GL_FLAT);

      glColor3f(1,0,0);
      glDrawElements( GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, f.data());

      //Pintamos puntos

      glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
      glColor3f(0,1,0);
      glDrawElements( GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, f.data());

      break;
    
    case SOLIDO:
      glEnable(GL_CULL_FACE);
      glPolygonMode(GL_FRONT, GL_FILL);

      if (c.size() != 0) {
        glEnableClientState(GL_COLOR_ARRAY);
        glColorPointer(3, GL_FLOAT, 0, c.data() );
      } else {
        glDisableClientState(GL_COLOR_ARRAY);
        glColor3f(0,0,1);
      }

      glShadeModel(GL_SMOOTH);
      glDrawElements( GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, f.data());

      break;

    case AJEDREZ:
      glEnable(GL_CULL_FACE);
      glPolygonMode(GL_FRONT, GL_FILL);
      glDisableClientState(GL_COLOR_ARRAY);

      int mitad;
      //Separamos los triángulos en 2 mitades, primero todos los pares y luego los impares
      for (int i = 0; i < f.size(); i+=2)
        nuevosTriangulos.push_back(f[i]);

      mitad = nuevosTriangulos.size();

      for (int i = 1; i < f.size(); i+=2)
        nuevosTriangulos.push_back(f[i]);


      glShadeModel(GL_FLAT);  //Indicamos que no queremos degradado en las caras
                              //pintamos primero las caras pares y luego las impares, asignando colores distintos

      glColor3f(0.5,1,0); //Primera mitad en verde
      glDrawElements(GL_TRIANGLES, mitad*3, GL_UNSIGNED_INT, nuevosTriangulos.data());

      glColor3f(1,0,0.25); //Segunda mitad en rojo
      glDrawElements(GL_TRIANGLES, (nuevosTriangulos.size()-mitad)*3, GL_UNSIGNED_INT, nuevosTriangulos.data()[mitad]);

      break;

    case PUNTOS:
      glDisable(GL_CULL_FACE);
      glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

      glDisableClientState(GL_COLOR_ARRAY);

      glColor3f(0,1,0);

      glShadeModel(GL_FLAT);
      glDrawElements( GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, f.data());

      break;

    case LINEAS:
      glDisable(GL_CULL_FACE);
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

      glDisableClientState(GL_COLOR_ARRAY);

      glColor3f(1,0,0);

      glShadeModel(GL_FLAT);
      glDrawElements( GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, f.data());

      break;

    default:    //Si el modo de visualizado se sale de lo contemplado (cosa que no debería pasar), pintamos como sólido
      glEnable(GL_CULL_FACE);
      glPolygonMode(GL_FRONT, GL_FILL);
      
      if (c.size() != 0) {
        glEnableClientState(GL_COLOR_ARRAY);
        glColorPointer(3, GL_FLOAT, 0, c.data() );
      } else {
        glDisableClientState(GL_COLOR_ARRAY);
        glColor3f(0,0,1);
      }

      glShadeModel(GL_SMOOTH);
      glDrawElements( GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, f.data());
      break;
   }
  
  glDisableClientState( GL_VERTEX_ARRAY );

}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Malla3D::draw_ModoDiferido(int visualizado)
{
   // (la primera vez, se deben crear los VBOs y guardar sus identificadores en el objeto)
   // completar (práctica 1)
   // .....
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

