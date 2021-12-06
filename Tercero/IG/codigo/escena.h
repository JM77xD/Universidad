#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "cubo.h"
#include "tetraedro.h"
#include "cilindro.h"
#include "cono.h"
#include "esfera.h"
#include "objply.h"
#include "luzdireccional.h"
#include "luzposicional.h"
#include "material.h"
#include "person.h"

typedef enum {NADA, SELVISUALIZACION, SELDIBUJADO, ANIMACION_AUTO} menu;
class Escena
{

   private:

   

 // ** PARÁMETROS DE LA CÁMARA (PROVISIONAL)
       
       // variables que definen la posicion de la camara en coordenadas polares
   GLfloat Observer_distance;
   GLfloat Observer_angle_x;
   GLfloat Observer_angle_y;

   // variables que controlan la ventana y la transformacion de perspectiva
   GLfloat Width, Height, Front_plane, Back_plane;

    // Transformación de cámara
	void change_projection( const float ratio_xy );
	void change_observer();
    


   void clear_window();

   menu modoMenu=NADA;
   modoDibujado modo = DIFERIDO;
   int visualizado = SOLIDO;
   bool tapa_sup = true, tapa_inf = true, luces = false;
   // Objetos de la escena
   Ejes ejes;
   Cubo * cubo = nullptr ; // es importante inicializarlo a 'nullptr'
   Tetraedro * tetraedro = nullptr ; // es importante inicializarlo a 'nullptr'
   Cilindro * cilindro = nullptr;
   Cono * cono = nullptr; 
   Esfera * esfera = nullptr;
   ObjRevolucion * revolt = nullptr;
   ObjRevolucion * revolt2 = nullptr;
   ObjPLY * plyObj = nullptr;
   Person * person = nullptr;
   LuzDireccional * luzDir = nullptr;
   LuzPosicional * luzPos = nullptr;
   Material * difuso = nullptr;
   Material * especular = nullptr;
   Material * ambiente = nullptr;

   bool luz[8];
   bool alpha, beta, automatico;
   float velocidad_auto;
   
   public:

    Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;

	// Dibujar
	void dibujar() ;

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );
    void animarModeloJerarquico();
};
#endif
