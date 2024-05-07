// Christian Duncan
// Node Class
//    for GD2004, Graph Drawing Contest

// package GD4;
import java.util.Iterator;
import java.util.*;
import java.awt.event.*;
import javax.swing.event.*;
import java.awt.*;
import javax.swing.*;

/*********************
 * A Node in the Graph
 *    Abstract Class
 *    Stores:
 *       id - integer index into Graph Vector list (currently irrelevant!)
 *       X, Y - double location coordinates
 *********************/
public abstract class Node {
  public static final int scale = 50;

  protected int     id;        // unique id of the node (based on loc in vector)
  protected double  x, y;      // coords of the node
  protected boolean pinState = false;  // True if "pinned down"

  protected boolean virtual  = false;  // True if virtual place holding node
  protected Node front;   // If virtual, this is the real node in front of this node
  protected Node back;    // If Virtual, this is the real node behind this node            

  protected int front_depth = -1; //record front depth when set by getFrontDepth
  protected int back_depth = -1;  //record back depth when set by getBackDepth

  protected SensitivePolygon sp;    // polygon for the node, for display
  protected IDV              idv;   // interactive derivation viewer
  protected boolean isSelected = false;

  public Node (int id, boolean virtual, IDV idv) {
    super();
    this.x       = 0; 
    this.y       = 0; 
    this.id      = id; 
    this.virtual = virtual;
    this.idv     = idv;
  }
  
  /* Accessor methods */
  public int getId() { return id; }
  public double getX() { return x; }
  public double getRoundedX () { return x; }
  public double getY() { return y; }
  public boolean isPinned() { return pinState; }
  public boolean isVirtual() { return virtual; }

  // Return iterator of incident edges
  public abstract Iterator iterator ();      // direct parents
  public abstract Iterator reverse_iterator (); // same as iterator if undirected graph

  public abstract Iterator upIterator (); // indirect parent nodes
  public abstract Iterator downIterator (); // indirect children nodes
  public abstract void setChains (Node node, Vector points, boolean flag);
  public abstract boolean addUp (Node node);
  public abstract void setBezierChain (Vector nodes);

  public abstract Node getFront (); //helper function for a virtual node
  public abstract Node getBack (); //helper function for a virtual node

  public abstract int getFrontDepth (); //get max distance from front nodes
  public abstract int getBackDepth ();  //get max distance from back nodes

  public abstract String getName ();     // Node name
  public abstract String getText ();     // Node extra info goes here
  
  /* Mutator methods */
  // public void setId(int _id) { id = _id; }
  public void setX(double _x) { 
    x = _x; 
  }
  public void setY(double _y) { 
    y = _y; 
  }
  public void flipPinState() { pinState = !pinState; }
  public void setPinned(boolean newState) { pinState = newState; }

  /* Add an edge to the list of edges
   */
  abstract void addEdge(Node other);
  
  public double distance(Node other) {
    return Math.sqrt(sqrDistance(other));
  }
  
  public double sqrDistance(Node other) {
    double dx = other.x - this.x;
    double dy = other.y - this.y;
    return dx * dx + dy * dy;
  }

  // Two nodes are equal if they have the same ID!
  public boolean equals(Node other) {
    return this.id == other.id;
  }

  //For debug purposes only
  public void show () {
    System.out.println("Node: [" + id + "]  (" + x + ",  y: " + y + ")");
  }

  //GraphPanel methods for displaying 
  public void initPolygon () {
    if (virtual) return;
    sp = new SensitivePolygon(idv.gridScreen, this);
    setPolygon();
  }
  // set polygon points that represent this node, reset before setting
  public SensitivePolygon getPolygon () { return sp; }
  public abstract void setPolygon ();
  public boolean processPoint(Point p) {
    if (!virtual) {
      return sp.processPoint(p);
    } else {
      return false;
    }    
  }
  public void highlight() { sp.highlight(); }
  public void unhighlight() { sp.unhighlight(); }
  public void openTextWindow() { sp.createTextWindow(true); }
  // paint
  public abstract void paint (Graphics2D g);
  public abstract void setSelected ();
  public abstract void clearSelected ();
  public boolean isSelected () { return isSelected; }
  public abstract void invalidateEdges ();


}
