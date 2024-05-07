// Christian Duncan
// Edge Class
//    for GD2004, Graph Drawing Contest

// package GD4;

/*********************
 * An Edge in the Graph
 *    Has two parts - start and end to the edge
 *    These are Nodes
 *    Ideally we could make it more space efficient
 *    And store just Destination as every edge is attached
 *    to a start Node anyway.
 *    But this allows greater flexibility in the future
 *    Notice that edges are DIRECTED, so start and end are just
 *    names for the two nodes (for now).
 * Edges currently are now mutable for memory efficiency
 * 
 *
 *********************/

import java.lang.Object;
import java.awt.*;
import java.util.*;
import java.util.Random;

public class Edge {
  private Node start, end;
  private Vector chains;

  public Edge(Node _start, Node _end) {
    start = _start; end = _end; 
    chains = new Vector();
  }
  
  /* Accessor methods */
  public Node getStartNode() { return start; }
  public Node getEndNode() { return end; }
  
  /* Mutator methods */
  public void setStartNode (Node start) { this.start = start; }
  public void setEndNode (Node end) { this.end = end; }

  /* Return length of edge */
  public double length() { return start.distance(end); }
  public double sqrLength() { return start.sqrDistance(end); }
  
  //dot product
  public double dot (Edge that) {
    double ax = this.end.getX() - this.start.getX();
    double ay = this.end.getY() - this.start.getY();
    double bx = that.end.getX() - that.start.getX();
    double by = that.end.getY() - that.start.getY();
    return ax * bx + ay * by;
  }

  public double dot (GravityForce gforce) {
    double ax = this.end.getX() - this.start.getX();
    double ay = this.end.getY() - this.start.getY();
    return ax * gforce.getX() + ay * gforce.getY();
  }

  public boolean equals (Object other) {
    if (other instanceof Edge == false) {
      throw new RuntimeException("Error: Edge.equals(other): " +
                                 "other MUST be instanceof Edge"); 
    }
    Edge that = (Edge)other;
    return this.start.equals(that.start) && this.end.equals(that.end);
  }

  // must override hashCode since we overrided equals(Object other)
  public int hashCode () {
    return start.hashCode() * 37 + end.hashCode();
  }

  //arc cosine
  public double angle (Edge that) {
    /*
      A dot B = mag(A) * mag(B) cos (THETA)
      cos(THETA) = (A dot B) / (mag(A) * mag(B))
      THETA = cos ^ -1 (A dot B) / (mag(A) * mag(B))
    */
    return Math.acos(this.dot(that) / (this.length() * that.length()));
  }

  public double angle (GravityForce gforce) {
    return Math.acos(this.dot(gforce) / (this.length() * gforce.length()));
  }

  //cross product
  public double sign (Edge that) {
    double ax = this.end.getX() - this.start.getX();
    double ay = this.end.getY() - this.start.getY();
    double bx = that.end.getX() - that.start.getX();
    double by = that.end.getY() - that.start.getY();
    return ((ax * by - ay * bx) > 0) ? 1 : -1;
  }

  public double sign (GravityForce gforce) {
    double ax = this.end.getX() - this.start.getX();
    double ay = this.end.getY() - this.start.getY();
    return ((ax * gforce.getY() - ay * gforce.getX()) > 0) ? -1 : 1;
  }

  public void show () {
    //    start.show();
    //end.show();
  }
  
  public void invalidate () {
    //System.out.println("__________CLEARING CHAIN_________________");
    for (int i = 0; i < chains.size(); i++) {
      ((BezierChain)chains.elementAt(i)).clear();      
    }
    chains.clear();
  }

  public void paint (Graphics2D g) {
    Node a = getStartNode();
    IDNode b = (IDNode)getEndNode();

    // draw bezier curve from node a to b, if node a is not virtual
    /*
    if (a.virtual) { 
      //System.out.println("is virtual");
      return;    
    }
    // make sure start node is interesting
    if (!((IDNode)a).isInteresting()) { 
      //System.out.println("is not intersting");
      return;
    }
    */
    /*
    IDV idv = ((IDNode)a).getGraph().idv;
    if (idv.getRedlineHeight() > a.getY()) 
      return;
    */
    /*
      Good Mode:
      If node a is not a lemma, dont draw edge.
      If node a is an assumption, dont draw edge
    */
    IDV idv = ((IDNode)a).getGraph().idv;
    if (idv.isGood()) {
      if (!((IDNode)a).isLemma() || ((IDNode)b).isAssumption()) {
        return;
      }
    }
    // if indirect upper nodes is not empty, draw
    Iterator nIt = a.upIterator();
    while (nIt.hasNext()) {      
      b = (IDNode)nIt.next();      
      Edge.drawChains(a, b, g);
    }
    
  }

  public static void drawChains (Node a, Node b, Graphics2D g) {

    //if (!a.isVirtual())
    //System.out.println("Drawing chain a: " + a.getName());
    //if (!b.isVirtual())
    ////System.out.println("Drawing chain b: " + b.getName());

    /* Good Mode:
       If node a is not a lemma, don't draw edge
       If node a is an assumption, dont draw edge
    */
    IDV idv = ((IDNode)a).getGraph().idv;
    if (idv.isGood()) {
      //      if (!((IDNode)a).isLemma() || (((IDNode)a).isAssumption() && ((IDNode)b).isAssumption())) {
      if (!((IDNode)a).isLemma() || ((IDNode)b).isAssumption()) {
        return;
      }
    }
    if (!((IDNode)b).leafExists() && !idv.isProtected() && idv.agint_called) {
      return;
    }
    boolean draw = true;
    int height = idv.getRedlineHeight(draw);
    IDGraph graph = ((IDNode)a).getGraph();
    NodePair pair = new NodePair(a, b);
    //System.out.println("Find BC in hash table");

    BezierChain bc = (BezierChain)graph.ctable.get(pair);
    
    //System.out.println("drawing chain, size: " + bc.size());
    //System.out.println("a rank: " + ((IDNode)a).getRank());
    //System.out.println("b rank: " + ((IDNode)b).getRank());

    //    int aRank = ((IDNode)a).getRank();
    //    int bRank = ((IDNode)b).getRank();
    
    //    if ((aRank - bRank) == bc.size()) {
    // if points have been calculated before, use those
    for (int i = 0; i < bc.size(); i++) {
      //System.out.println("i: " + i);
      BezierCurve curve = bc.get(i);
      //System.out.println("   drawing curve");
      if (height > curve.p[0].y)
        break;
      drawBezierCurve(g, curve.p[0], curve.p[1], curve.p[2], curve.p[3], height);
      //System.out.println("   done drawing curve");
      /*
      }
    }
    else {
      // some ranks are missing, randomly remove x curves,
      // where x is the difference in ranks and bc.size()
      // connect rest with straight lines
      Vector curves = (Vector)(bc.getCurves()).clone();
      int size = curves.size();
      int diff = size - (aRank - bRank) - 1;
      System.out.println("size: " + size);
      System.out.println("diff: " + diff);
      for (int i = 0; i < diff; i++) {
        System.out.println("remove r: " + curves.size()/2);
        curves.remove(curves.size()/2);
      }

      // fix the y coordinates on the cloned curves
      int yStart = (int)a.getY();
      int yEnd = (int)b.getY();
      int gap = (yStart - yEnd) / curves.size();
      int current = yStart;
      for (int i = 0; i < curves.size(); i++) {
        int spread = gap / 4;
        BezierCurve curve = (BezierCurve)curves.elementAt(i);
        for (int j = 0; j < 4; j++) {
          curve.p[j].y = current - spread * j;
        }
        current -= gap;
      }

      // draw
      for (int i = 0; i < curves.size(); i++) {
        BezierCurve curve = (BezierCurve)curves.elementAt(i);
        drawBezierCurve(g, curve.p[0], curve.p[1], curve.p[2], curve.p[3]);
        if (i < curves.size() - 1) {
          BezierCurve next = (BezierCurve)curves.elementAt(i+1);
          g.drawLine(curve.p[3].x, curve.p[3].y, next.p[0].x, next.p[0].y);
        }
      }
        */
    }
    //System.out.println("drawing chain done");
  }

    
  /*  
  public void paint (IDGraph graph, Graphics2D g) {
    Node a = getStartNode();
    Node b = getEndNode();
    
    // if indirect upper nodes is not empty, draw
    Iterator nIt = a.upIterator();
    if (nIt.hasNext()) {
      drawChains(a, graph, g);
    }

    // draw bezier curve from node a to b, if node a is not virtual
    if (a.virtual) { 
      //System.out.println("is virtual");
      return;    
    }

    // make sure start node is interesting
    if (!((IDNode)a).isInteresting()) { 
      //System.out.println("is not intersting");
      return;
    }

    
    //  Now that we know this node is interesting nonvirtual,
    //  we have to recurse upwards to make sure that the nodes
    //  up top are all interesting nonvirtual or else we recurse
      
    //  we mark each node everytime we visit it.

    Vector p = new Vector();
    p.add(new Point((int)a.getRoundedX(),(int)a.getY()));
    Vector c = getChains(b, b.getId(), p);

    //System.out.println("# chains formed: " + c.size());
    
    // turn each chain of points into chain of bezier curves
    for (int i = 0; i < c.size(); i++) {
      int d = ((Vector)c.elementAt(i)).size();
      //System.out.println("i: " + i + " size is: " + d);
      BezierChain bc = transform((Vector)c.elementAt(i));
      chains.add(bc);
    }
    
    drawChain(g);
    //drawBezierCurve(g,a,b); // from node a to node b
    

  }

  Vector getChains (Node current, int Id, Vector points) {
    //System.out.println("Getting chains, on curent: " + current.getName());
      //if next node is 'valid', then we stop chain

    // set this node as visited
    ((IDNode)current).setVisited(Id);
    Vector c = new Vector();

    // add this node
    points.add(new Point((int)current.getRoundedX(),(int)current.getY()));
    Iterator eIt = current.iterator();
    while (eIt.hasNext()) {      
      Edge edge = (Edge)eIt.next();
      Node next = edge.getEndNode();
      //System.out.println("next node: " + next.getName());
      if (next.virtual) {
        //System.out.println(" -> virtual");
      }
      if (!((IDNode)next).isVisited(Id)) {
        //System.out.println(" not visited");
        if (!((IDNode)next).isInteresting() || next.virtual) {
          //System.out.println("  not interesting");
          // not interesting so recurse
          Vector nc = getChains(next, Id, points);
          c.addAll(nc);
        }
        else {
          //System.out.println("  is interesting");
        points.add(new Point((int)next.getRoundedX(),(int)next.getY()));

        // clone points, and add chain
        Vector newp = (Vector)points.clone();
        BezierChain bc = transform(next, newp);

        //System.out.println("New chain: " );
        for (int i = 0; i < newp.size(); i++) {
          Point p = (Point)newp.elementAt(i);
          //System.out.println(" <" + p.x + ", " + p.y + ">");
        }
        c.add(newp);
        //System.out.println("new p size: " + newp.size());
        points.remove(points.size()-1);
        //System.out.println("new p size: " + newp.size());
        }
      } else {
        //System.out.println(" was visited");
      }
    }
    // remove this node for backtracking
    points.remove(points.size()-1);
    // return recursed chain
    return c;
  }

  void drawChain (Graphics2D g) {
    //System.out.println("drawing chain");
    // if points have been calculated before, use those
    if (!chains.isEmpty()) {
      for (int i = 0; i < chains.size(); i++) {
        //System.out.println("i: " + i);
        BezierChain chain = (BezierChain)chains.elementAt(i);        
        //System.out.println(" grab next chain");
        for (int j = 0; j < chain.size(); j++) {
          //System.out.println("  j: " + j);
          BezierCurve curve = chain.get(j);
          //System.out.println("   drawing curve");
          drawBezierCurve(g, curve.p[0], curve.p[1], curve.p[2], curve.p[3]);
          //System.out.println("   done drawing curve");
        }
      }
    }
    //System.out.println("drawing chain done");
  }

  */
  /*
  public void paint (Graphics2D g) {
    // Get start and end nodes
    Node a = getStartNode();
    Node b = getEndNode();
    if (!((IDNode)a).isInteresting()) return;
  */
    /*
    if (graph.isSelectedEdge(e)) {
      g.setColor(selectedEdgeColor);
      g.setStroke(selectedEdgeStroke);
    } else {
      g.setColor(edgeColor);
      g.setStroke(edgeStroke);
    }
    */

    //g.setColor(Color.black);

    
    // For some annoying reason, graphics2D doesn't take double coordinates
    //    for line drawing!!!
    //    Will probably do some minimal scaling here so can handle small points!!!

    /*    
    int ax = (int) Math.round(a.getX());
    int ay = (int) Math.round(a.getY());
    int bx = (int) Math.round(b.getX());
    int by = (int) Math.round(b.getY());
    // g.drawLine(ax, ay, bx, by);
    
    */
  /*
    // draw bezier curve from node a to b, if node a is not virtual
    if (a.virtual) return;
    ////System.out.println("draw curve from: " + a.getName() + " to " + b.getFront().getName());
    drawBezierCurve(g,a,b); // from node a to node b
    
  */
    /*
    //System.out.println("ax: " + ax + 
                       "ay: " + ay +
                       "bx: " + bx + 
                       "by: " + by);
    if (a.rank > b.rank) {
      //System.out.println("a higher rank");
      if (!a.virtual) ay -= Node.scale;
      if (!b.virtual) by += Node.scale;
    } else {
      //System.out.println("b higher rank");
      if (!a.virtual) ay += Node.scale;
      if (!b.virtual) by -= Node.scale;      
    }
    //System.out.println("ax: " + ax + 
                       "ay: " + ay +
                       "bx: " + bx + 
                       "by: " + by);
    */
    
    /*
    //DRAW ARROW HEAD
    double aDir=Math.atan2(bx-ax,by-ay);
    g.setStroke(new BasicStroke(1f));	
    Polygon tmpPoly=new Polygon();
    double stroke = 1;
    int i1=12+(int)(stroke*2);
    int i2=6+(int)stroke;	// make the arrow head the same size regardless of the length length
    tmpPoly.addPoint(ax,ay);		// arrow tip
    tmpPoly.addPoint(ax+xCor(i1,aDir+.5),ay+yCor(i1,aDir+.5));
    tmpPoly.addPoint(ax+xCor(i2,aDir),ay+yCor(i2,aDir));
    tmpPoly.addPoint(ax+xCor(i1,aDir-.5),ay+yCor(i1,aDir-.5));
    tmpPoly.addPoint(ax,ay);		// arrow tip
    g.drawPolygon(tmpPoly);
    g.fillPolygon(tmpPoly);		
    */
  //  }
  //private static int yCor(int len, double dir) {return (int)(len * Math.cos(dir));}
  //private static int xCor(int len, double dir) {return (int)(len * Math.sin(dir));}

//  void draw () {
    /*
      for this node, if its interesting, recurse to draw
      edges, skip non interesting nodes and recurse their chain of
      children.
    */
    
// }

  /*
  void drawBezierCurve(Graphics2D g, Node a, Node b) {

    Vector curves = new Vector();

    // we know that node a is not virtual
    // b should be virtual (since we add bend nodes)

    //gather all points from node a to front node of b
    Vector points = new Vector();
    points.add(new Point((int)a.getRoundedX(),(int)a.getY()));
    Node current = b;
    Iterator eIt = current.iterator();
    while (eIt.hasNext() && current.virtual) {
      points.add(new Point((int)current.getRoundedX(),(int)current.getY()));
      Edge edge = (Edge)eIt.next();
      current = edge.getEndNode();
      eIt = current.iterator();
    }
    points.add(new Point((int)current.getRoundedX(),(int)current.getY()));

    
  }
  */

  static void drawBezierCurve(Graphics2D g, Point p1, Point p2, Point p3, Point p4, int height) {
    if (p1.x == p2.x && p2.x == p3.x && p3.x == p4.x) {
      if (height > p4.y) {
        g.drawLine(p1.x,p1.y, p4.x,height);
      } else {
        g.drawLine(p1.x,p1.y, p4.x,p4.y);
      }
      return;
    }

    double x1,x2,y1,y2;
    x1 = p1.x;
    y1 = p1.y;
    double k = .125;
    
    for(double t=k;t<=1;t+=k){
      // use Berstein polynomials
      x2 = 
        (p1.x + t * (-p1.x * 3 + t * (3 * p1.x - p1.x * t))) + 
        t * (3 * p2.x + t * (-6 * p2.x + p2.x * 3 * t)) + 
        t * t * (p3.x *3 -p3.x * 3 * t) +
        p4.x * t * t * t;
      
      y2=
        (p1.y + t * (-p1.y * 3 + t * (3 * p1.y - p1.y * t))) +
        t * (3 * p2.y + t *(-6 * p2.y + p2.y * 3 * t)) + 
        t * t * (p3.y * 3 - p3.y * 3 * t)+
        p4.y*t*t*t;
      //draw curve
      if (height > y1)
        break;
      if (height > y2) {
        g.drawLine((int)x1,(int)y1,(int)x2, height);
      } else {
        g.drawLine((int)x1,(int)y1,(int)x2,(int)y2);
      }
      x1 = x2;
      y1 = y2;
    }
  }

  // if start node is virtual, then this is not the begining of the chain
  // get the edge that starts the chain (start node is not virtual)
  public Edge getBackEdge () {
    Edge current = this;
    while (current.getStartNode().virtual) {
      Node n = current.getStartNode();
      Iterator ritr = n.reverse_iterator();
      if (!ritr.hasNext()) {
        //System.out.println("Virtual node doesn't have any reverse edges");
        System.exit(0);
      }
      current = (Edge)ritr.next();
    }
    return current;
  }


}

