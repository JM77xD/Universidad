// -----------------------------------------------------------------------------
//
// Sistemas concurrentes y Distribuidos.
// Práctica 3. Implementación de algoritmos distribuidos con MPI
//
// Archivo: filosofos-plantilla.cpp
// Implementación del problema de los filósofos (sin camarero).
// Plantilla para completar.
//
// Historial:
// Actualizado a C++11 en Septiembre de 2017
// -----------------------------------------------------------------------------


#include <mpi.h>
#include <thread> // this_thread::sleep_for
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include <iostream>

using namespace std;
using namespace std::this_thread ;
using namespace std::chrono ;

const int
   num_filosofos    = 5,
   num_procesos     = 2*num_filosofos + 1,
   etiq_sentarse    = 0,
   etiq_levantarse  = 1,
   etiq_tenedor     = 2,
   id_camarero      = num_procesos - 1;


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

void funcion_filosofos( int id )
{
  int id_ten_izq = (id+1)              % num_procesos, //id. tenedor izq.
      id_ten_der = (id+num_procesos-1) % num_procesos, //id. tenedor der.
      peticion;
      if (id_ten_der == id_camarero)
        id_ten_der--;
    while ( true ) {
        cout << "Filósofo " <<id << " solicita sentarse a la mesa.\n";
        MPI_Ssend(&peticion, 1, MPI_INT, id_camarero, etiq_sentarse, MPI_COMM_WORLD);

        cout <<"Filósofo " <<id << " solicita ten. izq." <<id_ten_izq <<endl;
        MPI_Ssend(&peticion , 1, MPI_INT, id_ten_izq, etiq_tenedor, MPI_COMM_WORLD);      //Pedimos tenedor izq
        
        cout <<"Filósofo " <<id <<" solicita ten. der." <<id_ten_der <<endl;
        MPI_Ssend(&peticion , 1, MPI_INT, id_ten_der, etiq_tenedor, MPI_COMM_WORLD);      //Pedimos tenedor derecho
        
        cout <<"Filósofo " <<id <<" comienza a comer" <<endl ;
        sleep_for( milliseconds( aleatorio<10,100>() ) );
        
        cout <<"Filósofo " <<id <<" suelta ten. izq. " <<id_ten_izq <<endl;
        MPI_Ssend(&peticion , 1, MPI_INT, id_ten_izq, etiq_tenedor, MPI_COMM_WORLD);      //Soltamos tenedor izq
        
        cout<< "Filósofo " <<id <<" suelta ten. der. " <<id_ten_der <<endl;
        MPI_Ssend(&peticion , 1, MPI_INT, id_ten_der, etiq_tenedor, MPI_COMM_WORLD);
        
        cout << "Filósofo " <<id << " solicita levantarse de la mesa.\n";
        MPI_Ssend(&peticion, 1, MPI_INT, id_camarero, etiq_levantarse, MPI_COMM_WORLD);      //Soltamos tenedor derecho
        
        cout << "Filosofo " << id << " comienza a pensar" << endl;
        sleep_for( milliseconds( aleatorio<10,100>() ) );
    }
}

// ---------------------------------------------------------------------

void funcion_tenedores( int id )
{
  int valor, id_filosofo ;  // valor recibido, identificador del filósofo
  MPI_Status estado ;       // metadatos de las dos recepciones

  while ( true )
  {
     MPI_Recv(&valor, 1, MPI_INT, MPI_ANY_SOURCE, etiq_tenedor, MPI_COMM_WORLD, &estado);  //Recibimos un mensaje de cualquier emisor
     id_filosofo = estado.MPI_SOURCE;                                                     //Guardamos el id del filósofo
     cout <<"Ten. " <<id <<" ha sido cogido por filo. " <<id_filosofo <<endl;

     MPI_Recv(&valor, 1, MPI_INT, id_filosofo, etiq_tenedor, MPI_COMM_WORLD, &estado);     //Esperamos a la liberación del filósofo
     cout <<"Ten. "<< id<< " ha sido liberado por filo. " <<id_filosofo <<endl ;
  }
}

// ---------------------------------------------------------------------

void funcion_camarero() {
    int sentados = 0,
        valor;
    MPI_Status estado;
    
    while (true) {
        MPI_Probe (MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &estado);
        if (estado.MPI_TAG == etiq_sentarse && sentados < 4) {
            cout << "Sentado filósofo " << estado.MPI_SOURCE << endl;
            MPI_Recv(&valor, 1, MPI_INT, estado.MPI_SOURCE, etiq_sentarse, MPI_COMM_WORLD, &estado);
            sentados++;
        } else {
            MPI_Recv(&valor, 1, MPI_INT, MPI_ANY_SOURCE, etiq_levantarse, MPI_COMM_WORLD, &estado); 
            sentados--;
            cout << "Levantado filósofo " << estado.MPI_SOURCE << endl;
        }

    }
}

// ---------------------------------------------------------------------

int main( int argc, char** argv )
{
   int id_propio, num_procesos_actual ;

   MPI_Init( &argc, &argv );
   MPI_Comm_rank( MPI_COMM_WORLD, &id_propio );
   MPI_Comm_size( MPI_COMM_WORLD, &num_procesos_actual );


   if ( num_procesos == num_procesos_actual )
   {
        // ejecutar la función correspondiente a 'id_propio'
        if ( id_propio % 2 == 0 && id_propio != id_camarero)    // si es par y no es el camarero
            funcion_filosofos( id_propio ); //  es un filósofo
        else if (id_propio == id_camarero)  //Si es el camarero
            funcion_camarero();
        else                                //Si no
            funcion_tenedores( id_propio ); //  es un tenedor
   }
   else
   {
      if ( id_propio == 0 ) // solo el primero escribe error, indep. del rol
      { cout << "el número de procesos esperados es:    " << num_procesos << endl
             << "el número de procesos en ejecución es: " << num_procesos_actual << endl
             << "(programa abortado)" << endl ;
      }
   }

   MPI_Finalize( );
   return 0;
}

// ---------------------------------------------------------------------
