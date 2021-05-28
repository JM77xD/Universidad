#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include "player.h"
#include "environment.h"

using namespace std;

const double masinf=9999999999.0, menosinf=-9999999999.0;


// Constructor
Player::Player(int jug){
    jugador_=jug;
}

// Actualiza el estado del juego para el jugador
void Player::Perceive(const Environment & env){
    actual_=env;
}

double Puntuacion(int jugador, const Environment &estado){
    double suma=0;

    for (int i=0; i<7; i++)
      for (int j=0; j<7; j++){
         if (estado.See_Casilla(i,j)==jugador){
            if (j<3)
               suma += j;
            else
               suma += (6-j);
         }
      }

    return suma;
}


// Funcion de valoracion para testear Poda Alfabeta
double ValoracionTest(const Environment &estado, int jugador){
    int ganador = estado.RevisarTablero();

    if (ganador==jugador)
       return 99999999.0; // Gana el jugador que pide la valoracion
    else if (ganador!=0)
            return -99999999.0; // Pierde el jugador que pide la valoracion
    else if (estado.Get_Casillas_Libres()==0)
            return 0;  // Hay un empate global y se ha rellenado completamente el tablero
    else
          return Puntuacion(jugador,estado);
}

// ------------------- Los tres metodos anteriores no se pueden modificar

/**
 * @brief Cuenta las fichas sueltas pertenecientes a un jugador en el estado dado
 * 
 * @param jugador Jugador del que contar las parejas
 * @param estado Estado en el que contar las parejas
 * @return Devuelve el número de fichas sueltas del jugador
 */
int contarIndiv(int jugador, const Environment &estado) {
   int individuales = 0;
   
   for (int i = 0; i < 7; i++) {
      for (int j = 0; j < 7; j++) {
         if (estado.See_Casilla(i, j) == jugador)
            individuales++;
      }
   }

   return individuales;
}

/**
 * @brief Cuenta las parejas pertenecientes a un jugador en el estado dado
 * 
 * @param jugador Jugador del que contar las parejas
 * @param estado Estado en el que contar las parejas
 * @return Devuelve el número de parejas
 */
int contarParejas(int jugador, const Environment &estado) {
   int parejas = 0;

   for (int i = 0; i < 6; i++) {
      for (int j = 0; j < 6; j++) {

         if (estado.See_Casilla(i,j)==jugador && estado.See_Casilla(i,j+1)==jugador)
            parejas++;

         if (estado.See_Casilla(i,j)==jugador && estado.See_Casilla(i+1,j+1)==jugador)
            parejas++;
         
         if (estado.See_Casilla(i,j)==jugador && estado.See_Casilla(i+1,j)==jugador)
            parejas++;

      }
   }

   return parejas;
}

/**
 * @brief Cuenta los trios pertenecientes a un jugador en el estado dado
 * 
 * @param jugador Jugador del que contar las parejas
 * @param estado Estado en el que contar las parejas
 * @return Devuelve una pareja con el número de trios y los números de columna y fila en los que están
 */
int contarTrios(int jugador, const Environment &estado) {

   int trios = 0;

   for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {

         if (estado.See_Casilla(i,j)==jugador && estado.See_Casilla(i,j+1)==jugador && estado.See_Casilla(i,j+2)==jugador)
            trios++;

         if (estado.See_Casilla(i,j)==jugador && estado.See_Casilla(i+1,j+1)==jugador && estado.See_Casilla(i+2,j+2)==jugador)
            trios++;
         
         if (estado.See_Casilla(i,j)==jugador && estado.See_Casilla(i+1,j)==jugador && estado.See_Casilla(i+2,j)==jugador)
            trios++;
      }
   }

   return trios;
   
}

// Función que calcula la heurística de un jugador para un estado
double Heuristica(int jugador, const Environment &estado) {

   double suma = 0;

   //Contamos los trios

   suma += contarTrios(jugador, estado) * 10000;


   suma -= contarTrios(jugador==1?2:1, estado);


   //Contamos las parejas

   suma += contarParejas(jugador, estado) * 1000;

   suma -= contarParejas(jugador==1?2:1, estado) * 1000;

   
   //Contamos los individuales
   suma += contarIndiv(jugador, estado)*100;

   suma -= contarIndiv(jugador==1?2:1, estado)*100;

   Environment::ActionType acc = static_cast< Environment::ActionType > (estado.Last_Action(jugador));

   if (acc == Environment::PUT4)
      suma += 500;
   else if (acc == Environment::PUT3 || acc == Environment::PUT5)
      suma += 250;
   
   
   return suma; 
}



// Funcion heuristica (ESTA ES LA QUE TENEIS QUE MODIFICAR)
double Valoracion(const Environment &estado, int jugador){
   int ganador = estado.RevisarTablero();

    if (ganador==jugador)
      return 99999999.0; // Gana el jugador que pide la valoracion
    else if (ganador!=0)
      return -99999999.0; // Pierde el jugador que pide la valoracion
    else if (estado.Get_Casillas_Libres()==0)
      return 0;  // Hay un empate global y se ha rellenado completamente el tablero
    else
      return Heuristica(jugador,estado);
}

double Poda_AlfaBeta(const Environment &estado, const int Profundidad, double alfa, double beta, int jugadorActual, const int JugadorMax, const int rep = 1) {
   int fin = estado.RevisarTablero();
   if (Profundidad == 0 || estado.Get_Casillas_Libres() == 0 || fin == 0)
      return Valoracion(estado, jugadorActual);

   Environment next[10];
   int tam = estado.GenerateAllMoves(next);

   if (jugadorActual == JugadorMax) {

      for (int i = 0; i < tam; i++) {
         if (rep == 1)
            beta = min(beta, Poda_AlfaBeta(next[i], Profundidad - 1, alfa, beta, jugadorActual, JugadorMax, 2));
         else
            alfa = max(alfa, Poda_AlfaBeta(next[i], Profundidad - 1, alfa, beta, next[i].JugadorActivo(), JugadorMax));

         if (beta <= alfa)
            break;
      }

      return alfa;

   } else {

      for (int i = 0; i < tam; i++) {
         if (rep == 1)
            beta = min(beta, Poda_AlfaBeta(next[i], Profundidad - 1, alfa, beta, jugadorActual, JugadorMax, 2));
         else
            alfa = max(alfa, Poda_AlfaBeta(next[i], Profundidad - 1, alfa, beta, next[i].JugadorActivo(), JugadorMax));

         if (beta <= alfa)
            break;
      }

      return beta;

   }
}





// Esta funcion no se puede usar en la version entregable
// Aparece aqui solo para ILUSTRAR el comportamiento del juego
// ESTO NO IMPLEMENTA NI MINIMAX, NI PODA ALFABETA
void JuegoAleatorio(bool aplicables[], int opciones[], int &j){
    j=0;
    for (int i=0; i<8; i++){
        if (aplicables[i]){
           opciones[j]=i;
           j++;
        }
    }
}






// Invoca el siguiente movimiento del jugador
Environment::ActionType Player::Think(){
    const int PROFUNDIDAD_MINIMAX = 6;  // Umbral maximo de profundidad para el metodo MiniMax
    const int PROFUNDIDAD_ALFABETA = 8; // Umbral maximo de profundidad para la poda Alfa_Beta

    Environment::ActionType accion; // acci�n que se va a devolver
    bool aplicables[8]; // Vector bool usado para obtener las acciones que son aplicables en el estado actual. La interpretacion es
                        // aplicables[0]==true si PUT1 es aplicable
                        // aplicables[1]==true si PUT2 es aplicable
                        // aplicables[2]==true si PUT3 es aplicable
                        // aplicables[3]==true si PUT4 es aplicable
                        // aplicables[4]==true si PUT5 es aplicable
                        // aplicables[5]==true si PUT6 es aplicable
                        // aplicables[6]==true si PUT7 es aplicable
                        // aplicables[7]==true si BOOM es aplicable



    double valor = -99999999.0, aux; // Almacena el valor con el que se etiqueta el estado tras el proceso de busqueda.
    double alpha = -99999999.0, beta = 99999999.0; // Cotas de la poda AlfaBeta

    int n_act; //Acciones posibles en el estado actual


    n_act = actual_.possible_actions(aplicables); // Obtengo las acciones aplicables al estado actual en "aplicables"
    int opciones[10];

    // Muestra por la consola las acciones aplicable para el jugador activo
    //actual_.PintaTablero();
    cout << " Acciones aplicables ";
    (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
    for (int t=0; t<8; t++)
      if (aplicables[t])
         cout << " " << actual_.ActionStr( static_cast< Environment::ActionType > (t)  );
    cout << endl;


    //--------------------- COMENTAR Desde aqui
    /*
    cout << "\n\t";
    int n_opciones=0;
    JuegoAleatorio(aplicables, opciones, n_opciones);

    if (n_act==0){
      (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
      cout << " No puede realizar ninguna accion!!!\n";
      //accion = Environment::actIDLE;
    }
    else if (n_act==1){
           (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
            cout << " Solo se puede realizar la accion "
                 << actual_.ActionStr( static_cast< Environment::ActionType > (opciones[0])  ) << endl;
            accion = static_cast< Environment::ActionType > (opciones[0]);

         }
         else { // Hay que elegir entre varias posibles acciones
            int aleatorio = rand()%n_opciones;
            cout << " -> " << actual_.ActionStr( static_cast< Environment::ActionType > (opciones[aleatorio])  ) << endl;
            accion = static_cast< Environment::ActionType > (opciones[aleatorio]);
         }

    */
    //--------------------- COMENTAR Hasta aqui


    //--------------------- AQUI EMPIEZA LA PARTE A REALIZAR POR EL ALUMNO ------------------------------------------------


    // Opcion: Poda AlfaBeta
    // NOTA: La parametrizacion es solo orientativa
      Environment next[8];
      int tam = actual_.GenerateAllMoves(next);
      for (int i = 0; i < tam; i++) {
         if (next[i].JugadorActivo() == jugador_)
            aux = Poda_AlfaBeta(next[i], PROFUNDIDAD_ALFABETA, alpha, beta, jugador_ , jugador_, 2);
         else
            aux = Poda_AlfaBeta(next[i], PROFUNDIDAD_ALFABETA, alpha, beta, next[i].JugadorActivo() , jugador_, 1);

         if (aux >= valor) {
            valor = aux;
            accion = static_cast< Environment::ActionType > (next[i].Last_Action(jugador_));
         }
      }
    cout << "Valor MiniMax: " << valor << "  Accion: " << actual_.ActionStr(accion) << endl;

    return accion;
}

