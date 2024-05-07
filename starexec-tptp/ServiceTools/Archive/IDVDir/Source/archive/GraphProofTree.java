//*****************************************************************************
//*****************************************************************************
/* 
   Steven Trac
   Graph Proof Tree
*/
//*****************************************************************************
/*****
 * Graph Proof Tree Main
 * Build on to GraphMan by Dr. Christian Duncan
 ****/
//*****************************************************************************
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.event.*;
import java.awt.image.*;
import java.net.URL;
import java.io.*;
//*****************************************************************************
public class GraphProofTree extends JFrame implements ActionListener {
  public static final String
    IMG_PATH = "images/",
    DEFAULT_FILE_PATH = "/home/duncan/projects/GD2004/GraphMan",
    TK_TITLE = "Tool Kit",    // Toolkit info, actions, commands, etc...
    
    // File Load and Save Commands
    TK_UNDO_IMG = "undo.png",
    TK_UNDO_TEXT = "Undo last Spring Embedder Action",
    TK_UNDO_ALT = "Undo",
    UNDO_CMD = "Undo",
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
    TK_ZOOM100_IMG = "Zoom100.jpg",
    TK_ZOOM100_TEXT = "100% viewing",
    TK_ZOOM100_ALT = "1:1",
    ZOOM100_CMD = "No Zoom (1:1)",
    TK_FIT_TO_WINDOW_IMG = "viewmag.png",
    TK_FIT_TO_WINDOW_TEXT = "Fit graph to Window",
    TK_FIT_TO_WINDOW_ALT = "Fit",
    FIT_TO_WINDOW_CMD = "Zoom To Fit",
    
    TK_CROSSING_TITLE = "Crossing Kit",
    TK_CROSSTRACKER_IMG = null,
    TK_CROSSTRACKER_TEXT = "Track Crossings (Real-Time, disable for speed)",
    TK_CROSSTRACKER_ALT = "Crossings",
    CROSSTRACKER_CMD = "CrossTracker",
	
    TK_SPRING_EMBEDDER_IMG = "springembedder.png",
    TK_SPRING_EMBEDDER_TEXT = "Open Spring Embedder Window",
    TK_SPRING_EMBEDDER_ALT = "Spring Embedder",
    SPRING_EMBEDDER_CMD = "SpEmbedder",
    
    // And quit
    QUIT_CMD = "Quit";
  
  //GUI Material
  GraphPanel gridScreen;
  JScrollPane scroller;
  SpringEmbedder springEmbedderWindow;
  
  //Main entry point for the program
  public static void main (String args[]) {
    GraphProofTree win = new GraphProofTree();
    //win.setVisible(true);
    if (args.length > 0) {
      //first argument is name of graph file
      win.loadFile(new File(args[0]));
    }
    return;
  }
  
  /***************************
   * The constructor.
   * Main job: Coordinate the initial layout
   *           by creating buttons, menubars, etc.
   ***************************/
  public GraphProofTree () {
    super(); //not really necessary (default action)
    
    setTitle("Graph Proof Tree");
    
    Dimension size = getToolkit().getScreenSize();
    this.setSize(2 * size.width / 3, 2 * size.height / 3);
    
    makePanel();
    makeMenuBar();
    
    //creat a simple window listener for exiting
    this.addWindowListener (new WindowAdapter() {
        public void windowClosing (WindowEvent e) {
          System.exit(0);
        }
      });
  }
  
  /********************************
   * Makes the MenuBar
   *    Creates the following items/subitems
   *       File --> Load Save Quit
   *       ... just a sample right now ...
   ********************************/
  private void makeMenuBar() {
    JMenuItem m;
    JMenuBar mBar = new JMenuBar();
    setJMenuBar(mBar);
    
    JMenu fileMenu = new JMenu("File");
    m = new JMenuItem(FILELOAD_CMD);
    m.addActionListener(this);
    fileMenu.add(m);
    
    m = new JMenuItem(FILESAVE_CMD);
    m.addActionListener(this);
    fileMenu.add(m);
    
    m = new JMenuItem(QUIT_CMD);
    m.addActionListener(this);
    fileMenu.add(m);
    
    mBar.add(fileMenu);
    
    JMenu adderMenu = new JMenu("Edit");
    m = new JMenuItem(UNDO_CMD);
    m.addActionListener(this);
    adderMenu.add(m);
    mBar.add(adderMenu);
    
    JMenu viewMenu = new JMenu("View");
    m = new JMenuItem(ZOOMIN_CMD);
    m.addActionListener(this);
    viewMenu.add(m);
    m = new JMenuItem(ZOOMOUT_CMD);
    m.addActionListener(this);
    viewMenu.add(m);
    m = new JMenuItem(FIT_TO_WINDOW_CMD);
    m.addActionListener(this);
    viewMenu.add(m);
    m = new JMenuItem(ZOOM100_CMD);
    m.addActionListener(this);
    viewMenu.add(m);
    mBar.add(viewMenu);
  }
  
  /********************************
   * Makes the Main Panel
   *    Creates the main items for the panel
   ********************************/
  void makePanel() {
    // JFrame's have a Container (pane)
    // to where all other Components are added.
    JButton button;
    Container pane = this.getContentPane();
    pane.setLayout(new BorderLayout());  // Main Panel has BorderLayout
    
    // Create the main Grid Screen
    gridScreen = new GraphPanel();
    scroller = new JScrollPane(gridScreen);
    
    // Create the SpringEmbedder Window (linked to gridScreen)
    springEmbedderWindow = new SpringEmbedder(gridScreen);
    
    // Set up the toolbar
    JToolBar tools = new JToolBar(TK_TITLE);
    // tools.setRollover(true);  // Maybe make border highlighted by mouse...
    
    // Add Undo Button
    button = GraphManTools.makeActionButton(TK_UNDO_IMG, TK_UNDO_TEXT,
                                            TK_UNDO_ALT, UNDO_CMD, this);
    tools.add(button);
    tools.add(new JToolBar.Separator());
    
    // Add Load Button
    button = GraphManTools.makeActionButton(TK_FILELOAD_IMG, 
                                            TK_FILELOAD_TEXT,
                                            TK_FILELOAD_ALT, 
                                            FILELOAD_CMD, this);
    tools.add(button);

    // Add Save Button
    button = GraphManTools.
      makeActionButton(TK_FILESAVE_IMG, TK_FILESAVE_TEXT,
                       TK_FILESAVE_ALT, FILESAVE_CMD, this);
    tools.add(button);
    
    tools.add(new JToolBar.Separator());
    
    // Add Zoom In Button
    button = GraphManTools.
      makeActionButton(TK_ZOOMIN_IMG, TK_ZOOMIN_TEXT,  
                       TK_ZOOMIN_ALT, ZOOMIN_CMD, this);
    tools.add(button);
    
    // Add Fit To Window Button
    button = GraphManTools.
      makeActionButton(TK_FIT_TO_WINDOW_IMG, TK_FIT_TO_WINDOW_TEXT,
                       TK_FIT_TO_WINDOW_ALT, FIT_TO_WINDOW_CMD, this);
    tools.add(button);
    
    // Add Zoom Out Button
    button = GraphManTools.
      makeActionButton(TK_ZOOMOUT_IMG, TK_ZOOMOUT_TEXT,
                       TK_ZOOMOUT_ALT, ZOOMOUT_CMD, this);
    tools.add(button);
    
    // Add Zoom 100% Button
    button = GraphManTools.
      makeActionButton(TK_ZOOM100_IMG, TK_ZOOM100_TEXT,
                       TK_ZOOM100_ALT, ZOOM100_CMD, this);
    tools.add(button);
    tools.add(new JToolBar.Separator());
    
    // Add Crossing Tacker Button (move to separate Tool Bar)
    JToggleButton ctButton = GraphManTools.
      makeToggleButton(TK_CROSSTRACKER_IMG,
                       TK_CROSSTRACKER_TEXT,
                       TK_CROSSTRACKER_ALT, CROSSTRACKER_CMD,
                       true, this);
    tools.add(ctButton);
    gridScreen.setCrossTracker(ctButton);
    tools.add(new JToolBar.Separator());
    
    // Add Spring Embedder Button
    button = GraphManTools.
      makeActionButton(TK_SPRING_EMBEDDER_IMG, TK_SPRING_EMBEDDER_TEXT,
                       TK_SPRING_EMBEDDER_ALT, SPRING_EMBEDDER_CMD,
                       this);
    tools.add(button);
    
    pane.add(tools, BorderLayout.PAGE_START);
    pane.add(scroller, BorderLayout.CENTER);
  }
  
  /********************************
   * actionPerformed
   *     An Action was selected.   Deal with it!
   ********************************/
  public void actionPerformed(ActionEvent e) {
    String actionMessage = e.getActionCommand();
    
    // Use == instead of .equals for speed (are SAME string constants!)
    if (actionMessage == FILELOAD_CMD) {
      // Load (from Menu Bar)
      loadFile();
    } else if (actionMessage == FILESAVE_CMD) {
      // Save (from Menu Bar)
      saveFile();
    } else if (actionMessage == ZOOMIN_CMD) {
      zoomIn();
    } else if (actionMessage == ZOOMOUT_CMD) {
      zoomOut();
    } else if (actionMessage == ZOOM100_CMD) {
      zoom100();
    } else if (actionMessage == FIT_TO_WINDOW_CMD) {
      fitToWindow();
    } else if (actionMessage == CROSSTRACKER_CMD) {
      // Just force update of total number of crossings (each time)
      gridScreen.updateCrossTrackerTotal(true);
    } else if (actionMessage == SPRING_EMBEDDER_CMD) {
      springEmbedderWindow.setVisible(true);
    } else if (actionMessage == UNDO_CMD) {
      if (!gridScreen.undoEmpty()) {
        gridScreen.undo();
      } else {
        beep();
      }
    } else if (actionMessage.equals(QUIT_CMD)) {
      // Quit (from Menu Bar)
      System.exit(0);
    }
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
      //Graph gr = GraphReader.readGD4(file);
      Graph gr = ProofReader.readProof(file);
      gridScreen.setGraph(gr);
      gridScreen.clearUndoInfo();  // New file!
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
    System.out.println("Finish load file");
  }
  
  /**
   * GUI to save a graph to a file
   **/
  void saveFile() {
    JFileChooser save = new JFileChooser(DEFAULT_FILE_PATH);  // Use current directory location
    if (save.showSaveDialog(this) != JFileChooser.APPROVE_OPTION)
      return;  // Cancelled or Error occurred
    
    // Try to open the selected file
    FileWriter file;
    try {
      file = new FileWriter(save.getSelectedFile());
    } catch (Exception err) {
      JOptionPane.
        showMessageDialog(this,
                          "Unable to open specified file for saving. " +
                          "Make sure that you have enough permissions " +
                          "to write the file.",
                          "File Save Error",
                          JOptionPane.ERROR_MESSAGE);
      return;
    }
    
    try {
      GraphWriter.writeGD4(file, gridScreen.getGraph());
    } catch (Exception e) {
      JOptionPane.
        showMessageDialog(this,
                          "Unable to Save specified File. Reason given:\n" +
                          e.getMessage(),
                          "File Save Error",
                          JOptionPane.ERROR_MESSAGE);
    }
    
    // Close it no matter what...
    try { file.close(); } catch (Exception e) { }
  }
  
  /**
   * zoomIn()
   * Zoom the graph in a click
   **/
  void zoomIn() {
    gridScreen.zoomIn();
  }
  
  /**
   * zoomOut()
   * Zoom the graph out a click
   **/
  void zoomOut() {
    gridScreen.zoomOut();
  }
  
  /**
   * zoom100()
   * Set zoom level to 100%
   **/
  void zoom100() {
    gridScreen.setZoomLevel(1.0);
  }
  
  /**
   * fitToWindow()
   *      Compute best zoom level for fitting to window
   **/
  void fitToWindow() {
    gridScreen.fitToWindow();
  }
}

//*****************************************************************************
//*****************************************************************************
