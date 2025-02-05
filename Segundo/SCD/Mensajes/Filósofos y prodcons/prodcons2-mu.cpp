// -----------------------------------------------------------------------------
//
// Sistemas concurrentes y Distribuidos.
// Práctica 3. Implementación de algoritmos distribuidos con MPI
//
// Archivo: prodcons2.cpp
// Implementación del problema del productor-consumidor con
// un proceso intermedio que gestiona un buffer finito y recibe peticiones
// en orden arbitrario
// (versión con un único productor y un único consumidor)
//
// Historial:
// Actualizado a C++11 en Septiembre de 2017
// -----------------------------------------------------------------------------

#include <iostream>
#include <thread> // this_thread::sleep_for
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include <mpi.h>

using namespace std;
using namespace std::this_thread ;
using namespace std::chrono ;

const int
   nprods                  = 2,     //Número de productores
   ncons                   = 1,     //Número de consumidores
   id_buffer               = nprods,     //id del buffer
   num_procesos_esperado   = ncons + nprods + 1,  //Número de procesos totales
   num_items               = 16,
   porproductor            = num_items/nprods,    //Número de items que produce cada productor
   porconsumidor           = num_items/ncons,     //Número de items que consume cada consumidor
   tam_vector              = 3,
   etiq_prod0              = 0,                 //Etiqueta del productor 0
   etiq_prod1              = 1,                 //Etiqueta del productor 1
   etiq_cons               = 2;                 //Etiqueta del consumidor

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
// ---------------------------------------------------------------------
// ptoducir produce los numeros en secuencia (1,2,3,....)
// y lleva espera aleatorio
int producir(const int num_prod)
{
   static int contador = num_prod*porproductor ;     //Define el valor inicial del contador en función del orden del productor
   sleep_for( milliseconds( aleatorio<10,100>()) );
   contador++ ;
   cout << "Productor " << num_prod << " ha producido valor " << contador << endl << flush;
   return contador ;
}
// ---------------------------------------------------------------------

void funcion_productor(const int num_prod)
{
   for ( unsigned int i= 0 ; i < porproductor ; i++ )
   {
      // producir valor
      int valor_prod = producir(num_prod);
      // enviar valor
      cout << "Productor " << num_prod << " va a enviar valor " << valor_prod << endl << flush;
      if (num_prod == 0)
         MPI_Ssend( &valor_prod, 1, MPI_INT, id_buffer, etiq_prod0, MPI_COMM_WORLD );      //Enviamos el valor al buffer
      else
         MPI_Ssend( &valor_prod, 1, MPI_INT, id_buffer, etiq_prod1, MPI_COMM_WORLD );      //Enviamos el valor al buffer
   }
}
// ---------------------------------------------------------------------

void consumir( int valor_cons, const int num_cons )
{
   // espera bloqueada
   sleep_for( milliseconds( aleatorio<110,200>()) );
   cout << "Consumidor " << num_cons << " ha consumido valor " << valor_cons << endl << flush ;
}
// ---------------------------------------------------------------------

void funcion_consumidor(const int num_cons)
{
   int         peticion,
               valor_rec = 1 ;
   MPI_Status  estado ;

   for( unsigned int i=0 ; i < porconsumidor; i++ )
   {
      MPI_Ssend( &peticion,  1, MPI_INT, id_buffer, etiq_cons, MPI_COMM_WORLD);              //Enviamos petición al buffer
      MPI_Recv ( &valor_rec, 1, MPI_INT, id_buffer, etiq_cons, MPI_COMM_WORLD,&estado );     //Recibimos mensaje del buffer con la etiqueta correcta
      cout << "Consumidor " << num_cons << " ha recibido valor " << valor_rec << endl << flush ;
      consumir( valor_rec, num_cons );
   }
}
// ---------------------------------------------------------------------

void funcion_buffer()
{
   int        buffer[tam_vector],      // buffer con celdas ocupadas y vacías
              valor,                   // valor recibido o enviado
              primera_libre       = 0, // índice de primera celda libre
              primera_ocupada     = 0, // índice de primera celda ocupada
              num_celdas_ocupadas = 0, // número de celdas ocupadas
              etiq_aceptable ,         // etiqueta de emisor aceptable
              encontrado;              // indica si se ha detectado un mensaje en esa iteración
   MPI_Status estado ;                 // metadatos del mensaje recibido
   bool       modo0 = true;            // informa si está en modo 0 (si por defecto)

   for( unsigned int i=0 ; i < num_items*2 ; i++ )
   {
      encontrado = -1;
      cont = 0;
      // 1. determinar si puede enviar solo prod., solo cons, o todos

      // Hacemos uso de una etiqueta para saber que tenemos que recibir
      if ( num_celdas_ocupadas == 0 && modo0)        // si buffer vacío y modo0
         etiq_aceptable = etiq_prod0 ;               // $~~~$ solo prod0.
      else if ( num_celdas_ocupadas == 0 && !modo0 ) // si buffer vacío y no modo0
         etiq_aceptable = etiq_prod1 ;               // $~~~$ solo prod1.
      else if ( num_celdas_ocupadas == tam_vector ) // si buffer lleno
         etiq_aceptable = etiq_cons ;               // $~~~$ solo cons.
      else                                          // si no vacío ni lleno
         etiq_aceptable = MPI_ANY_TAG;              // $~~~$ cualquiera

      // 2. recibir un mensaje del emisor o emisores aceptables

      if (etiq_aceptable == MPI_ANY_TAG) {
         while (encontrado < 0) {
            if (modo0) {
               MPI_Iprobe(MPI_ANY_SOURCE, etiq_prod0, MPI_COMM_WORLD, &encontrado, &estado);
               MPI_Iprobe(MPI_ANY_SOURCE, etiq_cons, MPI_COMM_WORLD, &encontrado, &estado);
            } else {
               MPI_Iprobe(MPI_ANY_SOURCE, etiq_prod1, MPI_COMM_WORLD, &encontrado, &estado);
               MPI_Iprobe(MPI_ANY_SOURCE, etiq_cons, MPI_COMM_WORLD, &encontrado, &estado);
            }
         }
         etiq_aceptable = estado.MPI_TAG;
      }

      MPI_Recv(&valor, 1, MPI_INT, MPI_ANY_SOURCE, etiq_aceptable, MPI_COMM_WORLD, &estado);

      // 3. procesar el mensaje recibido

      switch( estado.MPI_TAG ) // leer etiqueta del mensaje en metadatos
      {
         case etiq_prod1: // si ha sido el productor1: insertar en buffer
            buffer[primera_libre] = valor ;
            primera_libre = (primera_libre+1) % tam_vector ;
            num_celdas_ocupadas++ ;
            cout << "Buffer ha recibido valor " << valor << " del productor 1." <<  endl ;
            modo0 = true;
            cout << "Cambiando a modo 0.\n";
            break;
         
         case etiq_prod0: // si ha sido el productor0: insertar en buffer
            buffer[primera_libre] = valor ;
            primera_libre = (primera_libre+1) % tam_vector ;
            num_celdas_ocupadas++ ;
            cout << "Buffer ha recibido valor " << valor << " del productor 0." <<  endl ;
            modo0 = false;
            cout << "Cambiando a modo 1.\n";
            break;

         case etiq_cons: // si ha sido el consumidor: extraer y enviarle
            valor = buffer[primera_ocupada] ;
            primera_ocupada = (primera_ocupada+1) % tam_vector ;
            num_celdas_ocupadas-- ;
            cout << "Buffer va a enviar valor " << valor << endl ;
            MPI_Ssend( &valor, 1, MPI_INT, estado.MPI_SOURCE, etiq_cons, MPI_COMM_WORLD);  //Enviamos mensaje al emisor que mandó el mensaje recibido antes del switch
            break;
      }
   }
}

// ---------------------------------------------------------------------

int main( int argc, char *argv[] )
{
   int id_propio, num_procesos_actual;

   // inicializar MPI, leer identif. de proceso y número de procesos
   MPI_Init( &argc, &argv );
   MPI_Comm_rank( MPI_COMM_WORLD, &id_propio );
   MPI_Comm_size( MPI_COMM_WORLD, &num_procesos_actual );

   if ( num_procesos_esperado == num_procesos_actual )
   {
      // ejecutar la operación apropiada a 'id_propio'
      if ( id_propio < id_buffer ) {
         const int orden = id_propio;  //Definimos orden para los productores
         funcion_productor(orden);
      } else if ( id_propio == id_buffer )
         funcion_buffer();
      else {
         const int orden = id_propio - nprods - 1; //Definimos orden para los consumidores
         funcion_consumidor(orden);
      }
   }
   else
   {
      if ( id_propio == 0 ) // solo el primero escribe error, indep. del rol
      { cout << "el número de procesos esperados es:    " << num_procesos_esperado << endl
             << "el número de procesos en ejecución es: " << num_procesos_actual << endl
             << "(programa abortado)" << endl ;
      }
   }

   // al terminar el proceso, finalizar MPI
   MPI_Finalize( );
   return 0;
}
