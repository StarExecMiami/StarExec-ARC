//*****************************************************************************
//*****************************************************************************
/* 
   Steven Trac
   IDGraph - Interactive Derivation Graph
*/
//*****************************************************************************
/*****
 * Build on to SparseGraph by Dr. Christian Duncan
 * IDGraph has a Formula f in each proof node
 ****/
//*****************************************************************************
import java.util.*;
import java.io.*;
import java.awt.event.*;
import javax.swing.event.*;
import javax.swing.*;
import java.util.HashMap;
import java.awt.*;
//*****************************************************************************
/*********************
 * IDGraph Class
 *    Represents an (Editable) Graph stored as a sparse graph
 *********************/
public class IDGraph extends Graph {
  public static int YSPLIT = 200;
    
  private Vector<IDNode> node;      // Vector of nodes
  private Vector<Formula> formula;   // Vector of all formulas from ProofReader
  private Hashtable ftable; // Hash table on formula names to vector locs
  public IDV idv;           // Link back to viewer
  public Hashtable ctable;  // Hash table for Bezier curves
  
  private int nR;            // Number of Ranks in Nodes
  private int maxRow;        // find the row with max nodes, help with display
  private Vector<IDNode> rank[];     // rank(depths) and order of nodes
  private Vector<IDNode> leaf;      // Vector of Leaves of the Proof Tree
  private Vector<IDNode> root;      // Vector of Roots of Proof Tree
  public boolean pure_fof = true;

  private Vector<IDNode> currentRank[];
  private int currentNR;

  private IDGraph () {
    node = new Vector();
  } // for cloning

  public IDGraph (Vector formula, Hashtable ftable, BufferedReader coord, IDV idv) {
    super();
//DEBUG System.out.println("formula size: " + formula.size());
    this.formula = formula;
    this.ftable  = ftable;
    this.idv     = idv;

    ctable = new Hashtable();

    // set node vector
    node = new Vector ();

    // set depths and count number of nodes
    System.out.println("Set depths");
    setDepths();
    System.out.println("Set finished");

    if (coord != null) {
      createWithCoords(coord);
    } else {
      createWithNoCoords();
    }

    setRanks();
    checkPureFOF();

  }

  private void buildTree (IDNode n, IDNode nn, boolean entire, boolean up, 
                         Hashtable<Integer,IDNode> ntable, Vector<IDNode> old) {
    // new n already added, do not re-add
    Iterator eIt;
    IDNode old_current, new_current;
    IDNode old_next, new_next;
    Vector<IDNode> oldQ = new Vector();
    Vector<IDNode> newQ = new Vector();
    //    IDNode nn = new IDNode(n, this);    
    oldQ.add(n);
    newQ.add(nn);
    //    node.add(nn);
    //n.setSubTree(true);
    //ntable.put(new Integer(n.getId()), nn);
    while (!oldQ.isEmpty()) {
      old_current = oldQ.remove(0);
      new_current = newQ.remove(0);
      if (up)
        eIt = old_current.iterator();
      else
        eIt = old_current.reverse_iterator();
      while(eIt.hasNext()) {
        Edge edge = (Edge)eIt.next();
        if (up)
          old_next = (IDNode)edge.getEndNode();
        else
          old_next = (IDNode)edge.getStartNode();
        if (!old_next.isSubTree()) {
          new_next = new IDNode(old_next, this);
          node.add(new_next);
          old_next.setSubTree(true);
          if (old != null)
            old.add(old_next);
          ntable.put(new Integer(old_next.getId()), new_next);
          if (up)
            new_current.addEdge(new_next);
          else
            new_next.addEdge(new_current);
          if (!old_next.isInteresting() || old_next.isVirtual() || entire) {
            oldQ.add(old_next);
            newQ.add(new_next);
          } else {
            // is interesting (leaf in new graph)
          }
        } else {
          new_next = ntable.get(new Integer(old_next.getId()));
          if (up)
            new_current.addEdge(new_next);
          else
            new_next.addEdge(new_current);
        }
      }
    }
  }

  public IDGraph (IDNode n, IDV idv, boolean entire, boolean up) {
    super();
    IDGraph g = n.idv.graph;
    this.formula = g.formula;
    this.ftable  = g.ftable;
    this.idv     = idv;
    ctable = new Hashtable();
    node = new Vector();
    // make sure old graph is reset
    for (IDNode oldNode : g.node) {
      oldNode.setSubTree(false);
    } 

    // add intial node
    Vector<IDNode> old = new Vector();
    Hashtable<Integer,IDNode> ntable = new Hashtable();
    IDNode nn = new IDNode(n, this);
    ntable.put(new Integer(n.getId()), nn);
    node.add(nn);
    n.setSubTree(true);
    buildTree(n, nn, entire, up, ntable, old);

    if (!up) {
      for (IDNode old_current : old) {
        Iterator eIt = old_current.iterator();
        while(eIt.hasNext()) {
          Edge edge = (Edge)eIt.next();
          IDNode old_next = (IDNode)edge.getEndNode();          
          if (!old_next.isSubTree()) {
            IDNode new_current = ntable.get(new Integer(old_current.getId()));
            IDNode new_next = ntable.get(new Integer(old_next.getId()));
            if (new_next == null) {
              // recurse
              new_next = new IDNode(old_next, this);
              ntable.put(new Integer(old_next.getId()), new_next);
              node.add(new_next);
              old_next.setSubTree(true);
              buildTree(old_next, new_next, false, true, ntable, null);
              old_next.setSubTree(false);
            }
            new_current.addEdge(new_next);
          }
        }
      }
    }

    // make sure old graph is reset
    for (IDNode oldNode : g.node) {
      oldNode.setVisited(-1);
      oldNode.setSubTree(false);
    }
    // initialize polygons for each node
    for (IDNode newNode : node) {
      newNode.initPolygon();
    }
    setRoot();
    nR = -1;
    for (IDNode r : root) {
      int max = r.getRank();
      if (max > nR) { nR = max; }
    }
    nR++;
    rank = new Vector[nR];
    for (int i = 0; i < nR; i++) {
      rank[i] = new Vector();
    }
    for (IDNode current : node) {
      int r = current.getRank();
      if (r != -1) {
        // dont add bend nodes (only bend nodes has r == -1)
        rank[r].add(current);
      }
    }
    // sort each row
    for (Vector row : rank) {
      Collections.sort(row, new IDNode.XComparer());
    }

    // find max row
    maxRow = -1;
    for (Vector row : rank) {
      if (row.size() > maxRow) 
        maxRow = row.size();
    }
    int w;
    if (maxRow == g.maxRow) {
      w = maxRow + 10;
    } else if (maxRow > 10) {
      w = maxRow + 5;
    } else {
      w = maxRow + 6;
    }
    double newWidth = w * 100.0;
    double oldWidth = (g.maxRow + 10) * 100.0;

    System.out.println("old width: " + oldWidth);
    System.out.println("new width: " + newWidth);

    for (Vector<IDNode> row : rank) {
      IDNode last = null;
      int threshold = 100;
      for (IDNode current : row) {
        int newX = (int)(current.getX() / oldWidth * newWidth);
        if (last == null) {
          current.setX(newX);
        } else {
          if ((newX - last.getX()) < threshold) {
            current.setX(last.getX() + threshold);
          } else {
            current.setX(newX);
          }
        }
        System.out.println("placed node: " + current.getName() + " at x: " + current.getX());
        last = current;
      }
    }
    for (IDNode current : node) {
      if (current.isVirtual() && current.getRank() == -1) {
        int newX = (int)(current.getX() / oldWidth * newWidth);
        current.setX(newX);
      }
    }
    
    setLeaf();
    checkPureFOF();
    setRanks();
    for (IDNode c : node) {
      System.out.println("new node: " + c.getName() + ", x: " + c.getX() + ", y: " + c.getY() + ", rank: " + c.getRank());
    }
  }

  public void checkPureFOF () {
    System.out.println("Checking if pure fof");
    for (int i = 0; i < node.size(); i++) {
      IDNode n = (IDNode)node.elementAt(i);
      if (!n.isVirtual()) {
        pure_fof = pure_fof && (n.getFormula().getFormat() == Formula.FORMULA_FORMAT_FOF);
      }
    }
  }

  public void createWithCoords(BufferedReader bin) {
    System.out.println("Coords given");
    Vector up = new Vector();
    Vector edge = new Vector();
    nR = 0;
    try {
      //      StringReader reader = new StringReader(coord);
      //      BufferedReader bin = new BufferedReader(reader);
      String entry;
      while ((entry = bin.readLine()) != null) {
//DEBUG System.out.println("Processing coordinate line ===" + entry + "===");
        StringTokenizer st = new StringTokenizer(entry, ",");
        while (st.hasMoreTokens()) {
          Vector upList = new Vector();
          Vector edgeList = new Vector();
          String name = st.nextToken();
          int nrank = Integer.valueOf(st.nextToken()).intValue();
          double x = Double.valueOf(st.nextToken()).doubleValue();
          double y = Double.valueOf(st.nextToken()).doubleValue();
          IDNode a, b;
//DEBUG System.out.print("Name: " + name + ", x: " + x + ", y: " + y);        
          if (nrank > nR) { nR = nrank; }
          int n = Integer.valueOf(st.nextToken()).intValue();
//DEBUG System.out.print(", up size: " + n + "[");
          if (n == 0) {
//DEBUG System.out.print("<empty>");
          }
          for (int i = 0; i < n; i++) {
            String tok = st.nextToken();
            upList.add(Integer.valueOf(tok));
            if (i < n - 1) {
//DEBUG System.out.print(tok + " ");
            } else {
//DEBUG System.out.print(tok);
            }
          }
//DEBUG System.out.print("]");
          
          n = Integer.valueOf(st.nextToken()).intValue();
//DEBUG System.out.print(", edgeupsize: " + n + "[");
          if (n == 0) {
//DEBUG System.out.print("<empty>");
          }
          
          for (int i = 0; i < n; i++) {
            String tok = st.nextToken();
            edgeList.add(Integer.valueOf(tok));
            if (i < n - 1) {
//DEBUG System.out.print(tok + " ");
            } else {
//DEBUG System.out.print(tok);
            }
          }
//DEBUG System.out.print("]");
          
//DEBUG System.out.println("");
          
          n = node.size();
//DEBUG System.out.println("n: " + n);
//DEBUG System.out.println("f: " + formula.size());
          if (n < formula.size()) {
            if (!name.equals(((Formula)formula.elementAt(n)).getUnbuffedName())) {
              System.out.println("ERROR n: " + name + ", " + ((Formula)formula.elementAt(n)).getUnbuffedName());
            }
//DEBUG System.out.println("not virtual");
            a = new IDNode(n, (Formula)formula.elementAt(n), nrank, x, y, this);
          } else {
//DEBUG System.out.println("is virtual1");
            a = new IDNode(n, null, nrank, x, y, this);
//DEBUG System.out.println("virtual node created");
          }
          node.add(a);          
          up.add(upList);
          edge.add(edgeList);
        }
      }
      System.out.println("Done parsing coordinates");
      nR++;
      rank = new Vector[nR];
      for (int i = 0; i < nR; i++) {
        rank[i] = new Vector();
      }
      for (IDNode current : node) {
        int r = current.getRank();
        rank[r].add(current);
      }
      // sort each row
      for (Vector row : rank) {
        Collections.sort(row, new IDNode.XComparer());
      }
//DEBUG System.out.println("node size: " + node.size());
//DEBUG System.out.println("edglist size: " + edge.size());
//DEBUG System.out.println("up size: " + up.size());
      if (up.size() != edge.size()) System.out.println("ERROR");
      if (up.size() != node.size()) System.out.println("ERROR");
//DEBUG System.out.println("Add Up and Edges");
      for (int k = 0; k < node.size(); k++) {        
        IDNode a, b;
        a = (IDNode)node.elementAt(k);
        a.initPolygon();
        Vector upf = (Vector)up.elementAt(k);
        Vector edgef = (Vector)edge.elementAt(k);
        for (int i = 0; i < upf.size(); i++) {
          int j = ((Integer)upf.elementAt(i)).intValue();
          if (j >= node.size()) {
            System.out.println("ERROR");
          } else {           
            b = (IDNode)node.elementAt(j);
//DEBUG System.out.println("a: " + a.getName() + " add UP to b: " + b.getName());
            a.addUp(b);
          }        
        }
        for (int i = 0; i < edgef.size(); i++) {
          int j = ((Integer)edgef.elementAt(i)).intValue();
          if (j >= node.size()) {
            System.out.println("ERROR");
          } else {           
            b = (IDNode)node.elementAt(j);
//DEBUG System.out.println("a: " + a.getName() + " add EDGE to b: " + b.getName());
            a.addEdge(b);
          }        
        }        
      }
      for (int k = 0; k < node.size(); k++) {
        Vector parents = ((IDNode)node.elementAt(k)).up;
//DEBUG System.out.println("node: " + ((IDNode)node.elementAt(k)).getName() + " parents size: " + parents.size());        
        for (int t = 0; t < parents.size(); t++) {
          IDNode upp = (IDNode)parents.elementAt(t);
//DEBUG System.out.println(" " + upp.getName() + ", ");
        }
      }
 
      //find all leafs
      setLeaf();

      // find all roots      
      setRoot();

      addBendNodes();
      setLemma();
      setAssumption();

//DEBUG System.out.println("done");

    } catch (IOException e) {
      System.out.println("IO Error parsing CLAYOUT applet parameter: " + e.getMessage());
    }
  }
  public int getFormulaSize () {
    return formula.size();
  }
  public void createWithNoCoords() {
    System.out.println("Coords not given");
    // add nodes and edges
    addNodes();
    addEdges();

    //find all leafs
    setLeaf();

    // find all roots
    setRoot();

    // get max ranks
    for (IDNode n : root) {
      int rank = n.getRank();
      if (rank > nR) { nR = rank; }      
    }
    nR++;

    // fix orderings and set coordinates
    Order order = ordering();

    System.out.println("get max row");

    maxRow = order.getMaxRow();

    System.out.println("get ranks: " + nR);

    rank = order.getRank();


    System.out.println("set coordinates");

    setCoordinates();    

    System.out.println("add bend nodes");

    // add bend virtual nodes between each rank
    addBendNodes ();
    // set all non axiom logical consequence
    setLemma();
    // set all virtual nodes as assumption or not
    setAssumption();
  }

  public Vector [] setRanks () {
    bnds = null;
    /* move all nodes into ranks based on current ranks
       if a rank is empty, remove. Then reset ranks, get max rank
    */
    Vector r[] = new Vector[nR];

    for (int i = 0; i < nR; i++) {
      r[i] = new Vector();
    }
    for (int i = 0; i < node.size(); i++) {
      IDNode n = (IDNode)node.elementAt(i);
      if (!n.isVirtual() && ((IDNode)n).isInteresting()) {
        int rr = n.getRank();
        //System.out.println("rr: " + rr);
        r[rr].add(new Integer(i));
      }
    }
    int c = 0;
    //    System.out.println("2");
    for (int i = 0; i < nR; i++) { 
      //      System.out.println("i: " + i + " / " + nR);
      if (!r[i].isEmpty()) {
        //        System.out.println(" not empty rank i size: " + rank[i].size());
        for (IDNode n : rank[i]) {
          n.setCurrentRank(c);
        }
        c++;
      } else {
        //        System.out.println(" empty set current rank to -2");
        for (IDNode n : rank[i]) {
          // must set rank to -2 meaning row is gone
          n.setCurrentRank(-2);
          n.setY(-1000);
          n.invalidate();
        }
      }
    }
    // got the new count of rows
    currentNR = c;
    currentRank = new Vector[currentNR];    
    c = 0;
    for (int i = 0; i < nR; i++) {
      if (!r[i].isEmpty()) {
        currentRank[c++] = rank[i];
      }
    }
    for (int i =0; i < node.size(); i++) {
      IDNode n = (IDNode)node.elementAt(i);
      if (n.getCurrentRank() >= 0) {
        n.setY(n.getCurrentRank() * IDGraph.YSPLIT);
        n.invalidate();
      }
    }
//DEBUG System.out.println("done");
    return r;
  }

  /* Constructor Helper Methods */
  private void setLemma () {
    // for each formulae, check all parents, if any is not ALC, then this is not ALC
    //System.out.println("reset");
    for (int i = 0; i < node.size(); i++) {
      //      System.out.println("at node i: " + i);
      IDNode n = (IDNode)node.elementAt(i);
      n.setVisited(-1);
    }
    //System.out.println("recurse");
    for (int i = 0; i < node.size(); i++) {
      IDNode n = (IDNode)node.elementAt(i);
      //System.out.println("set alc on ID: " + n.getName());
      if (!n.isVisited() && !n.isVirtual())
        n.setLemma();
    }    
    //System.out.println("reset axioms");
    for (IDNode n : leaf) {
      n.setNotLemma();
    }
  }
  private void setAssumption() {
    for (IDNode n : node) {
      n.setVisited(-1);
    }
    for (IDNode n : node) {
//DEBUG System.out.println("START: setAssumption n: " + n.getName());
      n.setAssumption();
//DEBUG System.out.println("DONE:  setAssumption n: " + n.getName());
    }
  }
  private boolean allFormulaeOfType(Vector formulaList,String type) {

    Integer loc;

    for (int i=0;i < formulaList.size();i++) {
      loc = (Integer)ftable.get(formulaList.elementAt(i));
      if (loc != null &&
!((Formula)formula.elementAt(loc.intValue())).getFormat().equals(type)) {
        return(false);
      }
    }
    return(true);
  }

  private void setDepths () {
    // find max cnf and fof axiom depth
    Vector C = new Vector();
    Vector F = new Vector();
    int maxC = 0;
    int maxF = 0;
    for (int i = 0; i < formula.size(); i++) {
      Formula f = (Formula)formula.elementAt(i);      
      // if fof has only thf parents, add to F, and dfsDepth it
      if (f.getFormat().equals(Formula.FORMULA_FORMAT_FOF) && 
allFormulaeOfType(f.getParents(),Formula.FORMULA_FORMAT_THF)) {
        // all parents thf formula, dfsdepth it          
//DEBUG System.out.println("do dfsDepth on FOF leaf f: " + f.getName());
        f.dfsDepth();
//DEBUG System.out.println("the FOF leaf depth of " + f.getName() + " is " + f.getDepth());
        F.add(f);
        if (f.getDepth() > maxF) {
          maxF = f.getDepth();
        }
      }
    }
//DEBUG System.out.println("done all the FOF layer depths, maxF is " + maxF + "\n");
    // reset heights on all F fof axiom formulas
    for (int i = 0; i < formula.size(); i++) {
      Formula f = (Formula)formula.elementAt(i);
      if (maxF > 0 && F.indexOf(f) >= 0) {
        f.setDepth(maxF);
      } else {
        f.setDepth(-1);
      }
    }

    for (int i = 0; i < formula.size(); i++) {
      Formula f = (Formula)formula.elementAt(i);      
      // if cnf has a fof parent, add to C, and dfsDepth it
      if (f.getFormat().equals(Formula.FORMULA_FORMAT_CNF) && 
allFormulaeOfType(f.getParents(),Formula.FORMULA_FORMAT_FOF)) {
        // all parents fof formula, dfsdepth it          
//DEBUG System.out.println("do dfsDepth on CNF leaf f: " + f.getName());
        f.dfsDepth();
//DEBUG System.out.println("the CNF leaf depth of " + f.getName() + " is " + f.getDepth());
        C.add(f);
        if (f.getDepth() > maxC) {
          maxC = f.getDepth();
        }
      }
    }
//DEBUG System.out.println("done all the CNF layer depths, maxC is " + maxC + "\n");
    // reset heights on all C cnf axiom formulas
//----This is gruesome, reseting all the FOF ones too, but in some cases
//----I can't imagine they might have been set by the recursive dfsDepth
//----that sets all those it touches.
    for (int i = 0; i < formula.size(); i++) {
      Formula f = (Formula)formula.elementAt(i);
      if (maxC > 0 && C.indexOf(f) >= 0) {
        f.setDepth(maxC);
      } else if (maxF > 0 && F.indexOf(f) >= 0) {
        f.setDepth(maxF);
      } else {
        f.setDepth(-1);
      }
    }
//DEBUG System.out.println("done all the upper type depths\n");
    //do dfs as far as the last cnf formula
    //then dfs rest of fof formulas if exists
    for (int i = 0; i < formula.size(); i++) {
      Formula f = (Formula)formula.elementAt(i);
//DEBUG System.out.println("do last dfsDepth on f: " + f.getName());
      f.dfsDepth();
//DEBUG System.out.println("the depth is " + f.getDepth());
    }
//DEBUG System.out.println("done all the depths\n");
  }

  private void addNodes () {
    System.out.println("# Formulae: " + formula.size());
    for (int i = 0; i < formula.size(); i++) {
      Formula f = (Formula)formula.elementAt(i);
      // only add node if its interesting
      //      if (f.isInteresting(idv.threshold)) {
        node.add(new IDNode(node.size(), f, this));
        //      }
    }
  }

  private void addEdges () {
    for (int i = 0; i < formula.size(); i++) {
      Formula f = (Formula)formula.elementAt(i);
      // add edges from this formula to ancestors
      Vector P = f.getAncestors();
      Vector A = new Vector();
      for (int j = 0; j < P.size(); j++) {
        Integer loc = (Integer)ftable.get((P.elementAt(j)).toString());
        A.add(loc);
      }
      // sort A
      for (int k = 0; k < A.size(); k++) {
        int n = ((Integer)A.elementAt(k)).intValue();
        int r = ((Formula)formula.elementAt(n)).getDepth();
      }
      Collections.sort(A, new Comparer());
      for (int k = 0; k < A.size(); k++) {
        int n = ((Integer)A.elementAt(k)).intValue();
        int r = ((Formula)formula.elementAt(n)).getDepth();
      }
      addEdge(i, A);
    }      
  }
  private class Comparer implements Comparator { 
    public int compare(Object obj1, Object obj2) {
      int o1 = ((Integer)obj1).intValue();
      int o2 = ((Integer)obj2).intValue();
      int r1 = ((Formula)formula.elementAt(o1)).getDepth();
      int r2 = ((Formula)formula.elementAt(o2)).getDepth();
      return r1 - r2;
    }
  }
  private void addEdge (int b, Vector A) {
    // Precondition: A is sorted
    // edges are from A -> b
    // if (a = elementof(A)) has rank one higher than b then addEdge
    //   else make a new virtual node and recurse
    IDNode nb = (IDNode)node.elementAt(b);
    int rb = nb.getRank();
    while (!A.isEmpty()) {
      int f = ((Integer)A.firstElement()).intValue();
      int ra = ((Formula)formula.elementAt(f)).getDepth();
      if ((ra - rb) <= 1) {
        //this is a good edge
        addEdge(f, b);
        A.remove(0);
      } else {
        break;
      }
    }
    if (!A.isEmpty()) {
      node.add(new IDNode(node.size(), rb + 1, this));
      addEdge(node.size() - 1, b); // connect v to b
      addEdge(node.size() - 1, A); // recurse
    }
  }

  //if a node is an axiom logical consequence (ALC)
  // and if interesting value passes threshold, highlight node
  public void updateInteresting (double threshold, boolean draw) {
    for (IDNode n : node) {
      if (!n.isVirtual()) {
        n.setInteresting(threshold, draw);
      }
      //      n.setVisited(-1);
      n.setSubTree(false);
    }
  }

  // close all child windows in nodes
  public void closeWindows () {
    for (IDNode n : node) {
      n.closeWindows();
    }
  }
  
  public Vector<IDNode> getNode () { return node; }
  public Vector<IDNode>[] getRank () { return rank; }
  public int getRankSize () { return nR; }
  
  public void setPolygons () {
    for (IDNode n : node)
      n.setPolygon();
  }

  // redraw graph with new interesting values
  public void redraw (double threshold) {
    
  }

  // IDNodes are not given coordinates, method not used
  public void addNode(double x, double y) {}
  
  /*****
   * Add an edge between two Nodes (referenced by index)
   * Returns true if successful and false otherwise
   * add Edge(parent, child)
   *****/
  public boolean addEdge (int a, int b) {
    if (a < 0 || b < 0) {
      // Too low
      System.out.println("a");
      System.err.println("Error: Index too low! a: " + a + ", b: " + b);
      return false;
    } else if (a >= node.size() || b >= node.size()) {
      // Too high
      System.out.println("a");
      System.err.println("Error: Index too high! a: " + a + ", b: " + b + ", nN: " + node.size());
      return false;
    }
    IDNode na = (IDNode)node.elementAt(a);
    IDNode nb = (IDNode)node.elementAt(b);

    //if rank of (a - b) > 1, split into diff edges, and add each
    if ((na.getRank() - nb.getRank()) > 1) {
      //split 
      /*
        a.r1 > v.r2 > v.r3 > ... > b.rn
      */
      int max = na.getRank(); //8
      int min = nb.getRank(); //1
      int size = max - min;   //7
      int start = node.size();
      for (int i = 0; i < size - 1; i++) {
        int rank = (max - i) - 1;
        //System.out.println("Formula: " + node.size() + ", node: " + node.size() + ", name: " + "virtual");
        node.add(new IDNode(node.size(), rank, this)); // virtual node
      }
      /*
        connect nodes with edges
        a - > nN;
        nN ... -> ... start;
        start -> b;
      */

      //do first section
      addEdge(a, start);

      //do middle sections
      for (int i = start; i < node.size() - 1; i++) {
        addEdge(i, i+1);
      }

      //do last section
      addEdge(node.size() - 1, b);
    }
    else {
      na.addEdge(nb);
    }
    return true;
  }
  
  // Get list of all nodes (Iterator of Nodes)
  public Iterator nodeIterator() {
    return node.iterator();
  }
  
  // Get list of ALL edges (Iterator of Edges)
  public Iterator edgeIterator() {
    return new IDGraphEdgeIterator(this);
  }
    
  public String getTSTPDump () {
    // return tstp dump of forumlae that are in the current synopsis (synopsis if redraw is pressed)
    
    // 1) check for new synopsis parents
    // 2) check for theory of equality in hidden nodes
    // 3) check for splitting in hidden nodes (propogate them down)
    // 4) check for non theorem
    boolean agint_called = idv.agint_called;
    //    double value = idv.slider.getValue();
    double value = idv.getSynopsisSlider().getValue();
    String dump = "";
    String indent = "";
    for (IDNode n : node) {
      n.setVisited(-1);
    }
    for (IDNode n : node) {
//DEBUG System.out.println("n: " + n.getName() + ", c rank: " + n.getCurrentRank());
      if (n.getCurrentRank() >= 0 && !n.isVirtual() && n.isInteresting()) {
        Formula f = n.getFormula();
        // if leaf and has parents,
        if (n.isLeaf() && f.getParents().size() > 0) {
          String mutatedSource = "creator(" + 
            Formula.FORMULA_SOURCE_CREATOR + ",[" + 
            f.getSource().toString() + "])";
          dump += f.getMutatedFormulaDump(indent,
                                          f.getFormat(),
                                          f.getType(),
                                          mutatedSource) + "\n";
          continue;
        }
        System.out.println(" added!!!");
        // check if any parent was omitted, if so, mutate useful info
        boolean omitted = false;
        Iterator eIt = n.iterator();
        while (eIt.hasNext()) {
          Edge edge = (Edge)eIt.next();
          IDNode other = (IDNode)(edge.getEndNode()).getFront();
          System.out.println("other: " + other.getName());
          if (!other.isInteresting()) {
            omitted = true;
          }
        }
        if (omitted && agint_called) {          
          String mutatedSource = "";
          String splitInfo;
          String statusInfo;
          String parentInfo = "";
          String equalityInfo;
          boolean equality;
          Set<IDNode> parents;
          SubTree subtree = new SubTree();
          n.generateSubTreeInfo(value, subtree);
          // generate split info
          splitInfo = subtree.splitInfo;
          // generate status info
          statusInfo = subtree.statusInfo;
          // generate parent info
          parents = subtree.parents;
          for (IDNode parent : parents) {
            if (!parentInfo.equals(""))
              parentInfo += ",";
            parentInfo += parent.getFormula().getUnbuffedName();            
          }
          // generate equality parent info
          equalityInfo = Formula.FORMULA_THEORY_EQUALITY;
          equality = subtree.equality;
          // create mutated source
          mutatedSource = "inference(synopsis,[";
          if (!splitInfo.equals("")) {
            mutatedSource += splitInfo + ",";
          }
          mutatedSource += statusInfo;
          mutatedSource += "],[";
          mutatedSource += parentInfo;
          if (equality) {
            mutatedSource += "," + equalityInfo;
          }
          mutatedSource += "])";
          dump += f.getMutatedFormulaDump(indent, 
                                          f.getFormat(), 
                                          f.getType(),
                                          mutatedSource) + "\n";
        } else {
          dump += n.getText() + "\n";
        }
      }
    }
    for (IDNode n : node) {
      n.setVisited(-1);
    }
    return dump;
  }
  public int numNodes() { return node.size(); }
  public int numEdges() { 
    int count = 0;
    for (int i = 0; i < node.size(); i++) {
      count += ((IDNode)node.elementAt(i)).numEdges();
    }
    return count;
  }

  public double getLeftBound () {
    return -300;
  }
  public double getRightBound () {
    return (maxRow + 3) * 100;
  }

  private void setLeaf () {
    leaf = new Vector ();
    for (IDNode n : node) {
      if (n.isLeaf()) {
        leaf.add(n);
      }
    }
  }

  private void setRoot () {
    root = new Vector();
    for (IDNode n : node) {
      if (n.isRoot()) {
        root.add(n);
      }
    }
  }

  /*****
   * ordering () {
   *   order = init_order;
   *   best_order = order;
   *   for i = 0 to max_iterations 
   *     wmedian(order,i);
   *     transpose(order);
   *     if crossing(order) < crossing(best)
   *       best = order;
   *   return best;
   *****/
  public Order ordering () {
    //show();
    Order order = new Order(this);
    Order best = new Order(order);
    int max = 24;
    int n = node.size();
//DEBUG System.out.println("Dealing with # nodes: " + n);
    //best.show();
    /*
      if n < 100, 24 is fine
      if n around 200, do about 20
      if n around 500 do around 10
      if n around 1000 do around 5
      if n > 1000, do 2
      n / 100
    */
    max = max - (2 * node.size() / 100);
    if (max < 0) {
      max = 4; // do at least 4 iterations
    }
    int not_improved_count = 0;
    int best_crossing = best.crossing();
    for (int i = 0; i < max; i++) {
//DEBUG System.out.println("i: " + i);
      if (idv.applet != null) {
        idv.applet.showStatus("Ordering Phase: (" + i + " / " + max + " iterations)");
      }
      if (i%4 == 0 || i%4 == 1) {
        order.wmedian(i);
        order.transpose(i);
      } else {
        order.transpose(i);
      }
      int order_crossing = order.crossing();
      if (order_crossing <= best_crossing) {
        int change = best_crossing - order_crossing;
        double percent = (double)change / (double)order_crossing;
        if (percent < .05) {
          not_improved_count++;
        } else {
          not_improved_count = 0;
        }
        best = new Order(order);
        best_crossing = order_crossing;
//DEBUG System.out.println("got new best: " + best_crossing);
      } else {
        not_improved_count++;
      }
      if (not_improved_count > 3) {
        break;
      }
    } 
    return best;
  }

  /*****
   * for each node
   *   split each edge
   *   return nodes and add to vector
   * place virtual nodes between each edge to create more bend effect
   *****/
  private void addBendNodes () {
    int nN = node.size();
    for (int i = 0; i < nN; i++) {
      IDNode n = (IDNode)node.elementAt(i);
      Vector bendNodes = n.splitEdges(node.size());
      if (!bendNodes.isEmpty()) {
        node.addAll(bendNodes);
      }
    }
  }

  public void setCoordinates () {
    //use order to determine coordinates
    int width = (maxRow + 10) * 100;
    System.out.println("---width: " + width);
    for (int i = 0 ; i < nR; i++) {
      int splits = width / (rank[i].size() + 1);
      IDNode last = null;
      int j = 0;
      for (IDNode current : rank[i]) {
        current.setX((++j) * splits);
        current.setY(i * IDGraph.YSPLIT);
        current.initPolygon();
        if (last != null) {
          last.setRight(current);
          current.setLeft(last);
        }
        last = current;
      }
    }
  }

  public void pinNodes () {
    for (int i = 0 ; i < node.size(); i++) {
      IDNode currentNode = (IDNode)node.elementAt(i);
      if (!currentNode.isVirtual())
        currentNode.setPinned(true);
    }
  }

  public void setChains () { 
    System.out.println("Setting chains");
    // reset nodes
    for (IDNode n : node) {
      n.setVisited(-1);
      n.clearUpDown();
      n.upParents.clear();
    }

    // for each node, set chains based on interestingness
    for (int i = 0; i < node.size(); i++) {
      IDNode n = (IDNode)node.elementAt(i);
      /*
        7 types of nodes:
        1: -1 virtual node with 1 parent 1 child, 
        2: > 0 virtual node with 1 parent n children, rank exist
        2b:> 0 virtual node with 1 parent 1 child, rank exists
        3: > 0 regular node that is interesting
        4: > 0 regular node that is not interesting, rank exist
        5: -2 virtual node with 1 parent many children, rank does not exist
        6: -2 regular node that is not interesting, rank does not exist
      
        if 2, 3, or 4, then draw
      */
      if (!n.isVirtual() && n.getCurrentRank() >= 0 && n.isInteresting()) {
        n.setChains();
      }    
    }
    for (IDNode n : node) {
      n.setVisited(-1);
    }
  }

  public boolean addInteresting () throws IOException {
    idv.textField.setText("Checking if interestingness ratings exist...");
    System.out.println("add interesting");
    // first check if there are any interesting values > 0
    String derivation = "";
    boolean intCheck = true;
    boolean flag = true;
    for (Formula f : formula) {
      if (f.getInteresting() > -2) {
        intCheck = false; // exit no need for more values
        flag = false;
        break;
      }
    }

    if (intCheck) {
      for (Formula f : formula) {
        derivation += f.getFormulaDump() + "\n";
      }

      // sent all to agint
      try {
    // there are no interesting values > 0, call Agint
        System.out.println("no interesting values, calling Agint, set up axiom set");    
        flag = TPTPReader.readAgint(derivation, formula, ftable, idv);
      } catch (Exception e) {
        System.out.println("ERROR with agint: " + e.getMessage());
      }      
    } else {
      idv.textField.setText("Interestingness ratings exist, do not recompute.");      
    }
    
        
    // set up Axioms set
    Vector<IDNode> axiom = new Vector();
    for (IDNode current : leaf) {
      if (pure_fof) {
        axiom.add(current);
      } else {
        // if current axiom is an fof, find first cnf formula, make axiom
        if (current.getFormula().getFormat().equals(Formula.FORMULA_FORMAT_FOF)) {
          // make sure to catch all children
          findAxioms(current, axiom);
        }
        else {
          axiom.add(current); // make sure not conjecture
        }
      }
    }
    
    System.out.println("axioms are interesting");
    // axioms are interesting
    for (IDNode current : axiom) {
      //current.getFormula().setInteresting(1);
      current.setIStatus(true);
    }
    
    System.out.println("original axioms are interesting");
    // original axioms are interesting
    for (IDNode n : leaf) {
      //n.getFormula().setInteresting(1);
      n.setIStatus(true);
    }
    
    System.out.println("roots are interesting");
    // roots are interesting
    for (IDNode n : root) {
      //n.getFormula().setInteresting(1);
      n.setIStatus(true);      
    }

    System.out.println("set thresholds, update interestingness");
    int i = 0;
    for (IDNode current : node) {
      //System.out.println("on node: " + i++);
      current.setInteresting(idv.getSynopsisThreshold(), true);
    }

    System.out.println("done");
    return flag;
  }
  
  private void findAxioms (IDNode current, Vector axioms) {
    // if current is fof, find first cnf
    if (current.isVirtual()) { 
      Iterator eIt = current.reverse_iterator();
      while(eIt.hasNext()) {
        Edge e = (Edge)eIt.next();
        IDNode back = (IDNode)e.getStartNode().getBack();
        findAxioms(back,axioms);
      }      
    } else if (current.getFormula().getFormat().equals(Formula.FORMULA_FORMAT_FOF)) {
      // recurse on all children
      Iterator eIt = current.reverse_iterator();
      while(eIt.hasNext()) {
        Edge e = (Edge)eIt.next();
        IDNode back = (IDNode)e.getStartNode().getBack();
        findAxioms(back,axioms);
      }
    } else {
      axioms.add(current);
    }
  } 

  // Override the Graph clone method to make perfect clone
  public Graph deepClone() {
    IDGraph copy = new IDGraph();

    //copy node list
    Iterator nIt = node.iterator();
    while (nIt.hasNext()) {
      IDNode n = (IDNode)nIt.next();
      IDNode copy_node = new IDNode(n,this);
      copy.node.add(copy_node);
    }

    // clone edge list
    for (int i = 0; i < node.size(); i++) {
      IDNode n = (IDNode)node.elementAt(i);
      IDNode c = (IDNode)copy.node.elementAt(i);
      // for each edge in n, clone to c (ancestor_edge will work itself out thru addEdge)
      Iterator eIt = n.iterator();
      while (eIt.hasNext()) {
        Edge e = (Edge)eIt.next();
        IDNode o = (IDNode)e.getEndNode();
        int id = o.getId(); //location in list
        c.addEdge((IDNode)copy.node.elementAt(id));
      }
    }

    //take same formula list, no change
    copy.formula = this.formula;

    //take same ftable hashtable, no change
    copy.ftable = this.ftable;

    //link back to same viewer
    copy.idv = this.idv;

    //rank info the same
    copy.nR = this.nR;
    copy.maxRow = this.maxRow;
    copy.rank = this.rank;
    copy.root = this.root;

    return copy;
  }

  public void invalidateEdges() {
    Iterator nIt = node.iterator();
    while (nIt.hasNext()) {
      IDNode n = (IDNode)nIt.next();
      n.invalidateEdges();
    }
  }
  
  public void invalidate () {
    Iterator nIt = node.iterator();
    while (nIt.hasNext()) {
      IDNode n = (IDNode)nIt.next();
      n.invalidate();
    }
  }

  /**********************************************************
   * This is a private class associated with IDGraphs
   * IDGraphEdgeIterator -
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
  private class IDGraphEdgeIterator implements Iterator {
    IDGraph g;   // The current Graph to iterate on
    int nA;          // Which start node are we currently on
    int nB;          // Which end node are we currently on

    // Iterate edges over entire graph
    public IDGraphEdgeIterator(IDGraph g) {
      this.g = g; nA = nB = 0;
    }
    
    public boolean hasNext() { 
      while (nA < g.numNodes() && 
             ((IDNode)g.node.elementAt(nA)).edge.isEmpty()) {
        advance();
      }
      return (nA < g.numNodes()); // Found edge or not
    }
    
    public Object next() {
      if (hasNext() == false) return null;
      
      IDNode na = (IDNode)g.node.elementAt(nA);
      Edge response = (Edge)na.edge.elementAt(nB);
      advance();      // Skip this edge - hasNext advances next time
      return response;
    }
    
    public void remove() {} // Not implemented 
    
    // Advance to next potential pair (in lower triangle)
    private void advance() {
      nB++;
      IDNode na = (IDNode)g.node.elementAt(nA);
      if (nB >= na.edge.size()) {
        nA++;
        nB=0;
      }
    }
  }

  public void resetVerified () {
    for (IDNode n : node) {
      n.resetVStatus();
    }
  }
  public void verifyALL (String ATPSelected, boolean gdv) {
    for (int i = 0; i < node.size() && idv.isVerify(); i++) {
      node.elementAt(i).verify(ATPSelected, gdv);
    }
  }
  public void setLeaves () {
    for (IDNode n : node) {
      n.resetLeaf();
    }
    for (IDNode n: node) {
      n.setLeaves();
    }
  }
  /**********************************************************
   * class Order:
   *  This is a private class associated with IDGraphs
   *  This class places all nodes of the same rank in the same
   *   vector, so you have an array of vector of nodes
   *********************************************************/
  private class Order {
    Vector<Integer> rank[];
    int pos[];
    IDGraph g;

    public Order (IDGraph g) {
      this.g = g;
      rank = new Vector[g.nR];
      pos = new int[g.node.size()];
      for (int i = 0; i < g.nR; i++) rank[i] = new Vector();
      //do DFS on nodes starting from root
      //If in same rank and not in vector, add it to rank 
      for (IDNode n : g.node) {
        n.setSubTree(false);
      }
      for (IDNode n : g.root) {
        setRank(n);
      }
      //      System.out.println("node size: " + node.size());
      /*
      for (int i = 0; i < node.size(); i++) {        
        System.out.println("i: " + i + ", node: " + node.elementAt(i).getName() + ", rank: " + node.elementAt(i).getRank() + ", pos: " + pos[i]);
      }
      System.out.println("done");
      */
      for (IDNode n : g.node) {
        n.setSubTree(false);
      }
    }
    public Order (Order order) {
      g = order.g;
      pos = new int[g.node.size()];
      rank = new Vector[g.nR];
      for (int i = 0; i < g.nR; i++) {
        rank[i] = new Vector(order.rank[i]);
      }
      for (int i = 0; i < node.size(); i++) {
        pos[i] = order.pos[i];
      }
    }
    
    public Vector[] getRank () { 
      Vector<IDNode> row[] = new Vector[g.nR];
      for (int i = 0; i < g.nR; i++) row[i] = new Vector();
      for (int i = 0; i < g.nR; i++) {
        for (int j = 0; j < rank[i].size(); j++) {
          int k = rank[i].elementAt(j).intValue();
          row[i].add(node.elementAt(k));
        }
      }
      return row; 
    }

    public int getMaxRow () {
      int max = 0;
      for (int i = 1; i < g.nR; i++) {
        if (rank[i].size() > rank[max].size())
          max = i;
      }
      return rank[max].size();
    }

    private void setRank (IDNode n) {
      n.setSubTree(true);
      int loc = n.getRank();
      Integer nn = new Integer(n.getId());
      rank[loc].add(nn);
      pos[nn.intValue()] = rank[loc].size() - 1;
      //recurse to parents since just added
      Iterator itr = n.iterator();
      while (itr.hasNext()) {
        Edge e = (Edge)itr.next();
        IDNode other = (IDNode)e.getEndNode();
        if (!other.isSubTree()) 
          setRank(other);        
      }
    }

    private class MedianPair {
      double median;
      Integer position;
      MedianPair(double m, Integer p) {
        median = m;
        position = p;
      }
    }
    private class MPairComparer implements Comparator {
      public int compare(Object obj1, Object obj2) {
        double m1 = ((MedianPair)obj1).median;
        double m2 = ((MedianPair)obj2).median;
        if (m1 < m2) {
          return -1;
        } else if (m1 > m2) {
          return 1;
        } else {
          if ((flip % 4) == 2 || (flip % 4) == 3) {
            return 1;
          } else {
            return -1;
          }
        }
      }
    }
    /*****    
     * wmedian(order,iter)
     *   if iter mod 2 == 0 then
     *     for r = 1 to max_rank
     *       for v in order[r] do
     *         median[v] = median_value(v,r-1);
     *       sort(order[r],median);
     *   else
     *     ...
     *****/
    int flip = 0;
    private void updateRank (int r, Vector<MedianPair> mpair) {
      Collections.sort(mpair, new MPairComparer());
      rank[r].clear();
      for (MedianPair m : mpair) {
        rank[r].add(m.position);
        pos[m.position.intValue()] = rank[r].size() - 1;
      }
    }
    public void wmedian (int i) {
      flip++;
      if (i%2 == 0) {
        //traverse ranks bottom to top
        for (int r = 1; r < g.nR; r++) {
          Vector<MedianPair> mpair = new Vector();
          for (int v = 0; v < rank[r].size(); v++) {
            mpair.add(new MedianPair(median_value(v, r, -1), rank[r].elementAt(v)));
          }
          updateRank(r, mpair);
        }
      }
      else {
        //traverse ranks top to bottom
        for (int r = g.nR - 2; r > -1; r--) {  
          Vector<MedianPair> mpair = new Vector();
          for (int v = 0; v < rank[r].size(); v++) {
            mpair.add(new MedianPair(median_value(v, r, 1), rank[r].elementAt(v)));
          }
          updateRank(r, mpair);
        }
      }
    }

    /*****
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
     *****/
    private double median_value(int v, int this_rank, int adj) {
      Vector<Double> P = adj_position(v, this_rank, adj);
      int n = P.size();
      int m = n / 2;
      if (n == 0) {
        return -1.0;
      }
      else if (n % 2 == 1) {
        return P.elementAt(m).doubleValue();
      }
      else if (n == 2) {
        return (P.elementAt(0).doubleValue() + 
                P.elementAt(1).doubleValue()) / 2.0;
      }
      else {
        double left = P.elementAt(m-1).doubleValue() - 
          P.elementAt(0).doubleValue();
        double right = P.elementAt(P.size()-1).doubleValue() - 
          P.elementAt(m).doubleValue();
        return (P.elementAt(m-1).doubleValue() * right + 
                P.elementAt(m).doubleValue() * left) / (left + right);
      }
    }
    private Vector<Double> adj_position (int v, int this_rank, int adj) {
      //return vector of all adj positions in adj_rank
      Vector<Double> P = new Vector();
      //int adj_rank = this_rank + adj;
      int b = ((Integer)rank[this_rank].elementAt(v)).intValue();
      IDNode nb = (IDNode) node.elementAt(b);
      Iterator eIt;
      IDNode other;
      if (adj == 1) {
        // top down
        eIt = nb.reverse_iterator();
      } else {
        // bottom up
        eIt = nb.iterator();
      }
      while (eIt.hasNext()) {
        Edge e = (Edge)eIt.next();        
        if (adj == 1) 
          other = (IDNode)e.getStartNode();
        else
          other = (IDNode)e.getEndNode();
        P.add(new Double(pos[other.getId()]));
      }
      Collections.sort(P, new DoubleComparer());
      return P;
    }
    private class DoubleComparer implements Comparator {
      public int compare(Object obj1, Object obj2) {
        double d1 = ((Double)obj1).doubleValue();
        double d2 = ((Double)obj2).doubleValue();
        if (d1 < d2) {
          return -1;
        } else if (d1 > d2) {
          return 1;
        } else {
          return 0;
        }
      }
    }
    private class DoublePosComparer implements Comparator {
      public int compare(Object obj1, Object obj2) {
        double pos1 = ((Double)obj1).doubleValue();
        double pos2 = ((Double)obj2).doubleValue();
        if (pos1 >= pos2) {
          return -1;
        } else {
          return 1;
        }
      }
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
      int count = 0;
      boolean improved = true;
      while (improved) {
        improved = false;
        //        System.out.println("Transposing");
        if (itr%2 == 0) {
          for (int r = 0; r < g.nR; r++) {
            improved = improved || transpose(r, adj);
          }
        } else {
          for (int r = g.nR - 1; r >= 0; r--) {
            improved = improved || transpose(r, adj);
          }
        }
        if (++count > 100)
          break;
      }
    }
    
    public boolean transpose (int r, int adj) {
      boolean improved = false;
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
          Integer temp = rank[r].elementAt(i);
          rank[r].setElementAt(rank[r].elementAt(i + 1), i);
          pos[rank[r].elementAt(i+1).intValue()] = i;
          rank[r].setElementAt(temp, i + 1);
          pos[temp.intValue()] = i + 1;
        }
      }
      return improved;
    }
    
    /*
      check adjacent rows for crossings
    */
    public int crossing (int a, int b, int r, int adj) {
      //System.out.println("crossing a: " + a + ", b: " + b + ", r: " + r + ", adj: " + adj);
      int cross = 0;
      int n[] = {a, b};
      OSTree<Double> adjRow = new OSTree(new DoublePosComparer());
      for (int i = 0; i < 2; i++) {
        Vector<Double> parents = adj_position(n[i], r, adj);
        for (Double p: parents) {
          OSTree.Node node = adjRow.insert(p);
          cross += adjRow.rank(node) - 1;
        }
      }
      return cross;
    }

    public int crossing (int r, int adj) {
      int cross = 0;     
      OSTree<Double> adjRow = new OSTree(new DoublePosComparer());
      for (int i = 0; i < rank[r].size(); i++) {
        Vector<Double> parents = adj_position(i, r, adj);
        for (Double p : parents) {
          OSTree.Node node = adjRow.insert(p);
          cross += adjRow.rank(node) - 1;
        }
      }
      return cross;
    }

    //count all crossings in this graph
    public int crossing () {
      int cross = 0;
      int adj = -1;
      //crossings can only happen between adjacent ranks
      for (int i = 1; i < g.nR; i++) {
        cross += crossing(i, adj);
      }
      return cross;
    }
  
    public void show () {
      for (int i = 0; i < g.nR; i++) {
        //System.out.print("rank: " + i + "=> ");
        for (int j = 0; j < rank[i].size(); j++ ) {
          int n = ((Integer)rank[i].elementAt(j)).intValue();
          Node current = (Node)g.node.elementAt(n);
          //System.out.print(current.getName() + " ");
        }
      //System.out.println("");
      }
    }

  }
  
  /**********************************************************
   Mouse Events
   *********************************************************/
  private int getDepth (MouseEvent e) {
    Point pt = idv.gridScreen.adjustPoint(e.getPoint());
    //    System.out.println("point clicked: " + pt);
    double y = pt.getY() + IDGraph.YSPLIT / 2;
    int depth = (int)(y / (double)IDGraph.YSPLIT);
    //    System.out.println(" corresponds to depth: " + depth);
    return depth;
  }
  public void mouseClicked (MouseEvent e) {
    boolean mouse1 = e.getButton() == MouseEvent.BUTTON1;
    boolean mouse2 = e.getButton() == MouseEvent.BUTTON2;
    boolean mouse3 = e.getButton() == MouseEvent.BUTTON3;
    boolean shift = e.isShiftDown();
    boolean alt = e.isAltDown();
    boolean control = e.isControlDown();
    int depth = getDepth(e);
    boolean entire = true;
    boolean up = true;
    if (depth < 0 || depth >= nR) 
      return;
    if (idv.CURRENT_NODE != null) {
      IDNode n = idv.CURRENT_NODE;
      if (n.processPoint(e.getPoint())) {
        // write out all booleans (incase of future additions)
        if (!shift && !alt && control && mouse1 && !mouse2 && !mouse3) {
          // immediate parents, up
          n.idv.createChildWindow((IDNode)n, !entire, up);
        } else if (shift && !alt && !control && mouse1 && !mouse2 && !mouse3) {
          // entire subtree, up but only axioms and clicked node remove discharged assumptions
          n.idv.createChildWindow((IDNode)n, entire, up);
        } else if (shift && !alt && control && mouse1 && !mouse2 && !mouse3) {
          // entire subtree, up
          n.idv.createChildWindow((IDNode)n, entire, up);
        } else if (!shift && !alt && control && !mouse1 && !mouse2 && mouse3) {
          // immediate parents, down
          n.idv.createChildWindow((IDNode)n, !entire, !up);
        } else if (shift && !alt && control && !mouse1 && !mouse2 && mouse3) {
          // entire subtree, down
          n.idv.createChildWindow((IDNode)n, entire, !up);
        } else {
          // default opens text window
          n.openTextWindow();
        }
      } else {
        //        n.unhighlight();
        invalidate();
        idv.gridScreen.repaint();
        idv.CURRENT_NODE = null;        
      }
    }
  }

  public void mouseMoved (MouseEvent e) {
    int depth = getDepth(e);
    //    System.out.println("depth: " + depth + " comared to current nR: " + currentNR);
    if (depth < 0 || depth >= currentNR) 
      return;
    for (IDNode n : currentRank[depth]) {
      //      System.out.println("looking at node: " + n.getName());
      if (n.isVirtual() || !n.isInteresting())
        continue;
      if (n.processPoint(e.getPoint())) {
        n.highlight();
        idv.textField.setForeground(Color.black);
        idv.textField.setText(n.getText());
        idv.textField.setCaretPosition(0);
      } else {
        if (idv.CURRENT_NODE == n) {
          idv.textField.setForeground(Color.gray);
          idv.textField.setText(n.getText());
          idv.textField.setCaretPosition(0);          
        }
      }

    }
  }
}
