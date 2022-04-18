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
 * @brief Búsqueda A*
 *
 */
public class AgenteAStar extends AbstractPlayer{
	private PriorityQueue<NodeCost> porVisitar;	// Nodos por visitar
	private HashMap<String, Integer> visitados;	// Nodos ya visitados, en un map con el string de la posición como clave
	private ArrayList<ACTIONS> listaAcciones;	//Plan
	private boolean first;						//Calcular el plan si first = true
	private NodeCost endNode;					// Nodo objetivo, desde el que se calcula el camino
	private Vector2d winPos;					//Posición de la meta
	private Vector2d fescala;					// factor de escala
	private ArrayList<Observation>[][] grid;	// grid para comprobar por posiciones si estamos o no en un obstáculo
	private int index;
	private int maxNodos;
	
	public AgenteAStar(StateObservation so, ElapsedCpuTimer elapsedTimer) {	//Inicializamos las variables
		porVisitar = new PriorityQueue<NodeCost>();
		visitados = new HashMap<String, Integer>();
		listaAcciones = new ArrayList<ACTIONS>(1000);	//Damos un tamaño inicial para luego no tener que redimensionar
		
		fescala = new Vector2d(so.getWorldDimension().width/so.getObservationGrid().length,
				so.getWorldDimension().height/so.getObservationGrid()[0].length);
		
		ArrayList<Observation>[] portales = so.getPortalsPositions();	//Posicione(s) de la(s) metas
		winPos = portales[0].get(index).position;	//Importante tener en cuenta el factor de escala
		winPos.x = Math.floor(winPos.x/fescala.x);
		winPos.y = Math.floor(winPos.y/fescala.y);
		
		
		//Primer nodo a la posición actual
		Vector2d pos = new Vector2d ( so.getAvatarPosition().x/fescala.x, so.getAvatarPosition().y/fescala.y);
		porVisitar.add(new NodeCost(null, pos,  ACTIONS.ACTION_NIL, winPos, 0));
		
		first = true;
		visitados.put(porVisitar.peek().pos.toString(), porVisitar.peek().getCoste());
		endNode = porVisitar.peek();
		grid = so.getObservationGrid();
		
		index = 0;
		maxNodos = porVisitar.size();
	}

	@Override
	public ACTIONS act(StateObservation stateObs, ElapsedCpuTimer elapsedTimer) {
		if (first) {	//Si es la primera iteración, calculamos el plan
			
			long tInicio = System.nanoTime();
			long iteraciones = findGoal();
			
			
			if (endNode.equals(winPos)) {	//Si hemos finalizado correctamente
				first = false;
				while(endNode.parent != null) {	// Vamos del nodo solución al inicial, apuntando las acciones
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
		if (listaAcciones.isEmpty())	//Si no hay acciones, realizamos NIL por defecto
			return ACTIONS.ACTION_NIL;
		else
			return listaAcciones.remove(0);
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
	
	private long findGoal() {
		long iteraciones = 0;
		NodeCost[] children;
		
		while(!porVisitar.isEmpty() && !endNode.equals(winPos)) {	//Hasta que estemos en la meta o no podamos seguir explorando
			iteraciones++;
			endNode = porVisitar.remove();	//Miramos el primer nodo disponible
			children = endNode.generateChildren();	//Generamos sus hijos
			
			// Por cada hijo, comprobamos que no se encuentre en un obstáculo y que no lo hayamos introducido ya, para no comprobarlo dos veces
			for (int i = 0; i < children.length; i++) {
				if (!obstaculo((int)children[i].pos.x, (int)children[i].pos.y) && visitados.getOrDefault(children[i].pos.toString(), Integer.MAX_VALUE) > children[i].getCoste()) {
					porVisitar.add(children[i]);	//Lo añadimos tanto a pendientes de visitar como a visitados, para asegurar que no lo volvemos a añadir
					visitados.put(children[i].pos.toString(), children[i].getCoste());
				}
			}
			
			
			if (porVisitar.size()+visitados.size() > maxNodos)
				maxNodos = porVisitar.size()+visitados.size();
			
		}
		
		return iteraciones;
	}
}
