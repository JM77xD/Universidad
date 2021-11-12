

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
   Front_plane       = 50.0;
   Back_plane        = 5000.0;
   Observer_distance = 4*Front_plane;
   Observer_angle_x  = 0.0 ;
   Observer_angle_y  = 0.0 ;

   ejes.changeAxisSize( 5000 );

   for (int i = 0; i < 8; i++)
      luz[i] = false;

   // crear los objetos de la escena....
   difuso = new Material(Tupla3f(1.0,1.0,1.0), Tupla3f(0,0,0), Tupla3f(0,0,0), 0.75);

   especular = new Material(Tupla3f(0.2,0.2,0.2), Tupla3f(1.0,1.0,1.0), Tupla3f(0,0,0), 0.75);

   cubo = new Cubo(50);
   
   tetraedro = new Tetraedro(50);

   cilindro = new Cilindro(100,100,50,30);

   cono = new Cono(100,100,50,30);

   esfera = new Esfera(100,100,30);

   revolt = new ObjRevolucion("plys/peon.ply",100);
   revolt->setColor(Tupla3f(1.0,1.0,1.0));
   revolt->setMaterial(*difuso);

   revolt2 = new ObjRevolucion("plys/peon.ply",100);
   revolt2->setColor(Tupla3f(0,0,0));
   revolt2->setMaterial(*especular);

   plyObj = new ObjPLY("plys/ant.ply");

   luzDir = new LuzDireccional(Tupla2f(120,30), GL_LIGHT0, Tupla4f(1.0, 1.0, 1.0, 1.0), Tupla4f(1.0, 1.0, 1.0, 1.0), Tupla4f(1.0, 1.0, 1.0, 1.0));

   luzPos = new LuzPosicional(Tupla3f(200.0, 0.0, 50.0), GL_LIGHT1, Tupla4f(1.0, 1.0, 1.0, 1.0), Tupla4f(1.0, 1.0, 1.0, 1.0), Tupla4f(1.0, 1.0, 1.0, 1.0));
   

}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer

   glEnable(GL_NORMALIZE);

	Width  = UI_window_width/10;
	Height = UI_window_height/10;

   change_projection( float(UI_window_width)/float(UI_window_height) );
	glViewport( 0, 0, UI_window_width, UI_window_height );
}



// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();
   glDisable(GL_LIGHTING);
   ejes.draw();

   if(luces)
      glEnable(GL_LIGHTING);

    
   if ((objeto & CUBO) == CUBO && cubo != nullptr) {
      glPushMatrix();
      glTranslatef(-175.0,0.0,0.0);
      cubo->draw(modo, visualizado);
      glPopMatrix();
   }

   if ((objeto & TETRAEDRO) == TETRAEDRO && tetraedro != nullptr) {
      glPushMatrix();
      glTranslatef(-105.0,0.0,0.0);
      tetraedro->draw(modo, visualizado);
      glPopMatrix();
   }

   if ((objeto & CILINDRO) == CILINDRO && cilindro != nullptr) {
      glPushMatrix();
      glTranslatef(-35.0,0.0,0.0);
      cilindro->draw(modo, visualizado, tapa_sup, tapa_inf);
      glPopMatrix();
   }

   if ((objeto & CONO) == CONO && cono != nullptr) {
      glPushMatrix();
      glTranslatef(35.0,0.0,0.0);
      cono->draw(modo, visualizado, tapa_sup, tapa_inf);
      glPopMatrix();
   }

   if ((objeto & ESFERA) == ESFERA && esfera != nullptr) {
      glPushMatrix();
      glTranslatef(105.0,0.0,0.0);
      esfera->draw(modo, visualizado, tapa_sup, tapa_inf);
      glPopMatrix();
   }

   if ((objeto & REVOLT) == REVOLT && revolt != nullptr) {
      //revolt
      glPushMatrix();
      glTranslatef(175.0,0.0,0.0);
      glScalef(35.0,35.0,35.0);
      revolt->draw(modo, visualizado, tapa_sup, tapa_inf);
      glPopMatrix();
      
      //revolt2
      glPushMatrix();
      glTranslatef(245.0,0.0,0.0);
      glScalef(35.0,35.0,35.0);
      revolt2->draw(modo, visualizado, tapa_sup, tapa_inf);
      glPopMatrix();
   }

   if ((objeto & PLY) == PLY && plyObj != nullptr) {
      glPushMatrix();
      glTranslatef(0.0,0.0,100.0);
      plyObj->draw(modo, visualizado);
      glPopMatrix();
   }

   if (luces) {
      if (luz[0])
         luzDir->activar();
      else 
         luzDir->desactivar();
      if(luz[1])
         luzPos->activar();
      else
         luzPos->desactivar();
   } else {
      luzDir->desactivar();
      luzPos->desactivar();
   }
   
    
}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
   using namespace std ;
   cout << "Tecla pulsada: '" << tecla << "'" << endl;
   bool salir=false;
   switch( toupper(tecla) )
   {
      case 'Q' :
         if (modoMenu!=NADA) {
            modoMenu=NADA;
            cout << "Saliendo del menú, pulse:\nO para modo selección de objeto\nV para modo selección de visualización\nD para modo selección de dibujado\nT para modo selección de tapas en objetos de revolución\nA o B para seleccionar ángulo alpha y beta\n< y > para decrementar o incrementar el ángulo seleccionado\n0 a 7 para alternar las diferentes luces\nQ para salir del programa\n";          
         } else {
            salir=true ;
         }
         break ;

      case 'O' :
         if (modoMenu == NADA) {
            // ESTAMOS EN MODO SELECCION DE OBJETO
            cout << "Entrando en modo selección de objeto, pulse:\nC para alternar cubo\nT para alternar tetraedro\nS para alternar cilindro\nK para alternar Cono\nE para alternar esfera\nR para alternar objeto de revolución\nP para alternar objeto PLY\nQ para salir del menu\n";
            modoMenu=SELOBJETO;
         } else
            cout << "Opción no válida\n";
         break ;

        case 'V' :
         if (modoMenu == NADA) {
            // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
            cout << "Entrando en modo selección de visualización, pulse:\nP para alternar puntos\nL para alternar líneas\nS para alternar sólido\nA para alternar ajedrez\nI para alternar iluminación plana\nR para alternar iluminacion suavizada\nQ para salir del menu\n";
            modoMenu=SELVISUALIZACION;
         } else
            cout << "Opción no válida\n";
         break ;

       case 'T' :
         if (modoMenu == NADA) {
            // ESTAMOS EN MODO SELECCION DE TAPAS
            cout << "Entrando en modo selección de tapas de objetos de revolución, pulse:\n1 para alternar tapa superior\n2 para alternar tapa inferior\nQ para salir del menu\n";
            modoMenu=SELTAPAS;
         } else if (modoMenu == SELOBJETO) {
            cout << "Alternando tetraedro\n";
            objeto ^= TETRAEDRO;
         } else
            cout << "Opción no válida\n";
         break ;

         case 'D' :
         if (modoMenu == NADA) {
            // ESTAMOS EN MODO SELECCION DE DIBUJADO
            cout << "Entrando en modo selección de dibujado, pulse:\n1 para activar dibujado con glDraw\n2 para activar dibujado con VBO\nQ para salir del menu\n";
            modoMenu=SELDIBUJADO;
         } else
            cout << "Opción no válida\n";
         break ;

         // COMPLETAR con los diferentes opciones de teclado     
      case 'C':
         if (modoMenu == SELOBJETO) {
            cout << "Alternando cubo\n";
            objeto ^= CUBO;
         } else
            cout << "Opción no válida\n";
         break;

      case 'K':
         if (modoMenu == SELOBJETO) {
            cout << "Alternando cono\n";
            objeto ^= CONO;
         } else
            cout << "Opción no válida\n";
         break;

      case 'E':
         if (modoMenu == SELOBJETO) {
            cout << "Alternando esfera\n";
            objeto ^= ESFERA;
         } else
            cout << "Opción no válida\n";
         break;

      case 'R':
         if (modoMenu == SELVISUALIZACION) {
            cout << "Alternando luz suavizada\n";
            if (luces && (visualizado & SUAVE) != SUAVE) {
               visualizado ^= SUAVE;
               visualizado ^= PLANO;
            } else if (!luces) 
               visualizado ^= SUAVE;

            glShadeModel(GL_SMOOTH);
            if (!luces) {
               luces = true;
            }
         } else if (modoMenu == SELOBJETO) {
            cout << "Alternando revolución\n";
            objeto ^= REVOLT;
         } else
            cout << "Opción no válida\n";
         break;

      case 'P':
         if (modoMenu == SELVISUALIZACION) {
            cout << "Alternando puntos\n";
            if (luces) {
               luces = false;
               glDisable(GL_LIGHTING);
               visualizado = PUNTOS;
            } else
               visualizado ^= PUNTOS;
         } else if (modoMenu == SELOBJETO) {
            cout << "Alternando PLY\n";
            objeto ^= PLY;
         } else
            cout << "Opción no válida\n";
         break;
      
      case 'L':
         if (modoMenu == SELVISUALIZACION) {
            cout << "Alternando lineas\n";
            if (luces) {
               luces = false;
               glDisable(GL_LIGHTING);
               visualizado = LINEAS;
            } else
               visualizado ^= LINEAS;
         } else
            cout << "Opción no válida\n";
         break;

      case 'I':
         if (modoMenu == SELVISUALIZACION) {
            cout << "Alternando luz plana\n";
            if (luces && (visualizado & PLANO) != PLANO) {
               visualizado ^= PLANO;
               visualizado ^= SUAVE;
            } else if (!luces) 
               visualizado ^= PLANO;

            glShadeModel(GL_FLAT);
            if (!luces) {
               luces = true;
            }
         } else
            cout << "Opción no válida\n";
         break;

      case 'S':
         if (modoMenu == SELVISUALIZACION) {
            cout << "Alternando solido\n";
            if (luces) {
               luces = false;
               glDisable(GL_LIGHTING);
               visualizado = SOLIDO;
            } else
               visualizado ^= SOLIDO;
         } else if (modoMenu == SELOBJETO) {
            cout << "Alternando cilindro\n";
            objeto ^= CILINDRO;
         } else
            cout << "Opción no válida\n";
         break;

      case 'A':
         if (modoMenu == SELVISUALIZACION) {
            cout << "Alternando ajedrez\n";
            if (luces) {
               luces = false;
               glDisable(GL_LIGHTING);
               visualizado = AJEDREZ;
            } else
               visualizado ^= AJEDREZ;
         } else if (modoMenu == NADA && luces && luz[0]) {
            cout << "Seleccionando el ángulo alfa\n";
            beta = false;
            alpha = true;
         } else
            cout << "Opción no válida\n";
         break;
      
      case 'B':
         if (modoMenu == NADA && luces && luz[0]) {
            cout << "Seleccionando el ángulo beta\n";
            beta = true;
            alpha = false;
         } else
            cout << "Opción no válida\n";
         break;

      case '<':
         if (modoMenu == NADA && luces && luz[0] && (alpha || beta)) {
            if (alpha) {
               luzDir->variarAnguloAlpha(-1.0);
               cout << "Decrementando el ángulo alpha\n";
            }
            else if (beta) {
               luzDir->variarAnguloBeta(-1.0);
               cout << "Decrementando el ángulo beta\n";
            }
         } else
            cout << "Opción no válida\n";
         break;

      case '>':
         if (modoMenu == NADA && luces && luz[0] && (alpha || beta)) {
            if (alpha) {
               luzDir->variarAnguloAlpha(1.0);
               cout << "Incrementando el ángulo alpha\n";
            }
            else if (beta) {
               luzDir->variarAnguloBeta(1.0);
               cout << "Incrementando el ángulo beta\n";
            }
         } else
            cout << "Opción no válida\n";
         break;

      case '0':
         if (modoMenu == NADA) {
            cout << "Alternando luz 0\n";
            luz[0] = !luz[0];
         } else
            cout << "Opción no válida\n";
         break;

      case '1':
         if (modoMenu == NADA) {
            cout << "Alternando luz 1\n";
            luz[1] = !luz[1];
         } else if (modoMenu == SELDIBUJADO) {
            cout << "Mostrando con glDraw\n";
            modo = INMEDIATO;
         } else if (modoMenu == SELTAPAS) {
            cout << "Alternando tapa superior\n";
            tapa_sup = !tapa_sup;
         } else
            cout << "Opción no válida\n";
         break;
      
      case '2':
         if (modoMenu == NADA) {
            cout << "Alternando luz 2\n";
            luz[2] = !luz[2];
         } else if (modoMenu == SELDIBUJADO) {
            cout << "Mostrando con VBO\n";
            modo = DIFERIDO;
         } else if (modoMenu == SELTAPAS) {
            cout << "Alternando tapa inferior\n";
            tapa_inf = !tapa_inf;
         } else
            cout << "Opción no válida\n";
         break;
      
      case '3':
         if (modoMenu == NADA) {
            cout << "Alternando luz 3\n";
            luz[3] = !luz[3];
         } else
            cout << "Opción no válida\n";
         break;
      
      case '4':
         if (modoMenu == NADA) {
            cout << "Alternando luz 4\n";
            luz[4] = !luz[4];
         } else
            cout << "Opción no válida\n";
         break;
      
      case '5':
         if (modoMenu == NADA) {
            cout << "Alternando luz 5\n";
            luz[5] = !luz[5];
         } else
            cout << "Opción no válida\n";
         break;

      case '6':
         if (modoMenu == NADA) {
            cout << "Alternando luz 6\n";
            luz[6] = !luz[6];
         } else
            cout << "Opción no válida\n";
         break;

      case '7':
         if (modoMenu == NADA) {
            cout << "Alternando luz 7\n";
            luz[7] = !luz[7];
         } else
            cout << "Opción no válida\n";
         break;
            
   }
   return salir;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         Observer_angle_y-- ;
         break;
	   case GLUT_KEY_RIGHT:
         Observer_angle_y++ ;
         break;
	   case GLUT_KEY_UP:
         Observer_angle_x-- ;
         break;
	   case GLUT_KEY_DOWN:
         Observer_angle_x++ ;
         break;
	   case GLUT_KEY_PAGE_UP:
         Observer_distance *=1.2 ;
         break;
	   case GLUT_KEY_PAGE_DOWN:
         Observer_distance /= 1.2 ;
         break;
	}

	//std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection( const float ratio_xy )
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   const float wx = float(Height)*ratio_xy ;
   glFrustum( -wx, wx, -Height, Height, Front_plane, Back_plane );
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth/10;
   Height = newHeight/10;
   change_projection( float(newHeight)/float(newWidth) );
   glViewport( 0, 0, newWidth, newHeight );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef( 0.0, 0.0, -Observer_distance );
   glRotatef( Observer_angle_y, 0.0 ,1.0, 0.0 );
   glRotatef( Observer_angle_x, 1.0, 0.0, 0.0 );
}
