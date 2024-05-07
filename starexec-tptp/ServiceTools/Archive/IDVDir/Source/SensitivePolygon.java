import java.net.URL;
import java.io.*;
import java.awt.*;
import java.awt.geom.*;
import java.awt.font.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;
import ClientHttpRequest.*;

public class SensitivePolygon 
  extends Polygon 
  implements ActionListener {

  public static final String NEW_LINE_TEXT = "%-------------------------------------";


  boolean isActive, isLinkActive;
  protected Color fillColor;
  protected Color lineColor;
  protected Color fillColorInside;
  protected Color fillColorInsideFront;
  protected Color fillColorInsideBack;
  protected Color lineColorInside;
  
  protected GraphPanel panel;
  protected Node n;
  protected boolean gdv = false;
  protected double intensity;

  Point location;

  boolean isFront, isBack;

  Image image = null;

  public static final double
    MIN_INTENSITY = 20,
    MAX_INTENSITY = 100;

  // textWindow
  private JFrame win = null;
  private JTextArea textArea;
  private JComboBox ATPComboBox;
  private JTextField TimeField;
  private String text;
  private Vector<IDNode> axioms;
  private Vector<IDV> cIDV;
  private String derivation;

  
  /**
   * Create this sensitive polygon, with 0 points.
   * and default colors.
   */
  public SensitivePolygon(GraphPanel panel, Node n) {
    super();
    this.n = n;
    intensity = -1;
    isActive = false;
    isLinkActive = false;
    fillColor = Color.white;
    lineColor = Color.black;
    //give fill a dark green color
    fillColorInsideFront = new Color(0,64,0);
    fillColorInside = new Color(0,0,128);
    fillColorInsideBack = new Color(64,0,0);
    lineColorInside = Color.black;
    
    isFront = false;
    isBack = false;

    this.panel = panel;
    
    axioms = new Vector();
    cIDV = new Vector();

    derivation = "";
  }
  
  protected void setColor(Color color) {
    lineColor = color;
    lineColorInside = color;
  }
  
  // ************************************************************
  
  public void paint(Graphics g) {
    if (g != null) {
      
      IDNode in = (IDNode)n;
      if (!in.isInteresting()) {
        return;
      }

      Color fi = ((isActive || isLinkActive)?(fillColorInside):(fillColor));
      Color li = ((isActive || isLinkActive)?(lineColorInside):(lineColor));

      if (fi != null) {
        if (intensity != -1) {
          fi = brightenColor(); 
        }
        g.setColor(fi);
        g.fillPolygon(this);
      }
      if (li != null) {
        g.setColor(li);
          g.drawPolygon(this);
      }

      Color si = ((isActive || isLinkActive)?(Color.white):(Color.black));
      g.setPaintMode();
      g.setColor(si);
      g.setFont(new Font("Arial", Font.PLAIN, 20));
      g.drawString(n.getName(), (int)n.getRoundedX() - 40, (int)n.getY() + 5);
    }
    return;
  }

  private Color brightenColor () {
    if (intensity == 1) return fillColorInside;
    Color color = null;
    if (isFront) {
      color = fillColorInsideFront;
    } else if (isBack) {
      color = fillColorInsideBack;
    } else {
      System.out.println("brighten error");
      System.exit(0);
    }
    double brighten = (1 - intensity) * 255;
    double r = color.getRed()   + brighten;
    double g = color.getGreen() + brighten;
    double b = color.getBlue()  + brighten;
    if (r > 255) r = 255;
    if (g > 255) g = 255;
    if (b > 255) b = 255;
    return new Color((int)r, (int)g, (int)b);
  }
 
  protected boolean processPoint(Point p) {
    // point p is not adjusted, needed for location of text window
    Point pt = panel.adjustPoint(p);
    if (npoints < 3) {
      isActive = false;
      return false;
    }
    if (contains(pt)) {

      // find location to place window
      if (location == null) {
        Container c = panel.getParent();
        if (c instanceof JViewport) {
          JViewport jv = (JViewport)c;
          double x = p.getX() / (double)panel.getWidth() * (double)jv.getWidth();
          double y = p.getY() / (double)panel.getHeight() * (double)jv.getHeight();
          location = new Point((int)x + 20, (int)y); // shift
        } else {
          location = new Point(0,0);
        }
      }
      IDNode in = (IDNode)n;
      if (!in.isInteresting()) {
        return false;
      }
      /*
      if (!isActive) {
        highlight();
      }
      */
      return true;
    }
    else {
      return false;
    }
  }

  public void setActive () { isLinkActive = true; }
  public void setNotActive () { isLinkActive = false; }
  
  public void setIntensityFront (Graphics2D g) { 
    Vector queue = new Vector();
    queue.add(n);
    int depth = n.getFrontDepth();
    double range = MAX_INTENSITY - MIN_INTENSITY;
    double range_split = (range / depth) / 100;
    intensity = 1;

    Vector nodes = new Vector();
    Node last = n;
    while (!queue.isEmpty()) {      
      Node current = (Node)queue.remove(0);
      Iterator nIt = current.upIterator();
      double current_intensity;
      if (!current.isVirtual()) {
        current_intensity = current.getPolygon().intensity - range_split;
        last = current;
      } else {
        current_intensity = last.getPolygon().intensity - range_split;
      }
      while (nIt.hasNext()) {
        Node front = (Node)nIt.next();
        // draw colored edge
        g.setColor(new Color(0,200,0));        
        g.setStroke(new BasicStroke((float) 1.0));
        Edge.drawChains(current, front, g);
        if (!((IDNode)front).isVisited(n.getId())) {
          ((IDNode)front).setVisited(n.getId());
          queue.add(front);
          if (!front.isVirtual()) {
            front.getPolygon().intensity = (current_intensity > 0)?current_intensity:0;
            front.getPolygon().isFront = true;
            front.getPolygon().setActive();
          }
        }        
        nodes.add(front);
      }
    }

    for (int i = 0; i < nodes.size(); i++) {
      ((Node)nodes.elementAt(i)).paint(g);
    }
  }

  public void setIntensityBack (Graphics2D g) { 
    Vector queue = new Vector();
    queue.add(n);
    int depth = n.getBackDepth();
    double range = MAX_INTENSITY - MIN_INTENSITY;
    double range_split = (range / depth) / 100;
    intensity = 1;

    Vector nodes = new Vector();
    while (!queue.isEmpty()) {
      Node current = (Node)queue.remove(0);
      Iterator nIt = current.downIterator();
      double current_intensity;
      if (!current.isVirtual()) {
        current_intensity = current.getPolygon().intensity - range_split;
      }  else {
        current_intensity = current.getFront().getPolygon().intensity - range_split;
      }

      while (nIt.hasNext()) {
        Node back = (Node)nIt.next();
        // draw colored edge
        g.setColor(new Color(200,0,0));        
        g.setStroke(new BasicStroke((float) 1.0));
        Edge.drawChains(back, current, g);
        if (!((IDNode)back).isVisited(n.getId())) {
          ((IDNode)back).setVisited(n.getId());
          queue.add(back);
          if (!back.isVirtual()) {
            back.getPolygon().intensity = (current_intensity > 0)?current_intensity:0;
            back.getPolygon().isBack = true;
            back.getPolygon().setActive();
          }
        }
        nodes.add(back);
      }
    } 
    for (int i = 0; i < nodes.size(); i++) {
      ((Node)nodes.elementAt(i)).paint(g);
    }    
  }
  
  public void clearIntensityFront(Graphics2D g) {
    Vector queue = new Vector();
    queue.add(n);
    intensity = -1;

    Vector nodes = new Vector();
    while (!queue.isEmpty()) {
      Node current = (Node)queue.remove(0);
      Iterator nIt = current.upIterator();
      while (nIt.hasNext()) {
        Node front = (Node)nIt.next();
        // draw colored edge
        g.setColor(Color.black);        
        g.setStroke(new BasicStroke((float) 1.0));
        Edge.drawChains(current, front, g);
        if (((IDNode)front).isVisited(n.getId())) {
          ((IDNode)front).setVisited(-1);
          queue.add(front);
          if (!front.isVirtual()) {
            front.getPolygon().intensity = -1;
            front.getPolygon().isFront = false;
            front.getPolygon().setNotActive();
          }
        }
        nodes.add(front);
      }
    }

    for (int i = 0; i < nodes.size(); i++) {
      ((Node)nodes.elementAt(i)).paint(g);
    }
  }
  public void clearIntensityBack(Graphics2D g) {
    Vector queue = new Vector();
    queue.add(n);
    intensity = -1;
    Vector nodes = new Vector();
    while (!queue.isEmpty()) {
      Node current = (Node)queue.remove(0);
      Iterator nIt = current.downIterator();
      while (nIt.hasNext()) {
        Node back = (Node)nIt.next();
        g.setColor(Color.black);
        g.setStroke(new BasicStroke((float) 1.0));
        Edge.drawChains(back, current, g);
        if (((IDNode)back).isVisited(n.getId())) {
          ((IDNode)back).setVisited(-1);
          queue.add(back);
          if (!back.isVirtual()) {
            back.getPolygon().intensity = -1;
            back.getPolygon().isBack = false;
            back.getPolygon().setNotActive();
          }
        }
        nodes.add(back);
      }
    }    
    for (int i = 0; i < nodes.size(); i++) {
      ((Node)nodes.elementAt(i)).paint(g);
    }    
  }

  public void invalidate () {
    intensity = -1;
    setNotActive();
    isActive = false;
    isBack = false;
    isFront = false;    
  }
  
  public void createTextWindow (boolean showWindow) {
    if (win == null) {
      //create window
      win = new JFrame("Formula: [" + ((IDNode)n).getFormula().getUnbuffedName() + "] and Parents");
      win.setSize(400,300);
      // = new JTextArea();
      textArea = new JTextArea("",15,10);
      textArea.setFont(new Font("Courier", Font.PLAIN, 12));
      textArea.setEditable(false);
      JScrollPane scrollArea = new JScrollPane(textArea);
      Container pane = win.getContentPane();
      pane.setLayout(new BorderLayout());  // Main Panel has BorderLayout
      pane.add(scrollArea, BorderLayout.CENTER);
    
      System.out.println("new atp tool bar");
      ATPToolBar atptoolbar = ATPToolBar.createATPToolBar(n.idv.ATPList, ATPComboBox, TimeField, this);
      JToolBar tools = atptoolbar.ToolBar;
      ATPComboBox = atptoolbar.ATPComboBox;
      TimeField = atptoolbar.TimeField;
      gdv = atptoolbar.GDVTButton.isSelected();
      //add tree button
      JButton button = GraphManTools.makeActionButton(ATPToolBar.TK_TREE_IMG, ATPToolBar.TK_TREE_TEXT,
                                                      ATPToolBar.TK_TREE_ALT, ATPToolBar.TREE_CMD, this);          
      tools.add(button);
      
      // add tool bar to panel
      pane.add(tools, BorderLayout.NORTH);    
      
      textArea.addMouseListener (new MouseAdapter() {
          public void mouseClicked (MouseEvent e) {
            System.out.println("textArea mouse clicked");
            unhighlight();
            highlight();
          }
        });
      
      win.addWindowFocusListener (new WindowAdapter() {
          public void windowGainedFocus (WindowEvent e) {
            //unhighlight();
            highlight();
          }
          public void windowLostFocus (WindowEvent e) {
            unhighlight();
          }
        });
      
      win.addWindowListener(new WindowAdapter() {
          public void windowClosing(WindowEvent e) {
            closeWindows();
          }
        });
      
      // set location once at initial click
      if (location != null) {
        win.setLocation(location);
      }
    }
    //fill window with data
    boolean agint_called = n.idv.agint_called;
    text = "";
    text += n.getText() + "\n";
    text += NEW_LINE_TEXT + "\n";
    Iterator eIt = n.iterator();
    boolean omitted = false;
    // check for omissions
    while (eIt.hasNext()) {
      Edge edge = (Edge)eIt.next();
      IDNode other = (IDNode)(edge.getEndNode()).getFront();
      //            if (other.getFormula().getInteresting() < ((IDGraph)panel.getGraph()).idv.threshold) {
      if (!other.isInteresting()) {
        omitted = true;
      }
    }         
    // append up parents
    axioms.clear();
    if (omitted && agint_called) {
      //      double value = n.idv.slider.getValue();
      double value = n.idv.getSynopsisSlider().getValue();
      System.out.println("value: " + value);
      //Set<IDNode> parents = ((IDNode)n).generateParentInfo(value);
      Set<IDNode> parents;
      SubTree subtree = new SubTree();
      ((IDNode)n).generateSubTreeInfo(value, subtree);
      System.out.println("# parents: " + subtree.parents.size());
      for (IDNode parent : subtree.parents) {
        text += parent.getText() + "\n";
        axioms.add(parent);
      }
    } else {
      for (IDNode up : ((IDNode)n).upParents) {
        text += up.getText() + "\n";
        axioms.add(up);
      }            
    }
    text += NEW_LINE_TEXT + "\n";
    if (omitted) {
      text += "%Some inferences omitted\n";
      text += NEW_LINE_TEXT + "\n";
    }
    text += n.getText() + "\n";
    
    textArea.setText(text);
    textArea.setCaretPosition(0);
    
    //show window
    if (showWindow) {
      win.show();
    }
  } // else
        
  public void checkLastCurrent () {
    //System.out.println(" checklastcurrent");
    if (n.idv.CURRENT_NODE == null) {
      //System.out.println(" last current is null, nothing to unhiglight");
      return;
    }

    if (n.idv.CURRENT_NODE != n) {
      // inside a different node that previous, unhighlight that one
      Node old = n.idv.CURRENT_NODE;
      //System.out.println("unhiglight: " + old.getName());
      old.getPolygon().unhighlight();
    } else {
      //System.out.println(" last current same as current, nothing to unhighlight");
    }
  }
  public void highlight () {
    checkLastCurrent();
    n.idv.CURRENT_NODE = (IDNode)n;
    Graphics2D g = (Graphics2D)panel.getGraphics();
    //System.out.println("node: " + n.getName() + " highlight");
    isActive = true;
    g.transform(panel.computeAffineTransform());
    setIntensityFront(g);
    setIntensityBack(g);
    n.paint(g);
    if (textArea != null)
      textArea.setBackground(new Color(122,238,255));
  }
  public void unhighlight () {
    //    n.idv.CURRENT_NODE = null;
    Graphics2D g = (Graphics2D)panel.getGraphics();
    //System.out.println("node: " + n.getName() + " unhighlight");
    isActive = false;
    g.transform(panel.computeAffineTransform());
    clearIntensityFront(g);
    clearIntensityBack(g);
    n.paint(g);               
    if (win!= null && textArea != null)
      textArea.setBackground(Color.white);
  }

  /**
   * Set the fill color for the polygon when it is at rest.
   */
  public void setFillColor(Color c) { fillColor = c; }
  
  /**
   * Get the fill color for the polygon when it is at rest.
   */
  public Color getFillColor() { return fillColor; }
  
  /**
   * Set the outline color for the polygon when it is at rest.
   */
  public void setLineColor(Color c) { lineColor = c; }
  
  /**
   * Get the outline color for the polygon when it is at rest.
   */
  public Color getLineColor() { return lineColor; }
  
  /**
   * Set the fill color for the polygon when it is activated.
   */
  public void setFillColorActive(Color c) { fillColorInside = c; }
  
  /**
   * Get the fill color for the polygon when it is activated.
   */
  public Color getFillColorActive() { return fillColorInside; }
  
  /**
   * Set the outline color for the polygon when it is activated.
   */
  public void setLineColorActive(Color c) { lineColorInside = c; }
  
  /**
   * Get the outline color for the polygon when it is activated.
   */
  public Color getLineColorActive() { return lineColorInside; }  
  
  public void actionPerformed(ActionEvent e) {
    String actionMessage = e.getActionCommand();
    if (actionMessage == ATPToolBar.GO_CMD) {
      // GO
      //unhighlight();
      verify((String)ATPComboBox.getSelectedItem(), gdv);
      highlight();
    } else if (actionMessage == ATPToolBar.GDV_CMD) {
      gdv = !gdv;
    } else if (actionMessage == ATPToolBar.ERASE_CMD) {
      ((IDNode)n).resetVStatus();
      panel.repaint();
    } else if (actionMessage == ATPToolBar.TREE_CMD) {
      if (derivation.equals("")) {
        return;
      }
      System.out.println("derivation---start");
      System.out.println(derivation);
      System.out.println("derivation---end");
      // recurse new IDV window
      IDV childWindow = new IDV(n.idv.applet, n.idv.ATPList, false);
      childWindow.loadString(derivation);
      childWindow.setVisible(true);
      childWindow.show();
      cIDV.add(childWindow);
    }
  }

  public void verify (String ATPSelected, boolean gdv) {
    // get formula list
    System.out.println("# of axioms: " + axioms.size());
    String subtree = "";
    /*
    if (gdv) {
      for (IDNode axiom: axioms) {
        subtree = subtree + axiom.getFormula().getFormulaDump() + "\n";
      }
      subtree = subtree + ((IDNode)n).getFormula().getFormulaDump() + "\n";      
    } else {
      for (IDNode axiom: axioms) {
        subtree = subtree + axiom.getFormula().getMutatedFormulaDump("","fof", "axiom",null) + "\n";
      }
      subtree = subtree + ((IDNode)n).getFormula().getMutatedFormulaDump("","fof", "conjecture",null) + "\n";
    }      
    */

//----FIX THE FOF HERE
    for (IDNode axiom: axioms) {
      subtree = subtree + axiom.getFormula().getMutatedFormulaDump("","fof", "axiom",null) + "\n";
    }
    subtree = subtree + ((IDNode)n).getFormula().getMutatedFormulaDump("","fof", "conjecture",null) + "\n";
    
    // multi post
    Hashtable<String,Object> URLParameters = new Hashtable<String,Object>();
    URLParameters.put("NoHTML",new Integer(1));
    URLParameters.put("QuietFlag","-q4");
    URLParameters.put("X2TPTP","-S");
    
    if (gdv) {
      URLParameters.put("System___GDV---0.0","GDV---0.0");
      URLParameters.put("Command___GDV---0.0","GDV -e -p " + ATPSelected + " %s");
    } else {
      URLParameters.put("System___System",ATPSelected);
    }

    URLParameters.put("TimeLimit___TimeLimit",new Integer(TimeField.getText()));
    URLParameters.put("ProblemSource","FORMULAE");
    URLParameters.put("FORMULAEProblem",subtree);
    URLParameters.put("SubmitButton","RunSelectedSystems");
    
    //URLParameters.put("SubmitButton","ListSystems");
    //URLParameters.put("ListStatus","SoTPTP");
    
    System.out.println("Call system: " + ATPSelected);
    textArea.setText(text);
    textArea.append("\n \n \n");
    
    textArea.append("%info passed to ATP system:\n");
    textArea.append(subtree);
    textArea.append("\n \n \n");

    System.out.println("subtree: " + subtree);
    
    // clear derivation results
    derivation = "";
    boolean flag = false;
    try {
      BufferedReader response = new BufferedReader(new InputStreamReader(ClientHttpRequest.post(new URL(IDV.SystemOnTPTPFormReplyURL),URLParameters)));
      String responseLine;
      while ((responseLine = response.readLine()) != null) {
        System.out.println(responseLine);
        textArea.append(responseLine + "\n");
        derivation += responseLine + "\n";
        if ((gdv && responseLine.contains("SZS status Verified")) ||
            (!gdv &&responseLine.contains("Result     : Theorem"))) {
          flag = true;
        }
      }
      response.close();
    } catch (Exception ioe) {
      System.err.println("Exception: " + ioe.getMessage());
    }
    textArea.setCaretPosition(0);
    Graphics2D g = (Graphics2D)panel.getGraphics();
    g.transform(panel.computeAffineTransform());
    ((IDNode)n).setVStatus(flag);
    ((IDNode)n).paint(g);
  }

  public void closeWindows () {
    // dispose of all children windows, then dispose this one
    if (cIDV.size() > 0)
      System.out.println("disposing child IDVs, size: " + cIDV.size());
    for (IDV childWindow : cIDV) {
      System.out.println("  DISPOSED!!");
      childWindow.closeWindows();
      childWindow.dispose();      
    }
    if (win != null) {
      win.setVisible(false);
      //      win.dispose();
      //      win = null;
      //      textArea = null;
    }
    cIDV.clear();
    derivation = "";    
  }
}

