package tracks.singlePlayer.evaluacion.src_RAMIREZ_GONZALEZ_JOSEMARIA;

import ontology.Types.ACTIONS;
import tools.Vector2d;

public class NodeCost extends SimpleNode implements Comparable<NodeCost>{
	
	public NodeCost parent;
	private int costeAcumulado;
	private int distancia;
	private int heur;
	private Vector2d winPos;
	
	public NodeCost(NodeCost parent, Vector2d pos, ACTIONS lastAction, Vector2d winPos, int coste) {	//Constructor
		super(pos, lastAction);
		this.parent = parent;
		
		this.winPos = winPos;
		
		int diff_x = (int) Math.abs(this.pos.x - winPos.x);
		int diff_y = (int) Math.abs(this.pos.y - winPos.y);
		
		this.distancia = diff_x + diff_y;
		
		this.costeAcumulado = 1 + coste;
		
		this.heur = this.costeAcumulado + this.distancia;
		
	}
	
	public Integer getCoste() {
		return this.heur;
	}
	
	public Integer getCosteAc() {
		return this.costeAcumulado;
	}
	
	public Integer getDistancia() {
		return this.distancia;
	}
	
	
	public NodeCost[] generateChildren() {	//Generamos los hijos del nodo actual
		NodeCost[] children = new NodeCost[4];
		children[0] = new NodeCost(this, this.pos, ACTIONS.ACTION_UP, winPos, costeAcumulado);
		children[1] = new NodeCost(this, this.pos, ACTIONS.ACTION_DOWN, winPos, costeAcumulado);
		children[2] = new NodeCost(this, this.pos, ACTIONS.ACTION_LEFT, winPos, costeAcumulado);
		children[3] = new NodeCost(this, this.pos, ACTIONS.ACTION_RIGHT, winPos, costeAcumulado);
		return children;
	}
	
	@Override
    public boolean equals(Object o) {
 
        if (o == this) {
            return true;
        }
 
        if (!(o instanceof NodeCost)) {
            return false;
        }
         
        NodeCost c = (NodeCost) o;
         
        return this.pos.equals(c.pos);
    }

	@Override
	public int compareTo(NodeCost y) {
		int comparacion = this.getCoste().compareTo(y.getCoste());
		if (comparacion == 0) {
			comparacion = this.getDistancia().compareTo(y.getDistancia());
		}
		if (comparacion == 0) {
			comparacion = this.lastAction.compareTo(y.lastAction);
		}
		
		return comparacion;
	}
	
	

}
