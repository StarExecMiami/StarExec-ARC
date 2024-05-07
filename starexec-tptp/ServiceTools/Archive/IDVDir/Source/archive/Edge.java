//*****************************************************************************
//*****************************************************************************
/* 
   Steven Trac
   Edge Class of Graph Proof Tree
*/
//*****************************************************************************
/*****
 * An Edge in the Graph
 *   Has two parts - head and head to the end (Nodes)
 *   Edges are directed, head is front and tail is the back
 *   ()-------->()
 *   tail      head
 ****/
//*****************************************************************************

public class Edge {
    //variables
    private Node tail, head;
    
    //constructors
    public Edge (Node _tail, Node _head) {
	tail = _tail; head = _head;
    }

    //methods
    public Node getHead () { return head; }
    public Node getTail () { return tail; }

    public double length () { return start.distance(end); }
    public double sqrLength() { return start.sqrDistance(end); }
}

//*****************************************************************************
//*****************************************************************************
