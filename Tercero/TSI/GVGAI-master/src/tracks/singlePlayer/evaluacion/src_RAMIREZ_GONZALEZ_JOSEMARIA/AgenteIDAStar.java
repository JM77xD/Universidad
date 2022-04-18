package tracks.singlePlayer.evaluacion.src_RAMIREZ_GONZALEZ_JOSEMARIA;

import core.game.Observation;
import core.game.StateObservation;
import core.player.AbstractPlayer;
import ontology.Types.ACTIONS;
import tools.ElapsedCpuTimer;
import tools.Vector2d;

import java.util.*;

public class AgenteIDAStar extends AbstractPlayer{

	private ArrayDeque<NodeCost> ruta;	// Nodos por visitar
	private ArrayList<ACTIONS> listaAcciones;	//Plan
	private boolean first;						//Calcular el plan si first = true
	private NodeCost endNode;					// Nodo objetivo, desde el que se calcula el camino
	private Vector2d winPos;					//Posición de la meta
	private Vector2d fescala;					// factor de escala
	private ArrayList<Observation>[][] grid;	// grid para comprobar por posiciones si estamos o no en un obstáculo
	private int index;
	private long iteraciones;
	private int maxNodos;
	
	public AgenteIDAStar(StateObservation so, ElapsedCpuTimer elapsedTimer) {
		ruta = new ArrayDeque<NodeCost>();
		listaAcciones = new ArrayList<ACTIONS>(1000);	//Damos un tamaño inicial para luego no tener que redimensionar
		
		fescala = new Vector2d(so.getWorldDimension().width/so.getObservationGrid().length,
				so.getWorldDimension().height/so.getObservationGrid()[0].length);
		
		ArrayList<Observation>[] portales = so.getPortalsPositions();	//Posicione(s) de la(s) metas
		winPos = portales[0].get(index).position;	//Importante tener en cuenta el factor de escala
		winPos.x = Math.floor(winPos.x/fescala.x);
		winPos.y = Math.floor(winPos.y/fescala.y);
		
		//Primer nodo a la posición actual
		Vector2d pos = new Vector2d ( so.getAvatarPosition().x/fescala.x, so.getAvatarPosition().y/fescala.y);
		ruta.push(new NodeCost(null, pos,  ACTIONS.ACTION_NIL, winPos, 0));
		
		first = true;
		endNode = ruta.peekFirst();
		grid = so.getObservationGrid();
		
		index = 0;
		iteraciones = 0;
		maxNodos = 0;
	}
	
	@Override
	public ACTIONS act(StateObservation stateObs, ElapsedCpuTimer elapsedTimer) {
		if (first) {	//En la primera iteración comenzamos expandiendo el nodo inicial
			
			long tInicio = System.nanoTime();
			boolean fin = IDAStar();
			
			if (fin) {	// Si llegamos a la meta
				first = false;	// Vamos del nodo solución al inicial, apuntando las acciones
				while(endNode.parent != null) {
					listaAcciones.add(endNode.lastAction);
					endNode = endNode.parent;
				}
				Collections.reverse(listaAcciones);	// Invertimos para que estén en el orden correcto
			} else {	// Si no
				//Comprobamos que no hay otra meta. Si la hay, intentamos conseguirla en la siguiente iteración
				if (index+1 < stateObs.getPortalsPositions()[0].size()) {
					System.out.println("Path not found, trying again");
					index++;
					winPos = stateObs.getPortalsPositions()[0].get(index).position;
					winPos.x = Math.floor(winPos.x/fescala.x);
					winPos.y = Math.floor(winPos.y/fescala.y);
				} else {
					first = false;
					System.out.println("Path not found");
				}
			}
			long tFin = System.nanoTime();
			
			double tmSegundos = (double)(tFin- tInicio)/(double)1000000;
			System.out.println("Tiempo en ms: " + tmSegundos);
			System.out.println("Total de nodos expandidos: " + iteraciones);
			System.out.println("Máximo de nodos en memoria: " + maxNodos);
			System.out.println("Tamaño de la ruta: " + listaAcciones.size());
		}
		if (listaAcciones.isEmpty())
			return ACTIONS.ACTION_NIL;
		else
			return listaAcciones.remove(0);
	}
	
	private boolean IDAStar() {
		int t = 0;
		
		int cota = ruta.peekFirst().getDistancia();
		
		while (t >= 0) {
			t = expand(0, cota);
			cota = t;
		}
		return t < 0;
	}
	
	private int expand(int g, int cota) {
		iteraciones++;
		
		
		endNode = ruta.peekFirst();
		maxNodos++;
		
		int f = g + endNode.getDistancia();
		
		if (f > cota)	// Si superamos la cota para esta iteración, salimos
			return f;
		
		if (endNode.equals(winPos)) { // Si el nodo que vamos a expandir es el solución, salimos 
			return -1;
		}
		
		int min = Integer.MAX_VALUE;
		
		NodeCost[] children  = endNode.generateChildren();	// Generamos los hijos
		
		Arrays.sort(children);	// Ordenamos por distancia
		
		for (int i = 0; i < children.length && min >= 0; i++) {	//Evaluamos de uno en uno
			if(!obstaculo((int)children[i].pos.x, (int)children[i].pos.y) && !ruta.contains(children[i])) {
				ruta.push(children[i]);
				int t = expand(g+1,cota);	//Antes de evaluar el siguiente, terminamos de evaluar la rama hasta la cota
				if (t >= 0) {	// Si no hemos llegado a la solución por esta rama
					if (t < min)	// Actualizamos min si hace falta
						min = t;
					ruta.pop();	// Eliminamos el nodo recién añadido de la ruta calculada
				} else
					min = t;
			}
		}
		
		if(min >= 0)
			maxNodos--;
		
		return min;
		
	}
	
	private boolean obstaculo(int x, int y) {	//Comprueba si una posición es un obstáculo
		if (x<0 || x>= grid.length || y < 0 || y >= grid[x].length) {	// Si se sale del grid, lo es
			return true;
		}
		for (Observation i : grid[x][y]) {	//Si corresponde a pinchos o muro, lo es
			if (i.itype == 0 || i.itype == 4)
				return true;
		}
		return false;	// Si no se da nada de lo anterior, no lo es
	}
}
