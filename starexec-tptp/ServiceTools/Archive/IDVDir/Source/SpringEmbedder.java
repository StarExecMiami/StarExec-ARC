// Christian Duncan
// SpringEmbedder Class
//    for GD2004, Graph Drawing Contest
//    Thanks to Harendra for some of the code...

// package GD4;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.event.*;
import java.awt.image.*;
import java.net.URL;
import java.io.*;
import java.util.*;
import java.text.*;

public class SpringEmbedder extends JFrame
  implements ActionListener, ChangeListener, Runnable {
  public static final String
    TK_RUN_EMBEDDER_IMG = "run.png",
    TK_RUN_EMBEDDER_IMG_SELECTED = "stop.png",
    TK_RUN_EMBEDDER_TEXT = "Run the Spring Embedder",
    TK_RUN_EMBEDDER_ALT = "Embed",
    RUN_EMBEDDER_CMD = "SpringEmbed",
    TK_REPULSIVE_FORCE_ALT = "Repulsive Force: ",
    TK_REPULSIVE_FORCE_TEXT = "Repelling Forces between Nodes",
    TK_KSPRING_CONSTANT_ALT = "Spring Constant: ",
    TK_KSPRING_CONSTANT_TEXT = "Spring Constant applied to Edges",
    TK_LSPRING_LENGTH_ALT = "Spring Length: ",
    TK_LSPRING_LENGTH_TEXT = "Ideal Spring Length applied to Edges",
    TK_MAX_ITERATIONS_ALT = "Max. Iterations: ",
    TK_MAX_ITERATIONS_TEXT = "Maximum Iterations allowed per Embedding.",
    TK_MAX_MOVEMENT_ALT = "Max. Movement: ",
    TK_MAX_MOVEMENT_TEXT = "Maximum Movement any node can take per iteration.\n Prevents unexpected blowout of graph.",
    TK_D_FACTOR_ALT = "Displacement Factor: ",
    TK_D_FACTOR_TEXT = "Scaling for Node Movement. dx -> dx*factor",
    TK_KANGLEB_CONSTANT_ALT = "Angle Constant Beta: ",
    TK_KANGLEB_CONSTANT_TEXT = "Angle Beta Constant applied to Edges",
    TK_KANGLEA_CONSTANT_ALT = "Angle Constant Alpha: ",
    TK_KANGLEA_CONSTANT_TEXT = "Angle Alpha Constant applied to Edges";
  
  /**
     Constants associated with SpringEmbedder
     Repulsive,Spring constants are actually computed
     using the formula 2^(v/BASE) just so that ranges
     are more easily adjusted.
     Spring Length is simply v/BASE
  **/
  public static final int
    BASE = 100,
    REPULSIVE_FORCE_MIN = -1*BASE,
    REPULSIVE_FORCE_MAX = 20*BASE,
    REPULSIVE_FORCE_DEFAULT = 11 * BASE,
    KSPRING_CONSTANT_MIN = -10*BASE,
    KSPRING_CONSTANT_MAX = 20*BASE,
    KSPRING_CONSTANT_DEFAULT = BASE,
    LSPRING_LENGTH_MIN = 0,
    LSPRING_LENGTH_MAX = 100*BASE,
    LSPRING_LENGTH_DEFAULT = BASE,
    MAX_ITERATIONS_MIN = 1,
    MAX_ITERATIONS_MAX = 1000,
    MAX_ITERATIONS_DEFAULT = 1,
    MAX_ITERATIONS_INITIAL = 50,
    MAX_MOVEMENT_MIN = 1,
    MAX_MOVEMENT_MAX = 200*BASE,
    MAX_MOVEMENT_DEFAULT = 100*BASE,
    D_FACTOR_MIN = 0,
    D_FACTOR_MAX = 1*BASE,
    D_FACTOR_DEFAULT = 5,
    KANGLEB_CONSTANT_MIN = 1*BASE,
    KANGLEB_CONSTANT_MAX = 5*BASE,
    KANGLEB_CONSTANT_DEFAULT = 2*BASE,
    KANGLEA_CONSTANT_MIN = 1*BASE,
    KANGLEA_CONSTANT_MAX = 5*BASE,
    KANGLEA_CONSTANT_DEFAULT = 1*BASE;
  
  public static final double DIST_THRESHOLD = 0.000001;
  
  GraphPanel gridScreen;          // The GraphPanel we are hooked to
  // gives access to Graph as well.
  JToggleButton embedButton;      // To run the embedding algorithm
  JLabel statusMessage;           // Shows various status messages as needed.
  
  public int maxIterations;       // Maximum iterations allowed
  public int minIterationsRequired; // Min. iterations required before stop...
  public double minChangeAllowed;   // .. when change is less than this
  public double maxMovement;         // Maximum movement any node can take
  public int animationDelay = 0;  // Delay in animating iterations 
  
  public double dFactor;          // Displacement factor (adjustable);
  public double kSpringConstant;  // Main Spring Constant
  public double lSpringLength;    // (Desired) Length of Spring
  public double kRepulsiveForce;  // Strength of node repulsions
  public double kAngleConstantB;
  public double kAngleConstantA;

  public SpringEmbedder(GraphPanel g) {
    super("Spring Embedder Utility");
    
    JButton button;
    Container mainPane;
    
    gridScreen = g;
    
    // Create the basic layout
    mainPane = this.getContentPane();
    mainPane.setLayout(new BorderLayout());
    
    // Create Run Button (most important)
    embedButton = 
      GraphManTools.makeToggleButton(TK_RUN_EMBEDDER_IMG,
                                     TK_RUN_EMBEDDER_IMG_SELECTED,
                                     TK_RUN_EMBEDDER_TEXT,
                                     TK_RUN_EMBEDDER_ALT,
                                     RUN_EMBEDDER_CMD, false, this);
    mainPane.add(embedButton, BorderLayout.SOUTH);
    
    JPanel centerPane = new JPanel();
    centerPane.setLayout(new BoxLayout(centerPane, BoxLayout.Y_AXIS));
    
    // Functions used to make sliders non-integer/non-linear
    GMSlider.Function expFunc = new GMSlider.Function() {
        double f(int min, int max, int val) {
          if (val == min) return 0;
          else return Math.pow(2.0,
                               (double) val/(double)BASE);
        }
      };
    
    GMSlider.Function scaleFunc = new GMSlider.Function() {
        double f(int min, int max, int val) {
          return (double) val / (double) BASE;
        }
      };
    
    // Create the sliders
    GMSlider slider;
    slider = GraphManTools.
      makeGMSlider(TK_REPULSIVE_FORCE_ALT, TK_REPULSIVE_FORCE_TEXT,
                   this, expFunc,
                   REPULSIVE_FORCE_MIN, REPULSIVE_FORCE_MAX,
                   REPULSIVE_FORCE_DEFAULT);
    centerPane.add(slider);
    centerPane.add(new JSeparator());
    kRepulsiveForce = slider.getValue();
    
    slider = GraphManTools.
      makeGMSlider(TK_KSPRING_CONSTANT_ALT, TK_KSPRING_CONSTANT_TEXT,
                   this, expFunc,
                   KSPRING_CONSTANT_MIN, KSPRING_CONSTANT_MAX,
                   KSPRING_CONSTANT_DEFAULT);
    centerPane.add(slider);
    centerPane.add(new JSeparator());
    kSpringConstant = slider.getValue();
    
    slider = GraphManTools.
      makeGMSlider(TK_LSPRING_LENGTH_ALT, TK_LSPRING_LENGTH_TEXT,
                   this, scaleFunc,
                   LSPRING_LENGTH_MIN, LSPRING_LENGTH_MAX,
                   LSPRING_LENGTH_DEFAULT);
    centerPane.add(slider);
    centerPane.add(new JSeparator());
    lSpringLength =  slider.getValue();
    
    slider = GraphManTools.
      makeGMSlider(TK_MAX_ITERATIONS_ALT, TK_MAX_ITERATIONS_TEXT,
                   this, null,
                   MAX_ITERATIONS_MIN, MAX_ITERATIONS_MAX,
                   MAX_ITERATIONS_DEFAULT);
    centerPane.add(slider);
    centerPane.add(new JSeparator());
    maxIterations = (int) slider.getValue();
    
    slider = GraphManTools.
      makeGMSlider(TK_MAX_MOVEMENT_ALT, TK_MAX_MOVEMENT_TEXT,
                   this, scaleFunc,
                   MAX_MOVEMENT_MIN, MAX_MOVEMENT_MAX,
                   MAX_MOVEMENT_DEFAULT);
    centerPane.add(slider);
    centerPane.add(new JSeparator());
    maxMovement = slider.getValue();
    
    slider = GraphManTools.
      makeGMSlider(TK_D_FACTOR_ALT, TK_D_FACTOR_TEXT,
                   this, scaleFunc,
                   D_FACTOR_MIN, D_FACTOR_MAX,
                   D_FACTOR_DEFAULT);
    centerPane.add(slider);
    centerPane.add(new JSeparator());
    dFactor = slider.getValue();

    slider = GraphManTools.
      makeGMSlider(TK_KANGLEA_CONSTANT_ALT, TK_KANGLEA_CONSTANT_TEXT,
                   this, scaleFunc,
                   KANGLEA_CONSTANT_MIN, KANGLEA_CONSTANT_MAX,
                   KANGLEA_CONSTANT_DEFAULT);
    centerPane.add(slider);
    centerPane.add(new JSeparator());
    kAngleConstantA = slider.getValue();
    
    slider = GraphManTools.
      makeGMSlider(TK_KANGLEB_CONSTANT_ALT, TK_KANGLEB_CONSTANT_TEXT,
                   this, scaleFunc,
                   KANGLEB_CONSTANT_MIN, KANGLEB_CONSTANT_MAX,
                   KANGLEB_CONSTANT_DEFAULT);
    centerPane.add(slider);
    centerPane.add(new JSeparator());
    kAngleConstantB = slider.getValue();

    statusMessage = new JLabel("Adjust Values Above and Hit Embed Below");
    centerPane.add(statusMessage);
    mainPane.add(centerPane, BorderLayout.CENTER);
    
    // Set initial default values for Constants
    minIterationsRequired = 1000;   // Note: Basically disables this
    minChangeAllowed = 0.001;
    
    pack();
    setVisible(false);
  }
  
  /********************************
   * actionPerformed
   *     An Action was selected.   Deal with it!
   ********************************/
  public void actionPerformed(ActionEvent e) {
    String actionMessage = e.getActionCommand();
    if (actionMessage == RUN_EMBEDDER_CMD) {
      // Run the Spring Embedder
      runEmbedder();
    }
  }
  
  /********************************
   * stateChanged
   *     A state changed (of a GMSlider)
   ********************************/
  public void stateChanged(ChangeEvent e) {
    GMSlider source = (GMSlider) e.getSource();
    if (!source.getValueIsAdjusting()) {
      double value = source.getValue();
      if (source.getName() == TK_REPULSIVE_FORCE_ALT) {
        kRepulsiveForce = value;
      } else if (source.getName() == TK_KSPRING_CONSTANT_ALT) {
        kSpringConstant = value;
      } else if (source.getName() == TK_LSPRING_LENGTH_ALT) {
        lSpringLength = value;
      } else if (source.getName() == TK_MAX_ITERATIONS_ALT) {
        maxIterations = (int) value;
      } else if (source.getName() == TK_MAX_MOVEMENT_ALT) {
        maxMovement = value;
      } else if (source.getName() == TK_D_FACTOR_ALT) {
        dFactor = value;
      } else if (source.getName() == TK_KANGLEA_CONSTANT_ALT) {        
        kAngleConstantA = value;
      } else if (source.getName() == TK_KANGLEB_CONSTANT_ALT) {
        kAngleConstantB = value;
      } else {
        System.err.println("Error: Did you forget to catch a Slider");
      }
    }
  }
  
  private Thread springThread;
  
  public void runEmbedder() {
    // Check that the action was selected and NOT deselected
    if (embedButton.isSelected() == false) {
      // Just clicked it off (it will stop itself)
      return;
    }
    
    if (springThread == null) {
      // No current running embedder
      //   We don't want multiple ones running!
      springThread = new Thread(this);
      springThread.start();
    }
  }
  
  public void run() { 
    embed(); 
    springThread = null;  // Makes sure that the SpringEmbedder can run another time!
  }
  
  /**
   * embed
   *    Perform a spring embedding on the assigned graph
   *       Taken from GraphPanel
   *    
   **/
  public void embed() {
    // Get the graph (if there is one)
    IDGraph g;
    if (gridScreen == null || (g=(IDGraph)gridScreen.getGraph()) == null) return;
    Vector<IDNode> rank[] = g.getRank();
    // Loop for either maxIterations or until
    //    embedButton is deselected (to stop it)
    for (int iter = 0; 
         iter < maxIterations &&
           embedButton.isSelected();
         iter++) {

      if (!embed(iter, rank, g, true))
        break;

      if ((maxIterations - iter) < 10) {
        adjustX();
      }

    }
    // Done - make sure embedButton is deselected!
    embedButton.setSelected(false);
    adjustX();
    gridScreen.revalidate();
  }

  public void adjustX () {

    // Readjust nodes if one parent sequence, force same x(average)
    IDGraph g;
    if (gridScreen == null || 
        (g=(IDGraph)gridScreen.getGraph()) == null) return;

    // reset visited
    Iterator nIt = g.nodeIterator();
    while (nIt.hasNext()) {
      IDNode node = (IDNode)nIt.next();
      node.invalidate();
    }

    nIt = g.nodeIterator();
    while (nIt.hasNext()) {
      IDNode node = (IDNode)nIt.next();
      if (node.isPinned())
        continue;
      if (node.reverse_edge.size() == 1) {
        IDNode check = (IDNode)((Edge)node.reverse_edge.elementAt(0)).getStartNode();
        //check virtual nodes
        if (node.isVirtual()) {
          IDNode next = (IDNode)((Edge)node.edge.elementAt(0)).getEndNode();
          if (next.isVirtual() && !next.isVisited()) {
            // if next is very close in x, make same x
            Vector nodes = new Vector();
            double threshhold = 50;
            double total = 0;
            do {
              if (Math.abs((next.getX() - node.getX())) < threshhold || !next.isVisited()) {
                nodes.add(next);
                next.setVisited(node.getId());
                next = (IDNode)((Edge)next.edge.elementAt(0)).getEndNode();
                total += next.getX();
              } else {
                break;
              }
            } while (next.isVirtual());
            double avg = total / nodes.size();
            for (int i = 0; i < nodes.size() - 3; i++) {
              IDNode n = (IDNode)nodes.elementAt(i);
              n.setX(avg);
            }
            continue;
          }
        }

        check = (IDNode)check.getBack();
        // if bottom node has one, start count from that node, not this one
        if (check.edge.size() == 1 && !check.isVirtual()) {
          continue;        
        }
      }
      Vector nodes = new Vector();
      int x = 0;
      int count = 0;
      if (node.edge.size() == 1 && !node.virtual) {
      //if (node.edge.size() == 1 && node.reverse_edge.size() != 1) {
        //System.out.println("Got one");
        IDNode current = node;
        // add first node, add extra weight to it
        nodes.add(current);
        //x = (int)current.getX();
        x += current.getX();
        count += 1;        
        boolean pin_flag = false;
        do {
          //System.out.println(" Adding node: " + current.getName());
          current = (IDNode)((Edge)current.edge.elementAt(0)).getEndNode();
          if (current.isPinned()) {
            pin_flag = true;
            break;
          }
          if (current.reverse_edge.size() == 1) {
            nodes.add(current);
          } else {
            break;
          }
          x += current.getX();
          count++;
        }  while (current.edge.size() == 1 && current.reverse_edge.size() == 1);

        if (pin_flag)
          continue;
        
        //add the last one
        //System.out.println(" Adding node: " + current.getName());
        int avg = x / count;
        for (int i = 0; i < nodes.size(); i++) {
          IDNode avgNode = (IDNode)nodes.elementAt(i);
          //System.out.println("  Averaging Node: " + avgNode.getName() + ": " + avg);
          avgNode.setX(avg);
          avgNode.setPolygon();
        }
      }
    }
  }

  public void computeSpringForce (IDNode n, SpringForce [] f) {
    Iterator eIt = n.iterator();  // Iterate edges of node
    while (eIt.hasNext()) {
      int intersect_spring = 1;
      Edge e = (Edge) eIt.next();
      IDNode endNode = (IDNode)e.getEndNode();
      double dx = endNode.getX() - n.getX();
      double dy = endNode.getY() - n.getY();
      double distance = Math.sqrt(dx * dx + dy * dy);
      
      // Prevent super rapid expansion
      double distance_denom = (distance <= DIST_THRESHOLD) ?
        DIST_THRESHOLD : distance;
      
      // Compute the force this edge produces
      double fx = kSpringConstant * 
        (distance - lSpringLength) * dx / distance_denom;
      double fy = kSpringConstant * 
        (distance - lSpringLength) * dy / distance_denom;
      if (!endNode.isPinned()) {
        f[endNode.getId()].inc(-fx,-fy);
      }
      f[n.getId()].inc(fx * intersect_spring, fy * intersect_spring);
    }
  }

  public void computeRepulsiveForce (IDNode n, IDNode m, SpringForce [] f) {
    // Now compute Node to Node repulsive forces
    double dx = m.getX() - n.getX();
    double dy = m.getY() - n.getY();
    double sqDistance = dx * dx + dy * dy;
    if (sqDistance < DIST_THRESHOLD) {
      sqDistance = DIST_THRESHOLD;
      dx = dy = Math.sqrt(DIST_THRESHOLD/2.0);
    }
    double distance = Math.sqrt(sqDistance);
      
    // Using the square so the kRF value appears reasonable
    //     SquaredDistance forces huge drop off here...
    double force = -(kRepulsiveForce*kRepulsiveForce) / sqDistance;
    double fx = force * dx / distance;
    double fy = force * dy / distance;
    if (!m.isPinned()) {
      f[m.getId()].inc(-fx,-fy);
    }
    f[n.getId()].inc(fx, fy);
  }

  public void computeGravityForce (IDNode n, SpringForce [] f) {
    Iterator eIt = n.iterator();  // Iterate edges of node
    GravityForce gforce = new GravityForce(0,-100);
    while (eIt.hasNext()) {
      Edge e = (Edge) eIt.next();
      IDNode endNode = (IDNode)e.getEndNode();
      double dx = endNode.getX() - n.getX();
      double dy = endNode.getY() - n.getY();
      double distance = Math.sqrt(dx * dx + dy * dy);
        
      // Prevent super rapid expansion
      double distance_denom = (distance <= DIST_THRESHOLD) ?
        DIST_THRESHOLD : distance;
      
      //Edge e2 = new Edge(n, endNode);
      double angle = e.angle(gforce);
      double fangle = Math.pow(distance_denom, kAngleConstantA);
      double force = fangle * Math.pow(angle, kAngleConstantB);
      
      //sign based on if left or right of gravity pull
      double sign = e.sign(gforce);//(dx > 0) ? 1 : -1;
      
      // Compute the force this edge produces
      double fx = force * -dy / distance_denom * sign;
      double fy = force * dx / distance_denom * sign;
      if (!endNode.isPinned()) {
        f[endNode.getId()].inc(-fx,-fy);
      }
      f[n.getId()].inc(fx, fy);
    }
  }

  public boolean embed (int iter, Vector<IDNode>[] rank, IDGraph g, boolean drawMe) {
    int numPoints;
    SpringForce[] f;
    
    // Each node will have forces acting on it
    //    Stored in a given array of values...
    numPoints = g.numNodes();
    int nR = g.getRankSize();
    f = new SpringForce[numPoints];
    for (int i = 0; i < numPoints; i++) {
      f[i] = new SpringForce();
    }
    for (int j = 1; j < nR; j++) {
      for (int k = 0; k < rank[j].size(); k++) {
        computeSpringForce(rank[j].elementAt(k), f);
        computeGravityForce(rank[j].elementAt(k), f);
        if (k < (int)rank[j].size() - 1) {
          computeRepulsiveForce(rank[j].elementAt(k), rank[j].elementAt(k+1), f);
        }
      }       
    }
    for (IDNode n : g.getNode()) {
      //remove virtual make things looke weird
      if (n.virtual)
        continue;

      // Now compute Node to Left Wall repulsive force
      double dx[] = new double[2];
      dx[0] = g.getLeftBound() - n.getX();
      dx[1] = g.getRightBound() - n.getX();        
      for (int k = 0; k < 2; k++) {
        if (dx[k] < 500) {
          double sqDistance = dx[k] * dx[k];
          if (sqDistance < DIST_THRESHOLD) {
            sqDistance = DIST_THRESHOLD;
              dx[k] = Math.sqrt(DIST_THRESHOLD/2.0);
          }
          double distance = Math.sqrt(sqDistance);
          
          // Using the square so the kRF value appears reasonable
          //     SquaredDistance forces huge drop off here...
          double force = -(kRepulsiveForce*kRepulsiveForce) / sqDistance;
          double fx = force * dx[k] / distance;
          f[n.getId()].inc(fx, 0);
        }
      } 
    }        
     
    Iterator nIt = g.nodeIterator();
    double totalChange = 0;
    while (nIt.hasNext()) {
      IDNode n = (IDNode) nIt.next();
      if (n.isPinned()) 
        // Node is pinned, don't MOVE IT!
        continue;
      
      double dx = f[n.getId()].getX() * dFactor;
      double dy = f[n.getId()].getY() * dFactor;
      double dist = Math.sqrt(dx * dx + dy * dy);
      
      // Prevent blow up of extraordinary scale!
      if (dist > maxMovement) {
        // Change magnitude but not direction
        double factor = maxMovement / dist;
        dx *= factor;
        dy *= factor;
      }
      
      f[n.getId()].reset();   // Force no longer needed, clear for next time
      
      totalChange += Math.abs(dx) + Math.abs(dy);   // Keep track of total displacement
      
      double nx = n.getX() + dx;
      double ny = n.getY() + dy;
      g.moveNode(n, nx, ny);
    }
      
    NumberFormat formatter = NumberFormat.getNumberInstance();
    statusMessage.setText("Iteration: " + (iter+1) + 
                          " Total Change: " + 
                          formatter.format(totalChange));
    
    // Update the boundary
    gridScreen.calculateGraphBounds();
    
    // Refresh
    if (drawMe) {
      gridScreen.invalidate();
      gridScreen.repaint();
    }
    if (animationDelay > 0) {
      // Put in some sleep between each iteration!
      try {
        Thread.sleep(animationDelay);
      } catch (Exception e){
        System.err.println(e);
      }
    }
    
    if (iter > minIterationsRequired && 
        totalChange < minChangeAllowed * dFactor) {
      // Enough iterations occurred and no real movement!
      return false;
    }
    return true;
  }
}

class SpringForce {
  double dx, dy;
  
  SpringForce() { dx = 0; dy = 0; }
    
  void reset() { dx = 0; dy = 0; }
  double getX() { return dx; }
  double getY() { return dy; }
  void inc(double ddx, double ddy) {
    dx += ddx; dy += ddy;
  }
}

