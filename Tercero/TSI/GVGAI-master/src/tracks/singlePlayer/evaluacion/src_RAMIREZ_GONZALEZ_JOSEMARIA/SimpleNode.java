package tracks.singlePlayer.evaluacion.src_RAMIREZ_GONZALEZ_JOSEMARIA;

import ontology.Types.ACTIONS;
import tools.Vector2d;

public class SimpleNode {
	public SimpleNode parent;
	public ACTIONS lastAction;
	public Vector2d pos;
	
	public SimpleNode(SimpleNode parent, Vector2d pos, ACTIONS lastAction) {	//Constructor
		this.parent = parent;	//Definimos al padre del nodo
		this.lastAction = lastAction;	//La acción tomada para llegar a la posición actual
		this.pos = pos.copy();	//Actualizamos la posición, teniendo en cuenta que el punto 0,0 es la esquina superior izq
		switch (lastAction) {
		case ACTION_UP:
			this.pos.y--;
			break;
		case ACTION_DOWN:
			this.pos.y++;
			break;
		case ACTION_LEFT:
			this.pos.x--;
			break;
		case ACTION_RIGHT:
			this.pos.x++;
			break;
		default:
			break;
		}
	}
	
	public SimpleNode(Vector2d pos, ACTIONS lastAction) {	//Constructor
		this.lastAction = lastAction;	//La acción tomada para llegar a la posición actual
		this.pos = pos.copy();	//Actualizamos la posición, teniendo en cuenta que el punto 0,0 es la esquina superior izq
		switch (lastAction) {
		case ACTION_UP:
			this.pos.y--;
			break;
		case ACTION_DOWN:
			this.pos.y++;
			break;
		case ACTION_LEFT:
			this.pos.x--;
			break;
		case ACTION_RIGHT:
			this.pos.x++;
			break;
		default:
			break;
		}
	}

	public SimpleNode[] generateChildren() {	//Generamos los hijos del nodo actual
		SimpleNode[] children = new SimpleNode[4];
		children[0] = new SimpleNode(this, this.pos, ACTIONS.ACTION_UP);
		children[1] = new SimpleNode(this, this.pos, ACTIONS.ACTION_DOWN);
		children[2] = new SimpleNode(this, this.pos, ACTIONS.ACTION_LEFT);
		children[3] = new SimpleNode(this, this.pos, ACTIONS.ACTION_RIGHT);
		return children;
	}
	
	public boolean equals(Vector2d o)	// Para comparar un nodo, comparamos su posición
    {
        return this.pos.equals(o);
    }

	

}
