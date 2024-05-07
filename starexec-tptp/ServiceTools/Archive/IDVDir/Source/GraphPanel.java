/*******************************
* GraphPanel:
*     Simple panel to draw a graph along with
*            its grid and other features...
*******************************/
// package GD4;

import javax.swing.*;
import java.awt.*;
import java.awt.geom.*;
import java.awt.event.*;
import javax.swing.event.*;
import java.awt.image.*;
import java.net.URL;
import java.util.*;

public class GraphPanel extends JPanel
  implements Scrollable, MouseMotionListener, MouseListener {
  Graph graph;                              // The graph that we plan to draw
  double zoomLvl = 1.0;
  Rectangle graphBnds = null;
  //Stack undoInfo;                           // Undo information
  final int MAX_UNDO = 20;                  // ... at least this much ...
  boolean drawme;
  
  JToggleButton crossTrackerButton;
  int numCrossings = -1;
  
  // Colors, stroke patterns, and size of various objects in the display
  Color edgeColor = Color.black;            
  Color selectedEdgeColor = Color.orange;
  Color nodeColor = Color.red;              
  Color nodePinColor = new Color(0.5f, 0.0f, 0.0f); // A darker red
  Color crossColor = Color.blue;            
  Stroke edgeStroke = new BasicStroke((float) 1.0);
  Stroke selectedEdgeStroke = new BasicStroke((float) 1.0);
  Stroke nodeStroke = new BasicStroke((float) 2.0);
  Stroke crossStroke = new BasicStroke((float) 1.0);
  float nodeRadius = 10;
  float crossRadius = 7;
  
  final int DEFAULT_SCREEN_WIDTH = 400;     //   Width/Height of Panel if no
  final int DEFAULT_SCREEN_HEIGHT = 400;    //  Parent is provided
  final double D_ZOOM = 1.5;                // Factor to change zoom (per click)
  int dx, dy;

  private int bufferWidth;
  private int bufferHeight;
  private Image bufferImage;
  //private Image initialImage = null;
  public Graphics bufferGraphics;
  public Rectangle vv;
  //private Graphics initialGraphics;
  private boolean save;
  private IDV idv;  
  
  //SensitivePolygon sp;
  
  GraphPanel(IDV idv) {
    super (false);   // NOTE: Not sure why false - double-buffering should be preferred?
    this.idv = idv;
    this.graph = null;
    
    addMouseListener (this);
    addMouseMotionListener (this);
    
    // Let us set its size to a large value
    setBounds(0, 0, DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT);
    setBackground(Color.lightGray);
    // For papers setBackground(new Color(245,245,245));

    //undoInfo = new Stack();
    drawme = false;
  }
  
  public void setDrawMe (boolean flag) {
    drawme = flag;
  }

  /**
   * setGraph
   *    set the graph we are drawing
   *      calculate zoom level for this new graph
   **/
  public void setGraph(Graph g) {
      graph = g;
      //graph.invalidate();
      fitToWindowHeight();
  }
  
  /**
   * getGraph
   *    returns direct reference to Graph we are drawing
   **/
  public Graph getGraph() { return graph; }
  
  /**
   * setCrossTracker
   **/
  public void setCrossTracker(JToggleButton button) {
    crossTrackerButton = button;
  }
  
  /**
   * updateCrossTrackerTotal
   *    CTButton reflects total number of crossings (as it changes)
   *    recompute: true if we should recompute total crossings
   **/
  void updateCrossTrackerTotal(boolean recompute) {
    if (recompute && graph != null) {
      // Recompute the number of intersections (crossings)
      numCrossings = graph.countIntersections();
    }
    
    if (numCrossings >= 0) {
      //	    crossTrackerButton.setText(GraphMan.TK_CROSSTRACKER_ALT+": " +
      //			       numCrossings);
      crossTrackerButton.setText(IDV.TK_CROSSTRACKER_ALT+": " + numCrossings);
      
    } else {
      //  crossTrackerButton.setText(GraphMan.TK_CROSSTRACKER_ALT);
      //  crossTrackerButton.setText(GraphProofTree.TK_CROSSTRACKER_ALT);
    }
    crossTrackerButton.revalidate();
  }
  
  /**
   * calculateGraphBounds()
   *   Determine the best bounds for viewing the graph
   *   Relies on the Graph class to give bounds.
   *      May then add additional units for visual appeal
   **/
  void calculateGraphBounds() {
    // Compute bound of graph
    if (graph == null) return;
    
    graphBnds = graph.getBounds();

    //take (screen width - graph width) / 2, add that to x
    //graphBnds.x += (DEFAULT_SCREEN_WIDTH - graphBnds.width) / 2;
    
    // Add one block step in each direction
    int step = getBlockStep();
    graphBnds.x -= step;
    graphBnds.y -= step;
    graphBnds.width += 2*step;
    graphBnds.height += 2*step;
  }
  
  /**
   * fitToWindow()
   *     Calculate largest zoom value to fit graph
   *     onto the screen.
   **/

   void fitToWindow() {
       // Calculate screen width and height
       int screenWidth = DEFAULT_SCREEN_WIDTH;
       int screenHeight = DEFAULT_SCREEN_HEIGHT;

       if (getParent() != null) {
	   screenWidth = getParent().getWidth();
	   screenHeight = getParent().getHeight();
       }
       
       // Calculate graph width and height
       calculateGraphBounds();
       
       // Compute the scale in each direction
       double scaleX = (double) screenWidth / graphBnds.width;
       double scaleY = (double) screenHeight / graphBnds.height;
       
       // zoom level is smaller of two
       //    We don't want stretching
       zoomLvl = (scaleX < scaleY) ? scaleX : scaleY;
       
       revalidate();   // Force redraw if necessary
       repaint();
   }

  void fitToWindowHeight() {
    System.out.println("Fitting to window");
    // Calculate screen width and height
    int screenHeight = DEFAULT_SCREEN_HEIGHT;
    
    if (getParent() != null) {
      screenHeight = getParent().getHeight();
    }
    
    // Calculate graph width and height
    calculateGraphBounds();
    
    // Compute the scale in height direction
    zoomLvl = (double) screenHeight / (graphBnds.height);    

    //zoomLvl = scaleX;
    revalidate();   // Force redraw if necessary
    repaint();
    System.out.println("Finished fitting");
  }

  void fitToWindowWidth() {
    System.out.println("Fitting to window");
    // Calculate screen width and height
    int screenWidth = DEFAULT_SCREEN_WIDTH;
    
    if (getParent() != null) {
      screenWidth = getParent().getWidth();
    }
    
    // Calculate graph width and height
    calculateGraphBounds();
    
    // Compute the scale in width direction
    zoomLvl = (double) screenWidth / (graphBnds.width);
    
    revalidate();   // Force redraw if necessary
    repaint();
    System.out.println("Finished fitting");
  }

  /*
  void fitToWindow() {
    System.out.println("Fitting to window");
    // Calculate screen width and height
    int screenWidth = DEFAULT_SCREEN_WIDTH;
    int screenHeight = DEFAULT_SCREEN_HEIGHT;
    
    if (getParent() != null) {
      screenWidth = getParent().getWidth();
      screenHeight = getParent().getHeight();
    }
    
    // Calculate graph width and height
    calculateGraphBounds();
    
    // Compute the scale in each direction
    double scaleX = (double) screenWidth / graphBnds.width;
    double scaleY = (double) screenHeight / graphBnds.height;
    
    // zoom level is smaller of two
    //    We don't want stretching
    zoomLvl = (scaleX < scaleY) ? scaleX : scaleY;
    //zoomLvl = scaleX;
    revalidate();   // Force redraw if necessary
    repaint();
    System.out.println("Finished fitting");
  }
  */
  /**
   * zoomIn()
   *   Zoom the graph in
   *     Just change the zoomLevel and force redraw
   **/
  public void zoomIn() {
    zoomLvl *= D_ZOOM;    // Adjust stored zoom level
    
    // Force a redraw (NOTE: not sure how?)
    revalidate();
    repaint();
  }
  
  /**
   * zoomOut()
   *   Zoom the graph out
   *     Just change the zoomLevel and force redraw
   **/
  public void zoomOut() {
    zoomLvl /= D_ZOOM;
    
    // Force a redraw (NOTE: not sure how?)
    revalidate();
    repaint();
  }
  
  /**
   * setZoomLevel()
   *   Set the zoom level to the given value
   *     Just set the zoomLevel and force redraw
   **/
  public void setZoomLevel(double newZoomLvl) {
    if (newZoomLvl > 0) {
      // Valid value - set it
      zoomLvl = newZoomLvl;
      revalidate();
    }
  }
  
  /*********************
   * Methods needed for Mouse Listeners
   *********************/
  public void mouseClicked (MouseEvent e) {
    //    System.out.println("CLICK! (GraphPanel)");
    /*    
    if (n.idv.CURRENT_NODE == n) {
      if (processPoint(e.getPoint())) {
        notifyListeners(MouseEvent.MOUSE_CLICKED, e);
      } else {
        unhighlight();
        n.idv.CURRENT_NODE = null;
      }
    }
    */
    graph.mouseClicked(e);
  }

  public void mouseEntered (MouseEvent e) {}
  public void mouseExited (MouseEvent e) {} 
  public void mousePressed(MouseEvent e) {
    //set drag coordinates, incase of drag
    setCursor(Cursor.getPredefinedCursor(Cursor.MOVE_CURSOR));
    dx = e.getX();
    dy = e.getY();
  }
  public void mouseReleased (MouseEvent e) {
    setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
  }

  /*********************
   * Methods needed for MouseMotion Listeners
   *********************/
  public void mouseMoved (MouseEvent e) {
    // check exit enter of a node
    graph.mouseMoved(e);
  }
  public void mouseDragged(MouseEvent e) {
    Container c = GraphPanel.this.getParent();
    if (c instanceof JViewport) {
      JViewport jv = (JViewport)c;
      Point p = jv.getViewPosition();
      int nx = p.x - (e.getX() - dx);
      int ny = p.y - (e.getY() - dy);
      int maxx = GraphPanel.this.getWidth() - jv.getWidth();
      int maxy = GraphPanel.this.getHeight() - jv.getHeight();
      if (nx < 0) nx = 0;
      if (ny < 0) ny = 0;
      if (nx > maxx) nx = maxx;
      if (ny > maxy) ny = maxy;
      if (maxx < 0) nx = 0;
      if (maxy < 0) ny = 0;
      jv.setViewPosition(new Point(nx,ny));
    }
  }
  
  public Point adjustPoint (Point p) {
    Point pt = new Point();
    Graphics2D g = (Graphics2D) this.getGraphics();
    this.computeAdjustedLocation(p, pt);
    return pt;
  }

  /**
   * Convert the given located point
   *    to the adjust one - with scale and translation
   *    taken into account.
   *
   *    Given point is altered.
   **/
  public void computeAdjustedLocation(Point2D orig, Point2D adjusted) {
    // First compute the AffineTransformation
    AffineTransform aft = computeInverseAffineTransform();
    aft.transform(orig, adjusted);
  }
  
  /**
   * Compute proper affine transformation
   *   needed to adjust values from regular to
   *   graph's coordinate system - scale, translate, etc.
   **/
  public AffineTransform computeAffineTransform() {
    AffineTransform aft = new AffineTransform();
    aft.scale(zoomLvl, zoomLvl);
    
    if (graphBnds != null) {
      // Translate so upper corner of bounding box
      //   is at the origin (0,0)
      aft.translate(-graphBnds.x, -graphBnds.y);
      
      //Try to center x direction
      //aft.translate(-graphBnds.x*2, -graphBnds.y*2);
      //int TX = graphBnds.x - (int)(graphBnds.width / 4);
      //int TY = graphBnds.y - (int)(graphBnds.height / 4);
      //aft.translate(-TX, -TY);
    }
    
    return aft;
  }
  
  /**
   * Compute proper (inverse) affine transformation
   *   needed to adjust values from regular to
   *   graph's coordinate system - scale, translate, etc.
   **/
  public AffineTransform computeInverseAffineTransform() {
    AffineTransform aft = new AffineTransform();
    
    if (graphBnds != null) {
      // Translate so origin (0,0) goes to upper corner of 
      //   bounding box of graph
      aft.translate(graphBnds.x, graphBnds.y);
      //aft.translate(graphBnds.x*2, graphBnds.y*2);
      //int TX = graphBnds.x - (int)(graphBnds.width / 4);
      //int TY = graphBnds.y - (int)(graphBnds.height / 4);
      //aft.translate(TX, TY);
    }
    
    aft.scale(1.0/zoomLvl, 1.0/zoomLvl);
    return aft;
  }
  
  /*********************
   * Methods needed for Scrollable interface
   *********************/
 public Dimension getPreferredSize() {
    if (graph == null) {
      // No graph - no preferred size
      return new Dimension(0, 0);
    }
    
    if (graphBnds == null)
      calculateGraphBounds();
    
    // Based on dimensions of graph and zoom level
    int graphDX = (int) Math.round(graphBnds.width * zoomLvl);
    int graphDY = (int) Math.round(graphBnds.height * zoomLvl);

    //int graphDX = (int) Math.round(graphBnds.width * 3 * zoomLvl);
    //int graphDY = (int) Math.round(graphBnds.height * zoomLvl);
 
    //int graphDX = (int) Math.round(graphBnds.width * 2 * zoomLvl);
    //int graphDY = (int) Math.round(graphBnds.height * 2 * zoomLvl);

    //int graphDX = (int) Math.round((graphBnds.width > 2000)?graphBnds.width:2000 * zoomLvl);
    //int graphDY = (int) Math.round((graphBnds.height > 4000)?graphBnds.width:4000 * zoomLvl);

    return new Dimension(graphDX, graphDY);
  }
  
  public Dimension getPreferredScrollableViewportSize() {
    return getPreferredSize();
  }
  
  public int getScrollableUnitIncrement(Rectangle visibleRect,
                                        int orientation,
                                        int direction) {
    /**
     * This sample is for computing unit increments
     * for a picture.
     *  We need to do something different for our Graph
     *  Currently just returns 1
     *
     * //Get the current position.
     * int currentPosition = 0;
     * if (orientation == SwingConstants.HORIZONTAL) {
     * currentPosition = visibleRect.x;
     * } else {
     * currentPosition = visibleRect.y;
     * }
     *
     * //Return the number of pixels between currentPosition
     * //and the nearest tick mark in the indicated direction.
     * if (direction < 0) {
     * int newPosition = currentPosition -
     * (currentPosition / maxUnitIncrement)
     *                               * maxUnitIncrement;
     *             return (newPosition == 0) ? maxUnitIncrement : newPosition;
     * } else {
     * return ((currentPosition / maxUnitIncrement) + 1)
     * * maxUnitIncrement - currentPosition;
     * }
     **/
    return 10;
  }
  
  public int getScrollableBlockIncrement(Rectangle visibleRect,
                                         int orientation,
                                          int direction) {
    /** See comments from above... (for block increments)
     * if (orientation == SwingConstants.HORIZONTAL) {
     *  return visibleRect.width - maxUnitIncrement;
     * } else {
     *  return visibleRect.height - maxUnitIncrement;
     * }
     **/
    return getBlockStep();
  }
  
  public boolean getScrollableTracksViewportWidth() {
    return false;
  }
  
  public boolean getScrollableTracksViewportHeight() {
    return false;
  }
  
  /**
   * Using the graph and other info
   *   Compute the block step used for
   *   scrolling and for drawing grid space
   **/
  public int getBlockStep() {
    return 100;  // NOTE: Currently just hard-coded for 100
  }
  
  public void update (Graphics g) {
    //System.out.println("update");
    paint(g);
  }

  public void saveImage () {
    save = true;
    /*
    if (initialImage != null) {
      initialImage.flush();
      initialImage = null;
    }
    System.gc();
    System.out.println("store image");
    initialImage = createImage(bufferWidth, bufferHeight);
    initialGraphics = initialImage.getGraphics();
    initialGraphics.setClip(0,0,bufferWidth,bufferHeight);
    paintBufferComponent(initialGraphics);
    */

    /*
      System.out.println("store image try");
    if (initialImage == null) {
      System.out.println("store image success w: " + getSize().width + ", h: " + getSize().height);
      System.out.println("height: " + graphBnds.height + ", width: " + graphBnds.width);
      initialImage = createImage(getSize().width, getSize().height);
      initialGraphics = initialImage.getGraphics();
      initialGraphics.setClip(0,0,getSize().width, getSize().height);
      paintBufferComponent(initialGraphics);    
      }*/
  }

  
  public void drawImage () {
    /*
      System.out.println("draw image try");
    Graphics g2 = getGraphics();
    //g2.drawImage(bufferImage, 0, 0, this);
    if (initialImage != null) {
      System.out.println("draw image succeess");
      g2.drawImage(initialImage, 0, 0, this);    
    }
    */
  }

  public void showBounds () {
    Container c = GraphPanel.this.getParent();
    if (c instanceof JViewport) {
      JViewport jv = (JViewport)c;
      Point p = jv.getViewPosition();
      int maxx = GraphPanel.this.getWidth() - jv.getWidth();
      int maxy = GraphPanel.this.getHeight() - jv.getHeight();
      //System.out.println("n: " + nx + ", " + ny);
      //System.out.println("n: " + nx + ", " + ny);
      //System.out.println("max: " + maxx + ", " + maxy);
      System.out.println("gp width: " + GraphPanel.this.getWidth());
      System.out.println("gp height: " + GraphPanel.this.getHeight());
      System.out.println("jv width: " + jv.getWidth());
      System.out.println("jv height: " + jv.getHeight());
      System.out.println("jv view position: " + p.x + ", " + p.y);
      
    }
  }

  public void paintComponent (Graphics g) {
    if (!drawme)
      return;
    idv.setSize();
    Graphics2D g2 = (Graphics2D)g;
    Rectangle v = g2.getClipBounds();
    super.paintComponent(g);
    paintBufferComponent(g);
  }

  public void paintBufferComponent (Graphics g) {
    Graphics2D g2 = (Graphics2D) g;  // Use the more sophisticated 2D methods...
    int width, height;
    
    // Compute the affine transform to plot the points
    AffineTransform old = new AffineTransform(g2.getTransform()); // Save old one...
    AffineTransform aft = computeAffineTransform();
    g2.transform(aft);
    Rectangle visiblePart = g2.getClipBounds();
    g2.setColor(getBackground());
    g2.fillRect(visiblePart.x, visiblePart.y, visiblePart.width, visiblePart.height);    
    drawGrid(g2);
    drawGraph(g2, visiblePart);
    drawIntersections(g2, visiblePart);
    idv.paint(g2);
    g2.setTransform(old);   // Restore original transform
  }
  
  /****
   * drawGrid
   *     Draws the grid but only the part within the
   *     given visible rectangle bounds - for SPEED!
   ****/
  void drawGrid(Graphics2D g) {
    int step = getBlockStep();
    int height = getHeight();
    int width = getWidth();
    
    if (graphBnds == null)
      calculateGraphBounds();

    Rectangle b = graphBnds;
    g.setColor(Color.black);
    g.drawRect(b.x, b.y, b.width - 2, b.height - 2);
  }
  
  /**
   * drawGraph
   *    Draws the current graph
   *      Ideally, only need to draw parts
   *      that hit visible region...
   *      But this can be somewhat tricky with
   *      edges... currently draws entire thing
   *      and lets clipping handle it
   **/
  void drawGraph (Graphics2D g, Rectangle visible) {
    // Is there a graph to draw?
    if (graph == null) return;

        
    Iterator it;
    
    // Draw all edges first
    it = graph.edgeIterator();
    while (it.hasNext()) {
      Edge e = (Edge) it.next();
      drawEdge(g, e);
    }
    
    // Draw all nodes now
    it = graph.nodeIterator();
    while (it.hasNext()) {
      Node n = (Node) it.next();
      drawNode(g, n);
    }
  }
  
  // draw at edge class
  void drawEdge(Graphics2D g, Edge e) {
    // normal edge drawing uses black
    g.setColor(Color.black);
    g.setStroke(new BasicStroke((float) 1.0));
    e.paint(g);
  }

  // draw at node class
  void drawNode(Graphics2D g, Node n) {
    if (!n.virtual)
      n.sp.invalidate();
    n.paint(g);
  }
  
  /**
   * drawIntersections
   *    Draws all the intersections in the current graph
   **/
  void drawIntersections(Graphics2D g, Rectangle visible) {
  }
  
  void drawIntersection(Graphics2D g, Intersection inter) {
    // Compute the starting x and y location
    double x = inter.getX() - crossRadius;
    double y = inter.getY() - crossRadius;
    
    // As with drawing an edge... round off values
    int cx = (int) Math.round(x);
    int cy = (int) Math.round(y);
    int rad = (int) Math.round(crossRadius*2);
    
    g.fillOval(cx, cy, rad, rad);
  }

  /*****************************************************
     Routines for undo capability
        Includes full graph storage (for spring embedding)
        And individual movement
  *****************************************************/
}
