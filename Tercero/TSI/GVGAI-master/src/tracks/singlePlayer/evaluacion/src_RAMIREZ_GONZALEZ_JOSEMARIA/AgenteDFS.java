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
 * @brief Búsqueda en Profundidad
 *
 */
public class AgenteDFS extends AbstractPlayer {
	
	private ArrayList<SimpleNode> porVisitar;	// Nodos por visitar
	private HashMap<String, Boolean> visitados;	// Nodos ya visitados, en un map con el string de la posición como clave
	private ArrayList<ACTIONS> listaAcciones;	//Plan
	private boolean first;						//Calcular el plan si first = true
	private SimpleNode endNode;					// Nodo objetivo, desde el que se calcula el camino
	private Vector2d winPos;					//Posición de la meta
	private Vector2d fescala;					// factor de escala
	private ArrayList<Observation>[][] grid;	// grid para comprobar por posiciones si estamos o no en un obstáculo
	private int index;
	private long iteraciones;
	private int maxNodos;
	
	public AgenteDFS(StateObservation so, ElapsedCpuTimer elapsedTimer) {
		porVisitar = new ArrayList<SimpleNode>();
		visitados = new HashMap<String, Boolean>();
		listaAcciones = new ArrayList<ACTIONS>(1000);	//Damos un tamaño inicial para luego no tener que redimensionar
		
		fescala = new Vector2d(so.getWorldDimension().width/so.getObservationGrid().length,
				so.getWorldDimension().height/so.getObservationGrid()[0].length);
		
		//Primer nodo a la posición actual
		Vector2d pos = new Vector2d ( so.getAvatarPosition().x/fescala.x, so.getAvatarPosition().y/fescala.y);
		porVisitar.add(new SimpleNode(null, pos,  ACTIONS.ACTION_NIL));
		
		first = true;
		visitados.put(porVisitar.get(0).pos.toString(), true);
		endNode = porVisitar.get(0);
		grid = so.getObservationGrid();
		
		index = 0;
		iteraciones = 0;
		maxNodos = 0;
		ArrayList<Observation>[] portales = so.getPortalsPositions();	//Posicione(s) de la(s) metas
		winPos = portales[0].get(index).position;	//Importante tener en cuenta el factor de escala
		winPos.x = Math.floor(winPos.x/fescala.x);
		winPos.y = Math.floor(winPos.y/fescala.y);
	}

	@Override
	public ACTIONS act(StateObservation stateObs, ElapsedCpuTimer elapsedTimer) {
		if (first) {	//En la primera iteración comenzamos expandiendo el nodo inicial
			
			long tInicio = System.nanoTime();
			boolean fin = expand(endNode);
			
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
	
	private boolean expand(SimpleNode node) {
		iteraciones++;
		
		if (node.equals(winPos)) { // Si el nodo que vamos a expandir es el solución, salimos e igualamos endNode al mismo para reconstruir el camino
			endNode = node;
			return true;
		}
		
		SimpleNode[] children = node.generateChildren();	// Generamos los hijos
		boolean fin = false;
		for (int i = 0; i < children.length && !fin; i++) {	//Evaluamos de uno en uno
			if(!visitados.getOrDefault(children[i].pos.toString(), false) && !obstaculo((int)children[i].pos.x, (int)children[i].pos.y)) {
				maxNodos++;
				visitados.put(children[i].pos.toString(), true); // Lo marcamos como visitado
				fin = expand(children[i]);	//Antes de evaluar el siguiente, terminamos de evaluar la rama
			}
		}
		
		if (!fin)
			maxNodos--;
		
		return fin;
		
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
