//*****************************************************************************
//*****************************************************************************
/*
  Steven Trac
  Node Class of Graph Proof Tree
*/
//*****************************************************************************
/****
 * A Node in the Graph
 *   Abstract Class
 *   Stores:
 *     X, Y - double location coordinates
 * Note: stores formula in the future
 ****/
//*****************************************************************************
import java.util.Vector;
import java.util.Iterator;
//*****************************************************************************

public abstract class Node {
    //variables
    protected double x, y;
    protected boolean pinState = false; // True if "pinned down"

    //constructors
    public Node (double _x, double _y) { x = _x; y = _y; }
    
    public Node (Node that) { 
	x = that.x; y = that.y; 
	pinState = other.pinState;
    }

    
    //methods
    public double getX () { return x; }
    public double getY () { return y; }
    public abstract Iterator iterator(); //return iterator of incident edges
    public boolean isPinned () { return pinState; }

    public void setX (double _x) { x = _x; }
    public void setY (double _y) { x = _y; }
    public void flipPinState () { pinState = !pinState; }
    public void setPinned (boolean newState) { pinState = newState; }

    abstract void addEdge (Node that); //add an edge to the list of edges
    
    public double distance (Node that) {
	return Math.sqrt(sqrDistance(that));
    }

    public double sqrDistance (Node that) {
	double dx = that.x - this.x;
	double dy = that.y - this.y;
	return dx * dx + dy * dy;
    }

}

//*****************************************************************************
//*****************************************************************************

