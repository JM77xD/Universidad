# Práctica 1: Técnicas de búsqueda en entorno.



### José María Ramírez González

#### 3º Grado en Ingeniería informática

#### [jmramirez@correo.ugr.es](mailto:jmramirez@correo.ugr.es)

<div style="page-break-after: always;"></div>

En esta práctica se nos pide desarrollar diferentes técnicas de búsqueda para el entorno de [GVGAI](http://www.gvgai.net/). Estas técnicas son:

* Búsqueda en Anchura.
* Búsqueda en profundidad.
* Búsqueda A*.
* Búsqueda IDA*.
* Búsqueda RTA*.

Ejecutando los algoritmos implementados sobre los mapas de evaluación, hemos obtenido la siguiente tabla de resultados:

![Tabla de resultados](/home/jmramirez/Nextcloud/Portatil/Universidad/Programacion/Tercero/TSI/P1/Tabla_resultados.png)

Como vemos, RTA* e IDA* no consiguen realizar los dos últimos mapas, en el caso de IDA* por *Timeout* y en el caso de RTA* por quedarse atascado.

No obstante, IDA* obtiene resultados óptimos en un tiempo razonable para las otras dos ejecuciones y RTA* explora bien los dos primeros mapas de evaluación.

Respecto a la búsqueda en anchura, A* y en profundidad, esta última no alcanza resultados óptimos, pero tiene un tiempo de ejecución considerablentes menor que las otras dos para los mapas grandes, siendo este efecto menos apreciable en los pequeños. Los dos primeros, A* y la búsqueda en anchura, si que proporcionan resultados óptimos. A* va a tardar más en mapas grandes que la búsqueda en anchura, debido a que la heurística lo puede llevar por caminos equivocados con más facilidad, pero también va a expandir menos nodos, mientras que la búsqueda en anchura resulta algo más lenta que A\* en mapas no muy grandes, pero va a ser más eficiente en memoria.

<div style="page-break-after: always;"></div> 

Ahora bien, se nos plantean las siguientes cuestiones:

* **Entre BFS y DFS, ¿qué algoritmo puede ser considerado más eficiente de cara a encontrar el camino óptimo?**
  
  A la vista de las pruebas empíricas y teóricas disponibles, BFS va a proporcionar siempre el camino óptimo. En cambio, DFS prioriza encontrar un camino (óptimo o no) de la forma más rápida posible.
  
  Por consiguiente, BFS resulta más eficiente que DFS si lo que queremos es encontrar el camino óptimo, ya que DFS no garantiza esto.
  
* **¿Se podría decir que A* es más eficiente que DFS?**

  Esta pregunta se puede responder de dos formas distintas.

  Si queremos un mejor tiempo de ejecución y un menor impacto en la memoria, DFS va a ser más eficiente, pero hay que recordar que este **no** garantiza el camino óptimo.

  Si necesitamos el camino óptimo, A* será siempre más eficiente que DFS, ya que aunque tarde más en ejecutarse y consuma más memoria, encuentra el camino óptimo.

  Basándonos en los resultados empíricos, podemos concluir que A* es menos eficiente que DFS, pero si necesitamos un resultado óptimo, usaremos A\*.

* **¿Cuáles son las principales diferencias entre A* e IDA*? ¿En qué contextos es más conveniente usar uno u otro?**
  
  A* se asimila a la búsqueda en anchura, teniendo una lista de nodos a explorar ordenada en función del coste de los mismos. Siempre explorará antes aquel nodo con menos coste.
  
  IDA* se asimila a la búsqueda en profundidad, pero si que garantiza el óptimo. También tiene una lista de nodos a explorar en función del coste, la diferencia es que, cuando se generan los hijos de un nodo, se ordenan en función del coste y se pasa a explorar directamente.
  
  A su vez, para garantizar el óptimo, hace uso de una cota máx, es decir, una profundidad máxima del árbol de nodos a la que se puede llegar. Si no se encuentra el objetivo en esa cota, se aumenta y se vuelve a intentar, garantizando así que cuando encontremos un resultado válido, sea el de menor coste.
  
  En mapas pequeños, será conveniente usar IDA*, ya que aunque sea algo más lento, ahorraremos en espacio, aunque nuestros resultados empíricos no lo demuestren.
  
  A* siempre es una buena opción, independientemente del mapa, por lo que puede usarse en cualquier situación. No obstante, da mejores resultados en mapas grandes que otros algoritmos equivalentes, ya que es bastante rápido.
  
* **¿Se podría decir que RTA* es más eficiente que A*?**
  Teóricamente, sí, es decir, como máximo RTA* encuentra el camino en el mismo tiempo que A\*, pero tiene posibilidades de encontrarlo antes. En nuestro caso particular, debido a la implementación de RTA\*, este tiene peores resultados de tiempo que A\*, pero no de memoria.
  Por consiguiente, podemos decir que **teóricamente** RTA\* debería ser más eficiente que A\*, sin embargo, debido a factores de la implementación, como una mayor dificultad del algoritmo, operaciones poco eficientes, estructuras de datos muy pesadas..., puede resultar menos eficiente que A*.