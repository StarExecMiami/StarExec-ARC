//*****************************************************************************
//*****************************************************************************
/* 
   Steven Trac
   IDNode - Interactive Derivation Node
*/
//*****************************************************************************
import java.util.*;
import java.io.*;
import javax.swing.*;
import java.awt.*;
import java.util.regex.*;
import tptp_parser.*;
//*****************************************************************************
public class IDNode extends Node {

  private enum VStatus { VNOTYET, VTRUE, VFALSE };
  private enum IStatus { INOTYET, ITRUE, IFALSE };

  Color thfColor = Color.magenta;
  Color fofColor = Color.cyan;
  Color cnfColor = Color.orange;

  public Vector<Edge> edge;
  public Vector<Edge> reverse_edge;

  public Vector up;
  public Vector down;

  public Vector<IDNode> upParents;

  private IDGraph g;      // the idgraph itself
  private Formula f;      // formula of this idnode
  private int     rank;   // rank in derivation tree
  private int     current_rank;   // current rank in derivation tree
  //  private int     pos;    // position in rank

  private int visit_depth = -1;
  private int adjust_y = 0;
  private int last_visited = -1;

  private double current_x;
  private double current_y;

  private boolean lemma = false;
  private boolean assumption = false;
  private boolean interesting = true;         // is this node currently interesting
  private IStatus istatus = IStatus.INOTYET;  // interesting status

  private IDNode left, right;         // nodes to the left and right on its row
  private VStatus vstatus;            // verified status

  private boolean subtree = false;

  private IDNode leaf;

//*****************************************************************************
  // non virtual node constructor
  public IDNode (int id, Formula f, IDGraph g) {
    super(id, false, g.idv);
    this.f = f;
    this.g = g;
    this.rank = f.getDepth();
    this.current_rank = this.rank;
    edge = new Vector();
    reverse_edge = new Vector();
    up = new Vector();
    down = new Vector();
    if (rank != 0 && !isConjecture()) {
      //      getFormula().setALC(true);
      lemma = true;
    }
    current_x = x;
    current_y = getCurrentRank() * IDGraph.YSPLIT;
    upParents = new Vector();
    left = null;
    right = null;
    vstatus = (f.isVerified()) ? VStatus.VTRUE : VStatus.VNOTYET;
  }
  // virtual node constructor
  public IDNode (int id, int rank, IDGraph g) {
    super(id, true, g.idv);
    this.f = null;
    this.g = g;
    this.rank = rank;
    this.current_rank = this.rank;
    edge = new Vector();
    reverse_edge = new Vector();
    up = new Vector();
    down = new Vector();
    current_x = x;
    current_y = y;
    upParents = new Vector();
    left = null;
    right = null;
    vstatus = VStatus.VNOTYET;
  }
  // node constructor for coordinates
  public IDNode (int id, Formula f, int rank, double _x, double _y, IDGraph g) {
    super(id, false, g.idv);
//DEBUG System.out.println("node constructor for coordinates");
    this.virtual = (f == null);
    this.f = f;
    this.g = g;
    this.rank = rank;
    this.current_rank = this.rank;
    x = _x;
    y = _y;
    current_x = x;
    current_y = y;
    upParents = new Vector();
    up = new Vector();
    down = new Vector();
    edge = new Vector();
    reverse_edge = new Vector();
    left = null;
    right = null;
//DEBUG System.out.println("check verified status");
    if (f != null) {
      vstatus = (f.isVerified()) ? VStatus.VTRUE : VStatus.VNOTYET;
//DEBUG System.out.println("checked verified status");
    }
  }

  // clone constructor
  
  public IDNode (IDNode idn, IDGraph g) {
    // shallow copy
    super(idn.id, idn.virtual, g.idv);

    // save coordinates
    this.sp = idn.sp;
    this.x = idn.x;
    this.y = idn.y;

    this.f = idn.f;
    this.g = g;
    this.rank = idn.rank;
    this.current_rank = this.rank;

    this.edge = new Vector();
    this.reverse_edge = new Vector();
    up = new Vector();
    down = new Vector();
    upParents = new Vector();
    //clone edges
    //this.edge = idn.edge;

    // clone reverse edges
    //this.reverse_edge = idn.reverse_edge;    
    left = null;
    right = null;
    vstatus = idn.vstatus;
  }

//*****************************************************************************
  
  public void invalidate () {
    current_x = x;
    if (isVirtual()) {
      current_y = y;
    }
    else {
      current_y = getCurrentRank() * IDGraph.YSPLIT;
    }
    last_visited = -1;
    if (sp != null) {
      sp.n = this;
      sp.invalidate();
      clearSelected();
    }
    front_depth = -1;
    back_depth = -1;
  }
  
  public void invalidateEdges () {
    // for all edges front, invalidate
    for (int i = 0; i < edge.size(); i++) {
      ((Edge)edge.elementAt(i)).invalidate();
    }
    
    // for all edges back, getBack() node, then invalidate
    for (int i = 0; i < reverse_edge.size(); i++) {
      Edge e = (Edge)reverse_edge.elementAt(i);
      Edge back = e.getBackEdge();
      back.invalidate();
    }
  }
  
  /* Accessor methods */
  //public void setPos (int p) { pos = p; }
  //public int getPos () { return pos; }
  public int getRank () { return rank; }
  public int numEdges () { return edge.size(); }
  public Formula getFormula () { return f; }
  public String getName () { return (virtual) ? "V" + getId() : f.getName(); }
  public String getText () { return ((IDNode)getFront()).getFormula().getFormulaDump(); }
  public Iterator iterator () { return edge.iterator(); }
  public Iterator reverse_iterator () { return reverse_edge.iterator(); }
  public boolean isVisited (int startID) { return last_visited == startID; }
  public boolean isVisited () { return last_visited >= 0; }
  public boolean isSubTree () { return subtree; }
  public void setSubTree (boolean flag) { subtree = flag; }
  public void setVisited (int startID) { last_visited = startID; }
  public IDGraph getGraph () { return g; }
  public boolean isLeaf () { return edge.size() == 0; } // leaf if empty
  public boolean isRoot () { return reverse_edge.size() == 0; } // root if empty

  public Point makePoint () {
    if (getRank() == -1)
      return (new Point((int)getRoundedX(), (int)getY()));
    else 
      return (new Point((int)getRoundedX(), (int)IDGraph.YSPLIT * getRank()));
  }

//*****************************************************************************
  public Node getFront () {
    if (virtual) {
      if (front == null) {
        //find the front node to this virtual node
        Edge e = (Edge)iterator().next();
        Node other = e.getEndNode();
        return other.getFront();
      } else {
        //front found already, return it
        return front;
      }
    } else {
      //not virtual so return this
      return this;
    }
  }
  public Node getBack () {
    if (virtual && reverse_edge.size() == 1) {
      if (back == null) {
        //find the back node to this virtual node
        Edge e = (Edge)reverse_iterator().next();
        Node other = e.getStartNode();
        return other.getBack();
      } else {
        //back found already, return it
        return back;
      }
    } else {
      //not virtual so return this
      return this;
    }
  } 
  public int getFrontDepth () {
    //if no children, then depth is 0
    //else its max children depth + 1
    if (front_depth != -1) {
      return front_depth;
    }
    Vector visited = new Vector();
    Vector queue = new Vector();
    queue.add(this);
    visit_depth = 0;
    while (!queue.isEmpty()) {
      IDNode current = (IDNode)queue.remove(0);
      visited.add(current);
      Iterator eIt = current.iterator();
      if (current.visit_depth > front_depth) { 
        front_depth = current.visit_depth; 
      }
      int next_depth = current.visit_depth;;
      if (isInteresting()) {
        next_depth++;
      }
      while(eIt.hasNext()) {
        Edge e = (Edge)eIt.next();
        IDNode front = (IDNode)e.getEndNode().getFront();
        if (front.visit_depth == -1) {
          front.visit_depth = next_depth;
          queue.add(front);
        }
      } 
    }
    for (int i = 0; i < visited.size(); i++) {
      IDNode current = (IDNode)visited.elementAt(i);
      current.visit_depth = -1;
    }
    return front_depth;
  }
  public int getBackDepth () {
    //if no children, then depth is 0
    //else its max children depth + 1
    if (back_depth != -1) {
      return back_depth;
    }
    Vector visited = new Vector();
    Vector queue = new Vector();
    queue.add(this);
    visit_depth = 0;
    while (!queue.isEmpty()) {
      IDNode current = (IDNode)queue.remove(0);
      visited.add(current);
      Iterator eIt = current.reverse_iterator();
      if (current.visit_depth > back_depth) { back_depth = current.visit_depth; }
      int next_depth = current.visit_depth;
      if (isInteresting()) {
        next_depth++;
      }      
      while(eIt.hasNext()) {
        Edge e = (Edge)eIt.next();
        IDNode back = (IDNode)e.getStartNode().getBack();
        if (back.visit_depth == -1) {
          back.visit_depth = next_depth;
          queue.add(back);
        }
      } 
    }
    for (int i = 0; i < visited.size(); i++) {
      IDNode current = (IDNode)visited.elementAt(i);
      current.visit_depth = -1;
    }
    return back_depth;
  }

//*****************************************************************************

  public double getRoundedX () {
    // snap x onto grid (currently not used)
    return x;
  }
  public void setLeft (IDNode _left) {
    left = _left;
  }
  public void setRight (IDNode _right) {
    right = _right;
  }
  public void setX (double _x) {
    double max = 100;
    double diffX = x - _x;
    double diff;
    double half;
    if (diffX > 0) {
      if (left != null) {
        diff = x - left.getX();
        half = (diff - 100) / 2 - 1;
        diff = diff - diffX;
        if (diff <= 100) {
          x = x - half; // move only half the rest of the distance
        } else {
          x = _x;
        }
      } else {
        x = _x;
      }
    } else if (diffX < 0) {
      diffX = Math.abs(diffX);
      if (right != null) {
        diff = Math.abs(x - right.getX());
        half = (diff - 100) / 2 - 1;
        diff = diff - diffX;
        if (diff <= 100) {
          x = x + half; // move only half the rest of the distance
        } else {
          x = _x;
        }
      } else {
        x = _x;
      }
    }
  }
  public int getCurrentRank () { return current_rank; }

  /* Mutator methods */
  public void setIStatus (boolean flag) {
    if (flag)
      istatus = IStatus.ITRUE;
    else
      istatus = IStatus.IFALSE;
  }

  public void resetVStatus () {
    vstatus = VStatus.VNOTYET;
  }
  public void setVStatus (boolean flag) {
    if (flag)
      vstatus = VStatus.VTRUE;
    else
      vstatus = VStatus.VFALSE;
  }
  
  public void setY (double _y) { y = _y;}
  public void setRank (int i) { rank = i; }
  public void setCurrentRank (int i) { current_rank = i; }
  void addEdge (Node other) {
    // Create NEW Edge and add it to both
    //    this and other edge lists
    if (other instanceof IDNode == false) {
      throw new RuntimeException("Error: IDNode.addEdge(other): " +
                                 "other MUST be instanceof SparseNode"); 
    }
    IDNode that = (IDNode) other;
    Edge e = new Edge(this, that);
    this.edge.add(e); 
    that.reverse_edge.add(e);
  }

  public boolean addUp (Node other) {
    if (!up.contains(other)) {
      up.add(other);
      ((IDNode)other).addDown(this);
      return true;    
    } 
    return false;
  }
  void addDown (Node other) {
    down.add(other);
  }
  public Iterator upIterator () {
    return up.iterator();
  }
  public Iterator downIterator () {
    return down.iterator();
  }
  void clearUpDown () {
    up.clear();
    down.clear();
  }
  void setChains () {
    Iterator eIt = iterator();
    Vector nodes = new Vector();
    nodes.add(this);
    boolean flag = true;
    while (eIt.hasNext()) {
      Node next = ((Edge)eIt.next()).getEndNode();
      next.setChains(this, nodes, flag);
    }
  }
  public boolean isValid () {
    return ((isVirtual() && getCurrentRank() >= 0 && reverse_edge.size() > 1) ||
            (!isVirtual() && getCurrentRank() >= 0));
  }

//*****************************************************************************
  private void resetSubTree() {
    //    System.out.println("reseting: " + getName() + ", subtree: " + subtree);
    setSubTree(false);
    Iterator eIt = iterator();
    while (eIt.hasNext()) {
      IDNode other = (IDNode)(((Edge)eIt.next()).getEndNode()).getFront();      
      if (other.isSubTree()) {
        other.resetSubTree();
      } 
    }
  }
  public void generateSubTreeInfo (final double threshold,
                                   SubTree subtree) {
    generateInfo(threshold, subtree);
    resetSubTree();
  }
  private void generateInfo (final double threshold,
                             SubTree subtree) {
    setSubTree(true);
    for (Edge e : edge) {
      IDNode other = (IDNode)e.getEndNode().getFront();
      if (!other.isSubTree()) {
        if (!other.interesting) {
          // recurse
          other.generateInfo(threshold, subtree);           
          Formula formula = other.getFormula();
          SimpleTptpParserOutput.Source source = formula.getSource();
          String sourceInfo = source.toString();
          // check for theory equality parent
          String eqString = Formula.FORMULA_THEORY_EQUALITY;
          boolean flag = sourceInfo.contains(eqString);
          subtree.equality = subtree.equality && flag;
          // check status of inference
          // if not inference, then unknown
          // if inference and sab, then sab
          // if inference and thm, and all are thm, then thm
          // else unk
          if (subtree.statusInfo != null) {
            if (sourceInfo.contains(Formula.FORMULA_STATUS_THM)) {              
              if (subtree.statusInfo.equals("")) {
                // not set yet
                subtree.statusInfo = Formula.FORMULA_STATUS_THM;
              } 
            } else if (sourceInfo.contains(Formula.FORMULA_STATUS_SAB)) {
              // if any are sab, its sab
              if (!subtree.statusInfo.equals(Formula.FORMULA_STATUS_SAB)) {
                subtree.statusInfo = Formula.FORMULA_STATUS_SAB;
              }
            } else {
              // make unknown unless already established as sab
              if (!subtree.statusInfo.equals(Formula.FORMULA_STATUS_SAB)) {
                subtree.statusInfo = Formula.FORMULA_STATUS_UNK;
              }
            }
            System.out.println("status now: " + subtree.statusInfo);
          }
          // check split info
          /*
          if (subtree.splitInfo != null) {
            // check if other is a split child
            if (!subtree.splitInfo.equals("")) {
              // add comma
              subtree.splitInfo += ",";
            }
            subtree.splitInfo += "split";
          }
          */
        } else {
          if (subtree.parents != null) {
            subtree.parents.add(other);
          }
        }
      }
    }
  }
  

//*****************************************************************************
  public void setChains (Node start, Vector nodes, boolean flag) {
    // set this node as visited
    setVisited(start.getId());
    // add this node
    // if current node is a bend node and next node is on a removed rank
    // do not add this bend node, next node, and node after that
    boolean added = true;
    if (getCurrentRank() < 0) {
      added = false;
    }
    if (added) {
      nodes.add(this);
    }
    // start recursion
    Iterator eIt = iterator();
    while (eIt.hasNext()) {      
      Edge edge = (Edge)eIt.next();
      Node next = edge.getEndNode();
      if (!((IDNode)next).isVisited(start.getId())) {
        if (!(!next.isVirtual() && ((IDNode)next).getCurrentRank() >= 0 && ((IDNode)next).isInteresting())) {
          next.setChains(start, nodes, flag);
        } 
        else {
          ((IDNode)start).upParents.add((IDNode)next);
          ((IDNode)next).setVisited(start.getId());
          nodes.add(next);
          setBezierChain(nodes);
          nodes.remove(nodes.size()-1);
        }
      } 
    }
    // remove this node for backtracking
    if (added) {
      nodes.remove(nodes.size()-1);
    }
    // return recursed chain
  }

  public void setBezierChain (Vector nodes) {
    // start from beginning
    Vector points = new Vector();
    IDNode current = (IDNode)nodes.elementAt(0);
    points.add(current.makePoint());
    if (nodes.size() < 2) {
      //System.out.println("not enough nodes");
      System.exit(0);
    }
    if (((IDNode)nodes.elementAt(nodes.size()-1)).getCurrentRank() < 0) {
      //System.out.println("last was somehow rank = -1");
      System.exit(0);
    }
    for (int i = 1; i < nodes.size(); i++) {
      IDNode next = (IDNode)nodes.elementAt(i);
      //System.out.println("i: " + i + "next rank: " + next.getCurrentRank());
      points.add(next.makePoint());
      if (next.isValid()) {
        // add NodePair
        //System.out.println("i: " + i + " add pair / " + nodes.size());
        if (current.addUp(next)) {
          NodePair pair = new NodePair(current, next);
          BezierChain bc = new BezierChain(current, next, points);
          //bc.show();
          g.ctable.put(pair, bc);
        }        
        // reset
        points = new Vector();
        current = next;
        points.add(current.makePoint());
      }
    }
  }


  /* If it's a star, or if the inference_info slot has a assumptions record
     with a non-empty list of assumptions => (assumption = true) */
  //return true if "assumption", meaning formula is an assumption or not all assumptions are discharged
  public boolean isAssumption () {
    return assumption;
  }
  public void setAssumption () {
    if (isVisited()) {
      return;
    }
    setVisited(1);
    if (!isVirtual() && this.edge.size() == 0) {
      //for real formulae, we know if it is an assumption already
      assumption = f.isAssumption();
      return;
    }
    //if all parents are assumptions, then this virtual node is an assumption
    assumption = true;
    Iterator eIt = iterator();
    while (eIt.hasNext()) {
      Edge edge = (Edge)eIt.next();
      IDNode next = (IDNode)edge.getEndNode();
      next.setAssumption();
      assumption = assumption && next.assumption;
    }
//DEBUG System.out.println("Vnode: " + getName() + ":  assumption: " + assumption);
  }
  //return true if logical consequence of axioms
  public boolean isLemma () {
    return lemma;
  }  
  public void setNotLemma () {
    lemma = false;
  }
  //set the logical consequence of axiom
  public void setLemma () {
    if (isVisited()) {
      return;
    }
    setVisited(1);
    if (!isVirtual()) {
      if (isConjecture()) {
        return;
      }
      if (getRank() == 0) {
        lemma = true;
        return;
      }
    }
    lemma = true;
    Iterator eIt = iterator();
    while (eIt.hasNext()) {
      Edge edge = (Edge)eIt.next();
      IDNode next = (IDNode)edge.getEndNode();
      next.setLemma();
      lemma = lemma && next.lemma;
    }
  }

  public boolean isConjecture () {
    boolean flag =  (f.getType().equals(Formula.FORMULA_TYPE_NEG_CONJ_D) ||
                     f.getType().equals(Formula.FORMULA_TYPE_NEG_CONJ) ||
                     f.getType().equals(Formula.FORMULA_TYPE_CONJ) ||
                     f.isFalseClause());
    /*
    //System.out.println("Formula: " + f.getName());
    if (flag) {
      //System.out.println("this is a conjecture type");
    }
    else {
      //System.out.println("this is not a conjecture type");
    }
    */
    return flag;
  }

  public void setInteresting(double synopsisThreshold, boolean draw) {
    if (isVirtual())
      return;
    boolean check = false;
    boolean agint_called = g.idv.agint_called;
    int currentHeight = getRank() * IDGraph.YSPLIT;
    //    System.out.println("redline: " + g.idv.getRedlineHeight(draw) + ", current: " + currentHeight);
    if (g.idv.getRedlineHeight(draw) > currentHeight) {
      //      System.out.println("node is below red line: " + getName());
      interesting = false;
      return;
    }
    if (!agint_called) {
      interesting = true;
      return;
    }
    interesting = f.getInteresting() >= g.idv.getSynopsisThreshold();
    if (istatus == IStatus.ITRUE) {
      interesting = true;
    } else if (istatus == IStatus.IFALSE) {
      interesting = false;
    } else {
      // IStatus.NOTYET, interesting status not set yet, so determine by actual interestingness value
    }
  }
  public boolean isInteresting () { return interesting; }

  public boolean equals (Object other) {
    if (other instanceof IDNode == false) {
      throw new RuntimeException("Error: IDNode.equals(other): " +
                                 "other MUST be instanceof IDNode"); 
    }
    IDNode that = (IDNode)other;
    return this.getId() == that.getId();
  }

  // remove methods used by IDGraph to add bend virtual nodes
  public Vector splitEdges (int max) {
    Vector bendEdges = new Vector();
    Vector newNodes = new Vector();
    while (!edge.isEmpty()) {
      IDNode newNode = new IDNode(max, -1, g); // no rank
      Edge remEdge = (Edge)edge.remove(0); // remove first edge

      // get end node 
      IDNode endNode = (IDNode)remEdge.getEndNode();

      // remove from end node's reverse edge list
      endNode.reverse_edge.remove(remEdge);

      // replace with new one
      remEdge.setEndNode(newNode);
      bendEdges.add(remEdge);
      
      // add bent remEdge to reverse_edge list of newNode
      newNode.reverse_edge.add(remEdge);

      // create and add new edge between new and end node
      newNode.addEdge(endNode);

      // set coordinates for new node
      newNode.x = (this.x + endNode.x) / 2.0;
      newNode.y = (this.y + endNode.y) / 2.0;

      // add to list to send back to graph node list
      newNodes.add(newNode);
      max++; // inc id
    }
    edge = bendEdges;
    return newNodes;
  }
  
  public void setPolygon () {
//DEBUG System.out.println("set polygon for role " + f.getType());
    if (sp != null) {
      //System.out.println("st polygon, sp != null");
      // set polygon based on formula type
      if (f.getType().equals(Formula.FORMULA_TYPE_AXIOM) || 
          f.getType().equals(Formula.FORMULA_TYPE_INITIAL)) {
        setAxiomNode();      
      } else if (f.getType().equals(Formula.FORMULA_TYPE_DEFINITION)) {
        setDefinitionNode();
      } else if (f.getType().equals(Formula.FORMULA_TYPE_ASSUMPTION)) {
        setAssumptionNode();
      } else if (f.getType().equals(Formula.FORMULA_TYPE_CONJ)) {
        setConjectureNode();
      } else if (f.isFalseClause()) {
        setFalseNode();
      } else if (f.getType().equals(Formula.FORMULA_TYPE_NEG_CONJ) ||
                 f.getType().equals(Formula.FORMULA_TYPE_NEG_CONJ_D)) {
        setNegatedConjectureNode();
      } else if (f.getType().equals(Formula.FORMULA_TYPE_HYP)) {
        setHypothesisNode();
      } else if (f.getType().equals(Formula.FORMULA_TYPE_LEMMA)) {
        setLemmaNode();      
      } else if (f.getType().equals(Formula.FORMULA_TYPE_THEOREM)) {
        setTheoremNode();      
      } else if (f.getSource().toString().startsWith("introduced(")) {
        setIntroducedNode();
      } else {
        setPlainNode();
      }
    }
  }

  public void closeWindows () {
    //    System.out.println("close window ID: " + getName());
    if (isVirtual() || sp == null)
      return;
    //System.out.println(" close it now!");
    sp.closeWindows();
  }

  public void paint (Graphics2D g) {
    //System.out.println("paint x:" + x + ", rounded x: " + getRoundedX() + ", y: " + y);
    //g.setColor(Color.red);
    // g.fillOval((int)x, (int)y, 200,200);
    Polygon p;
    int x1, y1, y2;
    
    if (virtual) { 
      //      g.drawString(getName(), (int)x-20, (int)y+10);
      return; 
    }  //don't draw virtual nodes

    if (!isInteresting()) {
      return;
    }

    /*
      Good Mode:
      Show only axioms and lemmas (logical consequence of axioms)
      Meaning, no conjectures, no non lemmas, and no assumptions
    */
    if (getGraph().idv.isGood()) {
      if (rank == 0) {
        if (isConjecture()) {
          return;
        }
      } else {
        if (!isLemma()) {
          return;
        }
      }
      if (getFormula().isAssumption()) {
        return;
      }
    }

    if (!getGraph().idv.isProtected() && !leafExists()) {
      return;
    }
    if (f == null) {
      //System.out.println("no formula"); // problem
      System.exit(-1);
      //g.drawString(getName(), (int)x + 5, (int)y + 5);
      return;
    }

    //get color
    if (f.getFormat().equals(Formula.FORMULA_FORMAT_CNF)) {
      sp.setColor(cnfColor);              
    } else if (f.getFormat().equals(Formula.FORMULA_FORMAT_FOF)) {
      sp.setColor(fofColor);              
    } else if (f.getFormat().equals(Formula.FORMULA_FORMAT_THF)) {
      sp.setColor(thfColor);              
    } else {
      System.out.println("Format not found, failure");  //only two formats atm
      System.exit(-1); 
    }
    //    setFont(g);
    sp.paint(g);
    
    // draw little circle on top of node if resolved by equality
    if (f.isEquality()) {
      g.setColor(Color.white);
      //g.fillOval((int)getRoundedX() - getScale()/4, (int)y - getScale() - getScale()/2 + adjustY(), getScale()/2, getScale()/2);
      g.fillOval((int)getRoundedX() - getScale()/4, (int)y - getScale() - getScale()/2 + adjustY(), getScale()/2, getScale()/2);
      g.setColor(Color.black);
      g.drawOval((int)getRoundedX() - getScale()/4, (int)y - getScale() - getScale()/2 + adjustY(), getScale()/2, getScale()/2);
      x1 = (int)getRoundedX() - getScale() / 4 + 8;
      y1 = (int)y - getScale() - getScale() / 2 + adjustY() + 10;
      y2 = y1 + 6;
      g.setStroke(new BasicStroke((float) 1.0));
      g.drawLine(x1, y1, x1 + 10, y1);
      g.drawLine(x1, y2, x1 + 10, y2);
      g.setStroke(new BasicStroke((float) 1.0));
      ////System.out.println("Draw oval");
    }

    if (!f.isTheorem() && getRank() != 0) {
      g.setColor(Color.red);
      g.fillOval((int)getRoundedX() - getScale()/4, (int)y - getScale() + adjustY(), getScale()/2, getScale()/2);
      g.setColor(Color.black);
      g.drawOval((int)getRoundedX() - getScale()/4, (int)y - getScale() + adjustY(), getScale()/2, getScale()/2);
    }

    if (f.isSplitParent()) {
      g.setColor(Color.red);
      p = new Polygon();
      x1 = (int)getRoundedX() - getScale()/4;
      y1 = (int)y + getScale() + adjustY() + getScale() / 2;
      p.addPoint(x1, y1);
      p.addPoint(x1 + getScale() / 2, y1);
      p.addPoint(x1 + getScale() / 4, y1 - getScale() / 2);
      g.setColor(Color.red);
      g.fillPolygon(p);
      g.setColor(Color.black);
      g.drawPolygon(p);
    }

    if (this.g.idv.isVerified()) {
      switch (vstatus) {
      case VNOTYET:
        // do nothing
        break;
      case VTRUE:
        // draw check mark below node in green
        p = new Polygon();
        x1 = (int)getRoundedX() - getScale() / 4;
        y1 = (int)y + getScale() + adjustY();
        p.addPoint(x1                 , y1);
        p.addPoint(x1 - getScale() / 4, y1 - getScale() / 4);
        p.addPoint(x1 - getScale() / 2, y1);
        p.addPoint(x1                 , y1 + getScale() / 2);
        p.addPoint(x1 + getScale()    , y1 - getScale() / 2);
        p.addPoint(x1 + getScale() - getScale() / 8, y1 - getScale() / 2 - getScale() / 8);
        g.setColor(Color.green);
        g.fillPolygon(p);
        g.setStroke(new BasicStroke((float) 1.5));
        g.setColor(Color.black);
        g.drawPolygon(p);
        break;
      case VFALSE:
        // draw x mark below node in red
        p = new Polygon();
        x1 = (int)getRoundedX();
        y1 = (int)y + getScale() + adjustY();
        p.addPoint(x1                 , y1 - getScale() / 4);
        p.addPoint(x1 - getScale() / 2 + getScale() / 8, y1 - getScale() / 2);
        p.addPoint(x1 - getScale() / 2 - getScale() / 4, y1 - getScale() / 2);
        p.addPoint(x1 - getScale() / 4, y1);
        p.addPoint(x1 - getScale() / 2 - getScale() / 4, y1 + getScale() / 2);
        p.addPoint(x1 - getScale() / 2 + getScale() / 8, y1 + getScale() / 2);
        p.addPoint(x1                 , y1 + getScale() / 4);
        p.addPoint(x1 + getScale() / 2 - getScale() / 8, y1 + getScale() / 2);
        p.addPoint(x1 + getScale() / 2 + getScale() / 4, y1 + getScale() / 2);
        p.addPoint(x1 + getScale() / 4, y1);
        p.addPoint(x1 + getScale() / 2 + getScale() / 4, y1 - getScale() / 2);
        p.addPoint(x1 + getScale() / 2 - getScale() / 8, y1 - getScale() / 2);
        g.setColor(Color.red);
        g.fillPolygon(p);
        g.setStroke(new BasicStroke((float) 1.5));
        g.setColor(Color.black);
        g.drawPolygon(p);
        break;
      }
    }
  }
  
  private int adjustY() {
    return adjust_y;
  }

  private int getScale () {
    // if virtual just return scale
    if (isVirtual())
      return scale;
    // if no synopsis selected, just return scale
    if (!this.g.idv.isSynopsis())
      return scale;
    // synopsis selected, return different sized nodes
    double value;
    if (istatus == IStatus.IFALSE) {
      value = 0;
    } else if (istatus == IStatus.ITRUE) {
      value = 1;
    } else {
      value = f.getInteresting();
    }
    double percent = value + (1.0 - value) * .5;
    return (int)((double)scale * percent);
  }
  
  public void setSelected () {
    isSelected = true;
    setPolygon();
  }
  public void clearSelected () {
    isSelected = false;
    setPolygon();
  }

  private void setAxiomNode () {
    //System.out.println("draw axiom");
    //upside down triangle
    /*
          ----
          \  /
           \/
           x, y (0,0)
           -50,-50, +50,-50, 0,50

    */
    int dx = (int)getRoundedX();
    int dy = (int)getY() + 10;
    adjust_y = 10;
    sp.reset();   //alternative is use invalidate() and set 3 points manually
    sp.addPoint(dx - getScale(), dy - getScale());
    sp.addPoint(dx + getScale(), dy - getScale());
    sp.addPoint(dx             , dy + getScale());
  }

  private void setDefinitionNode () {
    //System.out.println("draw definition");
    //upside down triangle
    /*
          ----
          \  /
           | |
           ---
           x, y (0,0)
           -50,-50, +50,-50, 0,50
    */
    int dx = (int)getRoundedX();
    int dy = (int)getY() + 10;
    adjust_y = 10;
    sp.reset();   //alternative is use invalidate() and set 3 points manually
    sp.addPoint(dx - getScale(), dy - getScale());
    sp.addPoint(dx + getScale(), dy - getScale());
    sp.addPoint(dx + (getScale()/2), dy);
    sp.addPoint(dx + (getScale()/2), dy + getScale());
    sp.addPoint(dx - (getScale()/2), dy + getScale());
    sp.addPoint(dx - (getScale()/2), dy);
  }

  private void setIntroducedNode () {
    //System.out.println("draw introduced");
    //triangle
    /*
           /\
          /  \
          ----
           x, y (0,0)
           -50,-50, +50,-50, 0,50
    */
    int dx = (int)getRoundedX();
    int dy = (int)getY() + 0;
    adjust_y = 0;
    sp.reset();   //alternative is use invalidate() and set 3 points manually
    sp.addPoint(dx             , dy - getScale());
    sp.addPoint(dx - getScale(), dy + getScale());
    sp.addPoint(dx + getScale(), dy + getScale());
  }

  private void setPlainNode () {
    //regular circle
    int dx = (int)getRoundedX();
    int dy = (int)y;
    sp.reset();
    /*
      FOR(i=0;i<NUM_LINES;i++){
	xcoord = l * cos(i*2*PI/NUM_LINES);
	ycoord = l * sin(i*2*PI/NUM_LINES);	
    */
    for (int i = 0; i < 20; i++) {
      sp.addPoint((int)(getScale() * Math.cos(i*2*Math.PI/20) + dx),
             (int)(getScale() * Math.sin(i*2*Math.PI/20) + dy));
    }
  }

  private void setConjectureNode () {
    //draw house
    /*      /\
           /  \
           |  | 
            --
           50,50 50,0 0,-50 -50,0, -50,50
    */
    sp.reset();
    int dx = (int)getRoundedX();
    int dy = (int)y - 10;
    adjust_y = -10;
    sp.addPoint(dx + getScale(), dy + getScale());
    sp.addPoint(dx + getScale(), dy        );
    sp.addPoint(dx             , dy - getScale());
    sp.addPoint(dx - getScale(), dy        );
    sp.addPoint(dx - getScale(), dy + getScale());
  }

  private void setNegatedConjectureNode () {
    //draw upsidedown house
    /*      --
           |  |
           \  / 
            \/
           -50,-50 -50,0 0,50, 50,0, 50,-50
    */
    sp.reset();
    int dx = (int)getRoundedX();
    int dy = (int)y + 5;
    adjust_y = 5;
    sp.addPoint(dx - getScale(), dy - getScale());
    sp.addPoint(dx - getScale(), dy        );
    sp.addPoint(dx             , dy + getScale());
    sp.addPoint(dx + getScale(), dy        );
    sp.addPoint(dx + getScale(), dy - getScale());
  }

  private void setFalseNode () {
    //draw rectangle
    /*      --
           |  |
           |  |
            --
           -50,-50 -50,50 50,50, 50,-50
    */
    sp.reset();
    int dx = (int)getRoundedX();
    int dy = (int)y;
    sp.addPoint(dx - getScale(), dy - getScale());
    sp.addPoint(dx - getScale(), dy + getScale());
    sp.addPoint(dx + getScale(), dy + getScale());
    sp.addPoint(dx + getScale(), dy - getScale());
  }

  private void setHypothesisNode () {
    //draw upside down trapezoid
    /*    ----
          \  /
           --
           -50,-50 -25,50 25,50 50,-50
    */
    sp.reset();
    int dx = (int)getRoundedX();
    int dy = (int)y;
    adjust_y = 10;
    sp.addPoint(dx - getScale()    , dy - getScale() + 10);
    sp.addPoint(dx - getScale() / 2, dy + getScale() - 10);
    sp.addPoint(dx + getScale() / 2, dy + getScale() - 10);
    sp.addPoint(dx + getScale()    , dy - getScale() + 10);        
  }

  private void setLemmaNode () {
    //draw diamond
    /*      
           / \
           \ /
            
    */
    sp.reset();
    int dx = (int)getRoundedX();
    int dy = (int)y;
    sp.addPoint(dx                 , (int) (dy - getScale() / 1.3));
    sp.addPoint(dx - getScale()    , dy             );
    sp.addPoint(dx                 , (int) (dy + getScale() / 1.3));
    sp.addPoint(dx + getScale()    , dy             );        
  }  

  private void setTheoremNode () {
    //draw hexagon
    /*      
           / \
           | |
           \ /
            
    */
    sp.reset();
    int dx = (int)getRoundedX();
    int dy = (int)y;
    sp.addPoint(dx                 , (int) (dy - getScale()));
    sp.addPoint(dx - getScale()    , (int) (dy - getScale() * .3));
    sp.addPoint(dx - getScale()    , (int) (dy + getScale() * .3));
    sp.addPoint(dx                 , (int) (dy + getScale()));
    sp.addPoint(dx + getScale()    , (int) (dy + getScale() * .3));        
    sp.addPoint(dx + getScale()    , (int) (dy - getScale() * .3));
  }  

  private void setAssumptionNode () {
    //draw star
    sp.reset();
    int dx = (int)getRoundedX();
    int dy = (int)y;
    sp.addPoint((int)(dx                  ), (int) (dy - getScale()     ));
    sp.addPoint((int)(dx - getScale() * .3), (int) (dy - getScale() * .3));
    sp.addPoint((int)(dx - getScale()     ), (int) (dy - getScale() * .3));
    sp.addPoint((int)(dx - getScale() * .4), (int) (dy + getScale() * .3));
    sp.addPoint((int)(dx - getScale() * .7), (int) (dy + getScale()     ));
    sp.addPoint((int)(dx                  ), (int) (dy + getScale() * .6));
    sp.addPoint((int)(dx + getScale() * .7), (int) (dy + getScale()     ));
    sp.addPoint((int)(dx + getScale() * .4), (int) (dy + getScale() * .3));
    sp.addPoint((int)(dx + getScale()     ), (int) (dy - getScale() * .3));
    sp.addPoint((int)(dx + getScale() * .3), (int) (dy - getScale() * .3));
  }  

  public static class NameComparer implements Comparator {
    public int compare(Object obj1, Object obj2) {
      String s1 = ((IDNode)obj1).getFormula().getUnbuffedName();
      String s2 = ((IDNode)obj2).getFormula().getUnbuffedName();
      return s1.compareTo(s2);
    }
  }
  public static class XComparer implements Comparator {
    public int compare(Object obj1, Object obj2) {
      int x1 = (int)((IDNode)obj1).getX();
      int x2 = (int)((IDNode)obj2).getX();
      return x1 - x2;
    }    
  }

  public void verify (String ATPSelected, boolean gdv) {
    if (virtual)
      return;
    if (!f.isTheorem())
      return;
    if (!isInteresting()) 
      return;
    if (vstatus == VStatus.VTRUE || vstatus == VStatus.VFALSE) {
      System.out.println("skip");
      return;
    }
    sp.createTextWindow(false);
    sp.verify(ATPSelected, gdv);
  }
  public void resetLeaf () {
    last_visited = -1;
    leaf = null;
  }
  public IDNode setLeaves () {
    if (isVisited()) {
      return leaf;
    }
    setVisited(1);
    if (!isVirtual()) {
      if (getFormula().getInteresting() >= this.g.idv.getSynopsisThreshold()) {
        leaf = this;
        return leaf;
      }
    }
    for (Edge e : edge) {
      IDNode other = (IDNode)e.getEndNode();
      leaf = other.setLeaves();
      if (leaf != null) {
        break;
      }
    }
    return leaf;
  }
  public boolean leafExists () {
    return leaf != null;
  }
}
class SubTree {
  public TreeSet<IDNode> parents;
  public String splitInfo;
  public String statusInfo;
  public boolean equality;
  public SubTree() {
    parents = new TreeSet(new IDNode.NameComparer());
    splitInfo = "";
    statusInfo = "";
    equality = true;
  }
}
