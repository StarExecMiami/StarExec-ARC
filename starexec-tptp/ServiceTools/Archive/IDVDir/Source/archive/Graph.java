//*****************************************************************************
//*****************************************************************************
/* 
   Steven Trac
   Graph Class of Graph Proof Tree
*/
//*****************************************************************************
/*****
 * Graph Abstract Class
 *   Represents a graph
 ****/
//*****************************************************************************
import java.util.*;
import java.awt.Rectangle;
//*****************************************************************************

public abstract class Graph {
    //variables
    protected Rectangle bnds;
    private Node selectedNode;

    //constructors
    public Graph () { selectedNode = null; bnds = null; }
    
    //methods
    
    //make a full new copy of this graph
    public Graph deepClone () throws CloneNotSupportedException {
	throw new CloneNotSupportedExeception("No clone supported");
    }

    //add a node specifying its x and y locations
    public abstract void addNode (double x, double y);

    //add an edge between two nodes (referenced by index)
    //public abstract boolean addEdge(int a, int b);

    //get list of all nodes (iterator of nodes)
    public abstract Iterator nodeIterator();

    //get list of all edges (iterator of edges)
    public abstract Iterator edgeIterator();

    public abstract int numNodes();
    public abstract int numEdges();

}

//*****************************************************************************
//*****************************************************************************

