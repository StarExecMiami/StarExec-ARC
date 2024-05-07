//*****************************************************************************
//*****************************************************************************
/* 
   Steven Trac
   IDV - Interactive Derivation Viewer
*/
//*****************************************************************************
/*****
 * Build on to GraphMan by Dr. Christian Duncan (Thanks!)
 ****/
//*****************************************************************************
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.SpringLayout;
import java.awt.*;
import java.awt.event.*;
import java.awt.geom.*;
import java.awt.image.*;
import java.util.*;
import java.io.*;
import java.net.*;
import netscape.javascript.*;
import ClientHttpRequest.*;

//*****************************************************************************

public class IDV extends JFrame
  implements ActionListener, ChangeListener, Runnable {
   public static final String
     SystemOnTPTPFormReplyURL = "http://www.cs.miami.edu/~tptp/cgi-bin/SystemOnTPTPFormReply",
       IMG_PATH = "images/",
       DEFAULT_FILE_PATH = "/home/duncan/projects/GD2004/GraphMan",
       TK_TITLE = "Tool Kit",                   // Toolkit info, actions, commands, etc...
       
   // File Load and Save Commands
     TK_UNDO_IMG = "undo.png",
     TK_UNDO_TEXT = "Undo to previous threshold set", 
     TK_UNDO_ALT = "Undo",
     UNDO_CMD = "Undo",
     TK_REDO_IMG = "redo.png",
     TK_REDO_TEXT = "Redo to previous threshold set", 
     TK_REDO_ALT = "Redo",
     REDO_CMD = "Redo",
     TK_REDRAW_IMG = "redraw.png",
     TK_REDRAW_TEXT = "Redraw with newly set threshold",
     TK_REDRAW_ALT = "Redraw",
     REDRAW_CMD = "Redraw",
     TK_FILESAVE_IMG = "filesave.png",
     TK_FILESAVE_TEXT = "Save the Graph",
     TK_FILESAVE_ALT = "Save",
     FILESAVE_CMD = "Save",
     TK_FILELOAD_IMG = "fileopen.png",
     TK_FILELOAD_TEXT = "Load the Graph",
     TK_FILELOAD_ALT = "Load",
     FILELOAD_CMD = "Load",
       
   // Zoom In and Out, etc...
     TK_ZOOMIN_IMG = "viewmag+.png",
     TK_ZOOMIN_TEXT = "Zoom In",
     TK_ZOOMIN_ALT = "ZoomIn",
     ZOOMIN_CMD = "Zoom In",
     TK_ZOOMOUT_IMG = "viewmag-.png",
     TK_ZOOMOUT_TEXT = "Zoom Out",
     TK_ZOOMOUT_ALT = "ZoomOut",
     ZOOMOUT_CMD = "Zoom Out",

     TK_FIT_TO_WINDOW_H_IMG = "viewmagH.png",
     TK_FIT_TO_WINDOW_H_TEXT = "Fit graph to Window Height",
     TK_FIT_TO_WINDOW_H_ALT = "Fit to Height",
     FIT_TO_WINDOW_H_CMD = "Zoom To Fit Height",
     
     TK_FIT_TO_WINDOW_W_IMG = "viewmagW.png",
     TK_FIT_TO_WINDOW_W_TEXT = "Fit graph to Window Width",
     TK_FIT_TO_WINDOW_W_ALT = "Fit to Width",
     FIT_TO_WINDOW_W_CMD = "Zoom To Fit Width",
     
     TK_CROSSING_TITLE = "Crossing Kit",
     TK_CROSSTRACKER_IMG = null,
     TK_CROSSTRACKER_TEXT = "Track Crossings (Real-Time, disable for speed)",
     TK_CROSSTRACKER_ALT = "Crossings",
     CROSSTRACKER_CMD = "CrossTracker",
     
     TK_SPRING_EMBEDDER_IMG = "springembedder.png",
     TK_SPRING_EMBEDDER_TEXT = "Open Spring Embedder Window",
     TK_SPRING_EMBEDDER_ALT = "Spring Embedder",
     SPRING_EMBEDDER_CMD = "SpEmbedder",
     
     TK_ABOUT_IMG = "TheU.png",
     TK_ABOUT_TEXT = "Click for About / Help Information",
     TK_ABOUT_ALT = "About",
     ABOUT_CMD = "About",
     
     TK_GO_IMG = "TheU.png",
     TK_GO_TEXT = "GO",
     TK_GO_ALT = "GO",
     GO_CMD = "GO",
     
     TK_TSTP_IMG = "superman_logo.jpg",
     TK_TSTP_TEXT = "System on TSTP",
     TK_TSTP_ALT = "TSTP",
     TSTP_CMD = "TSTP",
     
     TK_SYNOPSIS_TRUE_IMG = "bulb-on1.png",
     TK_SYNOPSIS_FALSE_IMG = "bulb-off1.png",
     TK_SYNOPSIS_TEXT = "Toggle on to show IDV Synopsis",
     TK_SYNOPSIS_ALT = "SYNOPSIS",
     SYNOPSIS_CMD = "SYNOPSIS",

     TK_PROTECTION_TRUE_IMG = "protection-on.png",
     TK_PROTECTION_FALSE_IMG = "protection-off.png",
     TK_PROTECTION_TEXT = "Toggle off to off protection of un-interesting axioms",
     TK_PROTECTION_ALT = "PROTECTION",
     PROTECTION_CMD = "PROTECTION",

     TK_VERIFIED_TRUE_IMG = "check-on1.png",
     TK_VERIFIED_FALSE_IMG = "check-off1.png",
     TK_VERIFIED_TEXT = "Toggle on to show verified formulae",
     TK_VERIFIED_ALT = "VERIFIED",
     VERIFIED_CMD = "VERIFIED",

     TK_REDLINE_TRUE_IMG = "redline-on4.png",
     TK_REDLINE_FALSE_IMG = "redline-off3.png",
     TK_REDLINE_TEXT = "Toggle on to show some above line",
     TK_REDLINE_ALT = "REDLINE",
     REDLINE_CMD = "REDLINE",

     TK_GE_TRUE_IMG = "good.png",
     TK_GE_FALSE_IMG = "evil.png",
     TK_GE_TEXT = "Toggle on to show only axioms and lemmas",
     TK_GE_ALT = "GOOD",
     GE_CMD = "GOOD",

     TK_VERIFY_TRUE_IMG = "flag-on.png",
     TK_VERIFY_FALSE_IMG = "flag-off.png",
     TK_VERIFY_TEXT = "Verify all formulae",
     TK_VERIFY_ALT = "VERIFY",
     VERIFY_CMD = "VERIFY",

     TK_SYNOPSIS_SLIDER_ALT  = "SynopsisSlider",
     TK_SYNOPSIS_SLIDER_TEXT = "Interesting Values",
     TK_REDLINE_SLIDER_ALT   = "RedlineSlider",
     TK_REDLINE_SLIDER_TEXT  = "Show Formulae below certain Threshold",

     
   // And quit
     QUIT_CMD = "Quit";

  public static int
    SLIDER_MIN   = 0,
    SLIDER_MAX   = 100;
  public static double
    SLIDER_ROUND = .005;

  /****** GUI Material ******/
  GraphPanel     gridScreen;           // The graph panel
  IDGraph        graph;                // graph stored in graph panel
  SpringEmbedder springEmbedderWindow; // Spring embed window
  JScrollPane    scroller;             // scroller for main graph
  //  JScrollPane    scrollField;          // scroller for text field
  JTextArea      textField;            // formula info goes here
  IDVApplet      applet;               // IDVApplet can call this
  JFrame         aboutWindow;          // About window
  //  Image          image = null;
  //JCheckBox      icheckbox;          // interesting check box
  //JCheckBox      vcheckbox;          // verified check box
  //JCheckBox      rcheckbox;          // verified check box
  //JCheckBox      gcheckbox;          // verified check box
  private JToggleButton  synopsisTButton;   // interesting togglebutton
  private JToggleButton  protectionTButton; // protection togglebutton
  private JToggleButton  verifiedTButton;   // togglebutton
  private JToggleButton  verifyTButton;    // togglebutton
  private JToggleButton  redlineTButton;    // togglebutton
  private JToggleButton  goodevilTButton;   // evil togglebutton
  private GMSlider       synopsisSlider;    // interesting value
  private GMSlider       redlineSlider;     // interesting value
  Stack          <DrawInfo>undoInfo;
  Stack          <DrawInfo>redoInfo; 
  protected int v_count = -1; // keep track of which was last verified
  private boolean gdv = false;

  // atp window
  private JComboBox ATPComboBox;
  private JTextField TimeField;
  private JFrame ATPWindow = null;

  private class DrawInfo {
    double synopsisThreshold;
    boolean synopsis;
    double redlineThreshold;
    boolean redline;
    DrawInfo (double d, boolean b, double h, boolean r) {
      this.synopsisThreshold = d;
      this.synopsis = b;
      this.redlineThreshold = h;
      this.redline = r;
    }
  }

  Vector<String> ATPList;
  Vector<IDV> cIDV;
 //URLReader      URLs;

  boolean agint_called = false;
  boolean agint_done = false;
  boolean addFinish = false;
  //  private boolean synopsis = false;
  //  boolean verified = false;
  //  boolean goodevil = false;
  //  boolean redline = false;
  boolean size_set = false;
  private double synopsisThreshold = 0;
  double redlineThreshold = 0;
  int s_height = 5;

  public IDNode CURRENT_NODE = null;
  //  boolean optimize = true;
  boolean optimize = false;
    
   // Main entry point for the program
   public static void main (String args[]) {
     IDV win = new IDV(null, null, true);

      win.setVisible(true);
      if (args.length > 0) {
	  // First argument is name of graph file
	  //    Maybe more features added later
System.out.println("About to load " + args[0]);
	  win.loadFile(new File(args[0]));
      }
   }

   /***************************
      * The constructor.
      * Main job: Coordinate the initial layout
      *           by creating buttons, menubars, etc.
      ***************************/
  public IDV (final IDVApplet applet, Vector atplist, final boolean top) {
    super();    // Not really necessary (default action)
    //setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
    this.applet = applet;
    setTitle ("IDV - Interactive Derivation Viewer, created by Steven C. Trac");
    this.setSize(800,600);
    setExtendedState(this.getExtendedState() | this.MAXIMIZED_BOTH);
    createATPList(atplist);
    makePanel();
    undoInfo = new Stack();
    redoInfo = new Stack();    
    cIDV = new Vector();
    // Create a simple window listener for exiting
    this.addWindowListener(new WindowAdapter() {
        public void windowClosing(WindowEvent e) {
          System.out.println("Exiting");
//DEBUG System.out.println("dispose!!");
          closeWindows();          
          if (applet == null && top) {
            System.exit(0);
          }
        }
      });
  }

  public void closeWindows () {
    if (graph != null)
      graph.closeWindows();
    // dispose of all children windows, then dispose this one
    if (cIDV.size() > 0)
      System.out.println("disposing child IDVs, size: " + cIDV.size());
    for (IDV childWindow : cIDV) {
//DEBUG System.out.println("  DISPOSED!!");
      childWindow.closeWindows();
      childWindow.dispose();      
    }
    cIDV.clear();
  }

  public void createChildWindow (IDNode n, boolean entire, boolean up) {
    IDV childWindow = new IDV(applet, ATPList, false);
    childWindow.graph = new IDGraph(n, childWindow, entire, up);
    childWindow.loadGraph(childWindow.graph);
    childWindow.setVisible(true);
    // set synopsis check box
    if (synopsisTButton.isSelected()) {
      //      childWindow.icheckbox.doClick();
      childWindow.synopsisTButton.setSelected(true);
    }
    // set slider value
    childWindow.synopsisSlider.slider.setValue((int)(synopsisSlider.getValue() * SLIDER_MAX));
    childWindow.show();
    cIDV.add(childWindow);          
  }
  
  private void createATPWindow () {
    // add atp list
    if (ATPWindow == null) {
      ATPWindow = new JFrame("Verification System Menu");
      ATPWindow.setSize(400,100);
      Container pane = ATPWindow.getContentPane();
      ATPToolBar atptoolbar = ATPToolBar.createATPToolBar(ATPList, ATPComboBox, TimeField, this);
      ATPComboBox = atptoolbar.ATPComboBox;
      TimeField = atptoolbar.TimeField;
      gdv = atptoolbar.GDVTButton.isSelected();
      pane.add(atptoolbar.ToolBar);
    }
    ATPWindow.show();
  }
  private Thread verifyThread;
  private void verifyALL () { 
    if (!verifyTButton.isSelected()) {
      return;
    }
    if (verifyThread == null) {
      verifyThread = new Thread(this);
      verifyThread.start();
    }
  }
  public void run () {
    graph.verifyALL((String)ATPComboBox.getSelectedItem(), gdv);
    verifyThread = null;
  }

  /********************************
   * Makes the Main Panel
   *    Creates the main items for the panel
   ********************************/
  void makePanel() {
    JToggleButton tbutton;
    JButton button;
    Dimension d;
    JLabel sliderText;

    Container pane = this.getContentPane();
    pane.setLayout(new BorderLayout());  // Main Panel has BorderLayout
    
    // Create the main Grid Screen
    gridScreen = new GraphPanel(this);
    scroller = new JScrollPane(gridScreen);
    
      // Create the SpringEmbedder Window (linked to gridScreen)
    springEmbedderWindow = new SpringEmbedder(gridScreen);
    
    createAboutWindow();
    
    //---- FIRST TOOL BAR
    JToolBar tools = new JToolBar(TK_TITLE);
    
    // Add Zoom In Button
    button = GraphManTools.
      makeActionButton(TK_ZOOMIN_IMG, TK_ZOOMIN_TEXT,
                       TK_ZOOMIN_ALT, ZOOMIN_CMD, this);
    tools.add(button);

    // Add Zoom Out Button
    button = GraphManTools.
      makeActionButton(TK_ZOOMOUT_IMG, TK_ZOOMOUT_TEXT,
                       TK_ZOOMOUT_ALT, ZOOMOUT_CMD, this);
    tools.add(button);

    // Add Fit To Window Height Button
    button = GraphManTools.
      makeActionButton(TK_FIT_TO_WINDOW_H_IMG, TK_FIT_TO_WINDOW_H_TEXT,
                       TK_FIT_TO_WINDOW_H_ALT, FIT_TO_WINDOW_H_CMD, this);
    tools.add(button);
    
    // Add Fit To Window Width Button
    button = GraphManTools.
      makeActionButton(TK_FIT_TO_WINDOW_W_IMG, TK_FIT_TO_WINDOW_W_TEXT,
                       TK_FIT_TO_WINDOW_W_ALT, FIT_TO_WINDOW_W_CMD, this);
    tools.add(button);
    
    tools.addSeparator();
    tools.addSeparator();
    tools.addSeparator();

    // Add verified togglebutton
    verifiedTButton = GraphManTools.
      makeToggleButton(TK_VERIFIED_FALSE_IMG, TK_VERIFIED_TRUE_IMG, TK_VERIFIED_TEXT,
                       TK_VERIFIED_ALT, VERIFIED_CMD, false, this);
    tools.add(verifiedTButton);

    // Add Verify Button
    verifyTButton = GraphManTools.
      makeToggleButton(TK_VERIFY_FALSE_IMG, TK_VERIFY_TRUE_IMG, TK_VERIFY_TEXT,
                       TK_VERIFY_ALT, VERIFY_CMD, false, this);
    tools.add(verifyTButton);   

    tools.addSeparator();
    tools.addSeparator();

    // Add GOOD EVIL togglebutton
    goodevilTButton = GraphManTools.
      makeToggleButton(TK_GE_FALSE_IMG, TK_GE_TRUE_IMG, TK_GE_TEXT,
                       TK_GE_ALT, GE_CMD, false, this);
    tools.add(goodevilTButton);

    tools.addSeparator();
    tools.addSeparator();
    
    // Add TSTP button
    button = GraphManTools.
      makeActionButton(TK_TSTP_IMG, TK_TSTP_TEXT,
                       TK_TSTP_ALT, TSTP_CMD,
                       this);
    tools.add(button);
    tools.addSeparator();
    
    // Add About Button
    button = GraphManTools.
      makeActionButton(TK_ABOUT_IMG, TK_ABOUT_TEXT,
                       TK_ABOUT_ALT, ABOUT_CMD,
                       this);
    tools.addSeparator();
    tools.add(button);

    //---- SECOND TOOL BAR
    JToolBar tools2 = new JToolBar(TK_TITLE);

    // Add RedLine Toggle Button
    redlineTButton = GraphManTools.
      makeToggleButton(TK_REDLINE_FALSE_IMG, TK_REDLINE_TRUE_IMG, TK_REDLINE_TEXT,
                       TK_REDLINE_ALT, REDLINE_CMD, true, this);
    tools2.add(redlineTButton);

    //Add Slider bar for the interesting value
    sliderText = new JLabel("Interestingness: ");
    GMSlider.Function scaleFunc = new GMSlider.Function() {
        double f(int min, int max, int val) {
          return (double) val / (double) SpringEmbedder.BASE;
        }
      };
    int t = (int)(redlineThreshold * SLIDER_MAX);
    redlineSlider = GraphManTools.makeGMSlider(TK_REDLINE_SLIDER_ALT, TK_REDLINE_SLIDER_TEXT, this, scaleFunc, SLIDER_MIN, SLIDER_MAX, t);    
    tools2.add(redlineSlider);

    // Add toggle button for interesting resizing
    synopsisTButton = GraphManTools.
      makeToggleButton(TK_SYNOPSIS_FALSE_IMG, TK_SYNOPSIS_TRUE_IMG, TK_SYNOPSIS_TEXT,
                       TK_SYNOPSIS_ALT, SYNOPSIS_CMD, false, this);
    tools2.add(synopsisTButton);

    //Add Slider bar for the interesting value
    sliderText = new JLabel("Interestingness: ");
    t = (int)(synopsisThreshold * SLIDER_MAX);
    synopsisSlider = GraphManTools.makeGMSlider(TK_SYNOPSIS_SLIDER_ALT, TK_SYNOPSIS_SLIDER_TEXT, this, scaleFunc, SLIDER_MIN, SLIDER_MAX, t);    
    tools2.add(synopsisSlider);
 
    // Add toggle button for axiom protection
    protectionTButton = GraphManTools.
      makeToggleButton(TK_PROTECTION_FALSE_IMG, TK_PROTECTION_TRUE_IMG, TK_PROTECTION_TEXT,
                       TK_PROTECTION_ALT, PROTECTION_CMD, true, this);
    tools2.add(protectionTButton);
    
    // Add Redraw Button 
    button = GraphManTools.makeActionButton(TK_REDRAW_IMG, TK_REDRAW_TEXT,
                                            TK_REDRAW_ALT, REDRAW_CMD, this);
    tools2.add(button);
    
    // Add UNDO Button
    button = GraphManTools.makeActionButton(TK_UNDO_IMG, TK_UNDO_TEXT,
                                            TK_UNDO_ALT, UNDO_CMD, this);
    tools2.add(button);
    // Add UNDO Button
    button = GraphManTools.makeActionButton(TK_REDO_IMG, TK_REDO_TEXT,
                                            TK_REDO_ALT, REDO_CMD, this);
    tools2.add(button);
    tools2.addSeparator();   

    // add both tool bars together
    JPanel top = new JPanel();
    top.setLayout(new BoxLayout(top, BoxLayout.LINE_AXIS));
    JPanel bot = new JPanel();
    bot.setLayout(new BoxLayout(bot, BoxLayout.LINE_AXIS));
    top.add(tools);
    top.add(Box.createHorizontalGlue());
    bot.add(tools2);
    bot.add(Box.createHorizontalGlue());
    JPanel panel = new JPanel();
    panel.setLayout(new BoxLayout(panel, BoxLayout.PAGE_AXIS));
    tools.setFloatable(false);
    tools2.setFloatable(false);    
    panel.add(top);
    panel.add(bot);
    pane.add(panel, BorderLayout.NORTH);

    // set bottom text field
    textField = new JTextArea("");
    textField.setEditable(false);
    textField.setFont(new Font("Courier", Font.PLAIN, 12));
    JScrollPane scrollField = new JScrollPane(textField, JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED, JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
    textField.setText("Highlight a formula to display.\n");
    textField.append("If nothing is displayed, click Zoom to Fit Button on Toolbar.\n");

    // add split pane of graph and bottom text field to panel
    JSplitPane splitPane = new JSplitPane(JSplitPane.VERTICAL_SPLIT, scroller, scrollField);
    scroller.setMinimumSize(new Dimension(600, 50));
    scrollField.setMinimumSize(new Dimension(600, 30));
    d = scrollField.getPreferredSize();
    Dimension newD = new Dimension(d.width, 85);
    scrollField.setPreferredSize(newD);
    scrollField.invalidate();
    splitPane.setDividerSize(3);
    splitPane.setResizeWeight(1.0);
    splitPane.invalidate();
    pane.add(splitPane, BorderLayout.CENTER);

  }

  public GMSlider getSynopsisSlider () { return synopsisSlider; }
  public boolean isRedline () { return redlineTButton.isSelected(); }
  public boolean isVerified () { return verifiedTButton.isSelected(); }
  public boolean isVerify () { return verifyTButton.isSelected(); }
  public boolean isSynopsis () { return synopsisTButton.isSelected(); }
  public boolean isProtected () { return protectionTButton.isSelected(); }
  public boolean isGood () { return goodevilTButton.isSelected(); }
  public boolean isGDV () { return gdv; }
  public double getSynopsisThreshold () { 
    if (isSynopsis()) 
      return synopsisSlider.getValue();
    return synopsisThreshold; 
  }
  public int getRedlineHeight (boolean draw) {
    /*
      start from height threshold set, from that MIN, to MAX, that is the new range
      from current_threshold to 1.0, but graph is visually from CMIN to CMAX.
    */

    int start = -100;
    //int start = 0; 
    int size = (graph.getRankSize() * IDGraph.YSPLIT) - start;
    int offset = (int)(redlineThreshold * size);
    //    int offset = 0;
    int height;
    if (isRedline()) {
      height = (int)(redlineSlider.getValue() * size) + start;
      /*
      System.out.println("slider: " + redlineSlider.getValue());
      System.out.println("size: " + size);
      System.out.println("start: " + start);
      System.out.println("offset: " + offset);
      System.out.println("red line on height");
      */
    } else {
      height = offset + start;
    }    
    if (draw)
      height -= offset;
    return height;
  }

  void callATP (String ATP, String Formulae) {

  }

  void createATPList (Vector atplist) {
    if (atplist != null) {
      ATPList = atplist;
      return;
    }
    ATPList = new Vector();
    Hashtable<String,Object> URLParameters = new Hashtable<String,Object>();

    URLParameters.put("NoHTML",new Integer(1));
    URLParameters.put("QuietFlag","-q2");
    URLParameters.put("SubmitButton","ListSystems");
    URLParameters.put("ListStatus","SoTPTP");

    try {
      BufferedReader response = new BufferedReader(new InputStreamReader(ClientHttpRequest.post(new URL(SystemOnTPTPFormReplyURL),URLParameters)));
      String responseLine;
      while ((responseLine = response.readLine()) != null) {
//DEBUG System.out.println(responseLine);
        ATPList.add(responseLine);
      }
      response.close();
      System.out.println("Got available ATP systems");
    } catch (Exception ioe) {
      System.err.println("Exception: " + ioe.getMessage());
    }
    
  }

  void createAboutWindow () {
    // Create about window button
    if (aboutWindow == null) {
      aboutWindow = IDVHelp.createAboutWindow(applet);
    } else {
      aboutWindow.show();
    }
  }

  private void tryAddInteresting () {
    if (!agint_called) {
      agint_called = true;
      graph.updateInteresting(0, false);
      // add interestingness
      SwingUtilities.invokeLater(
                                 new Runnable() {
                                   public void run() {      
                                     addInteresting();
                                     addFinish = true;
                                     graph.updateInteresting(synopsisSlider.getValue(), false);
                                     graph.setPolygons();
                                     gridScreen.repaint();
                                     agint_done = true;
                                   }
                                 }
                                 );
    } 
  }

  /********************************
   * stateChanged
   *     A state changed (of a Spinner)
   ********************************/
  public void stateChanged(ChangeEvent e) {
    //    else if (e.getSource() instanceof GMSlider) {
    if (e.getSource() instanceof GMSlider) {
      GMSlider source = (GMSlider)e.getSource();
      if (source.getValueIsAdjusting() && optimize) {
        return;
      }
      if (source.getGMName() == TK_SYNOPSIS_SLIDER_ALT) {
        System.out.println("synopsis slider");
        if (addFinish) {
          double value = source.getValue();
          if (value >= synopsisThreshold) {        
            v_count = -1;
            synopsisSlider.valueLabel.setForeground(Color.black);
            synopsisSlider.slider.setBackground(null);
            if (synopsisTButton.isSelected())
              graph.updateInteresting(value, false);
            graph.setLeaves();
            gridScreen.repaint();
          } else {
            synopsisSlider.valueLabel.setForeground(Color.red);
            synopsisSlider.slider.setBackground(Color.red);
          }
        }
      } else if (source.getGMName() == TK_REDLINE_SLIDER_ALT) {
        v_count = -1;
        double value = synopsisSlider.getValue();
        graph.updateInteresting(value, false);
        System.out.println("red slider");
        graph.setLeaves();
        gridScreen.repaint();
      } else {
        System.out.println("can not recognize: " + source.getGMName());
      }
    }
    else {
      System.err.println("Error: Did you forget to catch a spinner?");
    }
  }

  /********************************
   * actionPerformed
   *     An Action was selected
   ********************************/
  public void actionPerformed(ActionEvent e) {
    //    System.out.println("action performed");
    String actionMessage = e.getActionCommand();

    //---- FIRST TOOL BAR
    if (actionMessage == ZOOMIN_CMD) {
      zoomIn();
    } else if (actionMessage == ZOOMOUT_CMD) {
      zoomOut();
    } else if (actionMessage == FIT_TO_WINDOW_H_CMD) {
      fitToWindowHeight();
    } else if (actionMessage == FIT_TO_WINDOW_W_CMD) {
      fitToWindowWidth();
    } else if (actionMessage == VERIFIED_CMD) {
      System.out.println("Verified toggle");
      unhighlight();
      gridScreen.repaint();
    } else if (actionMessage == VERIFY_CMD) {
      System.out.println("Verify pop up");
      if (v_count == -1) {        
      //        graph.resetVerified();
      //        gridScreen.repaint();
        v_count = 0;        
        createATPWindow();
      } else {
        v_count = -1;
      }
    } else if (actionMessage == ATPToolBar.GO_CMD) {
      if (ATPWindow != null) {
        ATPWindow.hide();
        verifyALL();
      }
    } else if (actionMessage == ATPToolBar.ERASE_CMD) {
      graph.resetVerified();
      gridScreen.repaint();
    } else if (actionMessage == ATPToolBar.GDV_CMD) {
      gdv = !gdv;
    } else if (actionMessage == GE_CMD) {
      if (goodevilTButton.isSelected()) {
        System.out.println("good");
      } else {
        System.out.println("evil");
      }
      gridScreen.repaint();
    } else if (actionMessage == TSTP_CMD) {
      callSoTSTP();
    } else if (actionMessage == ABOUT_CMD) {
      aboutWindow.setVisible(true);      
    } 
    //---- SECOND TOOL BAR
    else if (actionMessage == REDLINE_CMD) {
      if (redlineTButton.isSelected()) {
        System.out.println("red line on");
      } else {
        System.out.println("red line off");
      }
      double value = synopsisSlider.getValue();
      graph.updateInteresting(value, false);
      gridScreen.repaint();
    } else if (actionMessage == PROTECTION_CMD) {
      //      graph.
      graph.setLeaves();
      gridScreen.repaint();
    } else if (actionMessage == SYNOPSIS_CMD) {
      if (synopsisTButton.isSelected()) {
        if (agint_called) {
          this.textField.setText("Now displaying derivation synopsis WITH resized interesting nodes.");      
        }
        tryAddInteresting();
      } else {
        textField.setText("Now displaying derivation synopsis WITHOUT resized interesting nodes.");              
      }
      if (agint_done) {
        graph.updateInteresting(synopsisSlider.getValue(), false);
        graph.setPolygons();
        unhighlight();
        gridScreen.repaint();
      }
    } else if (actionMessage.equals(QUIT_CMD)) {
      if (JOptionPane.showConfirmDialog(null,"Are you sure ?")==JOptionPane.YES_OPTION) {
        System.out.println("Disposed");
        setVisible(false);
        dispose();
      } 
    } else if (actionMessage == UNDO_CMD) {
      // if not empty
      //   1) undo to last synopsisThreshold, redlineThreshold
      //   2) pop undo stack
      //   3) push to redo stack
      //   4) reset
      resetSynopsisSlider();
      if (!undoInfo.empty()) {
        // fix stacks
        System.out.println("Pushing synopsisThreshold: " + synopsisThreshold + " and synopsis: " + synopsisTButton.isSelected() + " and height: " + redlineThreshold + ", and reline: " + redlineTButton.isSelected() + " to REDO stack");
        DrawInfo pair = undoInfo.pop();        
        redoInfo.push(new DrawInfo(synopsisThreshold, 
                                   synopsisTButton.isSelected(), 
                                   redlineThreshold, 
                                   redlineTButton.isSelected()));
        redraw(pair);
        // display
        textField.setText("Undo to last synopsisThreshold that was set: " + synopsisThreshold + "\n");        
        //        System.out.println("Popping synopsisThreshold: " + synopsisThreshold + " and synopsis: " + pair.synopsis + " to stack");
      System.out.println("Popped synopsisThreshold: " + synopsisThreshold + " and synopsis: " + synopsisTButton.isSelected() + " and height: " + redlineThreshold + ", and reline: " + redlineTButton.isSelected() + " from UNDO stack");
      }
    } else if (actionMessage == REDO_CMD) {
      // if not empty
      //   1) redo to last synopsisThreshold, redlineThreshold
      //   2) pop redo stack
      //   3) push to undo stack
      //   4) reset
      resetSynopsisSlider();
      if (!redoInfo.empty()) {
        // fix stacks
        System.out.println("Pushing synopsisThreshold: " + synopsisThreshold + " and synopsis: " + synopsisTButton.isSelected() + " and height: " + redlineThreshold + ", and reline: " + redlineTButton.isSelected() + " to UNDO stack");
        DrawInfo pair = redoInfo.pop();
        undoInfo.push(new DrawInfo(synopsisThreshold, 
                                   synopsisTButton.isSelected(),
                                   redlineThreshold,
                                   redlineTButton.isSelected()));
        redraw(pair);
        // display
        textField.setText("Redo to last synopsisThreshold that was set: " + synopsisThreshold + "\n");        
        //        System.out.println("Popping synopsisThreshold: " + synopsisThreshold + " and synopsis: " + pair.synopsis+ " to stack");

      System.out.println("Setting synopsisThreshold: " + synopsisThreshold + " and synopsis: " + synopsisTButton.isSelected() + " and height: " + redlineThreshold + ", and reline: " + redlineTButton.isSelected() + " from REDO stack");
      }
    } else if (actionMessage.equals(REDRAW_CMD)) {
      if (!isSynopsis() && !isRedline()) {
        // simulate clear of screen (remove highlighting)
        CURRENT_NODE = null;
        graph.invalidate();
        gridScreen.repaint();        
        return;
      }
      // fix stacks
      redoInfo.clear();
      DrawInfo pair = new DrawInfo(synopsisThreshold, 
                                   synopsisTButton.isSelected(), 
                                   redlineThreshold, 
                                   redlineTButton.isSelected());      
      undoInfo.push(pair);
      // set to new synopsisThreshold
      synopsisThreshold = synopsisSlider.getValue();
      // set to new redlineThreshold
      redlineThreshold = redlineSlider.getValue();
      updateGraph();
      // paint, display
      gridScreen.repaint();
      textField.setText("Redrawing to synopsisThreshold: " + synopsisSlider.getValue() + "\n");        
      System.out.println("Pushing synopsisThreshold: " + synopsisThreshold + " and synopsis: " + synopsisTButton.isSelected() + " and height: " + redlineThreshold + ", and reline: " + redlineTButton.isSelected() + " to undo stack");
    }
   System.out.println("done with action performer");
  }
  private void redraw (DrawInfo pair) {
    // set to new synopsisThreshold
    synopsisThreshold = pair.synopsisThreshold;
    synopsisSlider.slider.setValue((int)((synopsisThreshold + SLIDER_ROUND) * SLIDER_MAX));
    resetSynopsisSlider();
    // update to new red line threshold
    redlineThreshold = pair.redlineThreshold;        
    redlineSlider.slider.setValue((int)((redlineThreshold + SLIDER_ROUND) * SLIDER_MAX));
    // update buttons
    redlineTButton.setSelected(pair.redline);
    synopsisTButton.setSelected(pair.synopsis);
    // update graph
    updateGraph();
    // paint
    gridScreen.repaint();               
  }
  private void resetSynopsisSlider () {
    // clear synopsis slider
    synopsisSlider.valueLabel.setForeground(Color.black);
    synopsisSlider.slider.setBackground(null);
  }
  private void updateGraph () {
    v_count = -1; // reset verified count
    if (isRedline()) {
      System.out.println("red line is selected");
    }
    graph.updateInteresting(synopsisThreshold, false);
    Vector r[] = graph.setRanks();
    /*
    int i = 0;
    while (r[i++].isEmpty() && i < graph.getRankSize()) {}
    redlineThreshold = (i-1) * IDGraph.YSPLIT;            
    */
    graph.setChains();
    graph.invalidate();
    gridScreen.revalidate();
    gridScreen.calculateGraphBounds();
  }
  private void unhighlight () {
    if (CURRENT_NODE != null) 
      CURRENT_NODE.getPolygon().unhighlight();
  }


    /**
       A rudimentary way to make a little beep.
    **/
    void beep() { 
	System.out.print("\07"); System.out.flush();
    }

   /**
      GUI to load a graph from file
   **/
   void loadFile() {
      JFileChooser open = new JFileChooser(DEFAULT_FILE_PATH);  // Use current directory location
      if (open.showOpenDialog(this) != JFileChooser.APPROVE_OPTION)
         return;  // Cancelled or Error occurred

      loadFile(open.getSelectedFile());
   }

   void loadFile(File f) {
      // Try to open the selected file
      FileReader file;
      try {
	  file = new FileReader(f);
      } catch (Exception err) {
	  JOptionPane.showMessageDialog (this,
					 "Unable to Open specified File. " +
					 "Make sure that the file exists\n" +
					 "and that you have enough permissions to " +
					 "read the file.",
					 "File Load Error",
					 JOptionPane.ERROR_MESSAGE);
	  return;
      }

      try {
        graph = TPTPReader.readTPTP(file, null, this);
        gridScreen.setGraph(graph);        
        embed(null);
        if (graph.getFormulaSize() > 256) {
          optimize = true;
        }         
        if (optimize) {
          redlineSlider.slider.setValue((int)(20));
        }
        invalidate();
      } catch (Exception e) {
        JOptionPane.showMessageDialog (this,
                                       "Unable to Read specified File. Reason given:\n" +
                                       e.getMessage(),
                                       "File Load Error",
                                       JOptionPane.ERROR_MESSAGE);
      }
      // Close it no matter what...
      try { file.close(); } catch (Exception e) { }
   }

  private void embed (BufferedReader coord) {
    Vector<IDNode>[] rank = graph.getRank();
    if (coord == null) {
      int n = 10;
      for (int i = 0; i < n; i++) {
        if ((n - i) < n/2) {
          springEmbedderWindow.adjustX();
        } else {
          if (!springEmbedderWindow.embed(i, rank, graph, false))
            return;
        }
        //System.out.println("Embedding");
        if (applet != null) {
          applet.showStatus("Embedding Phase: (" + i + " / " + n + " iterations)");
        }
        System.out.println("Embedding Phase: (" + i + " / " + n + " iterations)");
      }
    }
    updateWindow();
  }
  
  private void updateWindow () {
    // Update the boundary
    gridScreen.calculateGraphBounds();

    if (applet != null) {
      applet.setVisible(false);
    } 
    if (graph == null) {
      System.out.println("graph is null");
    }
    this.setVisible(true);
    graph.invalidate();
    graph.setChains();
    graph.invalidate();
    graph.pinNodes();
    gridScreen.setDrawMe(true);
    fitToWindow();
    System.out.println("Finish updating window");
  }  

  void loadReader (BufferedReader tptpReader, BufferedReader coordReader) {
    try {
      System.out.println("Start to readTPTP");
      graph = TPTPReader.readTPTP(tptpReader, coordReader, this);
      System.out.println("Completed readTPTP");
      gridScreen.setGraph(graph);
      embed(coordReader);      
      if (graph.getFormulaSize() > 256) {
        optimize = true;
      } 
      if (optimize) {
        redlineSlider.slider.setValue((int)(20));
      }
      invalidate();
    } catch (Exception e) {
      JOptionPane.showMessageDialog (this,
                                     "Unable to Process Input String. Reason given:\n" +
                                     e.toString(),
                                     "Param Parsing Error",
                                     JOptionPane.ERROR_MESSAGE);
      killApplet();
    }    
  }
  void loadString(String in) {
    BufferedReader reader = new BufferedReader(new StringReader(in));
    loadReader(reader, null);
  }

  void loadGraph (IDGraph graph) {
    gridScreen.setGraph(graph);
    invalidate();
    updateWindow();
    show();
    this.setVisible(true);
  }

  void setSize() {
    if (!size_set) {
      System.out.println("Setting size");
//DEBUG System.out.println("g.width = " + gridScreen.getWidth());
      setSize(gridScreen.getWidth() + 15,getSize().height);
      show();
      size_set = true;
    }
  }

  void killApplet () {
    // kill applet
    if (applet != null) {
      applet.closePage();
    }
  }

   void zoomIn() { gridScreen.zoomIn(); }
   void zoomOut() { gridScreen.zoomOut(); }
  //   void zoom100() { gridScreen.setZoomLevel(1.0); }

  void fitToWindow () { gridScreen.fitToWindow(); }
  void fitToWindowHeight () { gridScreen.fitToWindowHeight(); }
  void fitToWindowWidth () { gridScreen.fitToWindowWidth(); }

  /*
  // for painting
  void saveImage () { image = gridScreen.createImage(gridScreen.getWidth(), gridScreen.getHeight());  }
  void drawImage (Graphics2D g) {
    if (image != null) {
      g.drawImage(image,0,0,null);
    }
  }
  */
  public void paint (Graphics2D g) {
    // draw red line
    if (redlineTButton.isSelected()) {
      Rectangle rect = gridScreen.graphBnds;      
      //      System.out.println("rect: h: " + rect.height + ", w: " + rect.width + ", x: " + rect.x + ", y: " + rect.y);
      //      int y =(int)(redlineSlider.getValue() * rect.height) + rect.y;
      boolean draw = true;
      int y = getRedlineHeight(draw);
      int x1 = rect.x;
      int x2 = rect.x + rect.width;      
      g.setColor(Color.red);
      g.drawLine(x1, y, x2, y);
    } else {
      
    }
  }

  private void addInteresting () {
    try {
    graph.addInteresting();
    } catch (Exception e) {
      JOptionPane.showMessageDialog (this,
                                     "Unable to add interesting values correctly\n" +
                                     e.getMessage(),
                                     "Param Parsing Error when adding Interestingness",
                                     JOptionPane.ERROR_MESSAGE);
    }
  }

  public void callSoTSTP () {
    System.out.println("Call System On TSTP");
    if (applet == null) {
      System.out.println("applet null");
      return;
    }
    try {
      String tstp_dump = graph.getTSTPDump();
      // old method
      //applet.getAppletContext().showDocument(new URL("javascript:openSoTSTP(\"" + tstp_dump + "\")"));
      // new method
      JSObject win = JSObject.getWindow(applet);
      Object[] args = new Object[1];
      args[0] = tstp_dump;
      win.call("openSoTSTP",args);
    } catch (Exception e) {
      System.out.println("trouble opening page: " + e);
    }
  }

}

