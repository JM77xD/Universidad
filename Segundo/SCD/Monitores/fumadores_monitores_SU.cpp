#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include "HoareMonitor.h"

using namespace std ;
using namespace HM ;


const static int num_fumadores = 3;


class Estanco : public HoareMonitor {
   private:
      int ingre;
      CondVar mostrador;
      CondVar fumadores[num_fumadores];
   
   public:
      Estanco();
      void ObtenerIngrediente(int nFumador);
      void PonerIngrediente(int ingrediente);
      void esperarRecogida();
};

Estanco::Estanco() {
   ingre = 4;
   mostrador = newCondVar();
   for (int i = 0; i < num_fumadores; i++)
      fumadores[i] = newCondVar();
}

void Estanco::ObtenerIngrediente(int nFumador) {
   if (ingre != nFumador)
      fumadores[nFumador].wait();
   cout << "\nEl fumador " << nFumador << " retira su ingrediente.\n";
   mostrador.signal();
}

void Estanco::PonerIngrediente(int ingrediente) {
   ingre = ingrediente;
   cout << "\nPuesto ingrediente " << ingrediente << ".\n";
   fumadores[ingrediente].signal();
}

void Estanco::esperarRecogida() {
   mostrador.wait();
}

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
void funcion_hebra_estanquero( MRef<Estanco> monitor)
{
   int ingrediente;
   while (true)
   {
      ingrediente = producir_ingrediente();
      monitor->PonerIngrediente(ingrediente);
      monitor->esperarRecogida();
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

}

/**
 * @brief Función que ejecuta la hebra del fumador
 * @param num_fumador Número del fumador que se está ejecutando
 */
void  funcion_hebra_fumador( int num_fumador, MRef<Estanco> monitor )
{
   while( true )
   {
      monitor->ObtenerIngrediente(num_fumador);
      fumar(num_fumador);
   }
}


int main()
{
   MRef<Estanco> estanco = Create<Estanco>();

   thread fumador1(funcion_hebra_fumador, 0, estanco),
          fumador2(funcion_hebra_fumador, 1, estanco),
          fumador3(funcion_hebra_fumador, 2, estanco),
          estanquero(funcion_hebra_estanquero, estanco);

   fumador1.join();
   fumador2.join();
   fumador3.join();
   estanquero.join();

}
