//*****************************************************************************
//*****************************************************************************
/* 
   Steven Trac
   Graph Proof Tree
*/
//*****************************************************************************
/*****
 * Graph Proof Tree Main
 * Build on to DenseGraph by Dr. Christian Duncan
 * Proof graph has a Formula f in each proof node
 ****/
//*****************************************************************************
import java.util.*;
import java.io.*;
import java.awt.event.*;
import javax.swing.event.*;
import javax.swing.*;
//*****************************************************************************
/*********************
 * ProofGraph Class
 *    Represents an (Editable) Graph stored as an adjacency matrix
 *    Most ideal for dense graphs or speedy edge existence queries
 *    (Might change to follow sparse graph 
 *********************/
public class ProofGraph extends Graph {
  private ProofNode node[];       // Info about all the Nodes
  private int nN;                 // Number of Nodes
  private int nE;                 // Number of Edges
  private boolean edge[][];       // The adjacency Matrix
  public  int nR;                 // Number of Ranks in Nodes
  private Vector root;            // Vector of Roots of Proof Tree

  private Vector formula;         // Vector of all formulas from ProofReader
  private Hashtable ftable;       // Hash table on formula names to vector locs
  GraphPanel panel;

  public int maxRow;
  public Vector rank[];
  public IDV idv;
  /*  
  public ProofGraph(int n) {
    edge = new boolean[n][n];   // The whole matrix
    nN = nE = nR = 0;           // None stored yet though
    node = new ProofNode[n];    // All the nodes

    System.out.println("Matrix size set to: " + n);
  }
  */

  public ProofGraph (Vector _formula, Hashtable _ftable, IDV _idv) {
    //set ProofGraph variables
    formula = _formula;
    ftable  = _ftable;    
    panel   = _idv.gridScreen;
    idv     = _idv;
    
    //SHOW FORMULA
    Vector parent;
    System.out.println("Formulas: ");
    System.out.println("**********************");
    for (int i = 0; i < formula.size(); i++) {
      Formula f = (Formula)formula.elementAt(i);
      System.out.print("i: " + i + ": " + f.getName());
      parent = f.getParents();
      for (int j = 0; j < parent.size(); j++) {
        System.out.print(" " + parent.elementAt(j).toString());
      }
      System.out.print(" [");
      for (int j = 0; j < parent.size(); j++) {
        Integer loc = (Integer)ftable.get((parent.elementAt(j)).toString());
        System.out.print(" " + loc);
        //Formula pf = (Formula)formula.elementAt(loc.intValue());
        //System.out.print("<" + pf.getDepth() + ">");
      }
      System.out.println(" ]");
    }

    //set depths and count number of nodes
    setDepths();
    countNodes();

    //add nodes and edges
    addNodes();
    addEdges();
    
    //find all roots
    setRoot();

    //fix orderings and set coordinates
    Order order = ordering();
    maxRow = order.getMaxRow();
    /*
    rank = new Vector[nR];
    for (i = 0; i < nR; i++) {
      rank[i] = order.getRank(i);
    }
    */
    rank = order.getRank();
    setCoordinates(order);
    
    //show graph
    //show();
  }

  private ProofGraph() {
    edge = null; nN = nE = 0; node = null;
  }
 
  /* Constructor Helper Methods */
  private void setDepths () {
    for (int i = 0; i < formula.size(); i++) {
      Formula f = (Formula)formula.elementAt(i);
      f.dfsDepth();
      System.out.println("i: " + i + ") " + f.getName() + " +++ d: " + f.getDepth());
    }
  }
  private void countNodes () {
    Vector parent;
    int count = 0;
    for (int i = 0; i < formula.size(); i++) {
      Formula f = (Formula)formula.elementAt(i);
      parent = f.getParents();
      int current_depth = f.getDepth();
      for (int j = 0; j < parent.size(); j++) {
        Integer loc = (Integer)ftable.get((parent.elementAt(j)).toString());
        Formula pf = (Formula)formula.elementAt(loc.intValue());
        count += current_depth - pf.getDepth() - 1;
      }
    }
    System.out.println("Count: " + count);
    int n = formula.size() + count;
    edge = new boolean[n][n];   // The whole matrix
    nN = nE = nR = 0;           // None stored yet though
    node = new ProofNode[n];    // All the nodes    
  }
  private void addNodes () {
    for (int i = 0; i < formula.size(); i++) {
      Formula f = (Formula)formula.elementAt(i);
      addNode(f);
    }
  }
  private void addEdges () {
    Vector parent;
    for (int i = 0; i < formula.size(); i++) {
      Formula f = (Formula)formula.elementAt(i);
      parent = f.getParents();
      //add edge(parent,child), direction(parent -> child)
      for (int j = 0; j < parent.size(); j++) {
        Integer loc = (Integer)ftable.get((parent.elementAt(j)).toString());
        //this will add end edge(a,b) from b -> a
        addEdge(loc.intValue(),i);
      }
    }
  }

  /*
  // Override the Graph clone method to make perfect clone
  public Graph deepClone() {
    ProofGraph copy = new ProofGraph();
    int i, j;
    int n = this.node.length;
    
    copy.edge = new boolean[n][n];
    copy.nN = this.nN;
    copy.nE = this.nE;
    copy.node = new ProofNode[n];
    
    // Copy the edges
    for (i = 0; i < n; i++)
      for (j = 0; j < n; j++)
        copy.edge[i][j] = this.edge[i][j];
    
    // Copy the nodes
    for (i = 0; i < n; i++) {
      Node thisNode = this.node[i];
      copy.node[i] = new ProofNode(this.node[i], copy);
    }
    return copy;
  }
  */
  
  // Add a node specifying its x and y locations
  public void addNode(double x, double y) {}
    /*
    if (nN >= node.length) {
      // Too many!
      throw new RuntimeException("Programming Error: Too many nodes!");
    }
    node[nN] = new ProofNode(nN, x, y, this);
    nN++;
    */
  //  }
  

  public void addNode (Formula f) {
    if (nN >= node.length) {
      // Too many!
      throw new RuntimeException("Programming Error: Too many nodes!");
    }
    node[nN] = new ProofNode(nN, f, this);
    //    int rank = node[nN].getRank();
    //if (rank > nR) { nR = rank; }
    //System.out.println("Added node with rank: " + rank);
    //System.out.println("Max Rank is: " + nR);
    nN++;
  }

  /*
  // Set proof to node
  public void setFormula (Formula f, int i) { 
    node[i].setProof(f);
  }

  public Node copyNode (Node _n) {
    ProofNode n = new ProofNode(_n, this);
    return n;
  }
  */
  
  // Add an edge between two Nodes (referenced by index)
  //    Returns true if successful and false otherwise
  //add Edge(parent, child)
  public boolean addEdge(int a, int b) {

    //separately
    if (a < 0 || b < 0) {
      // Too low
      System.err.println("Error: Index too low! a: " + a + ", b: " + b);
      return false;
    } else if (a >= nN || b >= nN) {
      // Too high
      System.err.println("Error: Index too high! a: " + a + ", b: " + b + ", nN: " + nN);
      return false;
    }

    //if rank of (a - b) > 1, split into diff edges, and add each
    if ((node[b].rank - node[a].rank) > 1) {
      //split 
      /*
        a.r1 v.r2 v.r3 ... b.rn
      */
      System.out.println("a rank: " + node[a].rank);
      System.out.println("b rank: " + node[b].rank);
      int max = node[b].rank; //8
      int min = node[a].rank; //1
      int size = max - min;   //7
      int start = nN;
      for (int i = 0; i < size - 1; i++) {
        int rank = (max - i) - 1;
        node[nN] = new ProofNode(nN, rank, this); //virtual nodes
        System.out.println("Added virtual node with rank: " + rank);
        nN++;
      }

      /*
        connect nodes with edges
        a - > start;
        start ... -> ... nN;
        nN -> b;
      */

      //do first section
      //System.out.println("First Section start: " + start + ", b: " + b);
      addEdge(start, b);
      
      //do middle sections
      for (int i = start; i < nN - 1; i++) {
        //System.out.println("Midde Section i+1: " + (i + 1) + ", i: " + i);
        addEdge(i+1, i);
      }

      //do last section
      //System.out.println("Last Section a: " + a + ", nN: " + nN);
      addEdge(a, nN - 1);

    }
    else {
      //only create edge from b to a, direction edges
      //edge[a][b] = true;
      //System.out.println("a: " + a + "b: " + b + " " + edge[a][b]);
      edge[b][a] = true; //removing this kills edges (investigate)
      nE++;
    }
    return true;
  }
  
  // Get list of all nodes (Iterator of Nodes)
  public Iterator nodeIterator() {
    return new ProofGraphNodeIterator(this);
  }
  
  // Get list of ALL edges (Iterator of Edges)
  public Iterator edgeIterator() {
	return new ProofGraphEdgeIterator(this);
  }

  
  /*           X
       1 2 3 4 5 6 7 8 9
     1
     2
     3
     4
   Y 5
     6
     7
     8
     9               T
     edge[8][9] = true, meaning node 8 connects to node 9

  */
  public void show () {
    System.out.println("Edges");
    for (int i = 0; i < nN; i++) {
      for (int j = 0; j < nN; j++) {
        if (edge[i][j])
          System.out.println("i: " + i + ", j: " + j + " = " + edge[i][j]);
      }
    }
    System.out.println("Roots:");
    for (int i = 0; i < root.size(); i++) {
      System.out.println("root: " + root.elementAt(i));
    }
  }
  
  public int numNodes() { return nN; }
  public int numEdges() { return nE; }

  public void setRoot () {
    //if edge[a][b] = false for all a, then b is a root
    root = new Vector();
    System.out.println("Set roots");
    for (int j = 0; j < nN; j++) {
      boolean notroot = false;
      for (int i = 0; i < nN; i++) {
        notroot = notroot || edge[i][j];
        //System.out.println("i: " + i + ", j: " + j);
      }
      if (!notroot) {
        //this is a root node
        root.add(new Integer(j));
        System.out.println("this is a root: " + j);
      }
    }
    System.out.println("Set roots end");
    for (int i = 0; i < root.size(); i++) {
      int loc = ((Integer)root.elementAt(i)).intValue();
      int rank = node[loc].getRank();
      if (rank > nR) { nR = rank; }
      System.out.println("Added node with rank: " + rank);
      System.out.println("Max Rank is: " + nR);
    }
    nR++;
  }
  
  /*
    ordering () {
        order = init_order;
        best_order = order;
        for i = 0 to max_iterations 
          wmedian(order,i);
          transpose(order);
          if crossing(order) < crossing(best)
            best = order;
        return best;
  */
  public Order ordering () {
    //show();
    Order order = new Order(this);
    Order best = new Order(order);
    int max = 10;
    for (int i = 0; i < max; i++) {
      order.wmedian(i);
      order.transpose(i);
      if (order.crossing() < best.crossing()) {
        best = new Order(order);
        System.out.println("got new best");
      }
    } 
    return best;
  }


    /*
  



      
    */
  

  public void setCoordinates (Order order) {
    //use order to determine coordinates
    for (int i = 0 ; i < nR; i++) {
      for (int j = 0; j < order.rank[i].size(); j++) {
        int n = ((Integer)order.rank[i].elementAt(j)).intValue();
        node[n].x = (j * 100);
        node[n].y = (i * 100);
        if (!node[n].virtual)
          node[n].initPolygon();
        System.out.println("Setting n: " + n + " to x: " + node[n].x + ", y: " + node[n].y + ", depth: " + node[n].rank);
      }
    }

    /*
    Random generator = new Random();
    //give all nodes temp x,y
    for (int i = 0; i < nN; i++) {
      node[i].setY(100 * node[i].rank);
      node[i].setX(generator.nextDouble() * 500);
    }
    */
  }
  
  
  /**********************************************************
   * This is a private class associated with ProofGraphs
   * ProofGraphNodeIterator -
   *     returns an iterator of the nodes in the given graph
   **********************************************************/
  private class ProofGraphNodeIterator implements Iterator {
    ProofGraph g;   // The current Graph to iterate on
    int n;          // Which node are we currently on
    
    public ProofGraphNodeIterator(ProofGraph _g) {
      g = _g; n = 0;
    }
    
    public boolean hasNext() { return (n < g.numNodes()); }
    
    public Object next() {
      if (n < g.numNodes()) {
        return node[n++]; // Return node n and THEN increment n
      } 
      else return null;     // No more elements!
    }
    
    public void remove() { /* Not implemented */ }
  }
  
  /**********************************************************
   * This is a private class associated with ProofGraphs
   * ProofGraphEdgeIterator -
   *     returns an iterator of the entire edges in the given graph
   * 
   *     Algorithm works as follows:
   *        nA,nB represents location in adj. matrix
   *                         between nodes nA and nB
   *        hasNext(): if mat[nA][nB] is an edge
   *                   then return true
   *                   otherwise find next edge (or set nA, nB to LARGE)
   *                              and return true/false
   *                   search only nB <= nA edges
   *                        This is the lower triangle
   *        next(): calls hasNext() first.
   *                if no - return null
   *                else nA,nB points to current one - then do advance()
   *        advance(): moves nB++ or nA++ (nB=0) and so on...
   **********************************************************/
  private class ProofGraphEdgeIterator implements Iterator {
    ProofGraph g;   // The current Graph to iterate on
    int nA;          // Which start node are we currently on
    int nB;          // Which end node are we currently on
    
    // Iterate edges over entire graph
    public ProofGraphEdgeIterator(ProofGraph _g) {
      g = _g; nA = nB = 0;
    }
    
    public boolean hasNext() { 
      // Skip until either end or found an edge
      while (nA < g.numNodes() && g.edge[nA][nB] == false) {
        //        System.out.println("nA: " + nA + ", nB: " + nB + ", numNodes: " + g.numNodes() + ", numEdges " + g.numEdges() + ", " +  g.edge[nA][nB]);
        advance();  // Keep going until find empty edge
      }
      
      return (nA < g.numNodes()); // Found edge or not
    }
    
    public Object next() {
      if (hasNext() == false) return null;
      
      // Create a new Edge object between the two nodes
      //Edge response = new Edge(g.node[nB], g.node[nA]);
      Edge response = new Edge(g.node[nA], g.node[nB]);
      advance();      // Skip this edge - hasNext advances next time
      return response;
    }
    
    public void remove() { /* Not implemented */ }
    
    // Advance to next potential pair (in lower triangle)
    private void advance() {
      nB++;
      if (nB >= g.numNodes()) {
      //if (nB > nA) {
        // Passed lower triangle (next row)
        nA++;
        nB=0;
      }
    }
  }
  


  /*********************
   * A ProofNode in the Graph
   *    Stores:
   *       id - integer index into Graph Vector list (currently irrelevant!)
   *       X, Y - double location coordinates
   *       reference to the ProofGraph
   *       f is the proof for the proof tree
   *********************/
  private class ProofNode extends Node {

    ProofGraph g;
    Formula f;
    int rank;
    /*
    public ProofNode(int _id, double _x, double _y, ProofGraph _g) {
      super(_id, _x, _y);
      g = _g;
      f = null;
    }
    
    public ProofNode(Node other, ProofGraph _g) {
      super(other); g = _g;
    }
    */

    // non virtual node constructor
    public ProofNode (int _id, Formula _f, ProofGraph _g) {
      //boolean virtual = false;
      super(_id, _f.getDepth(), false, _g);
      f = _f;
      g = _g;
    }

    // virtual node constructor
    public ProofNode (int _id, int _rank, ProofGraph _g) {
      //boolean virtual = true;
      super(_id, _rank, true, _g);
      f = null;
      g = _g;
    }
    
    /* Accessor methods */
    // Return iterator of incident edges
    public Iterator iterator() {
      return new ProofGraphNodeEdgeIterator(g, id);
    }
    
    /* Add an edge to the list of edges
     */
    int getDepth () { return f.getDepth(); }
    //void setProof (Formula _f) { f = _f; }
    
    void addEdge(Node other) {
      // Create NEW Edge and add it to both
      //    this and other edge lists
      if (other instanceof ProofNode == false) {
        throw new RuntimeException("Error: ProofNode.addEdge(other): " +
                                   "other MUST be instanceof ProofNode"); 
      }
      ProofNode o = (ProofNode) other;
      if (this.g != o.g) {
        throw new RuntimeException("Error: ProofNode.addEdge(other): " +
                                   "other MUST be in same graph as this node"); 
      }		
      g.addEdge(this.id, o.id);
    }

    
    //makes it impossible to set gravity node y axis
    public void setY (double _y) {
      /*  
      if (f.getDepth() == 0) { return; }
      else {
        y = _y;
      }
      */
    }
    /*    
    public void setX (double _x) {
      if (f != null && f.getDepth() == 0) { return; }
      else x = _x;
    }
    */

    public String getName () { 
      return (f == null) ? "V" + id : f.getName(); 
    }

    public Formula getFormula () {
      return f;
    }
  }
    
  
  /**********************************************************
   * This is a private class associated with ProofGraphs
   * ProofGraphNodeEdgeIterator -
   *     returns an iterator of the edges in the given graph's node
   * 
   *     Algorithm works as follows:
   *        nA,nB represents location in adj. matrix
   *                         between nodes nA and nB
   *        hasNext(): if mat[nA][nB] is an edge
   *                   then return true
   *                   otherwise find next edge (if exists)
   *                              and return true/false
   *        next(): calls hasNext() first.
   *                if no - return null
   *                else nA,nB points to current one - then do advance()
   **********************************************************/
  private class ProofGraphNodeEdgeIterator implements Iterator {
    ProofGraph g;   // The current Graph to iterate on
    int nA;          // Which start node are we using...
    int nB;          // Which end node are we currently on
    
    // Iterate edges over entire graph
    public ProofGraphNodeEdgeIterator(ProofGraph _g, int _node) {
      g = _g; nA = _node; nB = 0;
    }
    
    public boolean hasNext() { 
      // Skip until either end or found an edge
      while (nB < g.numNodes() && g.edge[nA][nB] == false) {
        nB++;
      }
      
      return (nB < g.numNodes()); // Found edge or not
    }
    
    public Object next() {
      if (hasNext() == false) return null;
      
      // Create a new Edge object between the two nodes
      //Edge response = new Edge(g.node[nA], g.node[nB]);
      Edge response = new Edge(g.node[nA], g.node[nB]);
      nB++;
      return response;
    }
    
    public void remove() { /* Not implemented */ }
  }


  /*
    This class places all nodes of the same rank in the same
    vector
    so you have an array of vector of nodes
  */
  private class Order {
    Vector rank[];
    ProofGraph g;

    public Order (ProofGraph _g) {
      g = _g;
      rank = new Vector[g.nR];
      for (int i = 0; i < g.nR; i++) rank[i] = new Vector();
      //System.out.println("Set ranks");
      //do DFS on nodes starting from root
      //If in same rank and not in vector, add it to rank 
      for (int i = 0; i < g.root.size(); i++) {
        //        System.out.println("i: " + i);
        setRank(((Integer)g.root.elementAt(i)).intValue());
      }
      //show();
    }
    public Order (Order order) {
      g = order.g;
      rank = new Vector[g.nR];
      for (int i = 0; i < g.nR; i++) {
        rank[i] = new Vector(order.rank[i]);
      }
    }
    
    public Vector[] getRank () {
      return rank;
    }

    public int getMaxRow () {
      int max = 0;
      for (int i = 1; i < g.nR; i++) {
        if (rank[i].size() > rank[max].size())
          max = i;
      }
      return rank[max].size();
    }

    private void setRank (int n) {
      //add f to a rank if its not there
      int loc = g.node[n].rank;
      Integer nn = new Integer(n);
      if (!rank[loc].contains(nn)) {
        rank[loc].add(nn);
        //recurse to parents since just added
        Iterator itr = node[n].iterator();
        while (itr.hasNext()) {
          Edge e = (Edge)itr.next();
          // Find the node that is other end of this edge
          //   It should be the endNode but no guarantee (as per interface rule)
          Node other = e.getEndNode();
          if (other.equals(node[n])) {
            // Other is the Start Node (not typical but possible)
            other = e.getStartNode();
          }
          setRank(other.getId());          
        }
      }
    }


    /*    
     * wmedian(order,iter)
     *   if iter mod 2 == 0 then
     *     for r = 1 to max_rank
     *       for v in order[r] do
     *         median[v] = median_value(v,r-1);
     *       sort(order[r],median);
     *   else
     *     ...
     */
    public void wmedian (int i) {
      //System.out.println("WMEDIAN");
      if (i%2 == 0) {
        //traverse ranks bottom to top
        //System.out.println("traversing from bottom to top");
        for (int r = 1; r < g.nR; r++) {
          //System.out.println("wmedian at rank: " + r);
          Vector median = new Vector();
          for (int v = 0; v < rank[r].size(); v++) {
            median.add(new Double(median_value(v, r, -1)));
          }
          sort(r, median);
        }
      }
      else {
        //traverse ranks top to bottom
        //System.out.println("traversing top to bottom");
        for (int r = g.nR - 2; r > -1; r--) {  
          //System.out.println("wmedian at rank: " + r);
          Vector median = new Vector();
          for (int v = 0; v < rank[r].size(); v++) {
            median.add(new Double(median_value(v, r, 1)));
          }
          sort(r, median);
        }
      }
    }

    /*
     * median_value(v,adj_rank)
     *   P = adj_position(v,adj_rank);
     *   m = |P| / 2;
     *   if |P| = 0 then
     *     return -1.0;
     *   elseif |P| mod 2 == 1 then
     *     return P[m];
     *   elseif |P| = 2 then
     *     return (P[0] + P[1]) / 2;
     *   else
     *     left = P[m-1] - P[0];
     *     right = P[|P|-1] - P[m];
     *     return (P[m-1]*right + P[m]*left) / (left+right);
     */
    private double median_value(int v, int this_rank, int adj) {
      Vector P = adj_position(v, this_rank, adj);
      int n = P.size();
      int m = n / 2;
      //System.out.println("psize: " + n + ", m: " + m);
      if (n == 0) {
        return -1.0;
      }
      else if (n % 2 == 1) {
        return ((Double)P.elementAt(m)).doubleValue();
      }
      else if (n == 2) {
        return (((Double)P.elementAt(0)).doubleValue() + 
                ((Double)P.elementAt(1)).doubleValue()) / 2.0;
      }
      else {
        double left = ((Double)P.elementAt(m-1)).doubleValue() - 
          ((Double)P.elementAt(0)).doubleValue();
        double right = ((Double)P.elementAt(P.size()-1)).doubleValue() - 
          ((Double)P.elementAt(m)).doubleValue();
        return (((Double)P.elementAt(m-1)).doubleValue() * right + 
                ((Double)P.elementAt(m)).doubleValue() * left) / (left + right);
      }
    }
    private Vector adj_position (int v, int this_rank, int adj) {
      //return vector of all adj positions in adj_rank
      Vector P = new Vector();
      int adj_rank = this_rank + adj;
      //System.out.println("adj rank: " + adj_rank);
      int b = ((Integer)rank[this_rank].elementAt(v)).intValue();
      for (int i = 0; i < rank[adj_rank].size(); i++) {
        int a = ((Integer)rank[adj_rank].elementAt(i)).intValue();
        if (adj == -1) {
          //System.out.println("checking adj between b: " + b + ", a: " + a);
          //adj rank is rank below
           if (g.edge[b][a]) {
             P.add(new Double(i));
             //System.out.println("added to P");
           }
        }
        else {
          //System.out.println("checking adj between a: " + a + ", b: " + b);
          //adj rank is rank above
          if (g.edge[a][b]) {
            P.add(new Double(i));
            //System.out.println("added to P");
          }
        }
      }
      //System.out.println("Finish find adj, psize: " + P.size());
      return P;
    }
    private void sort (int r, Vector median) {
      //rank r is the node indices
      //median is the rank r median values
      //System.out.println("r size: " + rank[r].size() + ", med size: " + median.size());
      //System.out.println("elements in rank before");
      //for (int i = 0; i < rank[r].size(); i++) {
        //System.out.println("i: " + i + ", : " + rank[r].elementAt(i));
      //}
      //System.out.println("elements in median before");
      //for (int i = 0; i < median.size(); i++) {
      //  System.out.println("i: " + i + ", : " + median.elementAt(i));
      //}
      for (int i = 0; i < rank[r].size() - 1; i++) {
        if (((Double)median.elementAt(i)).doubleValue() == -1.0)
          continue;
        for (int j = i+1; j < rank[r].size(); j++) {
          if (((Double)median.elementAt(j)).doubleValue() == -1.0)
            continue;
          if (((Double)median.elementAt(j)).doubleValue() < 
              ((Double)median.elementAt(i)).doubleValue()) {
            //swap rank[r][i] with rank[r][j]
            Object temp = rank[r].elementAt(i);
            rank[r].setElementAt(rank[r].elementAt(j), i);
            rank[r].setElementAt(temp, j);
            //swap median[i] with median[j]
            temp = median.elementAt(i);
            median.setElementAt(median.elementAt(j), i);
            median.setElementAt(temp, j);
          }
        }
      }
      /*
      System.out.println("elements in rank after");
      for (int i = 0; i < rank[r].size(); i++) {
        System.out.println("i: " + i + ", : " + rank[r].elementAt(i));
      }
      System.out.println("elements in median after");
      for (int i = 0; i < median.size(); i++) {
        System.out.println("i: " + i + ", : " + median.elementAt(i));
      }
      */
    }

    /*
     * transpose(rank)
     *   improved = true;
     *   while improved do
     *     improved = false;
     *     for r = 0 to max_rank 
     *       for i = 0 to |rank[r]|-2 do
     *         v = rank[r][i];
     *         w = rank[r][i+1];
     *         if crossing(v,w) > crossing(w,v) then
     *           improved = true;
     *           exchange(rank[r][i],rank[r][i+1]);
     */
    public void transpose (int itr) {
      int adj = 1;
      if (itr%2 == 0) 
        adj = -1;

      boolean improved = true;

      //System.out.println("Transposing");
      int k = 0;
      while (improved) {
        improved = false;
        if (itr%2 == 0) {
          for (int r = 0; r < g.nR; r++) {
            /*
            if (r == 8) {
            System.out.println(adj + ")" + k + "] Transposing rank: " + r);
            System.out.print(" Before");
            for (int i = 0; i < rank[r].size(); i++) {
              int n = ((Integer)rank[r].elementAt(i)).intValue();           
              System.out.print(" " + node[n].getName());
            }
            System.out.println("");
            }
            */
            for (int i = 0; i < rank[r].size() - 1; i++) {
              int v = i;
              int w = i + 1;
              //add crossings from prev rank and next rank
              /*
                if ((crossing(v, w, r, -1) + crossing(v, w, r, 1)) > 
                (crossing(w, v, r, -1) + crossing(w, v, r, 1))) {
              */
              if (crossing(v, w, r, adj) > crossing(w, v, r, adj)) {
                improved = true;
                //exchange(rank[r][i], rank[r][i+1]);
                Object temp = rank[r].elementAt(i);
                rank[r].setElementAt(rank[r].elementAt(i + 1), i);
                rank[r].setElementAt(temp, i + 1);
              }
            }
          }
        } else {
          for (int r = g.nR - 1; r >= 0; r--) {
            for (int i = 0; i < rank[r].size() - 1; i++) {
              int v = i;
              int w = i + 1;
              //add crossings from prev rank and next rank
              /*
                if ((crossing(v, w, r, -1) + crossing(v, w, r, 1)) > 
                (crossing(w, v, r, -1) + crossing(w, v, r, 1))) {
              */
              if (crossing(v, w, r, adj) > crossing(w, v, r, adj)) {
                improved = true;
                //exchange(rank[r][i], rank[r][i+1]);
                Object temp = rank[r].elementAt(i);
                rank[r].setElementAt(rank[r].elementAt(i + 1), i);
                rank[r].setElementAt(temp, i + 1);
              }
            }
          }
        }
        k++;
      }
    }

    /*
      check adjacent rows for crossings
    */
    public int crossing (int a, int b, int r, int adj) {
      //System.out.println("crossing a: " + a + ", b: " + b + ", r: " + r + ", adj: " + adj);
      int cross = 0;
      Vector A, B;
      //two nodes are adjacent on a rank

      //check crossings with previous rank
      if (adj == -1 && r > 0) {
        A = adj_position(a, r, adj);
        B = adj_position(b, r, adj);
        cross += crossing(A,B);
        //System.out.println("finish crossings");
      }

      //check crossings with next rank
      if (adj == 1 && r < g.nR - 1) {
        A = adj_position(a, r, adj);
        B = adj_position(b, r, adj);
        cross += crossing(A,B);
      }

      int v = ((Integer)rank[r].elementAt(a)).intValue();
      int w = ((Integer)rank[r].elementAt(b)).intValue();
      if (r == 8) 
      System.out.println("  For a: " + node[v].getName() + 
                         ", b: " + node[w].getName() + ", cross #: " + cross);
      return cross;
    }

    /*
     * for each node in A
     *   for each node in B
     *     if B.index < A.index
     *       cross++;
     */
    private int crossing (Vector A, Vector B) {
      int cross = 0;
      //A and B cant be empty if crosses exist
      if (!A.isEmpty() && !B.isEmpty()) {
        for (int i = 0; i < A.size(); i++) {
          for (int j = 0; j < B.size(); j++) {
            double aa = ((Double)A.elementAt(i)).doubleValue();
            double bb = ((Double)B.elementAt(j)).doubleValue();
            if (bb < aa)
                cross++;
          }
        }          
      }
      return cross;
    }

    //count all crossings in this graph
    public int crossing () {
      System.out.println("crossing");
      int cross = 0;
      //crossings can only happen between adjacent ranks
      for (int i = 1; i < g.nR; i++) {
        int this_rank = i;
        /*
          for each node in this_rank
            for each next_node after node
              count crossings
        */
        for (int j = 0; j < rank[i].size() - 1; j++) {
          for (int k = j + 1; k < rank[i].size(); k++) {
            cross += crossing(j, k, this_rank, -1);
          }
        }
      }
      System.out.println("Number of crosses: " + cross);
      return cross;
    }
    
    public void show () {
      for (int i = 0; i < g.nR; i++) {
        for (int j = 0; j < rank[i].size(); j++ ) {
          System.out.println("rank: " + i + ", node: " + rank[i].elementAt(j));
        }
      }
    }
  }
  
}
