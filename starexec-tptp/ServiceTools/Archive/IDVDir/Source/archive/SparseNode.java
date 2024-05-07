// Christian Duncan
// SparseNode Class
//    for GD2004, Graph Drawing Contest

// package GD4;

import java.util.Vector;
import java.util.Iterator;

/*********************
 * A Node in the Graph
 *    Stores:
 *       id - integer index into Graph Vector list (currently irrelevant!)
 *       X, Y - double location coordinates
 *       Vector (of Edges) - edges extending from this graph
 *                           will thus include duplicates (two per edge)
 *********************/
public class SparseNode extends Node {
    private Vector edge;  // Vector of Edges

    public SparseNode(int _id, double _x, double _y) {
	super(_id, _x, _y);
	edge = new Vector(2);
    }

    /* Accessor methods for edges */
    public Iterator iterator() { return edge.iterator(); }  // List of edges

    void addEdge(Node other) {
	// Create NEW Edge and add it to both
	//    this and other edge lists
	if (other instanceof SparseNode == false) {
	    throw new RuntimeException("Error: SparseNode.addEdge(other): " +
				       "other MUST be instanceof SparseNode"); 
	}
	SparseNode o = (SparseNode) other;
	Edge e = new Edge(this, o);
	this.edge.add(e); 
	o.edge.add(e);
    }
}
