// Christian Duncan
// Graph Class
//    for GD2004, Graph Drawing Contest

// package GD4;

import java.util.*;

/*********************
 * SparseGraph Class
 *    Represents a SparseGraph
 *    Stored as an adjacency list (in one form anyway)
 *       Slower look up for edges but more space efficient
 *       than adjacency matrix 
 *    Here we store a Vector of SparseNodes
 *       Each SparseNode in turn stores a Vector of Edges
 *             (along with its X,Y position)
 *       Each Edge stores the two Nodes incident to it.
 *       Edges should be present in BOTH Node lists
 *********************/
public class SparseGraph extends Graph {
    private Vector node;   // Vector of Nodes

    public SparseGraph() {
	node = new Vector();
    }

    // Add a node specifying its x and y locations
    public void addNode(double x, double y) {
	int index = node.size();
	SparseNode n = new SparseNode(index, x, y);
	node.add(n);
    }

    // Add an edge between two Nodes (referenced by index)
    //    Returns true if successful and false otherwise
    public boolean addEdge(int a, int b) {
	// Verify that indices exist
	if (a < 0 || b < 0) {
	    // Too low
	    System.err.println("Error: Index too low!");
	    return false;
	} else if (a >= node.size() || b >= node.size()) {
	    // Too high
	    System.err.println("Error: Index too high!");
	    return false;
	}

	SparseNode na = (SparseNode) node.elementAt(a);
	SparseNode nb = (SparseNode) node.elementAt(b);

	na.addEdge(nb);  // Add edge from na to nb (and vice-versa)
	return true;     // Successfully added
    }

    // Get list of all nodes
    public Iterator nodeIterator() {
	return node.iterator();
    }

    // Get list of ALL edges
    public Iterator edgeIterator() {
	System.err.println("DEBUG: Warning, not yet implemented!");
	return null;
    }

    public int numNodes() { return node.size(); }
    public int numEdges() {
	System.err.println("DEBUG: Warning, not yet implemented!");
	// Warning MUCH SLOWER BECAUSE DON'T KEEP TRACK!
	return 0;
    }
}
