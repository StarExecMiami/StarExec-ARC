// Christian Duncan
// Graph Class
//    for GD2004, Graph Drawing Contest

// package GD4;

import java.util.*;
import java.awt.Rectangle;
import java.awt.event.*;

/*********************
 * Graph Abstract Class
 *    Represents a Graph
 *    Can be stored in many different ways... efficiency trade-offs
 *    However, all Graph subclasses must have certain methods
 *    in common...
 *********************/
public abstract class Graph {
  protected Rectangle bnds;
  private Node selectedNode;
   
    public Graph() {
      selectedNode = null;
      bnds = null;
  }

  // Make a full new copy of this graph
  public Graph deepClone() throws CloneNotSupportedException {
    throw new CloneNotSupportedException("No clone support for this graph");
  }
  
  // Update graph info if copy is being used
  public abstract void invalidate ();

  // Add a node specifying its x and y locations
  public abstract void addNode(double x, double y);
  
  // Add an edge between two Nodes (referenced by index)
  //    Returns true if successful and false otherwise
  public abstract boolean addEdge(int a, int b);
  
  // Get list of all nodes (Iterator of Nodes)
  public abstract Iterator nodeIterator();
  
  // Get list of ALL edges (Iterator of Edges)
  public abstract Iterator edgeIterator();
  
  public abstract int numNodes();
  public abstract int numEdges();
  
  /**
   * Sets selected node
   *   to the given node...
   **/
  public void setSelectedNode(Node n) {
    selectedNode = n;
  }
  
  /**
     Do we have any node(s) selected?
  **/
  public boolean hasSelectedNodes() { return selectedNode != null; }
  
  /**
   * Unselects all nodes (currently one)
   **/
  public void unselectNodes() {
    selectedNode = null;
  }
  
  /**
   * isSelectedNode(Node a)
   *    returns true if given node is a selected node in this graph
   */
  public boolean isSelectedNode(Node a) {
    return (a == selectedNode);
  }
  
  /**
   * isSelectedEdge(Node a)
   *    returns true if given edge has an endpoint that is selected
   */
  public boolean isSelectedEdge(Edge e) {
    return (e != null && selectedNode != null && 
            (e.getStartNode() == selectedNode || 
             e.getEndNode() == selectedNode));
  }
  
  /**
   * Moves selected node to given location
   *  If others are highlighted move same displacement
   **/
  public void moveSelectedNodes(double x, double y) {
    if (selectedNode == null) {
      // No specific node selected... do nothing?
      return;
    }
    
    // With multiple nodes - compute displacement
    // For single node - just move it
    selectedNode.setX(x);
    selectedNode.setY(y);
    selectedNode.setPolygon();
    
    // Update the bounding box...
    // Currently we just invalidate it entirely...
    bnds = null;
  }
  
  /**
   * Moves the given node to given location
   * Assumes n is part of the current graph
   *    Result is unstable if not
   *    (Verification not done for performance space/time reasons!)  
   **/
  public void moveNode(Node n, double x, double y) {
    ((IDNode)n).setX(x);
    //      ((IDNode)n).setY(y);
    n.setPolygon();
    //        n.invalidateEdges();
    bnds = null;
  }
  
  // Returns the closest node to the given location
  //     with a given tolerance. 
  //     null if none present
  public Node nearestNode(double x, double y, double tolerance) {
    Node nearest = null;
    double nearestSquaredDist = tolerance * tolerance;
    
    Iterator it = nodeIterator();
    while (it.hasNext()) {
      // Compute distance to next node
      Node n = (Node) it.next();
      double dx = x - n.getX();
      double dy = y - n.getY();
      double sqDist = dx * dx + dy * dy;
      if (sqDist < nearestSquaredDist) {
        nearest = n;
        nearestSquaredDist = sqDist;
      }
    }
    return nearest;
  }
  
  // Returns the stored bounds
  public Rectangle getBounds() {
    if (bnds == null) {
      // Not computed yet
      bnds = getBoundsFromScratch();
    }
    
    return new Rectangle(bnds);
  }
  
  // Returns the bounds of the current node set
  //     Notice: This is very inefficient
  //             Ideally subclasses store the value
  //             and return it - rather than recalculating each time
  protected Rectangle getBoundsFromScratch() {
    double minX = 0, minY = 0, maxX = 0, maxY = 0;
    Node n;
    Iterator it;
    
    it = nodeIterator();
    if (it.hasNext() == false) {
      // No elements at all?
      return new Rectangle(0, 0, 0, 0);
    }
    
    n = (Node) it.next();
    minX = maxX = n.getX();
    //minY = maxY = n.getY();
    int currentRank = 0;
    if (currentRank < ((IDNode)n).getCurrentRank()) {
      currentRank = ((IDNode)n).getCurrentRank();
    }
    while (it.hasNext()) {
      // Compute distance to next node
      n = (Node) it.next();
      if (n.getX() < minX) {
        minX = n.getX();
      } else if (n.getX() > maxX) {
        maxX = n.getX();
      }
      if (currentRank < ((IDNode)n).getCurrentRank()) {
        currentRank = ((IDNode)n).getCurrentRank();
      }
      
      /*
        if (n.getY() < minY) {
        minY = n.getY();
        } else if (n.getY() > maxY) {
        maxY = n.getY();
        }
      */
    }
    minY = 0;
    maxY = currentRank * IDGraph.YSPLIT;
    
    //    System.out.println("max X: " + maxX);
    //    System.out.println("max Y: " + maxY);
    return new Rectangle((int) Math.floor(minX), 
                         (int) Math.floor(minY), 
                         (int) Math.ceil(maxX - minX), 
                         (int) Math.ceil(maxY - minY));
  }
  
  /**
   * countIntersections()
   *  Simply returns a count of the number of intersections
   *  Could be more efficient!!!
   **/
  public int countIntersections() {
    Vector res = findIntersections();
    return res.size();
  }
  
  /**
   * findIntersections()
   *  Computes all edge intersections with the given graph
   *  returns: A Vector of Intersections (2 Edges, one point)
   *
   *  Current technique: BRUTE-FORCE!
   *      Check every pair of edges for an intersection
   *      Will need to do plane-sweep if becomes SLOW!!!
   **/
  public Vector findIntersections() {
    Vector intersections = new Vector();
    Iterator listA = edgeIterator();
    int countA = 0;
    while (listA.hasNext()) {
      Edge edgeA = (Edge) listA.next();
      countA++;
      
      // Now check the other edges...
      Iterator listB = edgeIterator();
      
      //   but first skip until EdgeA (no duplicates)
      //   NOTE: Relies on fact that edgeIterator
      //         returns edges in SAME ORDER each time!!
      Edge edgeB;
      int countB = 0;
      while (listB.hasNext() && countB++ < countA) {
        listB.next();
      }
      
      // Now check the new edges with EdgeA
      while (listB.hasNext()) {
        edgeB = (Edge) listB.next();
        Intersection ab = new Intersection(edgeA, edgeB);
        if (ab.doesIntersect()){
          // There is an intersection point
          intersections.add(ab);
        }
      }
    }
    return intersections;
  }

  public abstract void mouseClicked (MouseEvent e);
  public abstract void mouseMoved (MouseEvent e);
}
