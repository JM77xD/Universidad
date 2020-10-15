#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random>
#include "Semaphore.h"

using namespace std ;
using namespace SEM ;

//**********************************************************************
// variables compartidas



const int num_items = 60 ,   // número de items
	       tam_vec   = 12 ;   // tamaño del buffer
int       cont_prod[num_items] = {0}, // contadores de verificación: producidos
          cont_cons[num_items] = {0}, // contadores de verificación: consumidos
          vector_intermedio[num_items],   //Vector intermedio para el traspaso de datos
          buffer[tam_vec],                //Buffer para el traspaso de datos
          escribir = 0,       //Contador de escritura en el buffer
          leer = 0;           //Contador de lectura del buffer

Semaphore available_read(0),              //semáforo para el proceso de lectura
          available_write(tam_vec-1);             //semáforo para el proceso de escritura

//**********************************************************************
// plantilla de función para generar un entero aleatorio uniformemente
// distribuido entre dos valores enteros, ambos incluidos
// (ambos tienen que ser dos constantes, conocidas en tiempo de compilación)
//----------------------------------------------------------------------

template< int min, int max > int aleatorio()
{
  static default_random_engine generador( (random_device())() );
  static uniform_int_distribution<int> distribucion_uniforme( min, max ) ;
  return distribucion_uniforme( generador );
}

//**********************************************************************
// funciones comunes a las dos soluciones (fifo y lifo)
//----------------------------------------------------------------------

int producir_dato()
{
   static int contador = 0 ;
   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));

   cout << "producido: " << contador << endl << flush ;

   cont_prod[contador] ++ ;
   return contador++ ;
}
//----------------------------------------------------------------------

void consumir_dato( unsigned dato )
{
   assert( dato < num_items );
   cont_cons[dato] ++ ;
   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));

   cout << "consumido: " << dato << endl ;

}


//----------------------------------------------------------------------

void test_contadores()
{
   bool ok = true ;
   cout << "comprobando contadores ...." ;
   for( unsigned i = 0 ; i < num_items ; i++ )
   {  if ( cont_prod[i] != 1 )
      {  cout << "error: valor " << i << " producido " << cont_prod[i] << " veces." << endl ;
         ok = false ;
      }
      if ( cont_cons[i] != 1 )
      {  cout << "error: valor " << i << " consumido " << cont_cons[i] << " veces" << endl ;
         ok = false ;
      }
   }
   if (ok)
      cout << endl << flush << "solución (aparentemente) correcta." << endl << flush ;
}

//----------------------------------------------------------------------

void  funcion_hebra_productora(  )
{
   for( unsigned i = 0 ; i < num_items ; i++ )
   {
      sem_wait(available_write);    //Espera a que pueda escribir en el buffer, este proceso solo se bloquea si el buffer se llena
      int dato = producir_dato();
      vector_intermedio[i] = dato;
      buffer[escribir] = dato;      //Escribe el dato en el buffer
      escribir = (escribir+1)%tam_vec; //Actualiza el valor del contador
      sem_signal(available_read);      //Señala que ya puede leer del buffer
   }
}

//----------------------------------------------------------------------

void funcion_hebra_consumidora(  )
{
   for( unsigned i = 0 ; i < num_items ; i++ )
   {
      int dato ;
      sem_wait(available_read);     //Espera a que pueda leer del buffer
      dato = buffer[leer];          //Lee el dato del buffer
      leer = (leer+1)%tam_vec;      //Actualiza el valor del contador
      consumir_dato( dato );
      sem_signal(available_write);  //Señala que puede escribir, esto hace que pueda seguir escribiendo en el buffer mientras haya espacio
    }
}
//----------------------------------------------------------------------

int main()
{
   cout << "--------------------------------------------------------" << endl
        << "Problema de los productores-consumidores (solución FIFO)." << endl
        << "--------------------------------------------------------" << endl
        << flush ;

   thread hebra_productora ( funcion_hebra_productora ),
          hebra_consumidora( funcion_hebra_consumidora );

   hebra_productora.join() ;
   hebra_consumidora.join() ;

   test_contadores();
}