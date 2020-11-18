#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include "Semaphore.h"

using namespace std ;
using namespace SEM ;

const int num_fumadores = 5;
int num_cigarros = 0;

Semaphore   fumador[] = {0, 0, 0, 0, 0},
            estanquero_libre(1);

/**
 * @brief Plantilla de función para generar un entero aleatorio uniformemente distribuido entre 2 valores enteros
 * @return Devuelve un entero aleatorio entre 2 valores conocidos en tiempo de compilación, ambos incluidos
 */
template< int min, int max > int aleatorio()
{
  static default_random_engine generador( (random_device())() );
  static uniform_int_distribution<int> distribucion_uniforme( min, max ) ;
  return distribucion_uniforme( generador );
}

/**
 * @brief Función que simula la acción de producir un ingrediente
 * @return Devuelve el número del ingrediente que ha producido
 */
int producir_ingrediente()
{
   // calcular milisegundos aleatorios de duración de la acción de fumar)
   chrono::milliseconds duracion_produ( aleatorio<10,100>() );

   // informa de que comienza a producir
   cout << "Estanquero : empieza a producir ingrediente (" << duracion_produ.count() << " milisegundos)" << endl;

   // espera bloqueada un tiempo igual a ''duracion_produ' milisegundos
   this_thread::sleep_for( duracion_produ );

   const int num_ingrediente = aleatorio<0,num_fumadores-1>() ;

   // informa de que ha terminado de producir
   cout << "Estanquero : termina de producir ingrediente " << num_ingrediente << endl;

   return num_ingrediente ;
}

/**
 * @brief Función que ejecuta la hebra del estanquero
 */
void funcion_hebra_estanquero(  )
{
   int ingrediente;
   while (true)
   {
      sem_wait(estanquero_libre);
      ingrediente = producir_ingrediente();
      sem_signal(fumador[ingrediente]);
      cout << "\nPuesto ingrediente " << ingrediente << ".\n";
   }
}


/**
 * @brief Función que simula la acción de fumar
 * @param num_fumador Número del fumador que comienza a fumar
 */
void fumar( int num_fumador )
{

   // calcular milisegundos aleatorios de duración de la acción de fumar)
   chrono::milliseconds duracion_fumar( aleatorio<20,200>() );

   // informa de que comienza a fumar

    cout << "Fumador " << num_fumador << "  :"
          << " empieza a fumar (" << duracion_fumar.count() << " milisegundos)" << endl;

   // espera bloqueada un tiempo igual a ''duracion_fumar' milisegundos
   this_thread::sleep_for( duracion_fumar );

   // informa de que ha terminado de fumar

    cout << "Fumador " << num_fumador << "  : termina de fumar, comienza espera de ingrediente." << endl;

    num_cigarros++;

}

/**
 * @brief Función que ejecuta la hebra del fumador
 * @param num_fumador Número del fumador que se está ejecutando
 */
void  funcion_hebra_fumador( int num_fumador )
{
   while( true )
   {
      sem_wait(fumador[num_fumador]);
      cout << "\nEl fumador " << num_fumador << " retira su ingrediente.\n";
      cout << endl << "\t" << num_cigarros << endl;
      if (num_cigarros % 2 == 0) {
         cout << "Fumador " << num_fumador << " avisa al estanquero\n";
         sem_signal(estanquero_libre);
         fumar(num_fumador);
      } else {
         fumar(num_fumador);
         cout << "Fumador " << num_fumador << " avisa al estanquero\n";
         sem_signal(estanquero_libre);
      }
   }
}


int main()
{
   thread fumador1(funcion_hebra_fumador, 0),
          fumador2(funcion_hebra_fumador, 1),
          fumador3(funcion_hebra_fumador, 2),
          fumador4(funcion_hebra_fumador, 3),
          fumador5(funcion_hebra_fumador, 4),
          estanquero(funcion_hebra_estanquero);

   fumador1.join();
   fumador2.join();
   fumador3.join();
   fumador4.join();
   fumador5.join();
   estanquero.join();

}
