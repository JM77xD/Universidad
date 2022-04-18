package tracks.singlePlayer.evaluacion.src_RAMIREZ_GONZALEZ_JOSEMARIA;

import core.game.Observation;
import core.game.StateObservation;
import core.player.AbstractPlayer;
import ontology.Types.ACTIONS;
import tools.ElapsedCpuTimer;
import tools.Vector2d;

import java.util.*;

/**
 * 
 * @author José María Ramírez
 * 
 * @brief Búsqueda Real-Time A*
 *
 */
public class AgenteRTAStar extends AbstractPlayer{
	
	private RTNode nextGen[];	// Nodos por visitar
	private HashMap<String, Integer> visitados;	// Nodos ya visitados, en un map con el string de la posición como clave
	private ArrayList<RTNode> sinSalida;	// Nodos sin salida
	private RTNode nodoAct;					// Nodo objetivo, desde el que se calcula el camino
	private Vector2d winPos;					//Posición de la meta
	private Vector2d fescala;					// factor de escala
	private ArrayList<Observation>[][] grid;	// grid para comprobar por posiciones si estamos o no en un obstáculo
	private int maxNodos;			// Máximo de nodos en memoria
	private static int iteraciones;	// Iteraciones totales
	private static double t;		// Tiempo acumulado
	private boolean volviendo;
	
	public AgenteRTAStar(StateObservation so, ElapsedCpuTimer elapsedTimer) {
		nextGen = new RTNode[1];
		sinSalida = new ArrayList<RTNode>();
		visitados = new HashMap<String, Integer>();	
		fescala = new Vector2d(so.getWorldDimension().width/so.getObservationGrid().length,
				so.getWorldDimension().height/so.getObservationGrid()[0].length);
		
		ArrayList<Observation>[] portales = so.getPortalsPositions();	//Posicione(s) de la(s) metas
		winPos = portales[0].get(0).position;	//Importante tener en cuenta el factor de escala
		winPos.x = Math.floor(winPos.x/fescala.x);
		winPos.y = Math.floor(winPos.y/fescala.y);
		
		
		//Primer nodo a la posición actual
		Vector2d pos = new Vector2d ( so.getAvatarPosition().x/fescala.x, so.getAvatarPosition().y/fescala.y);
		nextGen[0] = new RTNode(null, pos,  ACTIONS.ACTION_NIL, winPos, 0);
		
		visitados.put(nextGen[0].pos.toString(), nextGen[0].getDistancia());
		nodoAct = nextGen[0];
		grid = so.getObservationGrid();
		
		maxNodos = Integer.MIN_VALUE;
		iteraciones = 0;
		t= 0;
		volviendo = false;
	}
	
	public ACTIONS act(StateObservation stateObs, ElapsedCpuTimer elapsedTimer) {

		long tInicio = System.nanoTime();
		
		iteraciones++;
		
		nextGen = nodoAct.generateChildren();	// Generamos los hijos del nodo actual
		
		for (int i = 0; i < nextGen.length; i++) {
			if (visitados.containsKey(nextGen[i].pos.toString()))
				nextGen[i].actualizarDistancia(visitados.get(nextGen[i].pos.toString()));
		}
		
		Arrays.sort(nextGen);
		
		RTNode bestSon = null;
		RTNode secondBest = null;
		
		
		ArrayList<Integer> indexes = new ArrayList<Integer>();
		
		for (int i = 0; i < nextGen.length; i++) {	// Evaluamos los hijos
			if (!obstaculo(nextGen[i].pos) && !sinSalida.contains(nextGen[i])) {	// Que no sea obstáculo
				indexes.add(i);	// Guardamos aquellos índices que no sean obstáculo o sin salida en un array
			}
		}
		
		if (indexes.size() == 1) {	// Si solo tenemos un valor posible, lo cogemos independientemente de cúal sea
			sinSalida.add(nodoAct);
			bestSon = nextGen[indexes.get(0)];
			volviendo = true;
		} else if (indexes.size() > 1) {
			bestSon = nextGen[indexes.get(0)];
			secondBest = nextGen[indexes.get(1)];
			if (indexes.size() > 2 || !visitados.containsKey(bestSon.pos.toString()))
				volviendo = false;
		} else if (indexes.size() == 0)
			return ACTIONS.ACTION_NIL;
		
		if (visitados.containsKey(bestSon.pos.toString()) && volviendo ) {
			sinSalida.add(nodoAct);
		}
		
		int nuevaDist = visitados.getOrDefault(bestSon.pos.toString(), 10*bestSon.getDistancia());	// Actualizamos la distancia, con el valor según tengamos uno o dos hijos posibles
		
		if (secondBest != null)
			nuevaDist = Math.max(visitados.getOrDefault(nodoAct.pos.toString(), nodoAct.getDistancia()), visitados.getOrDefault(secondBest.pos.toString(), 10*secondBest.getDistancia()));
		else
			nuevaDist = Math.max(visitados.getOrDefault(nodoAct.pos.toString(), nodoAct.getDistancia()), visitados.getOrDefault(bestSon.pos.toString(), 10*bestSon.getDistancia()));

		visitados.put(nodoAct.pos.toString(), nuevaDist);	// ACtualizamos la distancia asociada
		
		
		nodoAct.actualizarDistancia(nuevaDist);
		
		nodoAct = bestSon;
		
		long tFin = System.nanoTime();
		
		double tmSegundos = (double)(tFin- tInicio)/(double)1000000;
		t += tmSegundos;
		
		if (sinSalida.size() + 5 > maxNodos)
			maxNodos = sinSalida.size() + 5;
		
		if (bestSon.pos.equals(winPos)) {	//Comprobamos si hemos llegado al final
			System.out.println("Tiempo en ms: " + t);
			System.out.println("Total de nodos expandidos: " + iteraciones);
			System.out.println("Máximo de nodos en memoria: " + maxNodos);
			System.out.println("Tamaño de la ruta: " + iteraciones);
		}
		
		return bestSon.lastAction;	// Devolvemos la acción
		
	}
	
	private boolean obstaculo(Vector2d pos) {	//Comprueba si una posición es un obstáculo
		if (pos.x<0 || pos.x>= grid.length || pos.y < 0 || pos.y >= grid[(int)pos.x].length) {	// Si se sale del grid, lo es
			return true;
		}
		
		for (Observation i : grid[(int)pos.x][(int)pos.y]) {	//Si corresponde a pinchos o muro, lo es
			if (i.itype == 0 || i.itype == 4)
				return true;
		}
		return false;	// Si no se da nada de lo anterior, no lo es
	}
	
	
	

}
