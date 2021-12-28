

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
   Front_plane       = 50.0;
   Back_plane        = 2000.0;
   Observer_distance = 4*Front_plane;
   Observer_angle_x  = 0.0 ;
   Observer_angle_y  = 0.0 ;

   ejes.changeAxisSize( 5000 );

   for (int i = 0; i < 8; i++)
      luz[i] = false;

   for (int i = 0; i < 11; i++)
      animacion_manual[i] = false;

   for (int i = 0; i < 3; i++)
      pos[i] = 0.0;

   for (int i = 0; i < num_auto; i++)
      animacion_automatica[i] = true;

   alpha = false;
   beta = false;
   automatico = false;
   for (int i = 0; i < num_auto; i++)
      velocidad_auto[i] = 0.0;

   // crear los objetos de la escena....
   difuso = new Material(Tupla3f(0.8,0.2,0.2), Tupla3f(0,0,0), Tupla3f(0,0,0), 0.75);

   especular = new Material(Tupla3f(0.0,0.0,0.0), Tupla3f(0.1, 0.9, 0.1), Tupla3f(0,0,0), 0.75);

   ambiente = new Material(Tupla3f(0.2,0.2,0.2), Tupla3f(0.2,0.2,0.2), Tupla3f(0.4,0.6,0.6), 0.75);

   cubo = new Cubo(50);
   
   tetraedro = new Tetraedro(50);

   cilindro = new Cilindro(100,100,50,30);

   cono = new Cono(100,100,50,30, false);

   esfera = new Esfera(100,100,30);

   revolt = new ObjRevolucion("plys/peon.ply",100, false);
   revolt->setColor(Tupla3f(1.0,1.0,1.0));
   revolt->setMaterial(*difuso);

   revolt2 = new ObjRevolucion("plys/peon.ply",100, false);
   revolt2->setColor(Tupla3f(0,0,0));
   revolt2->setMaterial(*especular);

   plyObj = new ObjPLY("plys/ant.ply");

   person = new Person();

   cubo->setMaterial(*ambiente);
   tetraedro->setMaterial(*ambiente);
   cilindro->setMaterial(*ambiente);
   cono->setMaterial(*ambiente);
   esfera->setMaterial(*ambiente);
   person->setMaterial(*ambiente);
   

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

   luzDir = new LuzDireccional(Tupla2f(120,30), GL_LIGHT0, Tupla4f(1.0, 1.0, 1.0, 1.0), Tupla4f(1.0, 1.0, 1.0, 1.0), Tupla4f(1.0, 1.0, 1.0, 1.0));

   luzPos = new LuzPosicional(Tupla3f(0.0, 0.0, 100.0), GL_LIGHT1, Tupla4f(0.25, 0.7, 0.3, 1.0), Tupla4f(0.25, 0.7, 0.3, 1.0), Tupla4f(0.25, 0.7, 0.3, 1.0));

   textura_cubo = new Textura("texturas/text-madera.jpg");

   cubo->setTextura(textura_cubo);

   textura_cilindro = new Textura("texturas/text-lata-1.jpg");

   cilindro->setTextura(textura_cilindro);

   textura_tierra = new Textura("texturas/tierra.jpg");

   esfera->setTextura(textura_tierra);

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
   ejes.draw();

   if (luces) {
      glEnable(GL_LIGHTING);
      if (luz[0])
         luzDir->activar();
      else 
         luzDir->desactivar();
      if(luz[1])
         luzPos->activar();
      else
         luzPos->desactivar();
   } else {
      glDisable(GL_LIGHTING);
      luzDir->desactivar();
      luzPos->desactivar();
   }
      
      glPushMatrix();
      glTranslatef(-195.0,0.0,0.0);
      if (texturas and cubo->tieneTextura())
         glEnable(GL_TEXTURE_2D);
      cubo->draw(modo, visualizado);
      glDisable(GL_TEXTURE_2D);
      glPopMatrix();

      glPushMatrix();
      glTranslatef(-125.0,0.0,0.0);
      if (texturas and tetraedro->tieneTextura())
         glEnable(GL_TEXTURE_2D);
      tetraedro->draw(modo, visualizado);
      glDisable(GL_TEXTURE_2D);
      glPopMatrix();

      glPushMatrix();
      glTranslatef(-55.0,0.0,0.0);
      if (texturas and cilindro->tieneTextura())
         glEnable(GL_TEXTURE_2D);
      cilindro->draw(modo, visualizado, tapa_sup, tapa_inf);
      glDisable(GL_TEXTURE_2D);
      glPopMatrix();

      glPushMatrix();
      glTranslatef(55.0,0.0,0.0);
      if (texturas and cono->tieneTextura())
         glEnable(GL_TEXTURE_2D);
      cono->draw(modo, visualizado, tapa_sup, tapa_inf);
      glDisable(GL_TEXTURE_2D);
      glPopMatrix();

      glPushMatrix();
      glTranslatef(125.0,0.0,0.0);
      if (texturas and esfera->tieneTextura())
         glEnable(GL_TEXTURE_2D);
      esfera->draw(modo, visualizado, tapa_sup, tapa_inf);
      glDisable(GL_TEXTURE_2D);
      glPopMatrix();

      //revolt
      glPushMatrix();
      glTranslatef(195.0,0.0,0.0);
      glScalef(35.0,35.0,35.0);
      if (texturas and revolt->tieneTextura())
         glEnable(GL_TEXTURE_2D);
      revolt->draw(modo, visualizado, tapa_sup, tapa_inf);
      glDisable(GL_TEXTURE_2D);
      glPopMatrix();
      
      //revolt2
      glPushMatrix();
      glTranslatef(265.0,0.0,0.0);
      glScalef(35.0,35.0,35.0);
      if (texturas and revolt2->tieneTextura())
         glEnable(GL_TEXTURE_2D);
      revolt2->draw(modo, visualizado, tapa_sup, tapa_inf);
      glDisable(GL_TEXTURE_2D);
      glPopMatrix();

      /*
      glPushMatrix();
      glTranslatef(0.0,0.0,-100.0);
      if (texturas and plyObj->tieneTextura())
         glEnable(GL_TEXTURE_2D);
      plyObj->draw(modo, visualizado);
      glDisable(GL_TEXTURE_2D);
      glPopMatrix();
      */

      glPushMatrix();
      glTranslatef(pos[0],0.0,pos[2]);
      glRotatef(pos[1], 0.0, 1.0, 0.0);
      glScalef(7.0,7.0,7.0);
      if (texturas and person->tieneTextura())
         glEnable(GL_TEXTURE_2D);
      person->draw(modo, visualizado);
      glDisable(GL_TEXTURE_2D);
      glPopMatrix();
   
    
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
            if (modoMenu == ANIMACION_AUTO) {
               for (int i = 0; i < num_auto; i++)
                  animacion_automatica[i] = false;
               for (int i = 0; i < num_auto; i++)
                  velocidad_auto[i] = 0.0;
               person->reset();
            }
            if (modoMenu == ANIMACION_MANUAL) {
               for (int i = 0; i < 11; i++)
                  animacion_manual[i] = false;

               person->reset();
               
               for (int i = 0; i < 3; i++)
                  pos[i] = 0.0;
            }
            modoMenu=NADA;
            cout << "Saliendo del menú, pulse:\nV para modo selección de visualización\nD para modo selección de dibujado\nU para modo de animación automática\nM para modo de animación manual\nT para alternar texturas de los objetos\nA o B para seleccionar ángulo alpha y beta\n< y > para decrementar o incrementar el ángulo seleccionado\n0 a 7 para alternar las diferentes luces\nQ para salir del programa\n";          
         } else {
            salir=true ;
         }
         break ;

      case 'V' :
         if (modoMenu == NADA) {
            // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
            cout << "Entrando en modo selección de visualización, pulse:\nP para alternar puntos\nL para alternar líneas\nS para alternar sólido\nA para alternar ajedrez\nI para alternar iluminación\nQ para salir del menu\n";
            modoMenu=SELVISUALIZACION;
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

      case 'U' :
         if (modoMenu == NADA) {
            cout << "Entrando en modo animación automática, pulse:\n0 para seleccionar las piernas\n1 para seleccionar los brazos\n2 para seleccionar el torso\n3 para seleccionar los dedos\n4 para seleccionar la cabeza\n5 para seleccionar la luz puntual\n6 para seleccionar la translación del brazo\nQ para salir\n";
            modoMenu=ANIMACION_AUTO;
            automatico = true;
            for (int i = 0; i < 5; i++)
               velocidad_auto[i] = 0.02;
            velocidad_auto[5] = 0.002;
         } else
            cout << "Opción no válida\n";
         break ;

      case '+' :
         if (modoMenu == ANIMACION_AUTO) {
            if (velocidad_auto[0] < 4.5 && animacion_automatica[0]) {
               cout << "Aumentando velocidad de la animación\n";
               velocidad_auto[0] += 0.02;
            } else if (!animacion_automatica[0]) {
               cout << "Piernas no seleccionadas\n";
            } else
               cout << "Velocidad al máximo\n";
            
            if (velocidad_auto[1] < 4.5 && animacion_automatica[1]) {
               cout << "Aumentando velocidad de la animación\n";
               velocidad_auto[1] += 0.02;
            } else if (!animacion_automatica[1]) {
               cout << "brazos no seleccionados\n";
            } else
               cout << "Velocidad al máximo\n";
            
            if (velocidad_auto[2] < 4.5 && animacion_automatica[2]) {
               cout << "Aumentando velocidad de la animación\n";
               velocidad_auto[2] += 0.02;
            } else if (!animacion_automatica[2]) {
               cout << "Torso no seleccionado\n";
            } else
               cout << "Velocidad al máximo\n";
            
            if (velocidad_auto[3] < 4.5 && animacion_automatica[3]) {
               cout << "Aumentando velocidad de la animación\n";
               velocidad_auto[3] += 0.02;
            } else if (!animacion_automatica[3]) {
               cout << "Dedos no seleccionados\n";
            } else
               cout << "Velocidad al máximo\n";
            
            if (velocidad_auto[4] < 4.5 && animacion_automatica[4]) {
               cout << "Aumentando velocidad de la animación\n";
               velocidad_auto[4] += 0.02;
            } else if (!animacion_automatica[4]) {
               cout << "Cabeza no seleccionada\n";
            } else
               cout << "Velocidad al máximo\n";
            
            if (velocidad_auto[5] < 1.5 && animacion_automatica[5]) {
               cout << "Aumentando velocidad de la animación\n";
               velocidad_auto[5] += 0.002;
            } else if (!animacion_automatica[5]) {
               cout << "Luz puntual no seleccionada\n";
            } else
               cout << "Velocidad al máximo\n";
            
            if (velocidad_auto[6] < 1.5 && animacion_automatica[6]) {
               cout << "Aumentando velocidad de la animación\n";
               velocidad_auto[6] += 0.002;
            } else if (!animacion_automatica[6]) {
               cout << "Caída de dedos no seleccionada\n";
            } else
               cout << "Velocidad al máximo\n";

         } else if (modoMenu == ANIMACION_MANUAL) {
            cout << "Aumentando grados de libertad seleccionado\n";
            if (animacion_manual[0]) {
               person->modificarGiroDedoGDrch(0.2);
               person->modificarGiroDedoGIzq(0.2);
               person->modificarGiroDedosDrch(0.2);
               person->modificarGiroDedosIzq(0.2);
            }
            if (animacion_manual[1]) {
               person->modificarGiroPiernaDrch(0.2);
               person->modificarGiroPiernaIzq(0.2);
            }
            if (animacion_manual[2])
               person->modificarGiroBrazoDrch(0.2);
            if (animacion_manual[3])
               person->modificarGiroBrazoIzq(0.2);
            if (animacion_manual[4])
               person->modificarGiroLCabeza(0.2);
            if (animacion_manual[5])
               person->modificarGiroVCabeza(0.2);
            if (animacion_manual[6])
               pos[1] += 0.5;
            if (animacion_manual[7])
               pos[0] += 1;
            if (animacion_manual[8])
               pos[2] += 1;
            if (animacion_manual[9])
               person->modificarGiroTronco(0.2);
         } else
            cout << "Opción no válida\n";
         break ;

      case '-' :
         if (modoMenu == ANIMACION_AUTO) {
            if (velocidad_auto[0] > -4.5 && animacion_automatica[0]) {
               cout << "Disminuyendo velocidad de la animación\n";
               velocidad_auto[0] -= 0.02;
            } else if (!animacion_automatica[0]) {
               cout << "Piernas no seleccionadas\n";
            } else
               cout << "Velocidad al mínimo\n";
            
            if (velocidad_auto[1] > -4.5 && animacion_automatica[1]) {
               cout << "Disminuyendo velocidad de la animación\n";
               velocidad_auto[1] -= 0.02;
            } else if (!animacion_automatica[1]) {
               cout << "brazos no seleccionados\n";
            } else
               cout << "Velocidad al mínimo\n";
            
            if (velocidad_auto[2] > -4.5 && animacion_automatica[2]) {
               cout << "Disminuyendo velocidad de la animación\n";
               velocidad_auto[2] -= 0.02;
            } else if (!animacion_automatica[2]) {
               cout << "Torso no seleccionado\n";
            } else
               cout << "Velocidad al mínimo\n";
            
            if (velocidad_auto[3] > -4.5 && animacion_automatica[3]) {
               cout << "Disminuyendo velocidad de la animación\n";
               velocidad_auto[3] -= 0.02;
            } else if (!animacion_automatica[3]) {
               cout << "Dedos no seleccionados\n";
            } else
               cout << "Velocidad al mínimo\n";
            
            if (velocidad_auto[4] > -4.5 && animacion_automatica[4]) {
               cout << "Disminuyendo velocidad de la animación\n";
               velocidad_auto[4] -= 0.02;
            } else if (!animacion_automatica[4]) {
               cout << "Cabeza no seleccionada\n";
            } else
               cout << "Velocidad al mínimo\n";

            if (velocidad_auto[5] > -1.5 && animacion_automatica[5]) {
               cout << "Disminuyendo velocidad de la animación\n";
               velocidad_auto[5] -= 0.002;
            } else if (!animacion_automatica[5]) {
               cout << "Luz puntual no seleccionada\n";
            } else
               cout << "Velocidad al mínimo\n";

            if (velocidad_auto[6] > -1.5 && animacion_automatica[6]) {
               cout << "Disminuyendo velocidad de la animación\n";
               velocidad_auto[6] -= 0.002;
            } else if (!animacion_automatica[6]) {
               cout << "Caída de dedos no seleccionada\n";
            } else
               cout << "Velocidad al mínimo\n";

         } else if (modoMenu == ANIMACION_MANUAL) {
            cout << "Disminuyendo grados de libertad seleccionado\n";
            if (animacion_manual[0]) {
               person->modificarGiroDedoGDrch(-0.2);
               person->modificarGiroDedoGIzq(-0.2);
               person->modificarGiroDedosDrch(-0.2);
               person->modificarGiroDedosIzq(-0.2);
            }
            if (animacion_manual[1]) {
               person->modificarGiroPiernaDrch(-0.2);
               person->modificarGiroPiernaIzq(-0.2);
            }
            if (animacion_manual[2])
               person->modificarGiroBrazoDrch(-0.2);
            if (animacion_manual[3])
               person->modificarGiroBrazoIzq(-0.2);
            if (animacion_manual[4])
               person->modificarGiroLCabeza(-0.2);
            if (animacion_manual[5])
               person->modificarGiroVCabeza(-0.2);
            if (animacion_manual[6])
               pos[1] -= 0.5;
            if (animacion_manual[7])
               pos[0] -= 1;
            if (animacion_manual[8])
               pos[2] -= 1;
            if (animacion_manual[9])
               person->modificarGiroTronco(-0.2);
         } else
            cout << "Opción no válida\n";
         break ;

      case 'M' :
         if (modoMenu == NADA) {
            cout << "Entrando en modo selección de animación manual, pulse:\n0 para seleccionar los dedos\n1 para seleccionar las piernas\n2 para seleccionar el brazo derecho\n3 para seleccionar el brazo izquiero\n4 para mover el cuello lateralmente\n5 para mover el cuello verticalmente\n6 para rotar lateralmente al personaje\n7 para desplazar al personaje en el eje x\n8 para desplazar al personaje en el eje z\nQ para salir\n";
            modoMenu=ANIMACION_MANUAL;
         } else
            cout << "Opción no válida\n";
         break ;  

      case 'I':
         if (modoMenu == SELVISUALIZACION) {
            cout << "Alternando luz suavizada\n";
            glShadeModel(GL_SMOOTH);
            if (!luces) {
               luces = true;
            }
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
         } else
            cout << "Opción no válida\n";
         break;
      
      case 'T':
         if (modoMenu == NADA) {
            cout << "Alternando texturas\n";
            texturas = !texturas;
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

      case 'S':
         if (modoMenu == SELVISUALIZACION) {
            cout << "Alternando solido\n";
            if (luces) {
               luces = false;
               glDisable(GL_LIGHTING);
               visualizado = SOLIDO;
            } else
               visualizado ^= SOLIDO;
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
               luzDir->variarAnguloAlpha(-0.1);
               cout << "Decrementando el ángulo alpha\n";
            }
            else if (beta) {
               luzDir->variarAnguloBeta(-0.1);
               cout << "Decrementando el ángulo beta\n";
            }
         } else
            cout << "Opción no válida\n";
         break;

      case '>':
         if (modoMenu == NADA && luces && luz[0] && (alpha || beta)) {
            if (alpha) {
               luzDir->variarAnguloAlpha(0.1);
               cout << "Incrementando el ángulo alpha\n";
            }
            else if (beta) {
               luzDir->variarAnguloBeta(0.1);
               cout << "Incrementando el ángulo beta\n";
            }
         } else
            cout << "Opción no válida\n";
         break;

      case '0':
         if (modoMenu == NADA) {
            cout << "Alternando luz 0\n";
            luz[0] = !luz[0];
         } else if (modoMenu == ANIMACION_MANUAL) {
            cout << "Alternando dedos\n";
            animacion_manual[0] = !animacion_manual[0];
         } else if (modoMenu == ANIMACION_AUTO) {
            animacion_automatica[0] = !animacion_automatica[0];
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
         } else if (modoMenu == ANIMACION_MANUAL) {
            cout << "Alternando piernas\n";
            animacion_manual[1] = !animacion_manual[1];
         } else if (modoMenu == ANIMACION_AUTO) {
            animacion_automatica[1] = !animacion_automatica[1];
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
         } else if (modoMenu == ANIMACION_MANUAL) {
            cout << "Alternando brazo derecho\n";
            animacion_manual[2] = !animacion_manual[2];
         } else if (modoMenu == ANIMACION_AUTO) {
            animacion_automatica[2] = !animacion_automatica[2];
         } else
            cout << "Opción no válida\n";
         break;
      
      case '3':
         if (modoMenu == NADA) {
            cout << "Alternando luz 3\n";
            luz[3] = !luz[3];
         } else if (modoMenu == ANIMACION_MANUAL) {
            cout << "Alternando brazo izquierdo\n";
            animacion_manual[3] = !animacion_manual[3];
         } else if (modoMenu == ANIMACION_AUTO) {
            animacion_automatica[3] = !animacion_automatica[3];
         } else
            cout << "Opción no válida\n";
         break;
      
      case '4':
         if (modoMenu == NADA) {
            cout << "Alternando luz 4\n";
            luz[4] = !luz[4];
         } else if (modoMenu == ANIMACION_MANUAL) {
            cout << "Alternando cabeza lateral\n";
            animacion_manual[4] = !animacion_manual[4];
         } else if (modoMenu == ANIMACION_AUTO) {
            animacion_automatica[4] = !animacion_automatica[4];
         } else
            cout << "Opción no válida\n";
         break;
      
      case '5':
         if (modoMenu == NADA) {
            cout << "Alternando luz 5\n";
            luz[5] = !luz[5];
         } else if (modoMenu == ANIMACION_MANUAL) {
            cout << "Alternando cabeza vertical\n";
            animacion_manual[5] = !animacion_manual[5];
         } else if (modoMenu == ANIMACION_AUTO) {
            animacion_automatica[5] = !animacion_automatica[5];
         } else
            cout << "Opción no válida\n";
         break;

      case '6':
         if (modoMenu == NADA) {
            cout << "Alternando luz 6\n";
            luz[6] = !luz[6];
         } else if (modoMenu == ANIMACION_MANUAL) {
            cout << "Alternando rotación del personaje\n";
            animacion_manual[6] = !animacion_manual[6];
         } else if (modoMenu == ANIMACION_AUTO) {
            animacion_automatica[6] = !animacion_automatica[6];
         } else
            cout << "Opción no válida\n";
         break;

      case '7':
         if (modoMenu == NADA) {
            cout << "Alternando luz 7\n";
            luz[7] = !luz[7];
         } else if (modoMenu == ANIMACION_MANUAL) {
            cout << "Alternando desplazamiento en el eje x\n";
            animacion_manual[7] = !animacion_manual[7];
         } else
            cout << "Opción no válida\n";
         break;
      
      case '8':
         if (modoMenu == ANIMACION_MANUAL) {
            cout << "Alternando desplazamiento en el eje z\n";
            animacion_manual[8] = !animacion_manual[8];
         } else
            cout << "Opción no válida\n";
         break;
      
      case '9':
         if (modoMenu == ANIMACION_MANUAL) {
            cout << "Alternando rotación del tronco\n";
            animacion_manual[9] = !animacion_manual[9];
         } else
            cout << "Opción no válida\n";
         break;
            
   }
   return salir;
}

void Escena::animarModeloJerarquico() {
   if (person != nullptr && automatico) {
      person->modificarGiroLCabeza(velocidad_auto[4], automatico);
      person->modificarGiroVCabeza(velocidad_auto[4], automatico);
      person->modificarGiroBrazoDrch(velocidad_auto[1], automatico);
      person->modificarGiroBrazoIzq(-velocidad_auto[1], automatico);
      person->modificarGiroPiernaDrch(-velocidad_auto[0], automatico);
      person->modificarGiroPiernaIzq(velocidad_auto[0], automatico);
      person->modificarGiroDedosDrch(velocidad_auto[3], automatico);
      person->modificarGiroDedosIzq(velocidad_auto[3], automatico);
      person->modificarGiroDedoGDrch(velocidad_auto[3], automatico);
      person->modificarGiroDedoGIzq(velocidad_auto[3], automatico);
      person->modificarGiroTronco(velocidad_auto[2], automatico);
      person->modificarPosBrazoDrch(velocidad_auto[6], automatico);
      luzPos->rotar(velocidad_auto[5]);
   }
}

//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         Observer_angle_y-=0.2 ;
         break;
	   case GLUT_KEY_RIGHT:
         Observer_angle_y+=0.2 ;
         break;
	   case GLUT_KEY_UP:
         Observer_angle_x-=0.2 ;
         break;
	   case GLUT_KEY_DOWN:
         Observer_angle_x+=0.2 ;
         break;
	   case GLUT_KEY_PAGE_UP:
         Observer_distance *=1.1 ;
         break;
	   case GLUT_KEY_PAGE_DOWN:
         Observer_distance /= 1.1 ;
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
   float wx = Width, wy = Height;
   if (ratio_xy < 1.0)
      wx = float(Height)/ratio_xy ;
   else if (ratio_xy > 1.0)
      wy = float(Width)*ratio_xy ;
   glFrustum( -wx, wx, -wy, wy, Front_plane, Back_plane );
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
