#include <iostream>
#include <random>
#include <thread>
#include <mutex>
#include "HoareMonitor.h"

using namespace std ;
using namespace HM ;

const unsigned  hebrasTipo = 10;

constexpr int
   num_items  = 500 ;     // número de items a producir/consumir
unsigned
   cont_prod[num_items], // contadores de verificación: producidos
   cont_cons[num_items]; // contadores de verificación: consumidos
mutex
   mtx ;                 // mutex de escritura en pantalla

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
   mtx.lock();
   cout << "producido: " << contador << endl << flush ;
   mtx.unlock();
   cont_prod[contador] ++ ;
   return contador++ ;
}
//----------------------------------------------------------------------

void consumir_dato( unsigned dato )
{
   if ( num_items <= dato )
   {
      cout << " dato === " << dato << ", num_items == " << num_items << endl ;
      assert( dato < num_items );
   }
   cont_cons[dato] ++ ;
   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));
}
//----------------------------------------------------------------------

void ini_contadores()
{
   for( unsigned i = 0 ; i < num_items ; i++ )
   {  cont_prod[i] = 0 ;
      cont_cons[i] = 0 ;
   }
}

//----------------------------------------------------------------------

void test_contadores()
{
   bool ok = true ;
   cout << "comprobando contadores ...." << flush ;

   for( unsigned i = 0 ; i < num_items ; i++ )
   {
      if ( cont_prod[i] != 1 )
      {
         cout << "error: valor " << i << " producido " << cont_prod[i] << " veces." << endl ;
         ok = false ;
      }
      if ( cont_cons[i] != 1 )
      {
         cout << "error: valor " << i << " consumido " << cont_cons[i] << " veces" << endl ;
         ok = false ;
      }
   }
   if (ok)
      cout << endl << flush << "solución (aparentemente) correcta." << endl << flush ;
}
//------------------------------------------------------------
/*
Clase MProdConsSu, monitor de Semántica SU para el manejo del productor consumidor con varios consumidores y productores
*/

class MProdConsSU : public HoareMonitor {
    private:

        static const int tam_buffer = 10;
        CondVar producir,
                consumir;
        int primera_libre,
            primera_ocupada,
            ocupadas,
            buffer[tam_buffer];

    public:

        MProdConsSU();
        void EscribirDato(int valor);
        int ConsumirDato();
};

MProdConsSU::MProdConsSU() {
    this->primera_libre = 0;
    this->primera_ocupada = 0;
    this->ocupadas = 0;
    this->consumir = newCondVar();
    this->producir = newCondVar();
}

void MProdConsSU::EscribirDato(int valor) {
    if (ocupadas == tam_buffer)
        producir.wait();

    buffer[primera_libre] = valor;
    ocupadas++;
    primera_libre = (primera_libre + 1) % tam_buffer;
    consumir.signal();
}

int MProdConsSU::ConsumirDato() {
    if (ocupadas == 0)
        consumir.wait();
    
    const int valor = buffer[primera_ocupada];
    primera_ocupada = (primera_ocupada + 1) % tam_buffer;
    ocupadas--;
    producir.signal();
    cout << "                  consumido: " << valor << endl ;
    return valor;
}

void funcion_hebra_productora( MRef<MProdConsSU> monitor )
{
   for( unsigned i = 0 ; i < num_items/hebrasTipo ; i++ )
   {
        int valor = producir_dato();
        monitor->EscribirDato(valor);
   }
}
// -----------------------------------------------------------------------------

void funcion_hebra_consumidora( MRef<MProdConsSU> monitor )
{
   for( unsigned i = 0 ; i < num_items/hebrasTipo ; i++ )
   {
      int valor = monitor->ConsumirDato();
      consumir_dato( valor ) ;
   }
}
// -----------------------------------------------------------------------------

int main()
{
    cout << "-------------------------------------------------------------------------------" << endl
        << "Problema de los productores-consumidores (varios prod/cons, Monitor SU, buffer FIFO). " << endl
        << "-------------------------------------------------------------------------------" << endl
        << flush ;

    // crear monitor  ('monitor' es una referencia al mismo, de tipo MRef<...>)
   MRef<MProdConsSU> monitor = Create<MProdConsSU>();

    thread hebras[hebrasTipo*2];

    for (int i = 0; i < hebrasTipo; i++)
        hebras[i] = thread(funcion_hebra_productora, monitor);

    for (int i = hebrasTipo; i < hebrasTipo*2; i++)
        hebras[i] = thread(funcion_hebra_consumidora, monitor);

    for (int i = 0; i < hebrasTipo*2; i++)
        hebras[i].join();

   // comprobar que cada item se ha producido y consumido exactamente una vez
   test_contadores() ;
}