#include "../Comportamientos_Jugador/jugador.hpp"
#include "motorlib/util.h"

#include <iostream>
#include <cmath>
#include <set>
#include <stack>
#include <unordered_map>
#include <queue>


// Este es el método principal que se piden en la practica.
// Tiene como entrada la información de los sensores y devuelve la acción a realizar.
// Para ver los distintos sensores mirar fichero "comportamiento.hpp"
Action ComportamientoJugador::think(Sensores sensores) {

	actual.fila        = sensores.posF;
	actual.columna     = sensores.posC;
	actual.orientacion = sensores.sentido;

	// Capturo los destinos
	cout << "Nivel actual: " << sensores.nivel << endl;
	objetivos.clear();
	for (int i=0; i<sensores.num_destinos; i++){
		estado aux;
		aux.fila = sensores.destino[2*i];
		aux.columna = sensores.destino[2*i+1];
		objetivos.push_back(aux);
	}

	if (!hayPlan)
		hayPlan = pathFinding (sensores.nivel, actual, objetivos, plan);
	
	Action accion;
	if (hayPlan && plan.size()>0) {
		accion = plan.front();
		plan.erase(plan.begin());
	} else {
		cout << "No se pudo encontrar un plan\n";
	}

  return accion;
}


// Llama al algoritmo de busqueda que se usara en cada comportamiento del agente
// Level representa el comportamiento en el que fue iniciado el agente.
bool ComportamientoJugador::pathFinding (int level, const estado &origen, const list<estado> &destino, list<Action> &plan){
	estado un_objetivo;
	switch (level){
		case 0: cout << "Demo\n";
						un_objetivo = objetivos.front();
						cout << "fila: " << un_objetivo.fila << " col:" << un_objetivo.columna << endl;
			      return pathFinding_Profundidad(origen,un_objetivo,plan);
						break;

		case 1: cout << "Optimo numero de acciones\n";
						un_objetivo = objetivos.front();
						cout << "fila: " << un_objetivo.fila << " col:" << un_objetivo.columna << endl;
						return pathFinding_Anchura(origen, un_objetivo, plan);
						break;
		case 2: cout << "Optimo en coste 1 Objetivo\n";
						un_objetivo = objetivos.front();
						cout << "fila: " << un_objetivo.fila << " col:" << un_objetivo.columna << endl;
						return pathFinding_Costo(origen, un_objetivo, plan);
						break;
		case 3: cout << "Optimo en coste 3 Objetivos\n";
						// Incluir aqui la llamada al algoritmo de busqueda para 3 objetivos
						cout << "No implementado aun\n";
						break;
		case 4: cout << "Algoritmo de busqueda usado en el reto\n";
						// Incluir aqui la llamada al algoritmo de busqueda usado en el nivel 2
						cout << "No implementado aun\n";
						break;
	}
	return false;
}


//---------------------- Implementación de la busqueda en profundidad ---------------------------

// Dado el codigo en caracter de una casilla del mapa dice si se puede
// pasar por ella sin riegos de morir o chocar.
bool EsObstaculo(unsigned char casilla){
	if (casilla=='P' or casilla=='M')
		return true;
	else
	  return false;
}


// Comprueba si la casilla que hay delante es un obstaculo. Si es un
// obstaculo devuelve true. Si no es un obstaculo, devuelve false y
// modifica st con la posición de la casilla del avance.
bool ComportamientoJugador::HayObstaculoDelante(estado &st){
	int fil=st.fila, col=st.columna;

  // calculo cual es la casilla de delante del agente
	switch (st.orientacion) {
		case 0: fil--; break;
		case 1: col++; break;
		case 2: fil++; break;
		case 3: col--; break;
	}

	// Compruebo que no me salgo fuera del rango del mapa
	if (fil<0 or fil>=mapaResultado.size()) return true;
	if (col<0 or col>=mapaResultado[0].size()) return true;

	// Miro si en esa casilla hay un obstaculo infranqueable
	if (!EsObstaculo(mapaResultado[fil][col])){
		// No hay obstaculo, actualizo el parametro st poniendo la casilla de delante.
    st.fila = fil;
		st.columna = col;
		return false;
	}
	else{
	  return true;
	}
}




struct nodo{
	estado st;
	list<Action> secuencia;
};

struct ComparaEstadosProf{
	bool operator()(const estado &a, const estado &n) const{
		if ((a.fila > n.fila) or (a.fila == n.fila and a.columna > n.columna) or
	      (a.fila == n.fila and a.columna == n.columna and a.orientacion > n.orientacion))
			return true;
		else
			return false;
	}
};


// Implementación de la busqueda en profundidad.
// Entran los puntos origen y destino y devuelve la
// secuencia de acciones en plan, una lista de acciones.
bool ComportamientoJugador::pathFinding_Profundidad(const estado &origen, const estado &destino, list<Action> &plan) {
	//Borro la lista
	cout << "Calculando plan\n";
	plan.clear();
	set<estado,ComparaEstadosProf> Cerrados; // Lista de Cerrados
	stack<nodo> Abiertos;								 // Lista de Abiertos

  nodo current;
	current.st = origen;
	current.secuencia.empty();

	Abiertos.push(current);

  while (!Abiertos.empty() and (current.st.fila!=destino.fila or current.st.columna != destino.columna)){

		Abiertos.pop();
		Cerrados.insert(current.st);

		// Generar descendiente de girar a la derecha
		nodo hijoTurnR = current;
		hijoTurnR.st.orientacion = (hijoTurnR.st.orientacion+1)%4;
		if (Cerrados.find(hijoTurnR.st) == Cerrados.end()){
			hijoTurnR.secuencia.push_back(actTURN_R);
			Abiertos.push(hijoTurnR);

		}

		// Generar descendiente de girar a la izquierda
		nodo hijoTurnL = current;
		hijoTurnL.st.orientacion = (hijoTurnL.st.orientacion+3)%4;
		if (Cerrados.find(hijoTurnL.st) == Cerrados.end()){
			hijoTurnL.secuencia.push_back(actTURN_L);
			Abiertos.push(hijoTurnL);
		}

		// Generar descendiente de avanzar
		nodo hijoForward = current;
		if (!HayObstaculoDelante(hijoForward.st)){
			if (Cerrados.find(hijoForward.st) == Cerrados.end()){
				hijoForward.secuencia.push_back(actFORWARD);
				Abiertos.push(hijoForward);
			}
		}

		// Tomo el siguiente valor de la Abiertos
		if (!Abiertos.empty()){
			current = Abiertos.top();
		}
	}

  cout << "Terminada la busqueda\n";

	if (current.st.fila == destino.fila and current.st.columna == destino.columna){
		cout << "Cargando el plan\n";
		plan = current.secuencia;
		cout << "Longitud del plan: " << plan.size() << endl;
		PintaPlan(plan);
		// ver el plan en el mapa
		VisualizaPlan(origen, plan);
		return true;
	}
	else {
		cout << "No encontrado plan\n";
	}


	return false;
}


// Implementación de la busqueda en anchura (camino mínimo).
// Entran los puntos origen y destino y devuelve la
// secuencia de acciones en plan, una lista de acciones.
/*
Creamos unordered_map(estado_final, nodoAnch(estado_anterior, accion))
Comprobamos los siguientes nodos al actual con la funcion siguientes
Evaluamos las 3 posibilidades
Insertamos las parejas en un unordered_map, dándole más valor a aquellos nodoAnchura donde la acción sea actFORWARD
*/

vector<ComportamientoJugador::nodoAnch> ComportamientoJugador::siguientes(const estado &origen) {
	vector<nodoAnch> siguientes;

	Action actions[] = {actFORWARD, actTURN_R, actTURN_L};

	for (int i = 0; i < 3; i++) {
		estado hijo = origen;

		hijo.orientacion = (origen.orientacion + i*(i+1)/2) % 4;
		/*

		De esta forma f(0) = 0, f(1) = 1 y f(2) = 3

		*/

		bool entra = true;

		if (i == 0)
			if (HayObstaculoDelante(hijo))
				entra = false;

		if (entra) {
			nodoAnch desc = { hijo, actions[i] };
			siguientes.push_back(desc);
		}
	}

	return siguientes;
}

namespace std{
template <> struct hash<estado> {
	typedef estado argument_type;
	typedef std::size_t result_type;
	/**
	 * @brief Función hash para unordered_map con clave estado
	 * Llamamos a la función hash d enteros
	 */
	std::size_t operator()(const estado &id) const noexcept {
		return std::hash<int>()(id.fila ^ (id.columna << 4)
			^ (id.orientacion << 8));
	}
};
}

bool ComportamientoJugador::pathFinding_Anchura(const estado &origen, const estado &destino, list<Action> &plan) {
	//Borro la lista
	cout << "Calculando plan\n";
	plan.clear();

	unordered_map<estado, nodoAnch, hash<estado>> Cerrados; // Lista de Cerrados
	queue<nodoAnch> Abiertos;		// Lista de Abiertos

	nodoAnch actual = {.st = origen, .accion = actIDLE};
	Cerrados[origen] = actual;

	Abiertos.push(actual);

	estado current = Abiertos.front().st;

	while (!Abiertos.empty() && !esDestino(current, destino)) {
		Abiertos.pop();

		for (auto next : siguientes(current)) {
			if (Cerrados.find(next.st) == Cerrados.end()) {
				Abiertos.push(next);
				actual = {.st = current, .accion = next.accion};
				Cerrados[next.st] = actual;
			}
		}

		if (!Abiertos.empty())
			current = Abiertos.front().st;
	}

	cout << "Busqueda terminada\n";

	if (esDestino(current, destino)) {
		cout << "Cargando el plan\n";
		while (!esOrigen(current, origen)) {
			plan.push_front(Cerrados[current].accion);
			current = Cerrados[current].st;
		}
		
		cout << "Longitud del plan: " << plan.size() << endl;
		PintaPlan(plan);
		//ver plan en el mapa
		VisualizaPlan(origen, plan);

		return true;
	} else
		return false;

	
}




// Implementación de la busqueda en anchura teniendo en cuenta el costo (camino de costo mínimo).
// Entran los puntos origen y destino y devuelve la
// secuencia de acciones en plan, una lista de acciones.
/*
Comprobamos los siguientes nodos al actual con la funcion siguientes
Evaluamos las 3 posibilidades
Creamos map(estado_final, nodo(estado_anterior, accion))
Insertamos las parejas en un unordered_map, dándole más valor a aquellos nodoAnchura donde la acción sea actFORWARD
*/

vector<tuple<ComportamientoJugador::nodoCost, Action, int>> ComportamientoJugador::siguientesCosto(const nodoCost &origen) {
	vector<tuple<nodoCost, Action, int>> siguientes;

	Action actions[] = {actFORWARD, actTURN_R, actTURN_L};

	for (int i = 0; i < 3; i++) {
		nodoCost hijo = origen;

		hijo.st.orientacion = (origen.st.orientacion + i*(i+1)/2) % 4;
		/*

		De esta forma f(0) = 0, f(1) = 1 y f(2) = 3

		*/

		int cost = 0;

		unsigned char casilla = mapaResultado[hijo.st.fila][hijo.st.columna];

		if 		(casilla == 'K')	hijo.bikini = true;
		else if (casilla == 'D') 	hijo.zapatillas = true;

		if 		(casilla == 'A') 	cost += hijo.bikini 	? 10 : 100;
		else if (casilla == 'B')	cost += hijo.zapatillas ? 5 : 50;
		else if (casilla == 'T')	cost += 2;
		else if (casilla == 'X')	cost += 0;	//No queremos incluir heurística de recarga aun
		else if (casilla == '?')	cost += 3;
		//else if (casilla == 'P')	cost += 10000;
		//else if (casilla == 'M')	cost += 10000;
		else						cost += 1;

		bool entra = true;

		if (i == 0)
			if (HayObstaculoDelante(hijo.st))
				entra = false;

		if (entra) {
			siguientes.push_back(make_tuple(hijo, actions[i], cost));
		}
	}

	return siguientes;
}

namespace std{
template <> struct hash<ComportamientoJugador::nodoCost> {
	typedef estado argument_type;
	typedef std::size_t result_type;
	/**
	 * @brief Función hash para unordered_map con clave estado
	 * Llamamos a la función hash d enteros
	 */
	std::size_t operator()(const ComportamientoJugador::nodoCost &id) const noexcept {
		return std::hash<int>()(id.st.fila ^ (id.st.columna << 4)
			^ (id.st.orientacion << 8) ^ (id.bikini << 9) ^ (id.zapatillas << 10));
	}
};
}

bool ComportamientoJugador::pathFinding_Costo(const estado &origen, const estado &destino, list<Action> &plan) {
	//Borro la lista
	cout << "Calculando plan\n";
	plan.clear();

	unordered_map<nodoCost, pair<nodoCost, Action>, hash<nodoCost>> Cerrados; // Lista de Cerrados
	unordered_map<nodoCost, double> coste;	//Mapa para guardar el coste asociado a un nodo sin hacer uso del nodo de la colade prioridades
	priority_queue<nodoCost_prio> Abiertos;		// Lista de Abiertos

	nodoCost actual = {
		.st = origen,
		.bikini=mapaResultado[origen.fila][origen.columna] == 'K' ? true : false,
		.zapatillas = mapaResultado[origen.fila][origen.columna] == 'D' ? true : false
	};

	Abiertos.push(nodoCost_prio{actual, 0});

	Cerrados[actual] = make_pair(actual, actIDLE);
	coste[actual] = 0;

	actual = Abiertos.top().nodo;

	while (!Abiertos.empty() && !esDestino(actual.st, destino)) {
		Abiertos.pop();

		for (auto next : siguientesCosto(actual)) {
			//Calculamos nuevo coste
			int nuevo_coste = coste[actual] + get<2>(next);

			//Añadimos si no se ha añadido o actualizamos el coste si ya se ha añadido
			if (coste.find(get<0>(next)) == coste.end() || nuevo_coste < coste[get<0>(next)]) {
				coste[get<0>(next)] = nuevo_coste;
				Cerrados[get<0>(next)] = make_pair(actual, get<1>(next));
				Abiertos.push(nodoCost_prio{get<0>(next), nuevo_coste});
			}
		}

		if (!Abiertos.empty())
			actual = Abiertos.top().nodo;
	}

	cout << "Busqueda terminada\n";

	if (esDestino(actual.st, destino)) {
		cout << "Cargando el plan\n";
		while (actual.st != origen) {
			plan.push_front(Cerrados[actual].second);
			actual = Cerrados[actual].first;
		}
		
		cout << "Longitud del plan: " << plan.size() << endl;
		PintaPlan(plan);
		//ver plan en el mapa
		VisualizaPlan(origen, plan);

		return true;
	} else
		return false;

	
}







// Sacar por la consola la secuencia del plan obtenido
void ComportamientoJugador::PintaPlan(list<Action> plan) {
	auto it = plan.begin();
	while (it!=plan.end()){
		if (*it == actFORWARD){
			cout << "A ";
		}
		else if (*it == actTURN_R){
			cout << "D ";
		}
		else if (*it == actTURN_L){
			cout << "I ";
		}
		else {
			cout << "- ";
		}
		it++;
	}
	cout << endl;
}

bool ComportamientoJugador::esDestino(const estado &est, const estado &dest) {
	return est.columna == dest.columna && est.fila == dest.fila;
}

bool ComportamientoJugador::esOrigen(const estado & est, const estado &orig) {
	return est.columna == orig.columna && est.fila == orig.fila;
}


// Funcion auxiliar para poner a 0 todas las casillas de una matriz
void AnularMatriz(vector<vector<unsigned char> > &m){
	for (int i=0; i<m[0].size(); i++){
		for (int j=0; j<m.size(); j++){
			m[i][j]=0;
		}
	}
}


// Pinta sobre el mapa del juego el plan obtenido
void ComportamientoJugador::VisualizaPlan(const estado &st, const list<Action> &plan){
  AnularMatriz(mapaConPlan);
  cout << "Visualizando el plan\n";
	estado cst = st;

	auto it = plan.begin();
	while (it!=plan.end()){
		if (*it == actFORWARD){
			switch (cst.orientacion) {
				case 0: cst.fila--; break;
				case 1: cst.columna++; break;
				case 2: cst.fila++; break;
				case 3: cst.columna--; break;
			}
			mapaConPlan[cst.fila][cst.columna]=1;
		}
		else if (*it == actTURN_R){
			cst.orientacion = (cst.orientacion+1)%4;
		}
		else {
			cst.orientacion = (cst.orientacion+3)%4;
		}
		it++;
	}
}



int ComportamientoJugador::interact(Action accion, int valor){
  return false;
}
