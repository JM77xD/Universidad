# Conecta 4 Boom

#### José María Ramírez González

<div style="page-break-after: always; break-after: page;"></div>

## Descripción del problema

El juego se trata del Conecta 4, juego al que todos hemos jugado, con unas pequeñas variaciones:

- Se juegan 2 acciones por cada turno (exceptuando el primer jugador que coloca ficha, que solo juega 1).
- Existen unas fichas especiales denominadas *fichas bomba* que al realizar la accion `boom` eliminan las fichas del rival que se encuentran en la misma fila.

Una vez sabemos esto, podemos ver que el juego se trata de un juego de 2 jugadores de información perfecta, es decir, sabemos en todo momento lo que tenemos disponible y como afectan nuestras acciones al estado del juego.

Nuestro problema se basa en implementar un bot que, basándose en los posibles desenlaces al tomar una decisión, tome aquella que es más probable que lo beneficie y le permita ganar la partida. Para ello, tendremos que plantear una heurística que determine que movimientos son más ventajosos y cuales perjudiciales, a la vez que implementar un buen algoritmo de búsqueda con adversarios, que use esta heurística para filtrar las acciones.

<div style="page-break-after: always; break-after: page;"></div>

## Descripción de la solución implementada

Para resolver el problema, hemos implementado el algoritmo de [Poda AlfaBeta](https://es.wikipedia.org/wiki/Poda_alfa-beta).

Este algoritmo se basa en ir expandiendo los posibles desenlaces de cada acción (realizando una búsqueda en **profundidad**) en forma de árbol y hacer una búsqueda [MinMax](https://es.wikipedia.org/wiki/Minimax) con cota. Básicamente el algoritmo se basa en algo como: "Suponiendo que el adversario realiza siempre la acción que más nos perjudica, que deberíamos realizar nosotros", esto hace que compruebe los posibles desenlaces de cada acción y tome el más beneficioso. La cota simplemente sirve para agilizar la ejecución del algoritmo y descartar aquellas ramas que no nos resulten beneficiosas.

La heurística que hemos implementado es bastante sencilla:

~~~c++
double Heuristica(int jugador, const Environment &estado) {

   double suma = 0;

   //Contamos las diagonales
   suma += contarDiagonales(jugador, estado);

   suma -= contarDiagonales(jugador==1?2:1, estado);
    
   //Contamos las verticales
   suma += contarVertical(jugador, estado);

   suma -= contarVertical(jugador==1?2:1, estado);
    
   //Contamos los horizontales
   suma += contarHorizontal(jugador, estado);

   suma -= contarHorizontal(jugador==1?2:1, estado);

   int ganador = estado.RevisarTablero();
   if (ganador == jugador)
      suma += 100000;
   else if (ganador != 0)
      suma -= 100000;

   return suma; 
}
~~~



Esto se reduce en asignar un valor a las posibles combinaciones verticales, horizontales y diagonales del jugador y del adversario, siendo las del adversario negativas.

<div style="page-break-after: always; break-after: page;"></div>

La llamada al algoritmo Poda AlfaBeta que realizamos es la siguiente:

~~~c++
Environment next[8];
      int tam = actual_.GenerateAllMoves(next);
      for (int i = 0; i < tam; i++) {
         aux = Poda_AlfaBeta(next[i], PROFUNDIDAD_ALFABETA, alpha, beta, next[i].JugadorActivo() , jugador_);
         if (aux >= valor) {
            valor = aux;
            accion = static_cast< Environment::ActionType > (next[i].Last_Action(jugador_));
         }
      }
~~~

Lo que hacemos es comprobar por cada acción que podemos tomar cual es la que más nos beneficia y realizarla.

La implementación que hemos realizado no es instantánea en lo que a la velocidad de ejecución se refiere, pero es bastante rápida comparada con la del *ninja 3* y el resultado es bastante bueno.

Un ejemplo de funcionamiento correcto, siendo yo el verde y mi heurística el azul, sería el siguiente:

<img src="/home/jmramirez/Imágenes/Conecta4_BuenFuncionamiento.png" alt="Evitando 4 en raya heurística" title="Buen funcionamiento heurístico" style="zoom:75%;" />

Como podemos observar, evita el 4 en raya de la primera fila colocando una ficha en la *columna 1*, así también estaría evitando una posible diagonal por la ficha verde de la posición (4,4), por lo que esta opción sería mejor que colocar la ficha en la *columna 2*.

<div style="page-break-after: always; break-after: page;"></div>

## Problemas encontrados durante el desarrollo de la práctica

Durante el desarrollo de la práctica nos hemos encontrado con varios problemas, de los cuales destacan los siguientes:

- Al tratarse de 2 acciones por jugador, ha resultado un tanto complicado implementar AlfaBeta de forma que no hiciera un árbol Minimax, si no un árbol que repita los nodos *min* y *max* si era necesario, cosa que al final hemos resuelto consultado el siguiente jugador al llamar a AlfaBeta para los estados siguientes.
- La llamada a AlfaBeta se realiza en un bucle desde think, ya que hemos encontrado bastantes problemas a la hora de devolver la acción si lo hacíamos dentro de la propia función de poda.
