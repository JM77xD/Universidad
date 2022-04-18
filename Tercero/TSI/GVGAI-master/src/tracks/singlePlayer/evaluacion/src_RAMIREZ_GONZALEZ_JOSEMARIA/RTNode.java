package tracks.singlePlayer.evaluacion.src_RAMIREZ_GONZALEZ_JOSEMARIA;


import ontology.Types.ACTIONS;
import tools.Vector2d;

public class RTNode extends SimpleNode implements Comparable<RTNode>{
	
	private Vector2d winPos;
	private int distancia;
	public static final int costeMov = 1;
	private int coste;
	
	
	public RTNode(RTNode parent, Vector2d pos, ACTIONS lastAction, Vector2d winPos, int coste) {	//Constructor
		super(pos, lastAction);
		this.parent = parent;
		
		this.winPos = winPos;
		
		int diff_x = (int) Math.abs(this.pos.x - winPos.x);
		int diff_y = (int) Math.abs(this.pos.y - winPos.y);
		
		this.coste = coste;
		this.distancia =coste + diff_x + diff_y;
		this.coste++;
	}
	
	
	public RTNode[] generateChildren() {	//Generamos los hijos del nodo actual
		RTNode[] children = new RTNode[4];
		children[0] = new RTNode(this, this.pos, ACTIONS.ACTION_UP, winPos, coste);
		children[1] = new RTNode(this, this.pos, ACTIONS.ACTION_DOWN, winPos, coste);
		children[2] = new RTNode(this, this.pos, ACTIONS.ACTION_LEFT, winPos, coste);
		children[3] = new RTNode(this, this.pos, ACTIONS.ACTION_RIGHT, winPos, coste);
		return children;
	}
	
	
	public Integer getDistancia() {
		return this.distancia;
	}
	
	public void actualizarDistancia(int distancia) {
		this.distancia = distancia;
	}
	
	@Override
    public boolean equals(Object o) {	// Igualdad, usado para los .contains(RTNode)
 
        if (o == this) {
            return true;
        }
        
        if (!(o instanceof RTNode)) {
            return false;
        }
         
        RTNode c = (RTNode) o;
         
        return this.pos.equals(c.pos);
    }
	
	@Override
	public int compareTo(RTNode y) {
		int comparacion = this.getDistancia().compareTo(y.getDistancia());

		if (comparacion == 0) {
			comparacion = this.lastAction.compareTo(y.lastAction);
		}
		
		return comparacion;
	}
	
	
}
